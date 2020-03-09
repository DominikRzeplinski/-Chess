#ifndef CHESSBOARDSIDEPANEL_H
#define CHESSBOARDSIDEPANEL_H

#include "QGraphicsRectItem"

class ChessBoardSidePanel: public QGraphicsRectItem
{
public:
  ChessBoardSidePanel(bool left = true, QGraphicsItem *parent=0);
};

#endif // CHESSBOARDSIDEPANEL_H
