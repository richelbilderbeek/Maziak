#ifndef MAZIAKMAINDIALOG_H
#define MAZIAKMAINDIALOG_H

#include <iosfwd>
#include <set>
#include <vector>

#include "maziakfwd.h"
#include "maziakkey.h"
#include "maziakdistancesmaze.h"
#include "maziakmaze.h"
#include "maziakgamestate.h"
#include "maziaksolutionmaze.h"
#include "maziakplayerdirection.h"
#include "maziakplayermove.h"
#include "maziaksprite.h"

namespace ribi {
namespace maziak {

struct Display;

/// Game contains all the logic:
///  * the IntMaze: contains all walls and roads
///  * the Maze: contains the maze, enemies, swords, prisoners, exit
///  * the solutionMaze: shows the road to the exit
///  * the game state: is the game running, over or won?
struct Game
{
  Game(const Maze& maze);

  void AnimateEnemiesAndPrisoners(const int view_width, const int view_height) noexcept;

  void AnimateFighting() noexcept;

  ///Is the coordinat in range of the maze?
  ///If not, this usually ends up in a wall being drawn
  bool CanGet(const int x, const int y) const noexcept;

  const Maze& GetMaze() const noexcept { return m_maze; }
  MazeSquare Get(const int x, const int y) const noexcept { return m_maze.Get(x, y); }
  bool GetDoShowSolution() const noexcept { return m_do_show_solution; }

  PlayerDirection GetPlayerDirection() const noexcept { return m_direction; }
  int GetPlayerFightingFrame() const noexcept { return m_fighting_frame; }
  bool GetPlayerHasSword() const noexcept { return m_has_sword; }
  PlayerMove GetPlayerMove() const noexcept { return m_move_now; }
  MazeSquare GetPlayerSquare() const noexcept { return Get(m_x, m_y); }

  const SolutionMaze& GetSolution() const noexcept { return m_solution; }


  /// Get the sprite above the floor, e.g. an enemy
  /// @param x column index of the maze
  /// @param y row index of the maze
  /// @param enemy_frame index in the enemy animation. Enemies have two
  ///   sprites, so any odd number gives one sprite, any even number the other
  /// @param prisoner_frame index in the prisoner animation. Prisoners have two
  ///   sprites, so any odd number gives one sprite, any even number the other
  Sprite GetSpriteAboveFloor(
    const int x,
    const int y,
    const int enemy_frame,
    const int prisoner_frame
  ) const;

  /// @param x column index of the maze
  /// @param y row index of the maze
  Sprite GetSpriteFloor(const int x, const int y) const;

  /// @param x column index of the maze
  /// @param y row index of the maze
  Sprite GetSpritePlayer() const;

  ///Get the sprites at the coordinat.
  ///Sprite that needs to be drawn first (usually the floor) is at the first index.
  ///Sprite that needs to be drawn last (for example the player) is at the last index.
  /// @param x column index of the maze
  /// @param y row index of the maze
  /// @param enemy_frame index in the enemy animation. Enemies have two
  ///   sprites, so any odd number gives one sprite, any even number the other
  /// @param prisoner_frame index in the prisoner animation. Prisoners have two
  ///   sprites, so any odd number gives one sprite, any even number the other
  std::vector<Sprite> GetSprites(
    const int x,
    const int y,
    const int enemy_frame = 0,
    const int prisoner_frame = 0
  ) const;

  /// Get the state of the game
  GameState GetState() const noexcept { return m_state; }

  int GetX() const noexcept { return m_x; }
  int GetY() const noexcept { return m_y; }

  ///Press a key and move the player directly if possible
  ///Call 'RespondToCurrentSquare' to let the player respond to the current square
  void PressKey(const Key keys);
  ///Press all active keys
  void PressKeys(const std::set<Key>& keys);

  ///Let the game respond to the current square the player is
  /// * If at a prisoner: show the solution
  /// * If at an enemy: start fighting animation
  /// * If at a sword: take the sword
  /// * If at the exit: game is done
  void RespondToCurrentSquare();

  ///Start showing the solution from the player's current square
  void SetDoShowSolution(const bool do_show) noexcept;

  private:

  PlayerDirection m_direction;
  DistancesMaze m_distances;

  ///Shows the solution. This really is a member variable of this class,
  ///as it determines if a player can or cannot walk upon a prisoner square
  bool m_do_show_solution;

  int m_fighting_frame;
  bool m_has_sword;
  Maze m_maze;
  PlayerMove m_move_now;

  std::mt19937 m_rng_engine;
  SolutionMaze m_solution;
  GameState m_state;

  ///The player its x coordinat
  int m_x;

  ///The player its y coordinat
  int m_y;

  SolutionMaze CreateNewSolution() noexcept;

  ///Key down is pressed
  void PressKeyDown();

  ///Key left is pressed
  void PressKeyLeft();

  ///Key right is pressed
  void PressKeyRight();

  ///Key up is pressed
  void PressKeyUp();

  friend std::ostream& operator<<(std::ostream& os, const Game& d) noexcept;
};

///Creates a MainDialog with TestMaze1
Game CreateTestGame1();

int get_n_cols(const Game& g) noexcept;
int get_n_rows(const Game& g) noexcept;


/// Get the sprite above the floor, e.g. Enemy
/// @param x column index of the maze
/// @param y row index of the maze
/// @param maze the maze
/// @param enemy_frame index in the enemy animation. Enemies have two
///   sprites, so any odd number gives one sprite, any even number the other
/// @param prisoner_frame index in the prisoner animation. Prisoners have two
///   sprites, so any odd number gives one sprite, any even number the other
Sprite GetSpriteAboveFloor(
  const int x,
  const int y,
  const Maze& maze,
  const int enemy_frame,
  const int prisoner_frame
);

Sprite GetSpriteFloor(
  const Maze& maze,
  const int x,
  const int y,
  const bool show_solution,
  const SolutionMaze& solution
);

Sprite GetSpritePlayer(
  const PlayerDirection direction,
  const PlayerMove moveNow,
  const bool has_sword,
  const int fighting_frame
);

Sprite GetSpritePlayerDown(
  const PlayerMove moveNow,
  const bool has_sword
);

Sprite GetSpritePlayerLeft(
  const PlayerMove moveNow,
  const bool has_sword
);

Sprite GetSpritePlayerRight(
  const PlayerMove moveNow,
  const bool has_sword
);

Sprite GetSpritePlayerUp(
  const PlayerMove moveNow,
  const bool has_sword
);

Sprite GetSpritePlayerFighting(
  const int fighting_frame,
  const bool has_sword
);

std::string to_str(const Game& d) noexcept;

std::ostream& operator<<(std::ostream& os, const Game& d) noexcept;

} //namespace maziak
} //namespace ribi


#endif // MAZIAKMAINDIALOG_H
