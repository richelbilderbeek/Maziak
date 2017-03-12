#ifndef MAZIAKPLAYERMOVE_H
#define MAZIAKPLAYERMOVE_H

#include <iosfwd>
#include <string>

namespace ribi {
namespace maziak {

enum class PlayerMove {
  none,
  left1,
  left2,
  right1,
  right2,
  up1,
  up2,
  down1,
  down2
};

std::string to_str(const PlayerMove m) noexcept;
std::ostream& operator<<(std::ostream& os, const PlayerMove m) noexcept;

} //~namespace maziak
} //~namespace ribi

#endif // MAZIAKPLAYERMOVE_H
