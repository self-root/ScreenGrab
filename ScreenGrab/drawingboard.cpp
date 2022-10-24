#include "drawingboard.h"
#include <QPainter>
#include <QDebug>

DrawingBoard::DrawingBoard(QPoint origin, QPoint current, QWidget *parent)
    : QWidget{parent}, m_origin(origin),  m_current(current)
{
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setAttribute(Qt::WA_NoSystemBackground);
    //setContentsMargins(0, 0, 0, 0);
    //qDebug() << geometry();
}

void DrawingBoard::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
    //painter.begin(this);
    //painter.setBackground(Qt::blue);
    painter.setPen(Qt::darkBlue);
    QColor fill;
    fill.setRgbF(22.7, 52.5, 100.0, 0.3);
    painter.setBrush(QBrush(fill));
    int w = m_current.x() - m_origin.x();
    int h = m_current.y() - m_origin.y();
    qDebug() << "Drawing rect: " << m_origin << " w: " << w << " h: " << h << " Current: " << m_current;


    painter.drawRect(m_origin.x() - 1, m_origin.y() - 1, w + 1, h + 1);
}
