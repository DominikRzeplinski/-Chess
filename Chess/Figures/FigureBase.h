#ifndef FIGUREBASE_H
#define FIGUREBASE_H
#include "QGraphicsPixmapItem"

class FigureBase :public QGraphicsPixmapItem
{
public:
  FigureBase();
  bool ValidatePosition();
protected:
  int PositionX;
  int PositionY;
};

#endif // FIGUREBASE_H
