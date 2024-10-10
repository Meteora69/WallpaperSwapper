#ifndef DAYLISTWIDGET_H
#define DAYLISTWIDGET_H

#include <QWidget>
#include "sqlitedbmanager.h"
#include <QWidget>
#include <QDebug>
#include "imagelist.h"
#include "dialogwindowlistofimage.h"
#include "dbdaylisttablemanager.h"
#include "timetabwidgets.h"
namespace Ui {
class DayListWidget;
}

class DayListWidget : public TimeTabWidgets
{
    Q_OBJECT
private:
    Ui::DayListWidget *ui;
    DBDayListTableManager dbDayListTableManager;

    QScopedPointer<DayImageList> currentDayImageList;
    QVector<DayImageList> DayImageLists;
    QVector<TimeRangeImage> currentImageIds;

     bool ValidateDataViewList();

public:
    explicit DayListWidget(QWidget *parent = nullptr);
    ~DayListWidget();
    void CreateInterfaceViewTab();
    void CreatInterfaceCreateTab();
    void UpdateViewTabItem();
    void CreateViewTabItem();
    void PrepareTabForEditingItem(int ListId) override;
    void PrepareTabForCreatingItem() override;
public slots:
    void AcceptSavingOfList() override;
    void addImageInList(int index) override;

    void ShowDialogWindowListOfImage();

    void getTimeEditUpdatetData(int id,QTime startTime,QTime endTime);



};

#endif // DAYLISTWIDGET_H