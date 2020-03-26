#include "ChessBoardPromotion.h"
#include <QGraphicsScene>

ChessBoardPromotion::ChessBoardPromotion(QGraphicsItem *parent):QGraphicsRectItem(parent)
{
  setRect(0,0,400,100);
  setPos(200,250);
  setOpacity(0.2);
  setBrush(Qt::red);
  setVisible(false);
}
