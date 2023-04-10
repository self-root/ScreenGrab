#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QQmlContext>
#include <QQmlEngine>
#include <QDebug>
#include <QTimer>

#include<QQuickWindow>

#include "selectionscreen.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGL);
    mainController = new MainController;
    resultTextController = new ResultTextViewController;
    ui->setupUi(this);

    ui->quickWidget->setSource(QUrl("qrc:/mainUi.qml"));

    ui->quickWidget->rootContext()->setContextProperty("mainController", mainController);
    ui->quickWidget->rootContext()->setContextProperty("textResultController", resultTextController);
    ui->quickWidget->engine()->addImageProvider("provider", mainController->getImageProvider());

    connect(mainController, &MainController::selection, this, &MainWindow::startSelection);
    connect(mainController, &MainController::selection, this, &MainWindow::hide);
    connect(mainController, &MainController::captureScreen, this, [this](){
        this->hide();
        QTimer::singleShot(200, this, &MainWindow::onCaptureScreen);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::startSelection()
{
    qDebug() << "Start selection";

    QList<QScreen*> screens = QApplication::screens();
    for (auto s : screens)
    {
        qDebug() << "Screen: " << s->geometry() << " Name: " << s->name();
        SelectionScreen *selectionScreen = new SelectionScreen(this);
        selectionScreen->setCaptureScreen(s);
        connect(selectionScreen, &SelectionScreen::captured, mainController, &MainController::onCaptured);
        connect(selectionScreen, &SelectionScreen::captured, selectionScreen, &QObject::deleteLater);
        connect(selectionScreen, &SelectionScreen::captured, this, &MainWindow::show);
        connect(selectionScreen, &SelectionScreen::abort, this, &MainWindow::show);
        connect(selectionScreen, &SelectionScreen::captured, this, &MainWindow::closeScreens);
        connect(selectionScreen, &SelectionScreen::abort, this, &MainWindow::closeScreens);
        selectionScreens.append(selectionScreen);
        selectionScreen->show();
    }

}

void MainWindow::onCaptureScreen()
{
    QPixmap img = this->screen()->grabWindow();
    QImage img_ = img.toImage();
    mainController->onCaptured(img_);
    this->show();
}

void MainWindow::capture()
{

}

void MainWindow::closeScreens()
{
    for (auto scr : selectionScreens)
    {
        if (scr != nullptr)
        {
            scr->close();
            scr->deleteLater();
        }

    }
    selectionScreens.clear();
}

