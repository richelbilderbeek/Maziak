#include "maziaksprites.h"

#include <cassert>

std::vector<ribi::maziak::Sprite> ribi::maziak::GetAllSprites() noexcept
{
  const std::vector<Sprite> v {
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
  assert(static_cast<int>(v.size()) == static_cast<int>(Sprite::n_sprites)
    && "All Sprite values (except Sprite::n_sprites) must be in");

  return v;
}


