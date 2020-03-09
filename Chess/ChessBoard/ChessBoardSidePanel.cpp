#include "ChessBoardSidePanel.h"
#include <QGraphicsScene>

ChessBoardSidePanel::ChessBoardSidePanel(bool left, QGraphicsItem *parent):QGraphicsRectItem(parent)
{
  setRect(0,0,200,600);
  if(left)
    setPos(0,0);
  else
    setPos(600,0);
  setBrush(Qt::white);
}
