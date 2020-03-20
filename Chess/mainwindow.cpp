#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QGraphicsView"
#include "ChessBoard/ChessBoard.h"
#include "ChessBoard/ChessBoardScene.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  setFixedSize(802,623);
  QGraphicsView * gameView = new QGraphicsView(this);
  gameView->move(0,21);
  gameView->setFixedSize(802,602);
  gameView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  gameView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  m_sceneChessBoard = new ChessBoardScene();
  m_chessBoard = new ChessBoard();
  for (int i =0; i < m_chessBoard->m_boxes.count(); ++i)
  {
    m_sceneChessBoard->addItem(m_chessBoard->m_boxes.at(i));
  }
  for (int i =0; i < m_chessBoard->m_figures.count(); ++i)
  {
    m_sceneChessBoard->addItem(m_chessBoard->m_figures.at(i));
  }
  m_sceneChessBoard->addItem(m_chessBoard->m_panelLeft);
  m_sceneChessBoard->addItem(m_chessBoard->m_panelRight);

  gameView->setScene(m_sceneChessBoard);

  QBrush brush;
  brush.setStyle(Qt::SolidPattern);
  brush.setColor(Qt::black);
  gameView->setBackgroundBrush(brush);
  gameView->show();

}

MainWindow::~MainWindow()
{
  delete ui;
}


void MainWindow::on_actionExit_triggered()
{
  exit(0);
}

void MainWindow::on_actionNew_game_triggered()
{
  m_chessBoard->Reset();
}

void MainWindow::on_actionSave_game_triggered()
{
    
}

void MainWindow::on_actionLoad_game_triggered()
{
    
}
