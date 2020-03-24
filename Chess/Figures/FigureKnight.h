#ifndef FIGUREKNIGHT_H
#define FIGUREKNIGHT_H
#include "FigureBase.h"


class FigureKnight: public FigureBase
{
public:
  FigureKnight(bool side = true, int x =0, int y =0,QGraphicsItem *parent =0);
  bool ValidatePosition(int PositionX, int PositionY);
  bool ValidateStrikePosition(int PositionX, int PositionY);
};

#endif // FIGUREKNIGHT_H
