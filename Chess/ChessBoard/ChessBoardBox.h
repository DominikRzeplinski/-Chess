#ifndef CHESSBOARDBOX_H
#define CHESSBOARDBOX_H
#include "QGraphicsRectItem"
#include "QGraphicsLayoutItem"

class ChessBoardBox: public QGraphicsRectItem
{
public:
  int positionX;
  int positionY;
  ChessBoardBox(int xPos, int yPos, QGraphicsItem *parent=0);
  void ResetBrush();
private:
  int const sizeOfBox = 50;
  int const leftOfBoard = 200;
  int const topOfBoard = 100;
};

#endif // CHESSBOARDBOX_H
