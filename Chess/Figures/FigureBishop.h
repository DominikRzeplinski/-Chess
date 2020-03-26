#ifndef FIGUREBISHOP_H
#define FIGUREBISHOP_H
#include "FigureBase.h"


class FigureBishop: public FigureBase
{
public:
  FigureBishop(bool side = true,FigureType type = FigureType::Alive, int x =0, int y =0,QGraphicsItem *parent =0);
  bool ValidatePosition(int PositionX, int PositionY);
  bool ValidateStrikePosition(int PositionX, int PositionY);
};

#endif // FIGUREBISHOP_H
