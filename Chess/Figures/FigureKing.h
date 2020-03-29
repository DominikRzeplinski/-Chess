#ifndef FIGUREKING_H
#define FIGUREKING_H
#include "FigureBase.h"

/*!
 * \brief The FigureKing class determinate king figure
 */
class FigureKing : public FigureBase
{
public:
  /*!
   * \brief FigureKing constructor
   * \param side determinate for wich player king is created
   * \param type enum for king
   * \param x coordinate of king on board
   * \param y coordinate of king on board
   */
  FigureKing(bool side = true,FigureType type = FigureType::Alive, int x =0, int y =0);
  /*!
   * \brief validatePosition validate if coordinates of new position are valid for king
   * \param PositionX new coordinates for king
   * \param PositionY new coordinates for king
   * \return true if new coordinates are in reach for king, other false
   */
  bool validatePosition(int PositionX, int PositionY);
  /*!
   * \brief validateStrikePosition validate if coordinates of new position are valid for king to strike
   * \param PositionX new coordinates of strike
   * \param PositionY new coordinates of strike
   * \return true if king can strike on new coordinates, other false
   */
  bool validateStrikePosition(int PositionX, int PositionY);
};

#endif // FIGUREKING_H
