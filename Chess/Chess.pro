QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ChessBoard/ChessBoard.cpp \
    ChessBoard/ChessBoardBox.cpp \
    ChessBoard/ChessBoardHistory.cpp \
    ChessBoard/ChessBoardMove.cpp \
    ChessBoard/ChessBoardPlayerText.cpp \
    ChessBoard/ChessBoardPromotion.cpp \
    ChessBoard/ChessBoardScene.cpp \
    ChessBoard/ChessBoardSidePanel.cpp \
    Figures/FigureBase.cpp \
    Figures/FigureBishop.cpp \
    Figures/FigureKing.cpp \
    Figures/FigureKnight.cpp \
    Figures/FigureKnightBishop.cpp \
    Figures/FigurePawn.cpp \
    Figures/FigureQueen.cpp \
    Figures/FigureRook.cpp \
    Figures/FigureView.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ChessBoard/ChessBoard.h \
    ChessBoard/ChessBoardBox.h \
    ChessBoard/ChessBoardHistory.h \
    ChessBoard/ChessBoardMove.h \
    ChessBoard/ChessBoardPlayerText.h \
    ChessBoard/ChessBoardPromotion.h \
    ChessBoard/ChessBoardScene.h \
    ChessBoard/ChessBoardSidePanel.h \
    Figures/FigureBase.h \
    Figures/FigureBishop.h \
    Figures/FigureKing.h \
    Figures/FigureKnight.h \
    Figures/FigureKnightBishop.h \
    Figures/FigurePawn.h \
    Figures/FigureQueen.h \
    Figures/FigureRook.h \
    Figures/FigureView.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources/Resources.qrc

DISTFILES +=
