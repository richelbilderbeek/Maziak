#include "maziakmenudialog.h"

#include <cassert>
#include <iostream>
#include <sstream>
#include <stdexcept>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "maziakmaindialog.h"
#include "maziakterminal.h"

 

#pragma GCC diagnostic pop

ribi::maziak::MenuDialog::MenuDialog()
{

}

int ribi::maziak::MenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  const int argc = static_cast<int>(argv.size());
  if (argc != 1)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }

  boost::shared_ptr<MainDialog> dialog {
    new MainDialog( 7 + (4 * 2) )
  };
  Terminal terminal;
  dialog->SetDisplay(&terminal);
  dialog->Execute();
  return 0;

}

ribi::About ribi::maziak::MenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "Maziak",
    "a simple maze game",
    "the 28th of January 2014",
    "2007-2015",
    "http://www.richelbilderbeek.nl/GameMaziak.htm",
    GetVersion(),
    GetVersionHistory()
  );
  return a;
}

ribi::Help ribi::maziak::MenuDialog::GetHelp() const noexcept
{
  return Help(
    this->GetAbout().GetFileTitle(),
    this->GetAbout().GetFileDescription(),
    {

    },
    {

    }
  );
}

std::string ribi::maziak::MenuDialog::GetVersion() const noexcept
{
  return "3.1";
}

std::vector<std::string> ribi::maziak::MenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2007-10-22: version 1.0: Initial version",
    "2010-02-16: version 1.1: Changed graphics to resemble the original Maziacs more. Changed manu screen. Changed 'Game Over' screen. Changed 'Congratulations' screen.",
    "2010-02-17: version 1.2: Animated prisoners. Animated enemies. Animated player. Improved 'Menu' screen. Improved 'About' screen. Added 'What's New?' screen",
    "2010-02-18: version 1.3: Animated fights. Prevent overlapping sprites. Add 'Instructions' screen in menu. Improved 'Menu' screen",
    "2010-02-25: version 1.4: Improved 'Game Over' screen. Added animation in 'Congratulations' screen. Improved enemies' intelligence. Improved maze creation algorithm. Ensured the player is not placed too close to the exit.",
    "2010-07-31: version 2.0: Reprogrammed in Qt Creator, so Maziak is now cross-platform!",
    "2012-03-06: version 2.1: Conformized architecture and naming for ProjectRichelBilderbeek.",
    "2014-01-06: version 3.0: Seperated GUI from game logic, allow console gaming",
    "2015-12-11: version 3.1: Minor update",
  };
}
