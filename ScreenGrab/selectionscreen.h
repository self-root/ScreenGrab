#ifndef SELECTIONSCREEN_H
#define SELECTIONSCREEN_H

#include <QWidget>
#include <QMouseEvent>
#include <QPoint>
#include <QVBoxLayout>
#include <QPixmap>
#include <QScreen>
#include <QMainWindow>
#include <QWindow>
#include <QKeyEvent>

#include "drawingboard.h"

class SelectionScreen : public QMainWindow
{
    Q_OBJECT
public:
    explicit SelectionScreen(QWidget *parent = nullptr);
    void setCaptureScreen(QScreen *screen);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    QPoint origin;
    DrawingBoard *board = nullptr;


signals:
    void captured(QImage &tmpPath);
    void abort();
private slots:
    void capture(int w, int h);
};

#endif // SELECTIONSCREEN_H
