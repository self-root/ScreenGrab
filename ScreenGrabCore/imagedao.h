#ifndef IMAGEDAO_H
#define IMAGEDAO_H

#include <vector>
#include <memory>

#include "ScreenGrabCore_global.h"
#include "image.h"

class QSqlDatabase;

/**
 * A class that poses as an API to read and write data from the database
 */
class SCREENGRABCORE_EXPORT ImageDao
{
public:
    ImageDao(QSqlDatabase &database);

    bool addImage(Image *image);
    std::unique_ptr<std::vector<std::unique_ptr<Image>>> getImages() const;
    bool update(const Image *image);
    bool remove(Image *image);
private:
    QSqlDatabase &mDatabase;
};

#endif // IMAGEDAO_H
