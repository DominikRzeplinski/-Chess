#include "FigureBishop.h"
#include "QtMath"

FigureBishop::FigureBishop(bool side,FigureType type,int x, int y,QGraphicsItem *parent):FigureBase(side,type,x,y,parent)
{
  if (side)
  {
    setPixmap(QPixmap(":/File_Chess_bdt45.svg"));
    m_image.load(":/File_Chess_bdt45.svg");
  }
  else
  {
    setPixmap(QPixmap(":/File_Chess_blt45.svg"));
    m_image.load(":/File_Chess_blt45.svg");
  }
  m_stopOnOtherFigure = true;
}

bool FigureBishop::ValidatePosition(int positionX, int positionY)
{
  if (qFabs(m_positionX - positionX) == qFabs(m_positionY - positionY))
    return true;

  return false ;
}

bool FigureBishop::ValidateStrikePosition(int PositionX, int PositionY)
{
  return ValidatePosition(PositionX,PositionY);
}
