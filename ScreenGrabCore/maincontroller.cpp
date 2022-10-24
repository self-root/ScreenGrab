#include "maincontroller.h"
#include <QDebug>
#include <filesystem>
#include "QtWidgets/qapplication.h"
#include <QClipboard>
#include "utils.h"

MainController::MainController(QObject *parent)
    : QObject(parent)
{

    scrgrab::Utils::makeConfigPaths();
    recentImageModel = new RecentImageModel;
    langModel = new LangModel;
    imageProvider = new ImageProvider;
    mImage = new Image;
    mLangModel = langModel->firstModel();

    connect(imageProvider, &ImageProvider::imageTextReady, this, &MainController::onTextExtracted);
    connect(imageProvider, &ImageProvider::imageTextReady,  this, [this](){setIsExtracting(false);});
    connect(this, &MainController::startExtraction, imageProvider, &ImageProvider::extractText);
    connect(this, &MainController::startExtraction, this, [this](){setIsExtracting(true);});
}

ImageProvider *MainController::getImageProvider()
{
    return imageProvider;
}

Image *MainController::image()
{
    return mImage;
}

bool MainController::getIsExtracting() const
{
    return isExtracting;
}

void MainController::setIsExtracting(bool newIsExtracting)
{
    isExtracting = newIsExtracting;
    emit extractionStatusChanged();
}

void MainController::onCaptured(QImage &img)
{
    imageProvider->setImage(img);
    Image::clear(mImage);
    mImage->setImagePath("newimage");
    emit startExtraction(mLangModel);
    emit imageView();
}

void MainController::onImageSelected(const QUrl &imgPath)
{
    Image::clear(mImage);
    mImage->setImagePath(imgPath.toLocalFile());
    imageProvider->setImage(QImage(imgPath.toLocalFile()));
    emit startExtraction(mLangModel);
    emit imageView();
}

void MainController::onSave(const QUrl &fileName)
{
    qDebug() << "Saving image..." << fileName.path();
    imageProvider->getImage().save(fileName.toLocalFile());
    mImage->setImagePath(fileName.path());
    if (mImage->imageId() > 0)
        recentImageModel->updateImage(mImage);
    else
        recentImageModel->addImage(mImage);
}

void MainController::onSave()
{
    imageProvider->getImage().save(mImage->imagePath());
    recentImageModel->updateImage(mImage);
}

QString MainController::imageDefaultName()
{
    return scrgrab::Utils::imageDefaultName();
}

QString MainController::pictureFolder()
{
    return scrgrab::Utils::pictureDir() + "/";
}

QString MainController::homeDir()
{
    return scrgrab::Utils::homePath() + "/";
}

void MainController::quit()
{
    QApplication::quit();
}

void MainController::recentImageSelected(int imageId, QString path, QString text, QDateTime dateTime)
{
    Image::clear(mImage);
    mImage->setImageId(imageId);
    mImage->setImagePath(path);
    mImage->setImageText(text);
    mImage->setSavedDate(dateTime);

    imageProvider->setImage(QImage(path));

    emit imageView();
}

void MainController::recentImageSelected(int index)
{
    Image *image = recentImageModel->imageAt(index);
    recentImageSelected(
                image->imageId(),
                image->imagePath(),
                image->imageText(),
                image->savedDate()
                );
}

void MainController::onTextExtracted(const QString &text)
{
    mImage->setImageText(text);
}

void MainController::onLangModelChange(const QString &langModel)
{
    mLangModel = langModel;
}

void MainController::addNewLanguage(const QUrl &langPath, const QString &language)
{
    langModel->addLang(std::filesystem::path(langPath.toLocalFile().toStdString()), language);
}

void MainController::rotateImage(int angle)
{
    imageProvider->rotate(angle);
}

void MainController::removeRecentImage(int index, bool withFile)
{
    recentImageModel->removeImage(index, withFile);
}

void MainController::toClipboard(const QString &txt)
{
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(txt);
}


RecentImageModel *MainController::getRecentImageModel() const
{
    return recentImageModel;
}

LangModel *MainController::getLangModel() const
{
    return langModel;
}

ImageProvider *MainController::getImageProvider() const
{
    return imageProvider;
}

QString MainController::version() const
{
    QString v_ = QString::fromStdString(scrgrab::version->toStdString());
    return v_;
}

