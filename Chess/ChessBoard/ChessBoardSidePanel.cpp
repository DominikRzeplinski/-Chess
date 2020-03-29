#include "ChessBoardSidePanel.h"
#include <QGraphicsScene>

ChessBoardSidePanel::ChessBoardSidePanel(bool left, QGraphicsItem *parent):QGraphicsRectItem(parent)
{
  setRect(0,0,200,600);
  if(left)
    setPos(0,0);
  else
    setPos(600,0);
  leftSifde = left;
  setBrush(Qt::white);
  setZValue(-1);
  ResetSlot();
}

void ChessBoardSidePanel::ResetSlot()
{
  freeSlotY =0;
  freeSlotX =0;
}

void ChessBoardSidePanel::SetSlotPos()
{
  freeSlotY ++;
  if (freeSlotY > 3)
    {
      freeSlotX ++;
      freeSlotY =0;
    }
}
QPointF ChessBoardSidePanel::GetFreeSlotPos()
{
  return QPointF((leftSifde ? 0:600) +freeSlotY * 50,freeSlotX * 50);
}

