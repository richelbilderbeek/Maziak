#ifndef MAZIAKMENUDIALOG_H
#define MAZIAKMENUDIALOG_H

#include "menudialog.h"

namespace ribi {
namespace maziak {

struct MenuDialog final : public ::ribi::MenuDialog
{
  MenuDialog();
  About GetAbout() const noexcept override;
  Help GetHelp() const noexcept override;
  std::string GetVersion() const noexcept override;
  std::vector<std::string> GetVersionHistory() const noexcept override;

  private:
  int ExecuteSpecific(const std::vector<std::string>& argv) noexcept override;
};

} //~namespace maziak
} //~namespace ribi

#endif // MAZIAKMENUDIALOG_H
