#include "ChessBoardHistory.h"
ChessBoardHistory::ChessBoardHistory()
{
}

void ChessBoardHistory::addMove(ChessBoardMove move)
{
  chessBoardMoves.append(move);
}

QList<ChessBoardMove>* ChessBoardHistory::getChessBoardHistory()
{
  return &chessBoardMoves;
}

void ChessBoardHistory::loadGame(QString fileName)
{
  QFile file(fileName);
  if (!file.open(QIODevice::ReadOnly))
    return;
  chessBoardMoves.clear();
  QDataStream in(&file);
  in.setVersion(QDataStream::Qt_4_5);
  while(!in.atEnd())
    {
      int x,y,newX,newY;
      bool promotion;
      in >> promotion;
      in >> x;
      in >> y;
      in >> newX;
      in >> newY;
      chessBoardMoves.append(ChessBoardMove(x,y,newX,newY,promotion));
    }
}

void ChessBoardHistory::saveGame(QString fileName)
{
  QFile file(fileName);
  if (!file.open(QIODevice::WriteOnly))
    return;
  QDataStream out(&file);
  out.setVersion(QDataStream::Qt_4_5);
  for (int i=0 ; i < chessBoardMoves.count(); ++i)
    {
      out << chessBoardMoves.at(i).getPromotion();
      out << chessBoardMoves.at(i).getPositionX();
      out << chessBoardMoves.at(i).getPositionY();
      out << chessBoardMoves.at(i).getNewPositionX();
      out << chessBoardMoves.at(i).getNewPositionY();
    }
}
