#include "ChessBoardBox.h"
#include <QGraphicsScene>

ChessBoardBox::ChessBoardBox(int xPos, int yPos, QGraphicsItem *parent):QGraphicsRectItem(parent)
{
  setRect(0,0,sizeOfBox,sizeOfBox);
  setPos(leftOfBoard+sizeOfBox*yPos,topOfBoard+sizeOfBox*xPos);
  setZValue(-1);
  positionX = xPos;
  positionY = yPos;
  ResetBrush();
}

void ChessBoardBox::ResetBrush()
{
  if((positionX+positionY)%2==0)
    setBrush(Qt::lightGray);
  else
    setBrush(Qt::darkGray);
}
