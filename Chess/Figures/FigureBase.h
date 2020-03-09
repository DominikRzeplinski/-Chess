#ifndef FIGUREBASE_H
#define FIGUREBASE_H
#include "QGraphicsPixmapItem"

class FigureBase :public QGraphicsPixmapItem
{
public:
  FigureBase(bool side = true, int x =0, int y =0, QGraphicsItem *parent = 0);
  bool virtual ValidatePosition() =0;
protected:
  bool LeftSide;
  int PositionX;
  int PositionY;
};

#endif // FIGUREBASE_H
