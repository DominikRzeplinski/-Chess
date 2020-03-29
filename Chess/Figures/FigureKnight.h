#ifndef FIGUREKNIGHT_H
#define FIGUREKNIGHT_H
#include "FigureBase.h"

/*!
 * \brief The FigureKnight class determinate knight figure
 */
class FigureKnight: public FigureBase
{
public:
  /*!
   * \brief FigureKnight constructor
   * \param side determinate for wich player knight is created
   * \param type enum for knight
   * \param x coordinate of bishop on knight
   * \param y coordinate of bishop on knight
   */
  FigureKnight(bool side = true,FigureType type = FigureType::Alive, int x =0, int y =0);
  /*!
   * \brief validatePosition validate if coordinates of new position are valid for knight
   * \param PositionX new coordinates for knight
   * \param PositionY new coordinates for knight
   * \return true if new coordinates are in reach for knight, other false
   */
  bool validatePosition(int PositionX, int PositionY);
  /*!
   * \brief validateStrikePosition validate if coordinates of new position are valid for knight to strike
   * \param PositionX new coordinates of strike
   * \param PositionY new coordinates of strike
   * \return true if knight can strike on new coordinates, other false
   */
  bool validateStrikePosition(int PositionX, int PositionY);
};

#endif // FIGUREKNIGHT_H
