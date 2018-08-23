#include "MainWindow.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow),
    m_sfml(nullptr)
{
    m_ui->setupUi(this);
}


QWidget* MainWindow::getRenderWindowFrame()
{
    return m_ui->frame;
}


void MainWindow::setRenderWindow(RenderWindow* renderWindow)
{
    m_sfml = renderWindow;
}
