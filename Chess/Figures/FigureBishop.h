#ifndef FIGUREBISHOP_H
#define FIGUREBISHOP_H
#include "FigureBase.h"

/*!
 * \brief The FigureBishop class determinate bishop figure
 */
class FigureBishop: public FigureBase
{
public:
  /*!
   * \brief FigureBishop constructor
   * \param side determinate for wich player bishop is created
   * \param type enum for bishop
   * \param x coordinate of bishop on board
   * \param y coordinate of bishop on board
   */
  FigureBishop(bool side = true,FigureType type = FigureType::Alive, int x =0, int y =0);
  /*!
   * \brief validatePosition validate if coordinates of new position are valid for bishop
   * \param PositionX new coordinates for bishop
   * \param PositionY new coordinates for bishop
   * \return true if new coordinates are in reach for bishop, other false
   */
  bool validatePosition(int PositionX, int PositionY);
  /*!
   * \brief validateStrikePosition validate if coordinates of new position are valid for bishop to strike
   * \param PositionX new coordinates of strike
   * \param PositionY new coordinates of strike
   * \return true if bishop can strike on new coordinates, other false
   */
  bool validateStrikePosition(int PositionX, int PositionY);
};

#endif // FIGUREBISHOP_H
