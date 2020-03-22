#ifndef CHESSBOARDBOX_H
#define CHESSBOARDBOX_H
#include "QGraphicsRectItem"
#include "QGraphicsLayoutItem"

class ChessBoardBox: public QGraphicsRectItem
{
public:
  int PositionX;
  int PositionY;
  bool m_bHasFigure;
  ChessBoardBox(int xPos, int yPos, QGraphicsItem *parent=0);
  void ResetBrush();
private:
  int const m_sizeOfBox = 50;
  int const m_leftOfBoard = 200;
  int const m_topOfBoard = 100;
};

#endif // CHESSBOARDBOX_H
