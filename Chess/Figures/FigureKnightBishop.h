#ifndef FIGUREKNIGHTBISHOP_H
#define FIGUREKNIGHTBISHOP_H
#include "FigureBase.h"

/*!
 * \brief The FigureKnightBishop class determinate funny figure
 */
class FigureKnightBishop: public FigureBase
{
public:
  /*!
   * \brief FigureKnightBishop constructor
   * \param side determinate for wich player KnightBishop is created
   * \param type enum for KnightBishop
   * \param x coordinate of bishop on board
   * \param y coordinate of bishop on board
   */
  FigureKnightBishop(bool side = true,FigureType type = FigureType::Alive, int x =0, int y =0);
  /*!
   * \brief validatePosition validate if coordinates of new position are valid for KnightBishop
   * \param PositionX new coordinates for KnightBishop
   * \param PositionY new coordinates for KnightBishop
   * \return true if new coordinates are in reach for KnightBishop, other false
   */
  bool validatePosition(int PositionX, int PositionY);
  /*!
   * \brief validateStrikePosition validate if coordinates of new position are valid for KnightBishop to strike
   * \param PositionX new coordinates of strike
   * \param PositionY new coordinates of strike
   * \return true if KnightBishop can strike on new coordinates, other false
   */
  bool validateStrikePosition(int PositionX, int PositionY);
};
#endif // FIGUREKNIGHTBISHOP_H
