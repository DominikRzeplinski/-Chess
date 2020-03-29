#ifndef FIGUREPAWN_H
#define FIGUREPAWN_H
#include "FigureBase.h"


/*!
 * \brief The FigurePawn class determinate pawn figure
 */
class FigurePawn: public FigureBase
{
public:
  /*!
   * \brief FigurePawn constructor
   * \param side determinate for wich player pawn is created
   * \param type enum for pawn
   * \param x coordinate of pawn on board
   * \param y coordinate of pawn on board
   */
  FigurePawn(bool side = true,FigureType type = FigureType::Alive, int x =0, int y =0);
  /*!
   * \brief validatePosition validate if coordinates of new position are valid for pawn
   * \param PositionX new coordinates for pawn
   * \param PositionY new coordinates for pawn
   * \return true if new coordinates are in reach for pawn, other false
   */
  bool validatePosition(int PositionX, int PositionY);
  /*!
   * \brief validateStrikePosition validate if coordinates of new position are valid for pawn to strike
   * \param PositionX new coordinates of strike
   * \param PositionY new coordinates of strike
   * \return true if pawn can strike on new coordinates, other false
   */
  bool validateStrikePosition(int PositionX, int PositionY);
private:
  /*!
   * \brief moveEnemyDirection validate if pawn is moving in direction of enemy player
   * \param PositionX new coordinates for pawn
   * \return true if direction is coorect, other false
   */
  bool moveEnemyDirection(int PositionX);
};

#endif // FIGUREPAWN_H
