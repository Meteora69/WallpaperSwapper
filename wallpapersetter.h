#ifndef WALLPAPERSETTER_H
#define WALLPAPERSETTER_H
#include <QString>
#include <Windows.h>
#include "wsexception.h"
#include <QDebug>

class WallpaperSetter
{
public:
    WallpaperSetter();
    bool setWallpaper(const QString &imagePath);
};

#endif // WALLPAPERSETTER_H
