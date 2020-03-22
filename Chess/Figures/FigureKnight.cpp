#include "FigureKnight.h"
#include "QtMath"

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
  m_stopOnOtherFigure = false;
}

bool FigureKnight::ValidatePosition(int PositionX, int PositionY)
{
  if ((qFabs(m_positionX - PositionX) + qFabs(m_positionY - PositionY))== 3 && qFabs(m_positionX - PositionX) > 0 && qFabs(m_positionY - PositionY)>0)
    return true;
  return false;
}
