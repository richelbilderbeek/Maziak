#include "maziakplayermove.h"

#include <cassert>
#include <iostream>

std::string ribi::maziak::to_str(const PlayerMove m) noexcept
{
  switch (m)
  {
    case PlayerMove::none: return "none";
    case PlayerMove::left1: return "left1";
    case PlayerMove::left2: return "left2";
    case PlayerMove::right1: return "right1";
    case PlayerMove::right2: return "right2";
    case PlayerMove::up1: return "up1";
    case PlayerMove::up2: return "up2";
    case PlayerMove::down1: return "down1";
    case PlayerMove::down2: return "down2";
  }
  assert(!"Should not get here"); //!OCLINT accepted idiom
  return "";
}

std::ostream& ribi::maziak::operator<<(std::ostream& os, const PlayerMove m) noexcept
{
  os << to_str(m);
  return os;
}
