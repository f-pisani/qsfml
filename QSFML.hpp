#ifndef QSFML_HPP
#define QSFML_HPP

#include <iostream>
#include <map>

#include <QWidget>

#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>

#include <QTimer>
#include <QPaintEngine>

#include <SFML/Graphics.hpp>

enum QSFMLKeyState : char
{
    None,
    Pressed,
    Released
};

class QSFML : public QWidget, protected sf::RenderWindow
{
    Q_OBJECT
    virtual void OnInit() =0; // Call once when the window is created
    virtual void OnUpdate() =0; // Call each frame (fps can be set by the fps parameter 0=Unlimited)
    void cleanEvents();

    bool m_initialized;
    QTimer m_refreshRate;
    QTimer m_fpsTimer;
    unsigned int m_fpsTick;
    unsigned int m_fps;

    int m_mouseX, m_mouseY;
    int m_mouseWheel;
    std::map<Qt::MouseButton, QSFMLKeyState> m_mouse;
    std::map<Qt::MouseButton, bool> m_mouseDoubleClick;
    std::map<int, QSFMLKeyState> m_keyboard;


    public:
        QSFML(QWidget* parent = nullptr, const QPoint& position = QPoint(0,0), const QSize& size = QSize(0,0), unsigned int fps = 0);
        virtual ~QSFML();
        inline unsigned int FPS() const { return m_fps; }
        void setFrameRate(unsigned int fps=0);

    protected:
        QPaintEngine* paintEngine() const;
        void showEvent(QShowEvent*);
        void paintEvent(QPaintEvent*);
        virtual void mouseMoveEvent(QMouseEvent* event);
        virtual void mousePressEvent(QMouseEvent* event);
        virtual void mouseReleaseEvent(QMouseEvent* event);
        virtual void mouseDoubleClickEvent(QMouseEvent* event);
        virtual void wheelEvent(QWheelEvent* event);
        virtual void keyPressEvent(QKeyEvent* event);
        virtual void keyReleaseEvent(QKeyEvent* event);
        int mouseX();
        int mouseY();
        bool isMouseButtonPressed(Qt::MouseButton button);
        bool isMouseButtonReleased(Qt::MouseButton button);
        bool isMouseButtonDoubleClick(Qt::MouseButton button);
        bool isMouseWheelForward();
        bool isMouseWheelBackward();
        bool isKeyPressed(Qt::Key key);
        bool isKeyReleased(Qt::Key key);

    private slots:
        void FPS_Calculation();
};

#endif // QSFML_HPP
