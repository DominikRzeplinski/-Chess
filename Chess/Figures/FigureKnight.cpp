#include "FigureKnight.h"

FigureKnight::FigureKnight(bool side,int x, int y,QGraphicsItem *parent):FigureBase(side,x,y,parent)
{
  if(side)
  {
    setPixmap(QPixmap(":/File_Chess_ndt45.svg"));
    m_image.load(":/File_Chess_ndt45.svg");
  }
  else
  {
    setPixmap(QPixmap(":/File_Chess_nlt45.svg"));
    m_image.load(":/File_Chess_nlt45.svg");
  }
}

bool FigureKnight::ValidatePosition()
{
  return false;
}
