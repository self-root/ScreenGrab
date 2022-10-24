#ifndef DATABASEACCESS_H
#define DATABASEACCESS_H

#include"ScreenGrabCore_global.h"
#include <QObject>


#include "imagedao.h"

class QSqlDatabase;

class SCREENGRABCORE_EXPORT DatabaseAccess
{
protected:
    /**
     * @brief DatabaseAccess the constructor create a connection to the database and
     * Create an instance of ImageDao object to access the saved images
     */
    DatabaseAccess();
private:
    QSqlDatabase *mDatabase;
    static DatabaseAccess *_instance;
    const QString dbName = "image.db";
public:
    ImageDao *imageDao;

    /**
     * @brief instance Create an instance of this class and ensure that it is unique (singleton)
     * @return The pointer to the unique instance of this class (DatabaseAccess)
     */
    static DatabaseAccess *instance();
    ~DatabaseAccess();

};

#endif // DATABASEACCESS_H
