#ifndef FIGUREQUEEN_H
#define FIGUREQUEEN_H
#include "FigureBase.h"


/*!
 * \brief The FigureQueen class determinate queen figure
 */
class FigureQueen: public FigureBase
{
public:
  /*!
   * \brief FigureQueen constructor
   * \param side determinate for wich player queen is created
   * \param type enum for queen
   * \param x coordinate of queen on board
   * \param y coordinate of queen on board
   */
  FigureQueen(bool side = true,FigureType type = FigureType::Alive, int x =0, int y =0);
  /*!
   * \brief validatePosition validate if coordinates of new position are valid for queen
   * \param PositionX new coordinates for queen
   * \param PositionY new coordinates for queen
   * \return true if new coordinates are in reach for queen, other false
   */
  bool validatePosition(int PositionX, int PositionY);
  /*!
   * \brief validateStrikePosition validate if coordinates of new position are valid for queen to strike
   * \param PositionX new coordinates of strike
   * \param PositionY new coordinates of strike
   * \return true if queen can strike on new coordinates, other false
   */
  bool validateStrikePosition(int PositionX, int PositionY);
};

#endif // FIGUREQUEEN_H
