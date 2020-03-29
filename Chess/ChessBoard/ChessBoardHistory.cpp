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

void ChessBoardHistory::LoadGame(QString fileName)
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

void ChessBoardHistory::SaveGame(QString fileName)
{
  QFile file(fileName);
  if (!file.open(QIODevice::WriteOnly))
    return;
  QDataStream out(&file);
  out.setVersion(QDataStream::Qt_4_5);
  for (int i=0 ; i < chessBoardMoves.count(); ++i)
    {
      out << chessBoardMoves.at(i).promotion;
      out << chessBoardMoves.at(i).positionX;
      out << chessBoardMoves.at(i).positionY;
      out << chessBoardMoves.at(i).newPositionX;
      out << chessBoardMoves.at(i).newPositionY;
    }
}
