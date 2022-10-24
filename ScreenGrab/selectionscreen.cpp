#include "selectionscreen.h"
#include <QDebug>
#include <QTimer>

//#include "screencapture.h"

SelectionScreen::SelectionScreen(QWidget *parent)
    : QMainWindow{parent}
{
    setWindowState(Qt::WindowFullScreen);
    setWindowOpacity(0.2);
    setCursor(Qt::CrossCursor);

}

void SelectionScreen::setCaptureScreen(QScreen *screen)
{
    setScreen(screen);
}

void SelectionScreen::mousePressEvent(QMouseEvent *event)
{
    origin = event->pos();
}

void SelectionScreen::mouseReleaseEvent(QMouseEvent *event)
{

    int w = event->pos().x() - origin.x();
    int h = event->pos().y() - origin.y();

    QTimer::singleShot(200, this, [this, w, h](){
        capture(w, h);
    });

    qDebug() << "SCreen: " << this->screen();


    this->close();
}

void SelectionScreen::mouseMoveEvent(QMouseEvent *event)
{
    if(board != nullptr)
    {
        delete board;
        board = nullptr;
    }
    board = new DrawingBoard(origin, event->pos());
    this->setCentralWidget(board);
    event->accept();
}

void SelectionScreen::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        this->close();
        emit abort();
    }
}

void SelectionScreen::capture(int w, int h)
{
    QPixmap image = this->screen()->grabWindow(0, origin.x(), origin.y(), w, h);
    QImage img = image.toImage();
    emit captured(img);
}
