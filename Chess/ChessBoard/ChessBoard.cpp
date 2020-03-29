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
  figureEnPassant = NULL;
  Reset();
}

void ChessBoard::cleanScene()
{
  figures.clear();
  availableMoves.clear();
  availableStrikeMoves.clear();
  enemyAvailableMoves.clear();
  enemyAvailableStrikeMoves.clear();
  promotionFigures.clear();
  promotionActive= false;
  endOfGame = false;
  if (figureEnPassant)
    delete figureEnPassant;
  figureEnPassant = NULL;
  checkMate = false;
}

void ChessBoard::Reset()
{
  cleanScene();
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
              figures.append(figureBase);
            }
        }
    }
  for (int i =0 ; i <8; ++i)
    {
      promotionFigures.append( new FigureQueen(true,FigureType::Promotion, -1,-1));
      promotionFigures.append( new FigureBishop(true,FigureType::Promotion, -1,-2));
      promotionFigures.append( new FigureKnight(true,FigureType::Promotion, -1,-3));
      promotionFigures.append( new FigureRook(true,FigureType::Promotion, -1,-4));
      promotionFigures.append(new FigureQueen(false,FigureType::Promotion, -2,-1));
      promotionFigures.append(new FigureBishop(false,FigureType::Promotion, -2,-2));
      promotionFigures.append(new FigureKnight(false,FigureType::Promotion, -2,-3));
      promotionFigures.append(new FigureRook(false,FigureType::Promotion, -2,-4));
    }
}

bool ChessBoard::setNewPosition(int positionX, int positionY, int newPositionX, int newPositionY)
{
  bool valid = false;
  if (endOfGame)
    return valid;
  checkMate = false;
  FigureBase* figure = getFigureAtPosition(positionX, positionY);
  if (figure != NULL)
    {
      bool removeEnPassant= true;
      QPair<int,int> xyPos =QPair<int,int>(newPositionX,newPositionY);
      bool validMove = false;
      for (int l=0; l< availableMoves.count();l++)
        {
          if (availableMoves.at(l) == xyPos)
            validMove = true;
        }
      bool validStrike = false;
      for (int l=0; l< availableStrikeMoves.count();l++)
        {
          if (availableStrikeMoves.at(l) == xyPos)
            validStrike = true;
        }
      FigurePawn * pawn = dynamic_cast<FigurePawn*>(figure);
      if (validMove)
        {

          FigureKing * king = dynamic_cast<FigureKing*>(figure);
          //castling
          if (king && (figure->positionX ==0 ||figure->positionX ==7) && qFabs(figure->positionY -newPositionY) == 2 && figure->positionY == 4)
            {
              figure->setPosition(newPositionX,newPositionY);

              if (figure->positionY == 2)
                {
                  FigureBase * castle = getFigureAtPosition(figure->positionX,0);
                  castle->setPosition(figure->positionX,3);
                }
              else
                {
                  FigureBase * castle = getFigureAtPosition(figure->positionX,7);
                  castle->setPosition(figure->positionX,5);
                }

            }
          else if(pawn && qFabs(pawn->positionX - newPositionX) == 2 )
            {
              figure->setPosition(newPositionX,newPositionY);
              if (pawn->leftSide)
                {
                  figureEnPassant = new FigurePawn(pawn->leftSide,FigureType::Alive,pawn->positionX -1,pawn->positionY);
                }
              else {
                  figureEnPassant = new FigurePawn(pawn->leftSide,FigureType::Alive,pawn->positionX +1,pawn->positionY);
                }
              removeEnPassant = false;
            }
          else
            {
              figure->setPosition(newPositionX,newPositionY);


            }
          figure->leftSideTurn = !figure->leftSideTurn;
        }
      else if (validStrike)
        {
          FigureBase * killedFigure = getFigureAtPosition(newPositionX,newPositionY);
          //EnPassant
          if (!killedFigure)
            {
              if(figure->leftSide)
                {
                  killedFigure =  getFigureAtPosition(newPositionX-1,newPositionY);
                }
              else
                {
                  killedFigure =  getFigureAtPosition(newPositionX+1,newPositionY);
                }
            }
          if (killedFigure->leftSide)
            {
              killedFigure->setPosition(-1,-1);
            }
          else
            {
              killedFigure->setPosition(-1,-1);
            }
          killedFigure->type = FigureType::Killed;
          figure->setPosition(newPositionX,newPositionY);

          figure->leftSideTurn = !figure->leftSideTurn;

        }
      if (validMove || validStrike)
        {
          valid = true;
          //remove enPassant
          if (removeEnPassant)
            {
              delete figureEnPassant;
              figureEnPassant = NULL;
            }
          //Promotion

          if(pawn && ((pawn->leftSide && newPositionX ==7) || (!pawn->leftSide && newPositionX ==0)))
            {
              promotionActive = true;
              figure->leftSideTurn = !figure->leftSideTurn;

            }

          if(isCheckMate(figure->leftSide))
            setWinner(!figure->leftSide);

          if(checkCheckMate(figure->positionX,figure->positionY))
            checkMate = true;
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
              if (figure->firstMove)
                {
                  int xPosOfRock =0;
                  if (!figure->leftSide)
                    xPosOfRock = 7;
                  FigureBase* rock = getFigureAtPosition(xPosOfRock,0);
                  if (rock != NULL && rock->firstMove)
                    {
                      if (getFigureAtPosition(xPosOfRock,1) == NULL && getFigureAtPosition(xPosOfRock,2) == NULL && getFigureAtPosition(xPosOfRock,3) == NULL)
                        {
                          bool enamyAttack = false;
                          for (int i =0; i < enemyAllValidStrikeMoves.count();i++)
                            {
                              if (enemyAllValidStrikeMoves.at(i) == QPair<int,int>(xPosOfRock,2) || enemyAllValidStrikeMoves.at(i) == QPair<int,int>(xPosOfRock,3) ||enemyAllValidStrikeMoves.at(i)== QPair<int,int>(king->positionX,king->positionY))
                                {
                                  enamyAttack = true;
                                  break;
                                }
                            }
                          if (!enamyAttack)
                            availableMoves.append(QPair<int,int>(xPosOfRock,2));
                        }

                    }
                  rock = getFigureAtPosition(xPosOfRock,7);
                  if (rock != NULL && rock->firstMove)
                    {
                      if (getFigureAtPosition(xPosOfRock,5) == NULL && getFigureAtPosition(xPosOfRock,6) == NULL)
                        {
                          bool enamyAttack = false;
                          for (int i =0; i < enemyAllValidStrikeMoves.count();i++)
                            {
                              if (enemyAllValidStrikeMoves.at(i) == QPair<int,int>(xPosOfRock,5) || enemyAllValidStrikeMoves.at(i) == QPair<int,int>(xPosOfRock,6) ||enemyAllValidStrikeMoves.at(i)== QPair<int,int>(king->positionX,king->positionY))
                                {
                                  enamyAttack = true;
                                  break;
                                }
                            }
                          if (!enamyAttack)
                            availableMoves.append(QPair<int,int>(xPosOfRock,6));
                        }

                    }

                }
              //dont alow to move on enamy attack positions
              for (int i =0; i < enemyAllValidStrikeMoves.count(); i++)
                {
                  for (int j=0; j < availableMoves.count();j++)
                    {
                      if( availableMoves.at(j) == enemyAllValidStrikeMoves.at(i))
                        availableMoves.remove(j);
                    }
                }
            }
        }
    }
}

bool ChessBoard::promotionSelected(int positionX, int positionY)
{
  bool ret = false;
  if (!promotionActive)
    return false;

  for (int i =0; i< promotionFigures.count();i++)
    {
      if (promotionFigures.at(i)->positionX == positionX && promotionFigures.at(i)->positionY==positionY)
        {
          int x =0;
          if (promotionFigures.at(i)->leftSide)
            x =7;
          for (int y=0;y<8;y++)
            {
              FigurePawn * pawn = dynamic_cast<FigurePawn*>(getFigureAtPosition(x,y));
              if (pawn)
                {
                  pawn->type = FigureType::Promotion;
                  pawn->setPosition(-1,-1);
                  for (int j=0; j < figures.count(); ++j)
                    {
                      if (figures.at(j) == pawn)
                        {
                          figures.removeAt(j);
                          promotionFigures.at(i)->setPosition(x,y);
                          promotionFigures.at(i)->type=FigureType::Alive;
                          figures.append(promotionFigures.at(i));
                          promotionFigures.removeAt(i);
                        }
                    }

                  promotionActive = false;

                  pawn->leftSideTurn = !pawn->leftSideTurn;
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
  if (endOfGame)
    return;
  if (promotionActive)
    {
      availableMoves.clear();
      availableStrikeMoves.clear();
      return;
    }

  FigureBase* figure = getFigureAtPosition(positionX,positionY);
  if (figure)
    getEnemyAvailableMoves(figure->leftSide);
  availableMoves.clear();
  availableStrikeMoves.clear();
  setAllValidMoves(positionX,positionY);
}

bool ChessBoard::isEnPassantPosition(int xPos, int yPos)
{
  if (!figureEnPassant)
    return false;
  if (figureEnPassant->positionX != xPos)
    return false;
  if (figureEnPassant->positionY != yPos)
    return false;
  return true;
}

bool ChessBoard::validateMoveInOneDirection(FigureBase* figure,int xPos, int yPos, bool enemy)
{
  if (figure->validateStrikePosition(xPos, yPos) && (getFigureAtPosition(xPos,yPos) || (isEnPassantPosition(xPos,yPos) && dynamic_cast<FigurePawn*>(figure))))
    {
      if (enemy)
        {
          enemyAvailableStrikeMoves.append(QPair<int,int>(xPos,yPos));
          enemyAllValidStrikeMoves.append(QPair<int,int>(xPos,yPos));
        }
      else if (getFigureAtPosition(xPos,yPos) && getFigureAtPosition(xPos,yPos)->leftSide != figure->leftSide)
        availableStrikeMoves.append(QPair<int,int>(xPos,yPos));
      else if (!getFigureAtPosition(xPos,yPos) && ((figure->leftSide && xPos == 5) || (!figure->leftSide && xPos == 2)))
        availableStrikeMoves.append(QPair<int,int>(xPos,yPos));
    }
  if (figure->validatePosition(xPos,yPos)
      && !getFigureAtPosition(xPos,yPos))
    {
      if (enemy)
        {
          enemyAvailableMoves.append(QPair<int,int>(xPos,yPos));
          if (!dynamic_cast<FigurePawn*>(figure))
            enemyAllValidStrikeMoves.append(QPair<int,int>(xPos,yPos));
        }
      else
        availableMoves.append(QPair<int,int>(xPos,yPos));
      return true;
    }
  else if (figure->validatePosition(xPos,yPos) && (getFigureAtPosition(xPos,yPos)) && figure->stopOnOtherFigure)
    return false;

  return true;
}


FigureBase* ChessBoard::getFigureAtPosition(int positionX, int positionY)
{
  for (int j=0; j< figures.count(); ++j)
    {
      if (figures.at(j)->positionX == positionX && figures.at(j)->positionY == positionY)
        return figures.at(j);
    }
  return NULL;
}

bool ChessBoard::checkCheckMate(int positionX, int positionY)
{
  setAllValidMoves(positionX,positionY);
  for (int i=0; i< figures.count();++i)
    {
      FigureKing *king = dynamic_cast<FigureKing*>(figures.at(i));
      if(king && king->leftSide != getFigureAtPosition(positionX,positionY)->leftSide)
        {
          for (int j=0; j< availableStrikeMoves.count();++j)
            {
              if (king->positionX == availableStrikeMoves.at(j).first && king->positionY == availableStrikeMoves.at(j).second)
                return true;
            }
          break;
        }
    }
  return false;
}

bool ChessBoard::isCheckMate(bool leftSide)
{
  getEnemyAvailableMoves(leftSide);
  for (int i=0; i< figures.count();++i)
    {
      FigureKing *king = dynamic_cast<FigureKing*>(figures.at(i));
      if(king && king->leftSide == leftSide)
        {
          for (int j=0; j< enemyAvailableStrikeMoves.count();++j)
            {
              if (king->positionX == enemyAvailableStrikeMoves.at(j).first && king->positionY == enemyAvailableStrikeMoves.at(j).second)
                return true;
            }
          break;
        }
    }
  return false;
}

void ChessBoard::getEnemyAvailableMoves(bool leftSide)
{
  enemyAvailableMoves.clear();
  enemyAvailableStrikeMoves.clear();
  enemyAllValidStrikeMoves.clear();
  for (int i=0; i< figures.count();++i)
    {
      if (figures.at(i)->leftSide != leftSide)
        setAllValidMoves(figures.at(i)->positionX,figures.at(i)->positionY,true);
    }
}

void ChessBoard::setWinner(bool leftSide)
{
  leftSideWinner = leftSide;
  endOfGame = true;
  for (int i=0; i< figures.count();++i)
    figures.at(i)->type = FigureType::Killed;
}
