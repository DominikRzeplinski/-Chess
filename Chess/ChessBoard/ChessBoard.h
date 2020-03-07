#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <QGraphicsScene>
#include "ChessBoardBox.h"

class ChessBoard:public QGraphicsScene
{
public:
  ChessBoard(QObject *parent = 0);
  void Reset();
private:
  QList<ChessBoardBox*> *m_boxes;
};

#endif // CHESSBOARD_H
