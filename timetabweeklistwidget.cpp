#include "timetabweeklistwidget.h"
#include "ui_timetabweeklistwidget.h"


TimeTabWeekListWidget::TimeTabWeekListWidget(QWidget *parent)
    : BaseListWidget(parent), ui(new Ui::TimeTabWeekListWidget)
{
    ui->setupUi(this);

    connect(uiElementEventHandler, &UIElementEventHandler::setImageIntoWeekListItem, this, &TimeTabWeekListWidget::ShowDialogWindowListOfImage);
    currentImageIds = fillCurrentImageIds(days);

    currentWeekImageList.reset(new WeekImageList());

    tabCreateList = tabInterfaceBuilder->buildTabCreateListForWeekList(tabWidget, scrollAreaConterinerCreateTab);
    tabWidget->addTab(tabCreateList, "Create List");

    nameLineEdit = tabInterfaceBuilder->CreateLineEdit(tabCreateList, WidgetGeometry(110, 30, 90, 10));
    CreateInterfaceViewTab();
}

TimeTabWeekListWidget::~TimeTabWeekListWidget()
{
    delete ui;
}

void TimeTabWeekListWidget::CreatInterfaceCreateTab()
{
    for (const QString& day : days) {
        if (currentImageIds.contains(day)) {
            scrollAreaManager->setWidgetIntoScrollArea(scrollAreaConterinerCreateTab, interfaceAddition->BuildWeekListOfImageItem(currentImageIds[day], day));
        } else {
            qDebug() << "Key" << day << "not found in currentImageIds";
            interfaceAddition->BuildWeekListOfImageItem(-1, day);
        }
    }
}


void TimeTabWeekListWidget::CreateInterfaceViewTab()
{
    WeekImageLists = dbWeekListTableManager.getAllWeekImageLists();
    for (const auto& list : WeekImageLists) {
        scrollAreaManager->setWidgetIntoScrollArea(scrollAreaConterinerViewTab, interfaceAddition->BuildWeekListOfImageView(&list));
    }
}

void TimeTabWeekListWidget::CreateViewTabItem()
{
    if (currentImageIds["Other days"] == -1) {
        for (const QString& day : days) {
            if (day != "Other days" && currentImageIds[day] != -1) {
                currentImageIds["Other days"] = currentImageIds[day];
                break;
            }
        }
    }
    currentWeekImageList.reset(new WeekImageList(nameLineEdit->text(), currentImageIds));
    dbWeekListTableManager.insertWeekImageList(currentWeekImageList.data());
    scrollAreaManager->setWidgetIntoScrollArea(scrollAreaConterinerViewTab, interfaceAddition->BuildWeekListOfImageView(currentWeekImageList.data()));
}
bool TimeTabWeekListWidget::ValidateDataViewList()
{
        if (nameLineEdit->text().isEmpty()) {
            return false;
        }

        int validImageCount = 0;
        for (int value : currentImageIds.values()) {
            if (value != -1) {
                validImageCount++;
                if (validImageCount >= 2) {
                    return true;
                }
            }
        }

        return false;
}
void TimeTabWeekListWidget::UpdateViewTabItem()
{
    currentWeekImageList->setName(nameLineEdit->text());
    currentWeekImageList->setImages(currentImageIds);
    dbWeekListTableManager.updateWeekImageList(currentWeekImageList.data());
}

void TimeTabWeekListWidget::PrepareTabForEditingItem(int ListId)
{
    tabWidget->setCurrentIndex(1);
    scrollAreaManager->ClearScrollAreaConteinerWidget(scrollAreaConterinerCreateTab);
    currentWeekImageList.reset(new WeekImageList(dbWeekListTableManager.findWeekImageListById(ListId)));
    nameLineEdit->setText(currentWeekImageList->getName());
    currentImageIds = currentWeekImageList->getImages();
    CreatInterfaceCreateTab();
}

void TimeTabWeekListWidget::PrepareTabForCreatingItem()
{
    currentWeekImageList.reset(new WeekImageList());
    currentImageIds = fillCurrentImageIds(days);
    scrollAreaManager->ClearScrollAreaConteinerWidget(scrollAreaConterinerCreateTab);
    CreatInterfaceCreateTab();
    tabWidget->setCurrentIndex(1);
}

QMap<QString, int> TimeTabWeekListWidget::fillCurrentImageIds(const QStringList &keys)
{
    QMap<QString, int> currentImageIds;
    for (const QString& key : keys) {
        currentImageIds[key] = -1;
    }
    return currentImageIds;
}

void TimeTabWeekListWidget::AcceptSavingOfList()
{
    if (ValidateDataViewList()) {
           int CurrentWeekListId = currentWeekImageList->getId();
           try {
               if (CurrentWeekListId == -1) {
                   CreateViewTabItem();
               } else if (CurrentWeekListId > 0) {
                   UpdateViewTabItem();
                   scrollAreaManager->ClearScrollAreaConteinerWidget(scrollAreaConterinerViewTab);
                   CreateInterfaceViewTab();
               } else {
                   throw WSExeptions("Error: Week List has incorrect index: " + CurrentWeekListId);
               }
           } catch (const WSExeptions& e) {
               qDebug() << "Caught WSExeptions: " << e.what();
           }

           tabWidget->setCurrentIndex(0);
       } else {
           QMessageBox::warning(this, "Warning", "Before saving the list, please ensure that you have entered a name and added at least two images.");
       }
}
void TimeTabWeekListWidget::ShowDialogWindowListOfImage(QString day)
{
    dialogWindowController->Open(this);
    currentDay = day;
}

void TimeTabWeekListWidget::addImageInList(int index)
{
    if (currentImageIds.contains(currentDay)) {
        currentImageIds[currentDay] = index;
        qDebug() << "Updated image index for" << currentDay << "to" << index;
    } else {
        qDebug() << "Key" << currentDay << "not found in currentImageIds";
    }

    scrollAreaManager->ClearScrollAreaConteinerWidget(scrollAreaConterinerCreateTab);
    CreatInterfaceCreateTab();
    dialogWindowController->Close();
}

