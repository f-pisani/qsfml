#include "RenderWindow.hpp"

RenderWindow::RenderWindow(QWidget* parent) :
    QSFML(parent, QPoint(0, 0), parent->size(), 120),
    m_bg(sf::Color::Black)
{

}


void RenderWindow::OnInit()
{

}


void RenderWindow::OnUpdate()
{
    clear(m_bg);
}
