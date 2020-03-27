#include "ChessBoard.h"
#include "Figures/FigureKing.h"
#include "Figures/FigureBishop.h"
#include "Figures/FigureKnight.h"
#include "Figures/FigurePawn.h"
#include "Figures/FigureQueen.h"
#include "Figures/FigureRook.h"
#include <QGraphicsScene>
#include "QtMath"
#include "QCursor"

ChessBoard::ChessBoard()
{
  m_panelLeft = NULL;
  m_panelRight = NULL;
  m_playerTextLeft = NULL;
  m_playerTextRight = NULL;
  Reset();
}

void ChessBoard::CleanScene()
{
  m_boxes.clear();
  m_figures.clear();
  if (m_panelLeft)
    delete m_panelLeft;
  if (m_panelRight)
    delete m_panelRight;
  m_panelLeft = NULL;
  m_panelRight = NULL;
  m_availableMoves.clear();
  m_availableStrikeMoves.clear();
  m_enemyAvailableMoves.clear();
  m_enemyAvailableStrikeMoves.clear();
  m_promotionFigures.clear();
  m_promotionActive= false;
  if (m_playerTextLeft)
    delete m_playerTextLeft;
  if (m_playerTextRight)
    delete m_playerTextRight;
  m_playerTextLeft = NULL;
  m_playerTextRight = NULL;
  m_endOfGame = false;
}

void ChessBoard::Reset()
{
  CleanScene();
  FigureBase * figureBase;
  ChessBoardBox *box;
  for(int y = 0; y < 8; y++) {
      for(int x = 0; x < 8; x++)
      {
          box = new ChessBoardBox(x,y);
          box->m_bHasFigure = false;

          if (x <= 1 || x >=6)
          {
              box->m_bHasFigure = true;
          if (x ==0 )
          {
              if (y == 0 || y == 7)
                figureBase = new FigureRook(true,FigureType::Alive, x,y);
              if (y==1 || y== 6)
                figureBase = new FigureKnight(true,FigureType::Alive, x,y);
              if (y==2 || y==5)
                figureBase = new FigureBishop(true,FigureType::Alive, x,y);
              if (y ==3)
                figureBase = new FigureQueen(true,FigureType::Alive,x,y);
              if (y==4)
                figureBase = new FigureKing(true,FigureType::Alive,x,y);
          }
          else if (x == 1)
          {
              figureBase = new FigurePawn(true,FigureType::Alive,x,y);
          }
          else if (x == 6)
          {
              figureBase = new FigurePawn(false,FigureType::Alive,x,y);
          }
          else if (x == 7)
          {
              if (y == 0 || y == 7)
                figureBase = new FigureRook(false,FigureType::Alive, x,y);
              if (y==1 || y== 6)
                figureBase = new FigureKnight(false,FigureType::Alive, x,y);
              if (y==2 || y==5)
                figureBase = new FigureBishop(false,FigureType::Alive, x,y);
              if (y ==3)
                figureBase = new FigureQueen(false,FigureType::Alive,x,y);
              if (y==4)
                figureBase = new FigureKing(false,FigureType::Alive,x,y);

          }
          figureBase->setPos(box->pos());
          m_figures.append(figureBase);
          QObject::connect(figureBase, &FigureBase::figureSelected,
                               this, &ChessBoard::validMoves);
          QObject::connect(figureBase, &FigureBase::figureDeselected,
                               this, &ChessBoard::clearMoves);
          QObject::connect(figureBase, &FigureBase::figureMoved,
                               this, &ChessBoard::setNewPosition);
          }

          m_boxes.append(box);
      }
  }
  m_panelLeft = new ChessBoardSidePanel();
  m_panelRight = new ChessBoardSidePanel(false);
  m_promotion = new ChessBoardPromotion();
  for (int i =0 ; i <8; ++i)
    {
  addPromotionFigure( new FigureQueen(true,FigureType::Promotion, -2,-1));
  addPromotionFigure( new FigureBishop(true,FigureType::Promotion, -2,-2));
  addPromotionFigure( new FigureKnight(true,FigureType::Promotion, -2,-3));
  addPromotionFigure( new FigureRook(true,FigureType::Promotion, -2,-4));
  addPromotionFigure(new FigureQueen(false,FigureType::Promotion, -3,-1));
  addPromotionFigure(new FigureBishop(false,FigureType::Promotion, -3,-2));
  addPromotionFigure(new FigureKnight(false,FigureType::Promotion, -3,-3));
  addPromotionFigure(new FigureRook(false,FigureType::Promotion, -3,-4));
    }

  m_playerTextLeft = new ChessBoardPlayerText(true);
  m_playerTextRight = new ChessBoardPlayerText(false);
}

void ChessBoard::addPromotionFigure(FigureBase *promotionFigure)
{
  int x = 450;
  int y =250;
  if (dynamic_cast<FigureQueen*>(promotionFigure))
   x= 300;
  else if (dynamic_cast<FigureBishop*>(promotionFigure))
    x = 350;
  else if (dynamic_cast<FigureKnight*>(promotionFigure))
    x = 400;
  else if (dynamic_cast<FigureRook*>(promotionFigure))
    x = 450;
  promotionFigure->setPos(x,y);
  promotionFigure->hide();
  QObject::connect(promotionFigure, &FigureBase::figureSelected,
                       this, &ChessBoard::validMoves);
  m_promotionFigures.append(promotionFigure);
}

void ChessBoard::setNewPosition(int positionX, int positionY)
{
  if (m_endOfGame)
    return;
  FigureBase* figure = getFigureAtPosition(positionX, positionY);
      if (figure != NULL)
        {
          ChessBoardBox *box = getBoxUnderMouse();
          ChessBoardBox *boxPrv = getBoxAtPosition(positionX,positionY);
              if (box != NULL)
                {
                  QPair<int,int> xyPos =QPair<int,int>(box->PositionX,box->PositionY);
                  bool validMove = false;
                  for (int l=0; l< m_availableMoves.count();l++)
                    {
                      if (m_availableMoves.at(l) == xyPos)
                        validMove = true;
                    }
                  bool validStrike = false;
                  for (int l=0; l< m_availableStrikeMoves.count();l++)
                    {
                      if (m_availableStrikeMoves.at(l) == xyPos)
                        validStrike = true;
                    }
                  FigurePawn * pawn = dynamic_cast<FigurePawn*>(figure);
                  if (validMove)
                     {

                        FigureKing * king = dynamic_cast<FigureKing*>(figure);
                       //castling
                       if (king && (figure->m_positionX ==0 ||figure->m_positionX ==7) && qFabs(figure->m_positionY -box->PositionY) == 2 && figure->m_positionY == 4)
                         {
                           figure->setPosition(box->pos(),box->PositionX,box->PositionY);

                           box->m_bHasFigure = true;
                               if (boxPrv!=NULL)
                                  boxPrv->m_bHasFigure = false;
                           if (figure->m_positionY == 2)
                           {
                               FigureBase * castle = getFigureAtPosition(figure->m_positionX,0);
                               castle->setPosition(getBoxAtPosition(figure->m_positionX,3)->pos(),figure->m_positionX,3);
                               getBoxAtPosition(figure->m_positionX,0)->m_bHasFigure = false;
                               getBoxAtPosition(figure->m_positionX,3)->m_bHasFigure = true;
                           }
                           else
                             {
                               FigureBase * castle = getFigureAtPosition(figure->m_positionX,7);
                               castle->setPosition(getBoxAtPosition(figure->m_positionX,5)->pos(),figure->m_positionX,5);
                               getBoxAtPosition(figure->m_positionX,7)->m_bHasFigure = false;
                               getBoxAtPosition(figure->m_positionX,5)->m_bHasFigure = true;
                             }

                         }
                       else if(pawn && qFabs(pawn->m_positionX - box->PositionX) == 2 )
                         {
                           figure->setPosition(box->pos(),box->PositionX,box->PositionY);

                           box->m_bHasFigure = true;
                               if (boxPrv!=NULL)
                                  boxPrv->m_bHasFigure = false;
                           if (pawn->m_leftSide)
                             {
                               getBoxAtPosition(pawn->m_positionX -1,pawn->m_positionY)->m_bHasFigure = true;
                             }
                             else {
                               getBoxAtPosition(pawn->m_positionX +1,pawn->m_positionY)->m_bHasFigure = true;
                             }
                         }
                       else
                         {
                           figure->setPosition(box->pos(),box->PositionX,box->PositionY);

                       box->m_bHasFigure = true;
                           if (boxPrv!=NULL)
                              boxPrv->m_bHasFigure = false;

                         }
                       figure->m_leftSideTurn = !figure->m_leftSideTurn;
                     }
                  else if (validStrike)
                    {
                      FigureBase * killedFigure = getFigureAtPosition(box->PositionX,box->PositionY);
                      //elPassa
                      if (!killedFigure)
                        {
                          if(figure->m_leftSide)
                            {
                            killedFigure =  getFigureAtPosition(box->PositionX-1,box->PositionY);
                            getBoxAtPosition(box->PositionX-1,box->PositionY)->m_bHasFigure = false;
                            }
                          else
                            {
                            killedFigure =  getFigureAtPosition(box->PositionX+1,box->PositionY);
                            getBoxAtPosition(box->PositionX+1,box->PositionY)->m_bHasFigure = false;
                            }
                        }
                      if (killedFigure->m_leftSide)
                        {
                          killedFigure->setPosition(m_panelLeft->GetFreeSlotPos(),-1,-1);
                        m_panelLeft->SetSlotPos();
                        }
                      else
                        {
                          killedFigure->setPosition(m_panelRight->GetFreeSlotPos(),-1,-1);
                        m_panelRight->SetSlotPos();
                        }
                      killedFigure->m_type = FigureType::Killed;
                      killedFigure->setAcceptedMouseButtons(Qt::NoButton);
                      killedFigure->setCursor(Qt::ArrowCursor);
                      figure->setPosition(box->pos(),box->PositionX,box->PositionY);

                      box->m_bHasFigure = true;
                          if (boxPrv!=NULL)
                             boxPrv->m_bHasFigure = false;
                          figure->m_leftSideTurn = !figure->m_leftSideTurn;

                    }
                  else
                    {
                          if (boxPrv != NULL)
                          {
                             figure->setPos(boxPrv->pos());
                        }

                    }
                  if (validMove || validStrike)
                    {
                      //remove el Passa
                      int x=5;
                      if (!figure->m_leftSide)
                        x =2;
                          for (int y=0; y<8; y++)
                            {
                              if (getFigureAtPosition(x,y) == NULL)
                                getBoxAtPosition(x,y)->m_bHasFigure=false;
                            }
                       //Promotion

                          if(pawn && ((pawn->m_leftSide && box->PositionX ==7) || (!pawn->m_leftSide && box->PositionX ==0)))
                            {
                              m_promotion->show();
                              for (int i=0;i<m_promotionFigures.count(); i++)
                                {
                                  if (m_promotionFigures.at(i)->m_leftSide == pawn->m_leftSide)
                                    m_promotionFigures.at(i)->show();
                                }
                              m_promotionActive = true;
                              figure->m_leftSideTurn = !figure->m_leftSideTurn;

                            }

                          getEnemyAvailableMoves(figure->m_leftSide);
                          if(checkMat(figure->m_leftSide))
                            {
                              setWinner(!figure->m_leftSide);
                            }
                    }



                }
        }


}

void ChessBoard::setAllValidMoves(int positionX, int positionY, bool enemy)
{

  FigureBase* figure = getFigureAtPosition(positionX, positionY);
      if (figure != NULL)
        {
          bool bLeftUp = true;
          bool bUp = true;
          bool bRightUp = true;
          bool bLeft = true;
          bool bRight = true;
          bool bLeftDown = true;
          bool bDown = true;
          bool bRightDown = true;
          for (int x=positionX;x<8;++x)
          {
              for (int y=positionY; y<8;++y)
              {
                  if (x == positionX && y == positionY)
                    continue;
                  if (!bDown && x== positionX)
                    continue;
                  if (!bRight && y == positionY)
                    continue;
                  if (!bRightDown && x!= positionX && y!=positionY)
                    continue;
                  if (!validateMoveInOneDirection(figure,x,y,enemy))
                    {
                      if (x== positionX)
                        bDown = false;
                      else if (y== positionY)
                        bRight = false;
                      else bRightDown = false;
                    }
              }
          }
          for (int x=positionX;x<8;++x)
          {
              for (int y=positionY-1; y>=0;--y)
              {
                  if (!bUp && x== positionX)
                    continue;
                  if (!bRightUp && x!= positionX)
                    continue;
                  if (!validateMoveInOneDirection(figure,x,y,enemy))
                    {
                      if (x== positionX)
                        bUp = false;
                      else
                        bRightUp = false;
                    }
              }
          }
          for (int x=positionX-1;x>=0;--x)
          {
              for (int y=positionY; y<8;++y)
              {
                  if (!bLeft && y== positionY)
                    continue;
                  if (!bLeftDown && y!=positionY)
                    continue;
                  if (!validateMoveInOneDirection(figure,x,y,enemy))
                    {
                      if (y== positionY)
                        bLeft = false;
                      else
                        bLeftDown = false;
                    }
              }
          }
          for (int x=positionX-1;x>=0;--x)
          {
              for (int y=positionY-1; y>=0;--y)
              {
                  if (!bLeftUp)
                    continue;
                  if (!validateMoveInOneDirection(figure,x,y,enemy))
                    {
                        bLeftUp = false;
                    }
              }
          }

       if (!enemy)
         {
       //Special moves
       FigureKing * king = dynamic_cast<FigureKing*>(figure);
       if (king)
         {
           //castling
           if (figure->m_firstMove)
             {
               int xPosOfRock =0;
               if (!figure->m_leftSide)
                 xPosOfRock = 7;
               FigureBase* rock = getFigureAtPosition(xPosOfRock,0);
               if (rock != NULL && rock->m_firstMove)
                 {
                   if (getFigureAtPosition(xPosOfRock,1) == NULL && getFigureAtPosition(xPosOfRock,2) == NULL && getFigureAtPosition(xPosOfRock,3) == NULL)
                     {
                       bool enamyAttack = false;
                        for (int i =0; i < m_enemyAvailableMoves.count();i++)
                          {
                            if (m_enemyAvailableMoves.at(i) == QPair<int,int>(xPosOfRock,2) || m_enemyAvailableMoves.at(i) == QPair<int,int>(xPosOfRock,3) )
                              {
                                enamyAttack = true;
                                break;
                              }
                          }

                        for (int i =0; i < m_enemyAvailableStrikeMoves.count();i++)
                          {
                            if (m_enemyAvailableStrikeMoves.at(i) == QPair<int,int>(king->m_positionX,king->m_positionY))
                              {
                                enamyAttack = true;
                                break;
                              }
                          }
                        if (!enamyAttack)
                        m_availableMoves.append(QPair<int,int>(xPosOfRock,2));
                     }

                 }
                  rock = getFigureAtPosition(xPosOfRock,7);
                              if (rock != NULL && rock->m_firstMove)
                                {
                                  if (getFigureAtPosition(xPosOfRock,5) == NULL && getFigureAtPosition(xPosOfRock,6) == NULL)
                                    {
                                      bool enamyAttack = false;
                                       for (int i =0; i < m_enemyAvailableMoves.count();i++)
                                         {
                                           if (m_enemyAvailableMoves.at(i) == QPair<int,int>(xPosOfRock,5) || m_enemyAvailableMoves.at(i) == QPair<int,int>(xPosOfRock,6) ||m_enemyAvailableMoves.at(i)== QPair<int,int>(king->m_positionX,king->m_positionY))
                                             {
                                               enamyAttack = true;
                                               break;
                                             }
                                         }
                                       for (int i =0; i < m_enemyAvailableStrikeMoves.count();i++)
                                         {
                                           if (m_enemyAvailableStrikeMoves.at(i) == QPair<int,int>(king->m_positionX,king->m_positionY))
                                             {
                                               enamyAttack = true;
                                               break;
                                             }
                                         }
                                       if (!enamyAttack)
                                       m_availableMoves.append(QPair<int,int>(xPosOfRock,6));
                                    }

                                }

             }
           //dont alow to move on enamy attack positions
           for (int i =0; i < m_enemyAvailableMoves.count(); i++)
             {
               for (int j=0; j < m_availableMoves.count();j++)
                 {
                   if( m_availableMoves.at(j) == m_enemyAvailableMoves.at(i))
                     m_availableMoves.remove(j);
                 }
             }
           for (int i =0; i < m_enemyAvailableStrikeMoves.count(); i++)
             {
               for (int j=0; j < m_availableStrikeMoves.count();j++)
                 {
                   if( m_availableStrikeMoves.at(j) == m_enemyAvailableStrikeMoves.at(i))
                     m_availableStrikeMoves.remove(j);
                 }
             }
         }
         }
    }
}



void ChessBoard::validMoves(int positionX, int positionY)
{
  if (m_endOfGame)
    return;
  if (m_promotionActive)
    {
      for (int i =0; i< m_promotionFigures.count();i++)
        {
          if (m_promotionFigures.at(i)->m_positionX == positionX && m_promotionFigures.at(i)->m_positionY==positionY)
            {
              int x =0;
              if (m_promotionFigures.at(i)->m_leftSide)
                x =7;
              for (int y=0;y<8;y++)
                {
                  FigurePawn * pawn = dynamic_cast<FigurePawn*>(getFigureAtPosition(x,y));
                  if (pawn)
                    {
                      for (int j=0; j < m_figures.count(); ++j)
                        {
                          if (m_figures.at(j) == pawn)
                            {
                              m_figures.removeAt(j);
                              m_promotionFigures.at(i)->setPosition(pawn->pos(),pawn->m_positionX,pawn->m_positionY);
                              m_promotionFigures.at(i)->m_type=FigureType::Alive;
                              m_figures.append(m_promotionFigures.at(i));
                              QObject::connect(m_promotionFigures.at(i), &FigureBase::figureDeselected,
                                                   this, &ChessBoard::clearMoves);
                              QObject::connect(m_promotionFigures.at(i), &FigureBase::figureMoved,
                                                   this, &ChessBoard::setNewPosition);
                              m_promotionFigures.removeAt(i);
                            }
                        }

                      m_promotionActive = false;

                      m_promotion->hide();
                      for (int z=0;z<m_promotionFigures.count(); z++)
                        {
                          if (m_promotionFigures.at(z)->m_leftSide == pawn->m_leftSide)
                            m_promotionFigures.at(z)->hide();
                        }
                      pawn->m_leftSideTurn = !pawn->m_leftSideTurn;
                      delete pawn;
                      break;
                    }
                }
              return ;
            }
        }
      return;
    }
  FigureBase* figure = getFigureAtPosition(positionX,positionY);
  if (figure)
      getEnemyAvailableMoves(figure->m_leftSide);
  m_availableMoves.clear();
  m_availableStrikeMoves.clear();
  setAllValidMoves(positionX,positionY);
  setColorForBoxes();

}

void ChessBoard::setColorForBoxes()
{
  for (int i=0; i < m_availableMoves.count(); i++)
    getBoxAtPosition(m_availableMoves.at(i).first,m_availableMoves.at(i).second)->setBrush(Qt::green);
  for (int i=0; i< m_availableStrikeMoves.count(); i++)
    getBoxAtPosition(m_availableStrikeMoves.at(i).first,m_availableStrikeMoves.at(i).second)->setBrush(Qt::red);

}

bool ChessBoard::validateMoveInOneDirection(FigureBase* figure,int xPos, int yPos, bool enemy)
{
  ChessBoardBox* box = getBoxAtPosition(xPos,yPos);
  if (box!= NULL)
    {
      if (figure->ValidateStrikePosition(box->PositionX, box->PositionY) && box->m_bHasFigure)
        {
          if (enemy)
            m_enemyAvailableStrikeMoves.append(QPair<int,int>(xPos,yPos));
          else if (getFigureAtPosition(box->PositionX,box->PositionY) && getFigureAtPosition(box->PositionX,box->PositionY)->m_leftSide != figure->m_leftSide)
            m_availableStrikeMoves.append(QPair<int,int>(xPos,yPos));
          else if (!getFigureAtPosition(box->PositionX,box->PositionY) && ((figure->m_leftSide && xPos == 5) || (!figure->m_leftSide && xPos == 2)))
            m_availableStrikeMoves.append(QPair<int,int>(xPos,yPos));
        }
        if (figure->ValidatePosition(box->PositionX, box->PositionY)
            && !box->m_bHasFigure)
        {
            if (enemy)
              m_enemyAvailableMoves.append(QPair<int,int>(xPos,yPos));
            else
              m_availableMoves.append(QPair<int,int>(xPos,yPos));
            return true;
          }
        else if (figure->ValidatePosition(box->PositionX, box->PositionY) && box->m_bHasFigure && figure->m_stopOnOtherFigure)
          return false;
    }
  return true;
}


void ChessBoard::clearMoves()
{
  for (int j=0;j<m_boxes.count();++j)
  {
     m_boxes.at(j)->ResetBrush();
  }
}

ChessBoardBox* ChessBoard::getBoxAtPosition(int positionX, int positionY)
{
  for (int j=0; j< m_boxes.count(); ++j)
    {
        if (m_boxes.at(j)->PositionX == positionX && m_boxes.at(j)->PositionY == positionY)
          return m_boxes.at(j);
    }
  return NULL;
}

ChessBoardBox* ChessBoard::getBoxUnderMouse()
{
  for (int j=0; j< m_boxes.count(); ++j)
    {
        if (m_boxes.at(j)->isUnderMouse())
          return m_boxes.at(j);
    }
  return NULL;
}

FigureBase* ChessBoard::getFigureAtPosition(int positionX, int positionY)
{
  for (int j=0; j< m_figures.count(); ++j)
    {
        if (m_figures.at(j)->m_positionX == positionX && m_figures.at(j)->m_positionY == positionY)
          return m_figures.at(j);
    }
  return NULL;
}

bool ChessBoard::checkMat(bool leftSide)
{
   for (int i=0; i< m_figures.count();++i)
     {
       FigureKing *king = dynamic_cast<FigureKing*>(m_figures.at(i));
       if(king && king->m_leftSide == leftSide)
        {
           for (int j=0; j< m_enemyAvailableStrikeMoves.count();++j)
             {
               if (king->m_positionX == m_enemyAvailableStrikeMoves.at(j).first && king->m_positionY == m_enemyAvailableStrikeMoves.at(j).second)
                 return true;
             }
         break;
        }
     }
   return false;
}

void ChessBoard::getEnemyAvailableMoves(bool leftSide)
{
  m_enemyAvailableMoves.clear();
  m_enemyAvailableStrikeMoves.clear();
  for (int i=0; i< m_figures.count();++i)
    {
      if (m_figures.at(i)->m_leftSide != leftSide)
          setAllValidMoves(m_figures.at(i)->m_positionX,m_figures.at(i)->m_positionY,true);
    }
}

void ChessBoard::setWinner(bool leftSide)
{
  if (leftSide)
  {
    m_playerTextLeft->setPlainText("Winner");
    m_playerTextLeft->adjustSize();
  }
  else {
      m_playerTextRight->setPlainText("Winner");
      m_playerTextLeft->adjustSize();
    }
  m_endOfGame = true;
  for (int i=0; i< m_figures.count();++i)
    m_figures.at(i)->m_type = FigureType::Killed;
}
