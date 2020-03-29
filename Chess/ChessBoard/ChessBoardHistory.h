#ifndef CHESSBOARDHISTORY_H
#define CHESSBOARDHISTORY_H
#include "ChessBoardMove.h"
#include "QList"

class ChessBoardHistory
{
public:
  ChessBoardHistory();
  void addMove(ChessBoardMove);
  QList<ChessBoardMove>* getChessBoardHistory();
  void SaveGame(QString fileName);
  void LoadGame(QString fileName);
private:
  QList<ChessBoardMove> chessBoardMoves;
};

#endif // CHESSBOARDHISTORY_H
