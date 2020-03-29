#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include "Figures/FigureBase.h"

class ChessBoard
{
public:
  ChessBoard();
  void Reset();
  QList<FigureBase*> m_figures;
  QList<FigureBase*> m_promotionFigures;
  FigureBase* figureElPassa;
  bool m_promotionActive;
  bool leftSideWinner;
  bool m_endOfGame;
  bool validateMoveInOneDirection(FigureBase* figure,int xPos, int yPos, bool enemy = false);
  void CleanScene();
  QVector<QPair<int,int>> m_availableMoves;
  QVector<QPair<int,int>> m_availableStrikeMoves;
  QVector<QPair<int,int>> m_enemyAvailableMoves;
  QVector<QPair<int,int>> m_enemyAvailableStrikeMoves;
  QVector<QPair<int,int>> m_enemyAllValidStrikeMoves;
  FigureBase* getFigureAtPosition(int positionX, int positionY);
  void setAllValidMoves(int positionX, int positionY, bool enemy = false);
  bool checkMat(bool leftSide);
  bool m_checkmate;
  void getEnemyAvailableMoves(bool leftSide);
  void setWinner(bool leftSide);
  bool promotionSelected(int positionX, int positionY);
  void validMoves(int positionX, int positionY);
  void clearMoves();
  bool setNewPosition(int positionX, int positionY,int newPositionX, int newPositionY);
  bool isElpassaPostion(int xPos, int yPos);
  bool checkCheckMat(int positionX, int positionY);
};

#endif // CHESSBOARD_H
