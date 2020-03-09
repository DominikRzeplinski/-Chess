#include "FigureRook.h"

FigureRook::FigureRook(bool side,int x, int y,QGraphicsItem *parent):FigureBase(side,x,y,parent)
{
  if (side)
    setPixmap(QPixmap(":/File_Chess_rdt45.svg"));
  else
    setPixmap(QPixmap(":/File_Chess_rlt45.svg"));

}

bool FigureRook::ValidatePosition()
{
  return false;
}
