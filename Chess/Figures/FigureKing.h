#ifndef FIGUREKING_H
#define FIGUREKING_H
#include "FigureBase.h"

class FigureKing : public FigureBase
{
public:
  FigureKing(bool side = true,FigureType type = FigureType::Alive, int x =0, int y =0,QGraphicsItem *parent =0);
  bool ValidatePosition(int PositionX, int PositionY);
  bool ValidateStrikePosition(int PositionX, int PositionY);
};

#endif // FIGUREKING_H
