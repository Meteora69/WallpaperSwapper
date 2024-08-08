
#ifndef DBMANAGER_H
#define DBMANAGER_H
#include <QSqlDatabase>
#include "wallpaperimage.h"
#include "randomimagelist.h"
#include "weekimagelist.h"
#include "dayimagelist.h"
class DBManager {
public:

    virtual void connectToDataBase() = 0;

    virtual QSqlDatabase getDB() = 0;

    virtual bool insertIntoImageTable(const WallpaperImage& wallpaperImage)=0;
    virtual QVector<WallpaperImage> getAllImages() = 0;
    virtual bool deleteImageById(int imageId)=0;

};

#endif // DBMANAGER_H
