#include "QSFML.hpp"

/***************************************************************************************************
 * PUBLIC METHODS
 */
QSFML::QSFML(QWidget* parent, const QPoint& position, const QSize& size, unsigned int fps) :
    QWidget(parent),
    m_initialized(false),
    m_refreshRate(),
    m_fpsTimer(),
    m_fpsTick(0),
    m_fps(0),
    m_mouseX(-1),
    m_mouseY(-1),
    m_mouseWheel(0),
    m_mouse(),
    m_mouseDoubleClick(),
    m_keyboard()
{
    // Settings attribute for SFML rendering
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);

    // Events configuration
    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);

    // Move and resize the window
    move(position);
    resize(size);

    // Frame Rate
    m_refreshRate.setTimerType(Qt::TimerType::PreciseTimer);
    setFrameRate(fps);

    // FPS Calculation each 1000ms (1s)
    m_fpsTimer.setInterval(1000);
}

QSFML::~QSFML()
{

}


void QSFML::setFrameRate(unsigned int fps)
{
    if(fps > 0)
        m_refreshRate.setInterval(1000/fps);
    else
        m_refreshRate.setInterval(0);
}


/***************************************************************************************************
 * PROTECTED METHODS
 */
////////////////////////////////////////////////////////////////////////////////////////////////////
/// RENDER METHODS
///
QPaintEngine* QSFML::paintEngine() const
{
    return nullptr;
}


void QSFML::showEvent(QShowEvent*)
{
    if(!m_initialized)
    {
        sf::RenderWindow::create(reinterpret_cast<HWND>(winId()));
        OnInit();

        // Connect timer to events
        connect(&m_refreshRate, SIGNAL(timeout()), this, SLOT(repaint()));
        connect(&m_fpsTimer, SIGNAL(timeout()), this, SLOT(FPS_Calculation()));

        // Start timer
        m_refreshRate.start();
        m_fpsTimer.start();

        // Initialization complete
        m_initialized = true;
    }
}


void QSFML::paintEvent(QPaintEvent*)
{
    // Window loop call each time the internal timer reach the fps goal !
    OnUpdate();
    sf::RenderWindow::display();

    cleanEvents();
    m_fpsTick++;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// QT EVENTS
///
void QSFML::mouseMoveEvent(QMouseEvent* event)
{
    m_mouseX = event->x();
    m_mouseY = event->y();
}


void QSFML::mousePressEvent(QMouseEvent* event)
{
    m_mouse[event->button()] = QSFMLKeyState::Pressed;
}


void QSFML::mouseReleaseEvent(QMouseEvent* event)
{
    m_mouse[event->button()] = QSFMLKeyState::Released;
}


void QSFML::mouseDoubleClickEvent(QMouseEvent* event)
{
    m_mouseDoubleClick[event->button()] = true;
}


void QSFML::wheelEvent(QWheelEvent* event)
{
    m_mouseWheel = event->delta();
}


void QSFML::keyPressEvent(QKeyEvent* event)
{
    m_keyboard[event->key()] = QSFMLKeyState::Pressed;
}


void QSFML::keyReleaseEvent(QKeyEvent* event)
{
    if(!event->isAutoRepeat())
        m_keyboard[event->key()] = QSFMLKeyState::Released;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// EVENTS ACCESS
///
int QSFML::mouseX()
{
    return m_mouseX;
}


int QSFML::mouseY()
{
    return m_mouseY;
}


bool QSFML::isMouseButtonPressed(Qt::MouseButton button)
{
    if(m_mouse.count(button) == 1)
    {
        if(m_mouse[button] == QSFMLKeyState::Pressed)
            return true;
    }

    return false;
}


bool QSFML::isMouseButtonReleased(Qt::MouseButton button)
{
    if(m_mouse.count(button) == 1)
    {
        if(m_mouse[button] == QSFMLKeyState::Released)
            return true;
    }

    return false;
}


bool QSFML::isMouseButtonDoubleClick(Qt::MouseButton button)
{
    if(m_mouseDoubleClick.count(button) == 1)
    {
        if(m_mouseDoubleClick[button])
            return true;
    }

    return false;
}


bool QSFML::isMouseWheelForward()
{
   if(m_mouseWheel > 0)
       return true;

   return false;
}


bool QSFML::isMouseWheelBackward()
{
    if(m_mouseWheel < 0)
        return true;

    return false;
}


bool QSFML::isKeyPressed(Qt::Key key)
{
    if(m_keyboard.count(key) == 1)
    {
        if(m_keyboard[key] == QSFMLKeyState::Pressed)
            return true;
    }

    return false;
}


bool QSFML::isKeyReleased(Qt::Key key)
{
    if(m_keyboard.count(key) == 1)
    {
        if(m_keyboard[key] == QSFMLKeyState::Released)
            return true;
    }

    return false;
}


/***************************************************************************************************
 * PRIVATE METHODS
 */
void QSFML::cleanEvents()
{
    // Mouse release buttons
    for(auto it=m_mouse.begin(); it!=m_mouse.end(); ++it)
    {
        if(it->second == QSFMLKeyState::Released)
            it->second = QSFMLKeyState::None;
    }

    // Mouse double click
    for(auto it=m_mouseDoubleClick.begin(); it!=m_mouseDoubleClick.end(); ++it)
    {
        if(it->second)
            it->second = false;
    }

    // Mouse wheel
    m_mouseWheel = 0;

    // Keyboard release keys
    for(auto it=m_keyboard.begin(); it!=m_keyboard.end(); ++it)
    {
        if(it->second == QSFMLKeyState::Released)
            it->second = QSFMLKeyState::None;
    }
}


/***************************************************************************************************
 * PRIVATE SLOTS METHODS
 */
void QSFML::FPS_Calculation()
{
    m_fps = m_fpsTick;

    m_fpsTick = 0;
}
