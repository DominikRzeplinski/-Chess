#include "ChessBoardScene.h"
#include "QCursor"
#include "ChessBoardMove.h"

ChessBoardScene::ChessBoardScene(QObject *parent): QGraphicsScene(parent)
{
  setSceneRect(0,0,800,600);
  chessBoard = new ChessBoard();
  chessBoard->Reset();
  panelLeft = NULL;
  panelRight = NULL;
  playerTextLeft = NULL;
  playerTextRight = NULL;
  promotion = NULL;
  history = NULL;
  Reset();

}

void ChessBoardScene::cleanScene()
{
  boxes.clear();
  figureViews.clear();
  if (panelLeft)
    delete panelLeft;
  if (panelRight)
    delete panelRight;
  panelLeft = NULL;
  panelRight = NULL;
  promotionFigureViews.clear();
  if (playerTextLeft)
    delete playerTextLeft;
  if (playerTextRight)
    delete playerTextRight;
  if (promotion)
    delete promotion;
  promotion = NULL;
  playerTextLeft = NULL;
  playerTextRight = NULL;
  if (history)
    delete history;
  history = NULL;
  clear();
}

void ChessBoardScene::loadGame(QString fileName)
{
  Reset();
  history->loadGame(fileName);
  for (int i=0;i< history->getChessBoardHistory()->count();++i)
    {
      chessBoard->validMoves(history->getChessBoardHistory()->at(i).getPositionX(),history->getChessBoardHistory()->at(i).getPositionY());
      chessBoard->setNewPosition(history->getChessBoardHistory()->at(i).getPositionX(),history->getChessBoardHistory()->at(i).getPositionY(),history->getChessBoardHistory()->at(i).getNewPositionX(),history->getChessBoardHistory()->at(i).getNewPositionY());
      if (history->getChessBoardHistory()->at(i).getPromotion())
        chessBoard->promotionSelected(history->getChessBoardHistory()->at(i).getPositionX(),history->getChessBoardHistory()->at(i).getPositionY());


    }
  refreshAfterPromotion();
  refresh();

}

void ChessBoardScene::saveGame(QString fileName)
{
  history->saveGame(fileName);
}

void ChessBoardScene::Reset()
{
  cleanScene();
  chessBoard->Reset();

  ChessBoardBox *box;
  //Creste boxes for board
  for(int y = 0; y < 8; y++) {
      for(int x = 0; x < 8; x++)
        {
          box = new ChessBoardBox(x,y);
          boxes.append(box);
          addItem(box);
        }
    }

  FigureView * figureView;
  //Create Views for figures
  for(int i=0; i< chessBoard->getFiguresCount();++i)
    {
      figureView = new FigureView(chessBoard->getFigureAt(i));
      figureView->setPos(getBoxAtPosition(chessBoard->getFigureAt(i)->getPositionX(),chessBoard->getFigureAt(i)->getPositionY())->pos());
      figureViews.append(figureView);
      addItem(figureView);
      QObject::connect(figureView, &FigureView::figureSelected,
                       this, &ChessBoardScene::validMoves);
      QObject::connect(figureView, &FigureView::figureDeselected,
                       this, &ChessBoardScene::clearMoves);
      QObject::connect(figureView, &FigureView::figureMoved,
                       this, &ChessBoardScene::setNewPosition);
    }

  //Create side panles
  panelLeft = new ChessBoardSidePanel();
  addItem(panelLeft);
  panelRight = new ChessBoardSidePanel(false);
  addItem(panelRight);
  promotion = new ChessBoardPromotion();
  addItem(promotion);

  //Create Views for promotion figures
  for (int i =0 ; i < chessBoard->getpromotionFiguresCount(); ++i)
    {
      figureView = new FigureView(chessBoard->getpromotionFiguresAt(i));
      figureView->setPos(250 - chessBoard->getpromotionFiguresAt(i)->getPositionY() * 50,200 - chessBoard->getpromotionFiguresAt(i)->getPositionX() * 50 );
      figureView->hide();
      promotionFigureViews.append(figureView);
      addItem(figureView);
      QObject::connect(figureView, &FigureView::figurePromotionSelected,
                       this, &ChessBoardScene::promotionSelected);
      QObject::connect(figureView, &FigureView::figureSelected,
                       this, &ChessBoardScene::validMoves);
      QObject::connect(figureView, &FigureView::figureDeselected,
                       this, &ChessBoardScene::clearMoves);
      QObject::connect(figureView, &FigureView::figureMoved,
                       this, &ChessBoardScene::setNewPosition);
    }

  //Create text displays for players
  playerTextLeft = new ChessBoardPlayerText(true);
  addItem(playerTextLeft);
  playerTextRight = new ChessBoardPlayerText(false);
  addItem(playerTextRight);
  history = new ChessBoardHistory();
}

ChessBoardBox* ChessBoardScene::getBoxAtPosition(int positionX, int positionY)
{
  for (int j=0; j< boxes.count(); ++j)
    {
      if (boxes.at(j)->positionX == positionX && boxes.at(j)->positionY == positionY)
        return boxes.at(j);
    }
  return NULL;
}

ChessBoardBox* ChessBoardScene::getBoxUnderMouse()
{
  for (int j=0; j< boxes.count(); ++j)
    {
      if (boxes.at(j)->isUnderMouse())
        return boxes.at(j);
    }
  return NULL;
}

void ChessBoardScene::setNewPosition(int positionX, int positionY)
{
  //get coordinates of new position
  ChessBoardBox *box = getBoxUnderMouse();

  //set new position of selected figure
  if (box)
    {
      if (chessBoard->setNewPosition(positionX,positionY,box->positionX,box->positionY))
        history->addMove(ChessBoardMove(positionX,positionY,box->positionX,box->positionY));
    }

  //refresh scene
  refresh();

}

void ChessBoardScene::refresh()
{
  if (chessBoard->isEndOfGame())
    {
      if (chessBoard->getLeftSideWinner())
        {
          playerTextLeft->setPlainText("Winner");
          playerTextLeft->adjustSize();
        }
      else {
          playerTextRight->setPlainText("Winner");
          playerTextLeft->adjustSize();
        }
      return;
    }
  else if (chessBoard->getCheckMate())
    {
      if (figureViews.at(0)->figureBase->leftSideTurn)
        {
          playerTextLeft->setPlainText("Check! Protect yours king");
          playerTextRight->setPlainText("");
          playerTextLeft->adjustSize();
        }
      else
        {
          playerTextRight->setPlainText("Check! Protect yours king");
          playerTextLeft->setPlainText("");
          playerTextRight->adjustSize();
        }
    }
  else {
      playerTextLeft->setPlainText("");
      playerTextRight->setPlainText("");

    }
  panelLeft->resetSlot();
  panelRight->resetSlot();
  for (int i=0; i< figureViews.count(); i++)
    {
      if (figureViews.at(i)->figureBase->getType() == FigureType::Alive)
        {
          figureViews.at(i)->setPos(getBoxAtPosition(figureViews.at(i)->figureBase->getPositionX(),figureViews.at(i)->figureBase->getPositionY())->pos());
          figureViews.at(i)->show();
        }
      else if (figureViews.at(i)->figureBase->getType() == FigureType::Killed)
        {
          figureViews.at(i)->setAcceptedMouseButtons(Qt::NoButton);
          figureViews.at(i)->setCursor(Qt::ArrowCursor);
          if (figureViews.at(i)->figureBase->isLeftSide())
            {
              figureViews.at(i)->setPos(panelLeft->getFreeSlotPos());
              panelLeft->setSlotPos();
            }
          else
            {
              figureViews.at(i)->setPos(panelRight->getFreeSlotPos());
              panelRight->setSlotPos();
            }
          figureViews.at(i)->show();
        }
      else
        figureViews.at(i)->hide();
    }
  if (chessBoard->getPromotionActive())
    {
      promotion->show();
      for (int i=0;i<promotionFigureViews.count(); i++)
        {
          if (promotionFigureViews.at(i)->figureBase->canSelect())
            promotionFigureViews.at(i)->show();
        }
    }
  else
    {
      promotion->hide();
      for (int i=0;i<promotionFigureViews.count(); i++)
        promotionFigureViews.at(i)->hide();
    }
}

void ChessBoardScene::refreshAfterPromotion()
{
  for (int i =0; i< promotionFigureViews.count(); ++i)
    {
      if (promotionFigureViews.at(i)->figureBase->getType() == FigureType::Alive)
        {
          figureViews.append(promotionFigureViews.at(i));
          QObject::disconnect(promotionFigureViews.at(i), &FigureView::figurePromotionSelected,
                              this, &ChessBoardScene::promotionSelected);
          promotionFigureViews.removeAt(i);
        }
    }
}

void ChessBoardScene::promotionSelected(int positionX, int positionY)
{
  if (!chessBoard->promotionSelected(positionX,positionY))
    return;
  refreshAfterPromotion();
  history->addMove(ChessBoardMove(positionX,positionY,0,0,true));

  refresh();
}

void ChessBoardScene::validMoves(int positionX, int positionY)
{
  chessBoard->validMoves(positionX,positionY);
  setColorForBoxes();

}

void ChessBoardScene::setColorForBoxes()
{
  QVector<QPair<int,int>> availableMoves = chessBoard->getAvailableMoves();
  for (int i=0; i < availableMoves.count(); i++)
    getBoxAtPosition(availableMoves.at(i).first,availableMoves.at(i).second)->setBrush(Qt::green);
  QVector<QPair<int,int>> availableStrikeMoves = chessBoard->getAvailableStrikeMoves();
  for (int i=0; i< availableStrikeMoves.count(); i++)
    getBoxAtPosition(availableStrikeMoves.at(i).first,availableStrikeMoves.at(i).second)->setBrush(Qt::red);

}


void ChessBoardScene::clearMoves()
{
  for (int j=0;j<boxes.count();++j)
    {
      boxes.at(j)->ResetBrush();
    }
}
