#ifndef FIGUREQUEEN_H
#define FIGUREQUEEN_H
#include "FigureBase.h"


class FigureQueen: public FigureBase
{
public:
  FigureQueen(bool side = true, int x =0, int y =0,QGraphicsItem *parent =0);
  bool ValidatePosition(int PositionX, int PositionY);
  bool ValidateStrikePosition(int PositionX, int PositionY);
};

#endif // FIGUREQUEEN_H
