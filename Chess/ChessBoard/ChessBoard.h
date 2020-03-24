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
  bool validateMoveInOneDirection(FigureBase* figure,int xPos, int yPos, bool enemy = false);
  void CleanScene();
  QVector<QPair<int,int>> m_availableMoves;
  QVector<QPair<int,int>> m_availableStrikeMoves;
  QVector<QPair<int,int>> m_enemyAvailableMoves;
  QVector<QPair<int,int>> m_enemyAvailableStrikeMoves;
  ChessBoardBox* getBoxAtPosition(int positionX, int positionY);
  ChessBoardBox* getBoxUnderMouse();
  FigureBase* getFigureAtPosition(int positionX, int positionY);
  void setAllValidMoves(int positionX, int positionY, bool enemy = false);
  void setColorForBoxes();

public slots:
    void validMoves(int positionX, int positionY);
    void clearMoves();
    void setNewPosition(int positionX, int positionY);
};

#endif // CHESSBOARD_H
