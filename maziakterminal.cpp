#include "maziakterminal.h"

#include <cassert>
#include <iostream>
#include <sstream>
#include "maziakgame.h"

ribi::maziak::Terminal::Terminal(const Game& game)
  : m_do_show_solution_cnt{0}, m_game{game},
    m_prisoner_frame{0},
    m_t{0}
{

}

ribi::maziak::Terminal ribi::maziak::CreateTestTerminal1()
{
  return Terminal{CreateTestGame1()};
}

void ribi::maziak::Terminal::Execute()
{
  while (1)
  {
    std::cout << *this << '\n';
    std::cout << '\n';
    m_game.PressKeys(RequestKeys());
    m_game.RespondToCurrentSquare();
    Tick();
  }
}

std::set<ribi::maziak::Key> ribi::maziak::Terminal::RequestKeys()
{
  std::set<Key> keys;
  while (keys.empty())
  {
    std::string s;
    std::getline(std::cin,s);

    if (s == "")
    {
      std::cout
        << "Please enter one of the following characters:" << '\n'
        << "a: move right" << '\n'
        << "s: move down" << '\n'
        << "d: move right" << '\n'
        << "w: move up" << '\n'
        << "q: quit" << '\n'
        << "other: wait" << '\n'
        << std::endl;
      continue;
    }
    for (const auto c: s)
    {

      switch (c)
      {
        case 'w': keys.insert(Key::up); break;
        case 'd': keys.insert(Key::right); break;
        case 's': keys.insert(Key::down); break;
        case 'a': keys.insert(Key::left); break;
        case 'q': keys.insert(Key::quit); break;
        default: keys.insert(Key::none); break;
      }
    }
  }
  return keys;
}

void ribi::maziak::Terminal::RespondToCurrentSquare()
{
  const bool show_solution_before = m_game.GetDoShowSolution();
  m_game.RespondToCurrentSquare();
  const bool show_solution_after = m_game.GetDoShowSolution();
  if (!show_solution_before && show_solution_after)
  {
    m_do_show_solution_cnt = 20;
  }
}

void ribi::maziak::Terminal::Tick()
{
  ++m_t;
  if (m_t % 4 == 1) this->TogglePrisoners();
  if (m_t % 4 == 2) this->TogglePrisoners();
  --m_do_show_solution_cnt;
  m_game.SetDoShowSolution(m_do_show_solution_cnt >= 0);
}

std::string ribi::maziak::to_str(const Terminal& t)
{
  std::stringstream s;
  s << t;
  return s.str();
}

std::ostream& ribi::maziak::operator<<(std::ostream& os, const Terminal& t)
{
  if (t.GetGame().GetState() == GameState::has_won)
  {
    os << "You won the game" << '\n';
    return os;
  }
  else if (t.GetGame().GetState() == GameState::game_over)
  {
    os << "GAME OVER" << '\n';
    return os;
  }

  const int view_height = 11;
  const int view_width = 11;
  //Draw maze
  {
    for (int y=0; y!=view_height; ++y)
    {
      for (int x=0; x!=view_width; ++x)
      {
        //xVector and yVector are the indices in the non-visual maze 2D std::vector
        const int xVector = t.GetGame().GetX() - (view_width  / 2) + x;
        const int yVector = t.GetGame().GetY() - (view_height / 2) + y;
        os << to_char(t.GetGame().GetSprites(
          xVector, yVector, t.GetPrisonerFrame(), t.GetPrisonerFrame())
        );
      }
      os << '\n';
    }
  }
  return os;
}
