#ifndef MAZIAKSPRITE_H
#define MAZIAKSPRITE_H

#include <iosfwd>
#include <string>
#include <initializer_list>

namespace ribi {
namespace maziak {

enum class Sprite
{
  //Floor
  empty, // A road
  wall,
  path, // The golden road to the exit
  transparent,
  //Player sprites
  player_look_down,
  player_look_down_sword,
  player_look_left,
  player_look_left_sword,
  player_look_right,
  player_look_right_sword,
  player_look_up,
  player_look_up_sword,
  player_walk_left1,
  player_walk_left2,
  player_walk_left_sword1,
  player_walk_left_sword2,
  player_walk_right1,
  player_walk_right2,
  player_walk_right_sword1,
  player_walk_right_sword2,
  player_walk_down1,
  player_walk_down2,
  player_walk_down_sword1,
  player_walk_down_sword2,
  player_walk_up1,
  player_walk_up2,
  player_walk_up_sword1,
  player_walk_up_sword2,
  player_won1,
  player_won2,
  //Fighting sprites
  fight_sword1,
  fight_no_sword1,
  fight2,
  fight3,
  fight4,
  fight_won1,
  fight_won2,
  fight_lost1,
  fight_lost2,
  //Non-player sprites
  enemy1,
  enemy2,
  prisoner1,
  prisoner2,
  sword,
  exit
};

constexpr std::initializer_list<Sprite> get_all_sprites() noexcept
{
  return
  {
    Sprite::empty,
    Sprite::wall,
    Sprite::path,
    Sprite::transparent,
    Sprite::player_look_down,
    Sprite::player_look_down_sword,
    Sprite::player_look_left,
    Sprite::player_look_left_sword,
    Sprite::player_look_right,
    Sprite::player_look_right_sword,
    Sprite::player_look_up,
    Sprite::player_look_up_sword,
    Sprite::player_walk_left1,
    Sprite::player_walk_left2,
    Sprite::player_walk_left_sword1,
    Sprite::player_walk_left_sword2,
    Sprite::player_walk_right1,
    Sprite::player_walk_right2,
    Sprite::player_walk_right_sword1,
    Sprite::player_walk_right_sword2,
    Sprite::player_walk_down1,
    Sprite::player_walk_down2,
    Sprite::player_walk_down_sword1,
    Sprite::player_walk_down_sword2,
    Sprite::player_walk_up1,
    Sprite::player_walk_up2,
    Sprite::player_walk_up_sword1,
    Sprite::player_walk_up_sword2,
    Sprite::player_won1,
    Sprite::player_won2,
    Sprite::fight_sword1,
    Sprite::fight_no_sword1,
    Sprite::fight2,
    Sprite::fight3,
    Sprite::fight4,
    Sprite::fight_won1,
    Sprite::fight_won2,
    Sprite::fight_lost1,
    Sprite::fight_lost2,
    Sprite::enemy1,
    Sprite::enemy2,
    Sprite::prisoner1,
    Sprite::prisoner2,
    Sprite::sword,
    Sprite::exit
  };
}

///ASCII art
char to_char(const Sprite s) noexcept;

///To full word
std::string to_str(const Sprite) noexcept;

std::ostream& operator<<(std::ostream& os, const Sprite& s) noexcept;

} //~namespace maziak
} //~namespace ribi

#endif // MAZIAKSPRITE_H
