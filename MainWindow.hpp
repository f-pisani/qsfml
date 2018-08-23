#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "ui_MainWindow.h"
#include "RenderWindow.hpp"

namespace Ui{ class MainWindow; }

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Ui::MainWindow* m_ui;
    RenderWindow* m_sfml;

    public:
        explicit MainWindow(QWidget *parent = 0);
        QWidget* getRenderWindowFrame();
        void setRenderWindow(RenderWindow* renderWindow);
};

#endif // MAINWINDOW_HPP
