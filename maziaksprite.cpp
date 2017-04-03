#include "maziaksprite.h"

#include <cassert>
#include <iostream>

char ribi::maziak::to_char(const ribi::maziak::Sprite sprite) noexcept //!OCLINT cannot lower cyclomatic complexity without impairing readability
{
  switch (sprite)
  {
    case Sprite::empty: return ' ';
    case Sprite::wall: return 'X';
    case Sprite::path: return '.';
    case Sprite::transparent: return ' ';
    case Sprite::player_look_down: return 'v';
    case Sprite::player_look_down_sword: return 'w';
    case Sprite::player_look_left: return '<';
    case Sprite::player_look_left_sword: return 'E';
    case Sprite::player_look_right: return '>';
    case Sprite::player_look_right_sword: return '3';
    case Sprite::player_look_up: return 'A';
    case Sprite::player_look_up_sword: return 'M';
    case Sprite::player_walk_left1: return '\\';
    case Sprite::player_walk_left2: return '/';
    case Sprite::player_walk_left_sword1: return '=';
    case Sprite::player_walk_left_sword2: return 'E';
    case Sprite::player_walk_right1: return '\\';
    case Sprite::player_walk_right2: return '/';
    case Sprite::player_walk_right_sword1: return '=';
    case Sprite::player_walk_right_sword2: return '3';
    case Sprite::player_walk_down1: return '\\';
    case Sprite::player_walk_down2: return '/';
    case Sprite::player_walk_down_sword1: return 'W';
    case Sprite::player_walk_down_sword2: return 'w';
    case Sprite::player_walk_up1: return '/';
    case Sprite::player_walk_up2: return '\\';
    case Sprite::player_walk_up_sword1: return 'm';
    case Sprite::player_walk_up_sword2: return 'M';
    case Sprite::player_won1: return '!';
    case Sprite::player_won2: return '!';
    case Sprite::fight_sword1: return '#';
    case Sprite::fight_no_sword1: return '+';
    case Sprite::fight2: return '*';
    case Sprite::fight3: return '%';
    case Sprite::fight4: return '@';
    case Sprite::fight_won1: return 'W';
    case Sprite::fight_won2: return 'w';
    case Sprite::fight_lost1: return 'Z';
    case Sprite::fight_lost2: return 'z';
    case Sprite::enemy1: return 'Z';
    case Sprite::enemy2: return 'z';
    case Sprite::prisoner1: return ':';
    case Sprite::prisoner2: return ';';
    case Sprite::sword: return '+';
    case Sprite::exit: return '!';
  }
  assert(!"Should not get here"); //!OCLINT accepted idiom
  return '\0';
}

std::string ribi::maziak::to_str(const Sprite sprite) noexcept //!OCLINT cannot lower cyclomatic complexity without impairing readability
{
  switch (sprite)
  {
    case Sprite::empty: return "empty";
    case Sprite::wall: return "wall";
    case Sprite::path: return "path";
    case Sprite::transparent: return "transparent";
    case Sprite::player_look_down: return "player_look_down";
    case Sprite::player_look_down_sword: return "player_look_down_sword";
    case Sprite::player_look_left: return "player_look_left";
    case Sprite::player_look_left_sword: return "player_look_left_sword";
    case Sprite::player_look_right: return "player_look_right";
    case Sprite::player_look_right_sword: return "player_look_right_sword";
    case Sprite::player_look_up: return "player_look_up";
    case Sprite::player_look_up_sword: return "player_look_up_sword";
    case Sprite::player_walk_left1: return "player_walk_left1";
    case Sprite::player_walk_left2: return "player_walk_left2";
    case Sprite::player_walk_left_sword1: return "player_walk_left_sword1";
    case Sprite::player_walk_left_sword2: return "player_walk_left_sword2";
    case Sprite::player_walk_right1: return "player_walk_right1";
    case Sprite::player_walk_right2: return "player_walk_right2";
    case Sprite::player_walk_right_sword1: return "player_walk_right_sword1";
    case Sprite::player_walk_right_sword2: return "player_walk_right_sword2";
    case Sprite::player_walk_down1: return "player_walk_down1";
    case Sprite::player_walk_down2: return "player_walk_down2";
    case Sprite::player_walk_down_sword1: return "player_walk_down_sword1";
    case Sprite::player_walk_down_sword2: return "player_walk_down_sword2";
    case Sprite::player_walk_up1: return "player_walk_up1";
    case Sprite::player_walk_up2: return "player_walk_up2";
    case Sprite::player_walk_up_sword1: return "player_walk_up_sword1";
    case Sprite::player_walk_up_sword2: return "player_walk_up_sword2";
    case Sprite::player_won1: return "player_won1";
    case Sprite::player_won2: return "player_won2";
    case Sprite::fight_sword1: return "fight_sword1";
    case Sprite::fight_no_sword1: return "fight_no_sword1";
    case Sprite::fight2: return "fight2";
    case Sprite::fight3: return "fight3";
    case Sprite::fight4: return "fight4";
    case Sprite::fight_won1: return "fight_won1";
    case Sprite::fight_won2: return "fight_won2";
    case Sprite::fight_lost1: return "fight_lost1";
    case Sprite::fight_lost2: return "fight_lost2";
    case Sprite::enemy1: return "enemy1";
    case Sprite::enemy2: return "enemy2";
    case Sprite::prisoner1: return "prisoner1";
    case Sprite::prisoner2: return "prisoner2";
    case Sprite::sword: return "sword";
    case Sprite::exit: return "exit";
  }
  assert(!"Should not get here"); //!OCLINT accepted idiom
  return "";
}

std::iostream& ribi::maziak::operator<<(std::iostream& os, const Sprite& s) noexcept
{
  os << to_char(s);
  return os;
}
