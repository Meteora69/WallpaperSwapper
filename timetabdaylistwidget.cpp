#include "timetabdaylistwidget.h"
#include "ui_timetabdaylistwidget.h"



TimeTabDayListWidget::TimeTabDayListWidget(QWidget *parent)
    : BaseListWidget(parent), ui(new Ui::TimeTabDayListWidget)
{
    ui->setupUi(this);
    connect(interfaceAddition, &InterfaceAddition::updateTimeEdit, this, &TimeTabDayListWidget::getTimeEditUpdatetData);
    connect(uiElementEventHandler, &UIElementEventHandler::ButtonAddImageClicked, this, &TimeTabDayListWidget::ShowDialogWindowListOfImage);

    currentDayImageList.reset(new DayImageList());

    tabCreateList = tabInterfaceBuilder->buildTabCreateListForDayList(tabWidget,scrollAreaConterinerCreateTab);
    tabWidget->addTab(tabCreateList, "Craete List");

    nameLineEdit = tabInterfaceBuilder->CreateLineEdit(tabCreateList,WidgetGeometry(110,30,90,10));

    CreateInterfaceViewTab();
}

TimeTabDayListWidget::~TimeTabDayListWidget()
{
    delete ui;
}

void TimeTabDayListWidget::CreateInterfaceViewTab()
{
    DayImageLists = dbDayListTableManager.getAllDayImageLists();
    for (auto& list : DayImageLists) {
        scrollAreaManager->setWidgetIntoScrollArea(scrollAreaConterinerViewTab, interfaceAddition->BuildDayListOfImageView(&list));
    }
}

void TimeTabDayListWidget::CreatInterfaceCreateTab()
{
    for (auto& item : currentImageIds) {
        scrollAreaManager->setWidgetIntoScrollArea(scrollAreaConterinerCreateTab, interfaceAddition->BuildDayListOfImageItem(&item));
    }
}
bool TimeTabDayListWidget::ValidateDataViewList()
{
    if(nameLineEdit->text().isEmpty() ||
            2 > currentImageIds.size()) {
         return false;
     } else {
         return true;
     }
}
void TimeTabDayListWidget::UpdateViewTabItem()
{
    currentDayImageList->setName(nameLineEdit->text());
    currentDayImageList->setImages(currentImageIds);
    dbDayListTableManager.updateDayImageList(currentDayImageList.data());
}

void TimeTabDayListWidget::CreateViewTabItem()
{
    currentDayImageList.reset(new DayImageList(nameLineEdit->text(), currentImageIds));
    dbDayListTableManager.insertDayImageList(currentDayImageList.data());
    scrollAreaManager->setWidgetIntoScrollArea(scrollAreaConterinerViewTab, interfaceAddition->BuildDayListOfImageView(currentDayImageList.data()));
}

void TimeTabDayListWidget::PrepareTabForEditingItem(int ListId)
{
    tabWidget->setCurrentIndex(1);
    scrollAreaManager->ClearScrollAreaConteinerWidget(scrollAreaConterinerCreateTab);
    currentDayImageList.reset(new DayImageList(dbDayListTableManager.findDayImageListById(ListId)));
    nameLineEdit->setText(currentDayImageList->getName());
    currentImageIds = currentDayImageList->getImages();
    CreatInterfaceCreateTab();
}

void TimeTabDayListWidget::PrepareTabForCreatingItem()
{
    currentDayImageList.reset(new DayImageList());
    nameLineEdit->clear();
    currentImageIds.clear();
    scrollAreaManager->ClearScrollAreaConteinerWidget(scrollAreaConterinerCreateTab);
    tabWidget->setCurrentIndex(1);
}

void TimeTabDayListWidget::addImageInList(int index)
{
    int id;
    if (currentImageIds.isEmpty()) {
        id = 1;
    } else {
        id = currentImageIds.last().id + 1;
    }
    TimeRangeImage newImage("00:00", "00:00", index, id);
    currentImageIds.push_back(newImage);
    scrollAreaManager->setWidgetIntoScrollArea(scrollAreaConterinerCreateTab, interfaceAddition->BuildDayListOfImageItem(&newImage));

    dialogWindowController->Close();
}

void TimeTabDayListWidget::getTimeEditUpdatetData(int id, QTime startTime, QTime endTime)
{
    qDebug() <<id;
    QString startTimeStr = startTime.toString("HH:mm");
    QString endTimeStr = endTime.toString("HH:mm");

    for (auto& image : currentImageIds) {
        if (image.id == id) {
            image.startTime = startTimeStr;
            image.endTime = endTimeStr;
            qDebug() << "Updated image with id:" << id;
            qDebug() << "New startTime:" << image.startTime;
            qDebug() << "New endTime:" << image.endTime;
            return;
        }
    }

    qDebug() << "Image with id:" << id << "not found in currentImageIds.";
}

void TimeTabDayListWidget::ShowDialogWindowListOfImage()
{
    dialogWindowController->Open(this);
}

void TimeTabDayListWidget::AcceptSavingOfList()
{
    if(ValidateDataViewList()){
    int CurrenDayListId = currentDayImageList->getId();
    try{
        if (CurrenDayListId == -1) {
            CreateViewTabItem();
        } else if (CurrenDayListId > 0) {
            UpdateViewTabItem();
            scrollAreaManager->ClearScrollAreaConteinerWidget(scrollAreaConterinerViewTab);
            CreateInterfaceViewTab();
        }else {
            throw WSExeptions("Error: Day List has incorrect index: " + CurrenDayListId);
        }
    } catch (const WSExeptions& e) {
        qDebug() << e.what();
    }

    tabWidget->setCurrentIndex(0);
    }
    else{
        QMessageBox::warning(this, "Warning", "Before creating the list, please make sure that you have entered a name and added at least two images with setted time.");
    }
}
