#ifndef RENDERWINDOW_HPP
#define RENDERWINDOW_HPP

#include "QSFML.hpp"

class RenderWindow : public QSFML
{
    void OnInit();
    void OnUpdate();
    sf::Color m_bg;

    public:
        RenderWindow(QWidget* parent);
};

#endif // RENDERWINDOW_HPP
