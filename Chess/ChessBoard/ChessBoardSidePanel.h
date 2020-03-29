#ifndef CHESSBOARDSIDEPANEL_H
#define CHESSBOARDSIDEPANEL_H

#include "QGraphicsRectItem"

class ChessBoardSidePanel: public QGraphicsRectItem
{
public:
  ChessBoardSidePanel(bool left = true, QGraphicsItem *parent=0);
  QPointF GetFreeSlotPos();
  void SetSlotPos();
  void ResetSlot();
private:
  int freeSlotX;
  int freeSlotY;
  bool leftSifde;
};

#endif // CHESSBOARDSIDEPANEL_H
