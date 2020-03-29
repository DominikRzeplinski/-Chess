#ifndef FIGUREROOK_H
#define FIGUREROOK_H
#include "FigureBase.h"


/*!
 * \brief The FigureRook class determinate rook figure
 */
class FigureRook: public FigureBase
{
public:
  /*!
   * \brief FigureRook constructor
   * \param side determinate for wich player rook is created
   * \param type enum for rook
   * \param x coordinate of rook on board
   * \param y coordinate of rook on board
   */
  FigureRook(bool side = true,FigureType type = FigureType::Alive, int x =0, int y =0);
  /*!
   * \brief validatePosition validate if coordinates of new position are valid for rook
   * \param PositionX new coordinates for rook
   * \param PositionY new coordinates for rook
   * \return true if new coordinates are in reach for rook, other false
   */
  bool validatePosition(int PositionX, int PositionY);
  /*!
   * \brief validateStrikePosition validate if coordinates of new position are valid for rook to strike
   * \param PositionX new coordinates of strike
   * \param PositionY new coordinates of strike
   * \return true if rook can strike on new coordinates, other false
   */
  bool validateStrikePosition(int PositionX, int PositionY);
};

#endif // FIGUREROOK_H
