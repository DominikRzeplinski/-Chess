#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <QGraphicsScene>
#include "ChessBoardBox.h"
#include "ChessBoardSidePanel.h"
#include "Figures/FigureBase.h"

class ChessBoard:public QGraphicsScene
{
public:
  ChessBoard(QObject *parent = 0);
  void Reset();
private:
  void CleanScene();
  QList<ChessBoardBox*> m_boxes;
  ChessBoardSidePanel* m_panelLeft;
  ChessBoardSidePanel* m_panelRight;
  QList<FigureBase*> m_figures;
};

#endif // CHESSBOARD_H
