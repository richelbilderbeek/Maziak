#ifndef SFMLMAZIAKGAMEDIALOG_H
#define SFMLMAZIAKGAMEDIALOG_H

namespace ribi {
namespace maziak {

class SfmlGameDialog
{
public:
  SfmlGameDialog();

  ///Run the dialog, until the user closes it
  void Exec();
};

} //~namespace maziak
} //~namespace ribi

#endif // SFMLMAZIAKGAMEDIALOG_H
