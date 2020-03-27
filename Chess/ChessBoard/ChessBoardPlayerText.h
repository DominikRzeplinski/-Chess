#ifndef CHESSBOARDPLAYERTEXT_H
#define CHESSBOARDPLAYERTEXT_H
#include "QGraphicsTextItem"

class ChessBoardPlayerText: public QGraphicsTextItem
{
public:
  ChessBoardPlayerText(bool leftSide, QGraphicsItem *parent=0);
};

#endif // CHESSBOARDPLAYERTEXT_H
