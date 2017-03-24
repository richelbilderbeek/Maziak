#include "maziakterminal.h"

#include <cassert>
#include <iostream>
#include <sstream>
#include "textcanvas.h"
#include "maziakgame.h"
#include "maziaksprites.h"

ribi::maziak::Terminal::Terminal(const Game& game)
  : m_do_show_solution_cnt{0}, m_game{game},
    m_prisoner_frame{0}
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
  }
}

std::set<ribi::maziak::Key> ribi::maziak::Terminal::RequestKeys()
{
  while (1)
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
    std::set<Key> keys;
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
    return keys;
  }

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

  TextCanvas canvas(11,11);
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
        //Draw the floor tile
        const char pixmap_floor {
          to_char(
            GetSpriteFloor(
              t.GetGame().GetMaze(),
              xVector,
              yVector,
              t.GetGame().GetDoShowSolution(),
              t.GetGame().GetSolution()
            )
          )
        };
        canvas.PutChar(x,y,pixmap_floor);
        //Draw what's moving or standing on the floor
        const Sprite sprite_above_floor {
          GetSpriteAboveFloor(xVector,yVector,t.GetGame().GetMaze())
        };
        if (sprite_above_floor != Sprite::transparent)
        {
          const char pixmap_above_floor {
            to_char(sprite_above_floor)
          };
          canvas.PutChar(x,y,pixmap_above_floor);
        }
      }
    }
  }

  //Draw player
  {
    const char player {
      to_char(
        GetSpritePlayer(
          t.GetGame().GetPlayerDirection(),
          t.GetGame().GetPlayerMove(),
          t.GetGame().GetPlayerHasSword(),
          t.GetGame().GetPlayerFightingFrame()
        )
      )
    };
    assert(player);
    canvas.PutChar(view_width/2,view_height / 2,player);
  }
  os << canvas;
  return os;
}
