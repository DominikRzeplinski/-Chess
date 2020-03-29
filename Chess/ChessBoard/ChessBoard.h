#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include "Figures/FigureBase.h"

class ChessBoard
{
public:
  ChessBoard();
  void Reset();
  void validMoves(int positionX, int positionY);
  bool setNewPosition(int positionX, int positionY,int newPositionX, int newPositionY);
  bool promotionSelected(int positionX, int positionY);
  bool endOfGame;
  bool checkMate;
  QList<FigureBase*> figures;
  QList<FigureBase*> promotionFigures;
  bool leftSideWinner;
  bool promotionActive;
  QVector<QPair<int,int>> availableMoves;
  QVector<QPair<int,int>> availableStrikeMoves;
private:
  FigureBase* figureEnPassant;
  bool validateMoveInOneDirection(FigureBase* figure,int xPos, int yPos, bool enemy = false);
  void cleanScene();
  QVector<QPair<int,int>> enemyAvailableMoves;
  QVector<QPair<int,int>> enemyAvailableStrikeMoves;
  QVector<QPair<int,int>> enemyAllValidStrikeMoves;
  FigureBase* getFigureAtPosition(int positionX, int positionY);
  void setAllValidMoves(int positionX, int positionY, bool enemy = false);
  bool isCheckMate(bool leftSide);
  void getEnemyAvailableMoves(bool leftSide);
  void setWinner(bool leftSide);
  void clearMoves();
  bool isEnPassantPosition(int xPos, int yPos);
  bool checkCheckMate(int positionX, int positionY);
};

#endif // CHESSBOARD_H
