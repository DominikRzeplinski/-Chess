#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ChessBoard/ChessBoard.h"
#include "ChessBoard/ChessBoardScene.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void on_actionExit_triggered();

  void on_actionNew_game_triggered();

  void on_actionSave_game_triggered();
  
  void on_actionLoad_game_triggered();
  void Reset();
private:
  Ui::MainWindow *ui;
  ChessBoard * m_chessBoard;
  ChessBoardScene *m_sceneChessBoard;
};
#endif // MAINWINDOW_H
