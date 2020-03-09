#include "FigureQueen.h"

FigureQueen::FigureQueen(bool side,int x, int y,QGraphicsItem *parent):FigureBase(side,x,y,parent)
{
  if (side)
    setPixmap(QPixmap(":/Chess_qdt45.svg"));
  else
    setPixmap(QPixmap(":/Chess_qlt45.svg"));

}

bool FigureQueen::ValidatePosition()
{
  return false;
}
