#ifndef CHESSBOARDBOX_H
#define CHESSBOARDBOX_H
#include "QGraphicsRectItem"
#include "QGraphicsLayoutItem"

class ChessBoardBox: public QGraphicsRectItem
{
public:
  ChessBoardBox(int xPos, int yPos, QGraphicsItem *parent=0);
private:
  int const m_sizeOfBox = 50;
  int const m_leftOfBoard = 200;
  int const m_topOfBoard = 75;
};

#endif // CHESSBOARDBOX_H
