#include "ChessBoardBox.h"
#include <QGraphicsScene>

ChessBoardBox::ChessBoardBox(int xPos, int yPos, QGraphicsItem *parent):QGraphicsRectItem(parent)
{
  setRect(0,0,m_sizeOfBox,m_sizeOfBox);
  setPos(m_leftOfBoard+m_sizeOfBox*yPos,m_topOfBoard+m_sizeOfBox*xPos);
  setZValue(-1);
  PositionX = xPos;
  PositionY = yPos;
  ResetBrush();
}

void ChessBoardBox::ResetBrush()
{
  if((PositionX+PositionY)%2==0)
    setBrush(Qt::lightGray);
  else
    setBrush(Qt::darkGray);
}
