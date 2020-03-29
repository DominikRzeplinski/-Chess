#include "FigurePawn.h"
#include "QtMath"

FigurePawn::FigurePawn(bool side,FigureType type,int x, int y):FigureBase(side,type,x,y)
{
  if(side)
    m_image.load(":/File_Chess_pdt45.svg");
  else
    m_image.load(":/File_Chess_plt45.svg");
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

