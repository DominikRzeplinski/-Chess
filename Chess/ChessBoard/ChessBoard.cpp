#include "ChessBoard.h"

ChessBoard::ChessBoard(QObject *parent): QGraphicsScene(parent)
{
  setSceneRect(0,0,800,600);
  Reset();
}

void ChessBoard::Reset()
{
  ChessBoardBox *box;
  for(int x = 0; x < 8; x++) {
      for(int y = 0; y < 8; y++)
      {
          box = new ChessBoardBox(x,y);
          addItem(box);
          //m_boxes->append(box);
      }
  }
}
