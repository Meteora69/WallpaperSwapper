#ifndef TIMETABDAYLISTWIDGET_H
#define TIMETABDAYLISTWIDGET_H

#include <QWidget>
#include "sqlitedbmanager.h"
#include <QWidget>
#include <QDebug>
#include "imagemanager.h"
#include "dialogwindowlistofimage.h"

namespace Ui {
class TimeTabDayListWidget;
}

class TimeTabDayListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TimeTabDayListWidget(DBManager* dbManager, ImageManager *imageManager, QWidget *parent = nullptr);
    ~TimeTabDayListWidget();

    void SetTimeTabDayListWidgetStyle();
    void CreateDialogWindowListOfImage();
    void CreateViewTabInterface();
    void CreatInterfaceCreateTab();
     void UpdateViewTabItem();
     void AddNewDayList();
     void SetScrollAreaAndConteinerForItems();
public slots:
    void AddDayListItem();
    void addImageInList(int index);
    void getTimeEditUpdatetData(int id,QTime startTime,QTime endTime);
    void receiveDayImageListEditSignal(int id);
private slots:
    void on_ButtonAddNewItemOfDayList_clicked();

    void on_TimeTabDayListTabButtonBox_accepted();

    void on_TimeTabDayListTabButtonBox_rejected();

private:
    Ui::TimeTabDayListWidget *ui;
    DialogWindowListOfImage* dialogWindowListOfImage;
    QWidget *scrollAreaConterinerCreateTab;
    QWidget *scrollAreaConterinerViewTab;

    DBManager* dbManager;
    ImageManager *imageManager;
    InterfaceAddition* interfaceAddition;

    DayImageList* currentDayImageList;
    QVector<DayImageList> DayImageLists;
    QVector<TimeRangeImage> currentImageIds;


};

#endif // TIMETABDAYLISTWIDGET_H
