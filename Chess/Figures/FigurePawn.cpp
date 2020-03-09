#include "FigurePawn.h"

FigurePawn::FigurePawn(bool side,int x, int y,QGraphicsItem *parent):FigureBase(side,x,y,parent)
{
  if(side)
    setPixmap(QPixmap(":/File_Chess_pdt45.svg"));
  else
    setPixmap(QPixmap(":/File_Chess_plt45.svg"));
}

bool FigurePawn::ValidatePosition()
{
  return false;
}
