#include "randomlistwidget.h"
#include "ui_randomlistwidget.h"

RandomListWidget::RandomListWidget(QWidget* parent)
    : TimeTabWidgets(parent), ui(new Ui::RandomListWidget)
{
    ui->setupUi(this);
    CurrentRandomImageList.reset(new RandomImageList());
    connect(uiElementEventHandler, &UIElementEventHandler::ButtonAddImageClicked, this, &RandomListWidget::ShowDialogWindowListOfImage);

    tabCreateList = tabInterfaceBuilder->buildTabCreateListForRandomList(tabWidget,scrollAreaConterinerCreateTab);
    tabWidget->addTab(tabCreateList, "Craete List");

    nameLineEdit = tabInterfaceBuilder->CreateLineEdit(tabCreateList,WidgetGeometry(110,30,90,10));
    timeEdit = tabInterfaceBuilder->CreateTimeEdit(tabCreateList,WidgetGeometry(70,30,410,10));
    CreateInterfaceViewTab();
}

RandomListWidget::~RandomListWidget()
{
    delete ui;
}

void RandomListWidget::CreateInterfaceViewTab()
{
    RandomImageLists = dbManager.getAllRandomImageLists();
    for (const auto& list : RandomImageLists)
        scrollAreaManager->setWidgetIntoScrollArea(scrollAreaConterinerViewTab, interfaceAddition->BuildRandomListView(&list));
}

void RandomListWidget::CreatInterfaceCreateTab()
{
    for (int i = 0; i < currentImageIds.size(); i++){
        QWidget* itemWidget = interfaceAddition->BuildRandomListItem(imageList->findImageById(currentImageIds[i]));
        scrollAreaManager->setWidgetIntoScrollArea(scrollAreaConterinerCreateTab, itemWidget);
    }
}

void RandomListWidget::CreateViewTabItem()
{
    CurrentRandomImageList.reset(new RandomImageList(nameLineEdit->text(), timeEdit->dateTime(), currentImageIds));
    dbManager.insertImageList(CurrentRandomImageList.data());
}

void RandomListWidget::UpdateViewTabItem()
{
    CurrentRandomImageList->setName(nameLineEdit->text());
    CurrentRandomImageList->setTimeInterval(timeEdit->dateTime());
    CurrentRandomImageList->setImageIds(currentImageIds);
    dbManager.updateRandomImageList(CurrentRandomImageList.data());
}

void RandomListWidget::PrepareTabForCreatingItem()
{
    CurrentRandomImageList.reset(new RandomImageList());
    nameLineEdit->clear();
    timeEdit->setTime(QTime(0, 0));
    currentImageIds.clear();
    scrollAreaManager->ClearScrollAreaConteinerWidget(scrollAreaConterinerCreateTab);
    tabWidget->setCurrentIndex(1);
}

void RandomListWidget::PrepareTabForEditingItem(int ListId)
{
    tabWidget->setCurrentIndex(1);
    scrollAreaManager->ClearScrollAreaConteinerWidget(scrollAreaConterinerCreateTab);
    CurrentRandomImageList.reset(new RandomImageList(dbManager.FindRandomImageListById(ListId)));
    currentImageIds = CurrentRandomImageList->getImageIds();
    nameLineEdit->setText(CurrentRandomImageList->getName());
    timeEdit->setTime(CurrentRandomImageList->getTimeInterval().time());
    CreatInterfaceCreateTab();
}

void RandomListWidget::addImageInList(int index)
{
    scrollAreaManager->setWidgetIntoScrollArea(scrollAreaConterinerCreateTab, interfaceAddition->BuildRandomListItem(index));
    currentImageIds.append(imageList->GetImageByIndex(index).getId());
    dialogWindowController->Close();
}

void RandomListWidget::ShowDialogWindowListOfImage()
{
    dialogWindowController->Open(this);
}

bool RandomListWidget::ValidateDataViewList()
{
    if(nameLineEdit->text().isEmpty() ||
            timeEdit->text().isEmpty() ||
           2 > currentImageIds.size()) {
        return false;
    } else {
        return true;
    }
}

void RandomListWidget::AcceptSavingOfList()
{
    if(ValidateDataViewList()){
        try {
            int CurrentRandomListId = CurrentRandomImageList->getId();
            if (CurrentRandomListId == -1) {
                CreateViewTabItem();
                RandomImageLists = dbManager.getAllRandomImageLists();
                scrollAreaManager->setWidgetIntoScrollArea(scrollAreaConterinerViewTab, interfaceAddition->BuildRandomListView(&RandomImageLists.last()));
            } else if (CurrentRandomListId > 0) {
                UpdateViewTabItem();
                scrollAreaManager->ClearScrollAreaConteinerWidget(scrollAreaConterinerViewTab);
                CreateInterfaceViewTab();
            } else {
                throw WSExceptions("Error: Random List has incorrect index: " + CurrentRandomListId);
            }
        } catch (const WSExceptions& e) {
            qDebug() << "Caught WSExceptions: " << e.what();
        }

        tabWidget->setCurrentIndex(0);
    }
    else{
        QMessageBox::warning(this, "Warning", "Before creating the list, please make sure that you have entered a name, set the time interval, and added at least two images.");
    }
}

