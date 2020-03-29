#include "ChessBoard.h"
#include "Figures/FigureKing.h"
#include "Figures/FigureBishop.h"
#include "Figures/FigureKnight.h"
#include "Figures/FigurePawn.h"
#include "Figures/FigureQueen.h"
#include "Figures/FigureRook.h"
#include "QtMath"

ChessBoard::ChessBoard()
{
  figureElPassa = NULL;
  Reset();
}

void ChessBoard::CleanScene()
{
  m_figures.clear();
  m_availableMoves.clear();
  m_availableStrikeMoves.clear();
  m_enemyAvailableMoves.clear();
  m_enemyAvailableStrikeMoves.clear();
  m_promotionFigures.clear();
  m_promotionActive= false;
  m_endOfGame = false;
  if (figureElPassa)
    delete figureElPassa;
  figureElPassa = NULL;
  m_checkmate = false;
}

void ChessBoard::Reset()
{
  CleanScene();
  FigureBase * figureBase;
  for(int y = 0; y < 8; y++) {
      for(int x = 0; x < 8; x++)
        {

          if (x <= 1 || x >=6)
            {
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
              m_figures.append(figureBase);
            }
        }
    }
  for (int i =0 ; i <8; ++i)
    {
      m_promotionFigures.append( new FigureQueen(true,FigureType::Promotion, -1,-1));
      m_promotionFigures.append( new FigureBishop(true,FigureType::Promotion, -1,-2));
      m_promotionFigures.append( new FigureKnight(true,FigureType::Promotion, -1,-3));
      m_promotionFigures.append( new FigureRook(true,FigureType::Promotion, -1,-4));
      m_promotionFigures.append(new FigureQueen(false,FigureType::Promotion, -2,-1));
      m_promotionFigures.append(new FigureBishop(false,FigureType::Promotion, -2,-2));
      m_promotionFigures.append(new FigureKnight(false,FigureType::Promotion, -2,-3));
      m_promotionFigures.append(new FigureRook(false,FigureType::Promotion, -2,-4));
    }
}

bool ChessBoard::setNewPosition(int positionX, int positionY, int newPositionX, int newPositionY)
{
  bool valid = false;
  if (m_endOfGame)
    return valid;
  m_checkmate = false;
  FigureBase* figure = getFigureAtPosition(positionX, positionY);
  if (figure != NULL)
    {
      bool removeElpassa= true;
      QPair<int,int> xyPos =QPair<int,int>(newPositionX,newPositionY);
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
          if (king && (figure->m_positionX ==0 ||figure->m_positionX ==7) && qFabs(figure->m_positionY -newPositionY) == 2 && figure->m_positionY == 4)
            {
              figure->setPosition(newPositionX,newPositionY);

              if (figure->m_positionY == 2)
                {
                  FigureBase * castle = getFigureAtPosition(figure->m_positionX,0);
                  castle->setPosition(figure->m_positionX,3);
                }
              else
                {
                  FigureBase * castle = getFigureAtPosition(figure->m_positionX,7);
                  castle->setPosition(figure->m_positionX,5);
                }

            }
          else if(pawn && qFabs(pawn->m_positionX - newPositionX) == 2 )
            {
              figure->setPosition(newPositionX,newPositionY);
              if (pawn->m_leftSide)
                {
                  figureElPassa = new FigurePawn(pawn->m_leftSide,FigureType::Alive,pawn->m_positionX -1,pawn->m_positionY);
                }
              else {
                  figureElPassa = new FigurePawn(pawn->m_leftSide,FigureType::Alive,pawn->m_positionX +1,pawn->m_positionY);
                }
              removeElpassa = false;
            }
          else
            {
              figure->setPosition(newPositionX,newPositionY);


            }
          figure->m_leftSideTurn = !figure->m_leftSideTurn;
        }
      else if (validStrike)
        {
          FigureBase * killedFigure = getFigureAtPosition(newPositionX,newPositionY);
          //elPassa
          if (!killedFigure)
            {
              if(figure->m_leftSide)
                {
                  killedFigure =  getFigureAtPosition(newPositionX-1,newPositionY);
                }
              else
                {
                  killedFigure =  getFigureAtPosition(newPositionX+1,newPositionY);
                }
            }
          if (killedFigure->m_leftSide)
            {
              killedFigure->setPosition(-1,-1);
            }
          else
            {
              killedFigure->setPosition(-1,-1);
            }
          killedFigure->m_type = FigureType::Killed;
          figure->setPosition(newPositionX,newPositionY);

          figure->m_leftSideTurn = !figure->m_leftSideTurn;

        }
      if (validMove || validStrike)
        {
          valid = true;
          //remove el Passa
          if (removeElpassa)
            {
              delete figureElPassa;
              figureElPassa = NULL;
            }
          //Promotion

          if(pawn && ((pawn->m_leftSide && newPositionX ==7) || (!pawn->m_leftSide && newPositionX ==0)))
            {
              m_promotionActive = true;
              figure->m_leftSideTurn = !figure->m_leftSideTurn;

            }

          if(checkMat(figure->m_leftSide))
            setWinner(!figure->m_leftSide);

          if(checkCheckMat(figure->m_positionX,figure->m_positionY))
            m_checkmate = true;
        }



    }
  return valid;
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
                          for (int i =0; i < m_enemyAllValidStrikeMoves.count();i++)
                            {
                              if (m_enemyAllValidStrikeMoves.at(i) == QPair<int,int>(xPosOfRock,2) || m_enemyAllValidStrikeMoves.at(i) == QPair<int,int>(xPosOfRock,3) ||m_enemyAllValidStrikeMoves.at(i)== QPair<int,int>(king->m_positionX,king->m_positionY))
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
                          for (int i =0; i < m_enemyAllValidStrikeMoves.count();i++)
                            {
                              if (m_enemyAllValidStrikeMoves.at(i) == QPair<int,int>(xPosOfRock,5) || m_enemyAllValidStrikeMoves.at(i) == QPair<int,int>(xPosOfRock,6) ||m_enemyAllValidStrikeMoves.at(i)== QPair<int,int>(king->m_positionX,king->m_positionY))
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
              for (int i =0; i < m_enemyAllValidStrikeMoves.count(); i++)
                {
                  for (int j=0; j < m_availableMoves.count();j++)
                    {
                      if( m_availableMoves.at(j) == m_enemyAllValidStrikeMoves.at(i))
                        m_availableMoves.remove(j);
                    }
                }
            }
        }
    }
}

bool ChessBoard::promotionSelected(int positionX, int positionY)
{
  bool ret = false;
  if (!m_promotionActive)
    return false;

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
                  pawn->m_type = FigureType::Promotion;
                  pawn->setPosition(-1,-1);
                  for (int j=0; j < m_figures.count(); ++j)
                    {
                      if (m_figures.at(j) == pawn)
                        {
                          m_figures.removeAt(j);
                          m_promotionFigures.at(i)->setPosition(x,y);
                          m_promotionFigures.at(i)->m_type=FigureType::Alive;
                          m_figures.append(m_promotionFigures.at(i));
                          m_promotionFigures.removeAt(i);
                        }
                    }

                  m_promotionActive = false;

                  pawn->m_leftSideTurn = !pawn->m_leftSideTurn;
                  ret = true;
                  break;
                }
            }
          break;
        }
    }
  return ret;
}

void ChessBoard::validMoves(int positionX, int positionY)
{
  if (m_endOfGame)
    return;
  if (m_promotionActive)
    {
      m_availableMoves.clear();
      m_availableStrikeMoves.clear();
      return;
    }

  FigureBase* figure = getFigureAtPosition(positionX,positionY);
  if (figure)
    getEnemyAvailableMoves(figure->m_leftSide);
  m_availableMoves.clear();
  m_availableStrikeMoves.clear();
  setAllValidMoves(positionX,positionY);
}

bool ChessBoard::isElpassaPostion(int xPos, int yPos)
{
  if (!figureElPassa)
    return false;
  if (figureElPassa->m_positionX != xPos)
    return false;
  if (figureElPassa->m_positionY != yPos)
    return false;
  return true;
}

bool ChessBoard::validateMoveInOneDirection(FigureBase* figure,int xPos, int yPos, bool enemy)
{
  if (figure->ValidateStrikePosition(xPos, yPos) && (getFigureAtPosition(xPos,yPos) || (isElpassaPostion(xPos,yPos) && dynamic_cast<FigurePawn*>(figure))))
    {
      if (enemy)
        {
          m_enemyAvailableStrikeMoves.append(QPair<int,int>(xPos,yPos));
          m_enemyAllValidStrikeMoves.append(QPair<int,int>(xPos,yPos));
        }
      else if (getFigureAtPosition(xPos,yPos) && getFigureAtPosition(xPos,yPos)->m_leftSide != figure->m_leftSide)
        m_availableStrikeMoves.append(QPair<int,int>(xPos,yPos));
      else if (!getFigureAtPosition(xPos,yPos) && ((figure->m_leftSide && xPos == 5) || (!figure->m_leftSide && xPos == 2)))
        m_availableStrikeMoves.append(QPair<int,int>(xPos,yPos));
    }
  if (figure->ValidatePosition(xPos,yPos)
      && !getFigureAtPosition(xPos,yPos))
    {
      if (enemy)
        {
          m_enemyAvailableMoves.append(QPair<int,int>(xPos,yPos));
          if (!dynamic_cast<FigurePawn*>(figure))
            m_enemyAllValidStrikeMoves.append(QPair<int,int>(xPos,yPos));
        }
      else
        m_availableMoves.append(QPair<int,int>(xPos,yPos));
      return true;
    }
  else if (figure->ValidatePosition(xPos,yPos) && (getFigureAtPosition(xPos,yPos)) && figure->m_stopOnOtherFigure)
    return false;

  return true;
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

bool ChessBoard::checkCheckMat(int positionX, int positionY)
{
  setAllValidMoves(positionX,positionY);
  for (int i=0; i< m_figures.count();++i)
    {
      FigureKing *king = dynamic_cast<FigureKing*>(m_figures.at(i));
      if(king && king->m_leftSide != getFigureAtPosition(positionX,positionY)->m_leftSide)
        {
          for (int j=0; j< m_availableStrikeMoves.count();++j)
            {
              if (king->m_positionX == m_availableStrikeMoves.at(j).first && king->m_positionY == m_availableStrikeMoves.at(j).second)
                return true;
            }
          break;
        }
    }
  return false;
}

bool ChessBoard::checkMat(bool leftSide)
{
  getEnemyAvailableMoves(leftSide);
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
  m_enemyAllValidStrikeMoves.clear();
  for (int i=0; i< m_figures.count();++i)
    {
      if (m_figures.at(i)->m_leftSide != leftSide)
        setAllValidMoves(m_figures.at(i)->m_positionX,m_figures.at(i)->m_positionY,true);
    }
}

void ChessBoard::setWinner(bool leftSide)
{
  leftSideWinner = leftSide;
  m_endOfGame = true;
  for (int i=0; i< m_figures.count();++i)
    m_figures.at(i)->m_type = FigureType::Killed;
}
