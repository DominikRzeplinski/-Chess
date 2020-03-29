#include "ChessBoardScene.h"
#include "QCursor"

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
  Reset();

}

void ChessBoardScene::CleanScene()
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
  clear();
}

void ChessBoardScene::Reset()
{
  CleanScene();
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
  for(int i=0; i< chessBoard->m_figures.count();++i)
    {
      figureView = new FigureView(chessBoard->m_figures.at(i));
      figureView->setPos(getBoxAtPosition(chessBoard->m_figures.at(i)->m_positionX,chessBoard->m_figures.at(i)->m_positionY)->pos());
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
  for (int i =0 ; i < chessBoard->m_promotionFigures.count(); ++i)
    {
      figureView = new FigureView(chessBoard->m_promotionFigures.at(i));
      figureView->setPos(250 - chessBoard->m_promotionFigures.at(i)->m_positionY * 50,200 - chessBoard->m_promotionFigures.at(i)->m_positionX * 50 );
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
}

ChessBoardBox* ChessBoardScene::getBoxAtPosition(int positionX, int positionY)
{
  for (int j=0; j< boxes.count(); ++j)
    {
        if (boxes.at(j)->PositionX == positionX && boxes.at(j)->PositionY == positionY)
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
    chessBoard->setNewPosition(positionX,positionY,box->PositionX,box->PositionY);

  //refresh scene
  Refresh();

}

void ChessBoardScene::Refresh()
{
  if (chessBoard->m_endOfGame)
    {
      if (chessBoard->leftSideWinner)
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
  else if (chessBoard->m_checkmate)
    {
      if (figureViews.at(0)->figureBase->m_leftSideTurn)
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
  panelLeft->ResetSlot();
  panelRight->ResetSlot();
  for (int i=0; i< figureViews.count(); i++)
    {
      if (figureViews.at(i)->figureBase->m_type == FigureType::Alive)
        figureViews.at(i)->setPos(getBoxAtPosition(figureViews.at(i)->figureBase->m_positionX,figureViews.at(i)->figureBase->m_positionY)->pos());
      else if (figureViews.at(i)->figureBase->m_type == FigureType::Killed)
        {
          figureViews.at(i)->setAcceptedMouseButtons(Qt::NoButton);
          figureViews.at(i)->setCursor(Qt::ArrowCursor);
          if (figureViews.at(i)->figureBase->m_leftSide)
            {
          figureViews.at(i)->setPos(panelLeft->GetFreeSlotPos());
          panelLeft->SetSlotPos();
            }
          else
            {
              figureViews.at(i)->setPos(panelRight->GetFreeSlotPos());
              panelRight->SetSlotPos();
            }
        }
      else
        figureViews.at(i)->hide();
    }
  if (chessBoard->m_promotionActive)
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

void ChessBoardScene::promotionSelected(int positionX, int positionY)
{
  chessBoard->promotionSelected(positionX,positionY);

  for (int i =0; i< promotionFigureViews.count(); ++i)
    {
      if (promotionFigureViews.at(i)->figureBase->m_type == FigureType::Alive)
        {
          figureViews.append(promotionFigureViews.at(i));
          QObject::disconnect(promotionFigureViews.at(i), &FigureView::figurePromotionSelected,
                               this, &ChessBoardScene::promotionSelected);
          promotionFigureViews.removeAt(i);
        }
    }
  Refresh();
}

void ChessBoardScene::validMoves(int positionX, int positionY)
{
  chessBoard->validMoves(positionX,positionY);
  setColorForBoxes();

}

void ChessBoardScene::setColorForBoxes()
{
  for (int i=0; i < chessBoard->m_availableMoves.count(); i++)
    getBoxAtPosition(chessBoard->m_availableMoves.at(i).first,chessBoard->m_availableMoves.at(i).second)->setBrush(Qt::green);
  for (int i=0; i< chessBoard->m_availableStrikeMoves.count(); i++)
    getBoxAtPosition(chessBoard->m_availableStrikeMoves.at(i).first,chessBoard->m_availableStrikeMoves.at(i).second)->setBrush(Qt::red);

}


void ChessBoardScene::clearMoves()
{
  for (int j=0;j<boxes.count();++j)
  {
     boxes.at(j)->ResetBrush();
  }
}
