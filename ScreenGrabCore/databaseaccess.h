#ifndef DATABASEACCESS_H
#define DATABASEACCESS_H

#include"ScreenGrabCore_global.h"
#include <QObject>


#include "imagedao.h"

class QSqlDatabase;

class SCREENGRABCORE_EXPORT DatabaseAccess
{
protected:
    DatabaseAccess();
private:
    QSqlDatabase *mDatabase;
    static DatabaseAccess *_instance;
    const QString dbName = "image.db";
public:
    ImageDao *imageDao;

    static DatabaseAccess *instance();
    ~DatabaseAccess();

};

#endif // DATABASEACCESS_H
