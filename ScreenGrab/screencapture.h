#ifndef SCREENCAPTURE_H
#define SCREENCAPTURE_H

#include <QObject>
#include <QPoint>
#include <QPixmap>
#include <QScreen>
#include <QDir>
#include <QDateEdit>

class ScreenCapture : public QObject
{
public:
    static QString capture(QScreen *screen, const QPoint &origin, int w, int h)
    {
        QPixmap image;
        image = screen->grabWindow(0, origin.x(), origin.y(), w, h);
        QString fileName = makeFileName();
        image.save(fileName);
        return fileName;
    }

    static QPixmap capture(QScreen *screen)
    {
        QPixmap image;
        image = screen->grabWindow(0);
        //QString fileName = makeFileName();
        //image.save(fileName);
        return image;
    }

    static QString makeFileName()
    {
        QString filePath = QDir::home().absolutePath() + "/.config/screenGrab/tmp/screen grab ";
        filePath += QDateTime::currentDateTime().toString("dd-MM-yy hh:mm:ss");
        filePath += ".png";
        qDebug() << "File: " << filePath;
        return filePath;
    }
};

#endif // SCREENCAPTURE_H
