#ifndef FIGUREBISHOP_H
#define FIGUREBISHOP_H
#include "FigureBase.h"


class FigureBishop: public FigureBase
{
public:
  FigureBishop(bool side = true, int x =0, int y =0,QGraphicsItem *parent =0);
  bool ValidatePosition();
};

#endif // FIGUREBISHOP_H
