#include "FigurePawn.h"
#include "QtMath"

FigurePawn::FigurePawn(bool side,int x, int y,QGraphicsItem *parent):FigureBase(side,x,y,parent)
{
  if(side)
  {
    setPixmap(QPixmap(":/File_Chess_pdt45.svg"));
    m_image.load(":/File_Chess_pdt45.svg");
  }
  else
  {
    setPixmap(QPixmap(":/File_Chess_plt45.svg"));
    m_image.load(":/File_Chess_plt45.svg");
  }
  m_stopOnOtherFigure = true;
}

bool FigurePawn::ValidatePosition(int positionX, int positionY)
{
  if (m_leftSide)
    {
      if (positionX < m_positionX)
        return false;
    }
  else
    {
      if (positionX > m_positionX)
        return false;
    }

  if (qFabs(m_positionX - positionX) == 1 && (m_positionY == positionY))
    return true;

  if (qFabs(m_positionX - positionX) == 2 && (m_positionY == positionY) && m_firstMove)
    return true;

  return false;
}
