#ifndef FIGUREPAWN_H
#define FIGUREPAWN_H
#include "FigureBase.h"


class FigurePawn: public FigureBase
{
public:
  FigurePawn(bool side = true, int x =0, int y =0,QGraphicsItem *parent =0);
  bool ValidatePosition();
};

#endif // FIGUREPAWN_H
