#include "FigureBishop.h"

FigureBishop::FigureBishop(bool side,int x, int y,QGraphicsItem *parent):FigureBase(side,x,y,parent)
{
  if (side)
    setPixmap(QPixmap(":/File_Chess_bdt45.svg"));
  else
    setPixmap(QPixmap(":/File_Chess_blt45.svg"));
}

bool FigureBishop::ValidatePosition()
{
  return false;
}
