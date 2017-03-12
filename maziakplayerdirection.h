#ifndef MAZIAKPLAYERDIRECTION_H
#define MAZIAKPLAYERDIRECTION_H

#include <iosfwd>
#include <string>

namespace ribi {
namespace maziak {

enum class PlayerDirection { pdLeft, pdRight, pdUp, pdDown };

std::string to_str(const PlayerDirection d) noexcept;

std::ostream& operator<<(std::ostream& os, const PlayerDirection d) noexcept;

} //~namespace maziak
} //~namespace ribi

#endif // MAZIAKPLAYERDIRECTION_H
