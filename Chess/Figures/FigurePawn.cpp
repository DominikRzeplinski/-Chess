#include "FigurePawn.h"
#include "QtMath"

FigurePawn::FigurePawn(bool side,FigureType type,int x, int y,QGraphicsItem *parent):FigureBase(side,type,x,y,parent)
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
  if (!moveEnemyDirection(positionX))
    return false;

  if (qFabs(m_positionX - positionX) == 1 && (m_positionY == positionY))
    return true;

  if (qFabs(m_positionX - positionX) == 2 && (m_positionY == positionY) && m_firstMove)
    return true;

  return false;
}

bool FigurePawn::ValidateStrikePosition(int PositionX, int PositionY)
{
  if (!moveEnemyDirection(PositionX))
    return false;
  if (qFabs(m_positionX - PositionX) == 1 && qFabs(m_positionY - PositionY) ==1)
    return true;
  return false;
}

bool FigurePawn::moveEnemyDirection(int PositionX)
{
  if (m_leftSide)
    {
      if (PositionX < m_positionX)
        return false;
    }
  else
    {
      if (PositionX > m_positionX)
        return false;
    }
  return true;
}

void FigurePawn::Promote()
{
  QGraphicsRectItem *promoteScene = new QGraphicsRectItem(0,0,800,600);
  promoteScene->setOpacity(0.2);

}
