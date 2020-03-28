#ifndef FIGUREROOK_H
#define FIGUREROOK_H
#include "FigureBase.h"


class FigureRook: public FigureBase
{
public:
  FigureRook(bool side = true,FigureType type = FigureType::Alive, int x =0, int y =0);
  bool ValidatePosition(int PositionX, int PositionY);
  bool ValidateStrikePosition(int PositionX, int PositionY);
};

#endif // FIGUREROOK_H
