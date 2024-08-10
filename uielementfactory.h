#ifndef UIELEMENTFACTORY_H
#define UIELEMENTFACTORY_H
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include <QVBoxLayout>
#include <QDebug>
#include <QTimeEdit>
#include <QDesktopServices>
#include <QScrollArea>
#include <QCheckBox>
#include <QLineEdit>
#include <QDialogButtonBox>
#include "imagelist.h"
#include "uielementeventhandler.h"
#include "sqltableimagelist.h"
struct WidgetGeometry {
    int width;
    int height;
    int xPos;
    int yPos;

    WidgetGeometry() : width(0), height(0), xPos(0), yPos(0) {}

    WidgetGeometry(int w, int h, int x, int y)
        : width(w), height(h), xPos(x), yPos(y) {}
};

class UIElementFactory: public QWidget
{
    Q_OBJECT
public:
    UIElementFactory(UIElementEventHandler* uiElementEventHandler);
    void CreateLableWithImage(QWidget* conteinerWidget, int imageIndex, const WidgetGeometry& geometry);
    void CreateButtonImage(QWidget* conteinerWidget, int index, const WidgetGeometry& geometry);
    void CreateButtonSetImage(QWidget *conteinerWidget, QString day, const WidgetGeometry& geometry);

    void CreateButtonInfo(QWidget* conteinerWidget);
    void CreateButtonDelete(QWidget* conteinerWidget, int index, int width, int hight, int cordinate_x, int cordinate_y);
    void CreateButtonFullSize(QWidget* conteinerWidget, int index);
    void CreateButtonEdit(QWidget* conteinerWidget, int id, int width, int hight, int cordinate_x, int cordinate_y);

    void CreateLableWithText(QWidget* conteinerWidget, QString TextOfLabel, int Cordinate_x, int Cordinate_y);
    void CreateToggleButton(QWidget *containerWidget, int id);

    QTimeEdit* CreateTimeEditor(QWidget *conteinerWidget, int id, int cordinate_x, int cordinate_y);

    void CreateButtonAddImage(QWidget *containerWidget, const WidgetGeometry &geometry);
    void CreateButtonBox(QWidget *containerWidget, int cordinate_x, int cordinate_y);
    QLineEdit* CreateLineEdit(QWidget *containerWidget, const WidgetGeometry &geometry);


private:
    UIElementEventHandler* uiElementEventHandler;
    ImageList*  imageList;
};

#endif // UIELEMENTFACTORY_H
