#ifndef CHESSBOARDSCENE_H
#define CHESSBOARDSCENE_H
#include <QGraphicsScene>
#include "ChessBoardBox.h"
#include "ChessBoardSidePanel.h"
#include "Figures/FigureView.h"
#include "ChessBoardPlayerText.h"
#include "ChessBoardPromotion.h"
#include "ChessBoard.h"
#include "ChessBoardHistory.h"

class ChessBoardScene:public QGraphicsScene
{
public:
  ChessBoardScene(QObject *parent = 0);
  void Reset();
  void SaveGame(QString fileName);
  void LoadGame(QString fileName);
  QList<ChessBoardBox*> boxes;
  ChessBoardSidePanel* panelLeft;
  ChessBoardSidePanel* panelRight;
  QList<FigureView*> figureViews;
  QList<FigureView*> promotionFigureViews;
  ChessBoardPromotion *promotion;
  ChessBoardPlayerText *playerTextLeft;
  ChessBoardPlayerText *playerTextRight;
  ChessBoardBox* getBoxAtPosition(int positionX, int positionY);
  ChessBoardBox* getBoxUnderMouse();
  void setColorForBoxes();
  void CleanScene();
  ChessBoard* chessBoard;
  ChessBoardHistory* history;
  void Refresh();
  void RefreshAfterPromotion();
public slots:
  void promotionSelected(int positionX, int positionY);
  void validMoves(int positionX, int positionY);
  void clearMoves();
  void setNewPosition(int positionX, int positionY);
};

#endif // CHESSBOARDSCENE_H
