#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include "ChessBoardBox.h"
#include "ChessBoardSidePanel.h"
#include "Figures/FigureBase.h"

class ChessBoard :public QObject
{
Q_OBJECT
public:
  ChessBoard();
  void Reset();
  QList<ChessBoardBox*> m_boxes;
  ChessBoardSidePanel* m_panelLeft;
  ChessBoardSidePanel* m_panelRight;
  QList<FigureBase*> m_figures;
private:
  void CleanScene();
public slots:
    void validMoves(int PositionX, int PositionY);
    void clearMoves();
};

#endif // CHESSBOARD_H
