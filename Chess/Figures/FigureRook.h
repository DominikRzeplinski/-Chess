#ifndef FIGUREROOK_H
#define FIGUREROOK_H
#include "FigureBase.h"


class FigureRook: public FigureBase
{
public:
  FigureRook(bool side = true, int x =0, int y =0,QGraphicsItem *parent =0);
  bool ValidatePosition();
};

#endif // FIGUREROOK_H
