#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ChessBoard/ChessBoard.h"
#include "ChessBoard/ChessBoardScene.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/*!
 * \brief The MainWindow class
 */
class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  /*!
   * \brief MainWindow constructor
   * \param parent QWidget
   */
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  /*!
   * \brief on_actionExit_triggered slot for menu exit action
   */
  void on_actionExit_triggered();

  /*!
   * \brief on_actionNew_game_triggered slot for meny new game action
   */
  void on_actionNew_game_triggered();

  /*!
   * \brief on_actionSave_game_triggered slot for save game action
   */
  void on_actionSave_game_triggered();
  
  /*!
   * \brief on_actionLoad_game_triggered slot for load game action
   */
  void on_actionLoad_game_triggered();
  /*!
   * \brief Reset game
   */
  void Reset();
private:
  /*!
   * \brief ui
   */
  Ui::MainWindow *ui;
  /*!
   * \brief m_sceneChessBoard
   */
  ChessBoardScene *m_sceneChessBoard;
};
#endif // MAINWINDOW_H
