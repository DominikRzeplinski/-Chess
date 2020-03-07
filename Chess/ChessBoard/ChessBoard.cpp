#include "ChessBoard.h"
#include "Figures/FigureKing.h"

ChessBoard::ChessBoard(QObject *parent): QGraphicsScene(parent)
{
  setSceneRect(0,0,800,600);
  Reset();
}

void ChessBoard::Reset()
{
  clear();
  FigureKing * king;
  ChessBoardBox *box;
  for(int x = 0; x < 8; x++) {
      for(int y = 0; y < 8; y++)
      {
          box = new ChessBoardBox(x,y);
          king = new FigureKing();
          king->setPos(box->pos());
          addItem(box);
          addItem(king);
          m_boxes.append(box);
      }
  }
}
