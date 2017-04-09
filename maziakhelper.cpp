#include "maziakhelper.h"

std::string ribi::maziak::CamelCasify(const std::string& s) noexcept
{
  std::string t;
  const auto sz = s.size();
  for(auto i = 0u; i!=sz;++i)
  {
    const char c = s[i];
    if (s[i] == '_')
    {
      assert(i + 1 < s.size());
      ++i;
      const char d = std::toupper(s[i]);
      t += d;
    }
    else
    {
      t += c;
    }
  }
  return t;
}

