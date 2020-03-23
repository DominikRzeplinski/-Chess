#include "ChessBoard.h"
#include "Figures/FigureKing.h"
#include "Figures/FigureBishop.h"
#include "Figures/FigureKnight.h"
#include "Figures/FigurePawn.h"
#include "Figures/FigureQueen.h"
#include "Figures/FigureRook.h"
#include <QGraphicsScene>

ChessBoard::ChessBoard()
{
  m_panelLeft = NULL;
  m_panelRight = NULL;
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
                figureBase = new FigureRook(true, x,y);
              if (y==1 || y== 6)
                figureBase = new FigureKnight(true, x,y);
              if (y==2 || y==5)
                figureBase = new FigureBishop(true, x,y);
              if (y ==3)
                figureBase = new FigureQueen(true,x,y);
              if (y==4)
                figureBase = new FigureKing(true,x,y);
          }
          else if (x == 1)
          {
              figureBase = new FigurePawn(true,x,y);
          }
          else if (x == 6)
          {
              figureBase = new FigurePawn(false,x,y);
          }
          else if (x == 7)
          {
              if (y == 0 || y == 7)
                figureBase = new FigureRook(false, x,y);
              if (y==1 || y== 6)
                figureBase = new FigureKnight(false, x,y);
              if (y==2 || y==5)
                figureBase = new FigureBishop(false, x,y);
              if (y ==3)
                figureBase = new FigureQueen(false,x,y);
              if (y==4)
                figureBase = new FigureKing(false,x,y);

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
}

void ChessBoard::setNewPosition(int PositionX, int PositionY)
{
  for (int i =0; i < m_figures.count(); ++i)
    {
      if (m_figures.at(i)->m_positionX == PositionX && m_figures.at(i)->m_positionY == PositionY)
        {
          for (int j=0; j < m_boxes.count(); ++j)
          {
              if (m_boxes.at(j)->isUnderMouse())
                {
                  QPair<int,int> xyPos =QPair<int,int>(m_boxes.at(j)->PositionX,m_boxes.at(j)->PositionY);
                  bool valid = false;
                  for (int l=0; l< m_availableMoves.count();l++)
                    {
                      if (m_availableMoves.at(l) == xyPos)
                        valid = true;
                    }
                  if (valid)
                     {
                       m_figures.at(i)->setPos(m_boxes.at(j)->pos());
                       m_figures.at(i)->m_positionX = m_boxes.at(j)->PositionX;
                       m_figures.at(i)->m_positionY = m_boxes.at(j)->PositionY;
                       m_boxes.at(j)->m_bHasFigure = true;
                       for (int k=0; k< m_boxes.count();++k)
                         {
                           if (m_boxes.at(k)->PositionX == PositionX && m_boxes.at(k)->PositionY == PositionY)
                           {
                              m_boxes.at(k)->m_bHasFigure = false;
                              break;
                           }
                         }
                     }
                  else
                    {
                      for (int k=0; k< m_boxes.count();++k)
                        {
                          if (m_boxes.at(k)->PositionX == PositionX && m_boxes.at(k)->PositionY == PositionY)
                          {
                             m_figures.at(i)->setPos(m_boxes.at(k)->pos());
                             break;
                          }
                        }

                    }
                  break;
                }
          }
          break;
        }
    }

}

void ChessBoard::validMoves(int positionX, int positionY)
{
  m_availableMoves.clear();
  for (int i =0; i < m_figures.count(); ++i)
    {
      if (m_figures.at(i)->m_positionX == positionX && m_figures.at(i)->m_positionY == positionY)
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
                  if (!validateMoveInOneDirection(i,x,y))
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
                  if (!validateMoveInOneDirection(i,x,y))
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
                  if (!validateMoveInOneDirection(i,x,y))
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
                  if (!validateMoveInOneDirection(i,x,y))
                    {
                        bLeftUp = false;
                    }
              }
          }
          break;
        }
    }
}


bool ChessBoard::validateMoveInOneDirection(int idxFigure,int xPos, int yPos)
{
  for (int j=0; j< m_boxes.count(); ++j)
    {
        if (m_boxes.at(j)->PositionX == xPos && m_boxes.at(j)->PositionY == yPos)
        {
            if (m_figures.at(idxFigure)->ValidatePosition(m_boxes.at(j)->PositionX, m_boxes.at(j)->PositionY)
                && !m_boxes.at(j)->m_bHasFigure)
              {
                m_availableMoves.append(QPair<int,int>(xPos,yPos));
                m_boxes.at(j)->setBrush(Qt::green);
                return true;
              }
            else if (m_figures.at(idxFigure)->ValidatePosition(m_boxes.at(j)->PositionX, m_boxes.at(j)->PositionY) && m_boxes.at(j)->m_bHasFigure && m_figures.at(idxFigure)->m_stopOnOtherFigure)
              return false;
            break;
        }
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
