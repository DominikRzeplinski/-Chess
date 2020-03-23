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
  bool validateMoveInOneDirection(int idxFigure,int xPos, int yPos);
  void CleanScene();
  QVector<QPair<int,int>> m_availableMoves;
public slots:
    void validMoves(int PositionX, int PositionY);
    void clearMoves();
    void setNewPosition(int PositionX, int PositionY);
};

#endif // CHESSBOARD_H
