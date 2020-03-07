#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QGraphicsView"
#include "ChessBoard/ChessBoard.h"

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
  m_sceneChessBoard = new ChessBoard();
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
  m_sceneChessBoard->Reset();
}
