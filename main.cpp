#include <iostream>
#include <QApplication>

#include "MainWindow.hpp"
#include "RenderWindow.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("Fusion");

    MainWindow mainWindow;
    mainWindow.show();

    RenderWindow *renderWindow = new RenderWindow(mainWindow.getRenderWindowFrame());
    renderWindow->show();
    mainWindow.setRenderWindow(renderWindow);

    return a.exec();
}
