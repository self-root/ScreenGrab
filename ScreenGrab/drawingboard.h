#ifndef DRAWINGBOARD_H
#define DRAWINGBOARD_H

#include <QWidget>
#include <QPaintEvent>
#include <QPoint>

class DrawingBoard : public QWidget
{
    Q_OBJECT
public:
    DrawingBoard(QPoint origin, QPoint current, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QPoint m_origin;
    QPoint m_current;

};

#endif // DRAWINGBOARD_H
