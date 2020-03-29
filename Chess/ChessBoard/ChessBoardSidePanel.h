#ifndef CHESSBOARDSIDEPANEL_H
#define CHESSBOARDSIDEPANEL_H

#include "QGraphicsRectItem"

class ChessBoardSidePanel: public QGraphicsRectItem
{
public:
  ChessBoardSidePanel(bool left = true, QGraphicsItem *parent=0);
  QPointF getFreeSlotPos();
  void setSlotPos();
  void resetSlot();
private:
  int freeSlotX;
  int freeSlotY;
  bool leftSifde;
};

#endif // CHESSBOARDSIDEPANEL_H
