#ifndef FIGUREKING_H
#define FIGUREKING_H
#include "FigureBase.h"

class FigureKing : public FigureBase
{
public:
  FigureKing(bool side = true, int x =0, int y =0,QGraphicsItem *parent =0);
  bool ValidatePosition();
};

#endif // FIGUREKING_H
