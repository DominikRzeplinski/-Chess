#include "FigureKing.h"

FigureKing::FigureKing(bool side,int x, int y,QGraphicsItem *parent):FigureBase(side,x,y,parent)
{
  if (side)
  {
    setPixmap(QPixmap(":/Chess_kdt45.svg"));
    m_image.load(":/Chess_kdt45.svg");
  }
  else
  {
    setPixmap(QPixmap(":/Chess_klt45.svg"));
    m_image.load(":/Chess_klt45.svg");
  }
}

bool FigureKing::ValidatePosition()
{
  return false;
}
