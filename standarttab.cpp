#include "standarttab.h"
#include "ui_standarttab.h"
#include "style.h"
StandartTab::StandartTab(DBManager *dbManager, ImagesList *imageManager, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StandartTab), dbManager(dbManager),imageManager(imageManager)
{
    ui->setupUi(this);
   // imageManager = new ImageManager(dbManager);
    setStandartTabStyle();
    interfaceAddition = new InterfaceAddition(parent,imageManager);
    imageLoader = new ImageLoader(dbManager);
    wlapperSetter = new WlapperSetter();

    CreateDialogWindowListOfImage();
}

StandartTab::~StandartTab()
{
    delete ui;
}

void StandartTab::showImage(int index)
{
    if (index >= 0 && index < imageManager->getsizeOfImages()) {
        QPixmap pixmap(imageManager->GetImageByIndex(index).getUrl());
        ui->SliderImage->setPixmap(pixmap.scaled(ui->SliderImage->size(), Qt::KeepAspectRatio));
    }
}

void StandartTab::nextImage()
{
    currentIndex = (currentIndex + 1) % imageManager->getsizeOfImages();
    showImage(currentIndex);
}
void StandartTab::previousImage()
{
    currentIndex = (currentIndex - 1 + imageManager->getsizeOfImages()) % imageManager->getsizeOfImages();
    showImage(currentIndex);
}
void StandartTab::setStandartTabStyle()
{
    ui->StandartTabWidget->setStyleSheet(Style::getTabsStyle());
    ui->StandartTabButtonMenuWidget->setStyleSheet(Style::getStandartTabStyle());
    ui->StandartTabWlapperSliderWidget->setStyleSheet(Style::getStandartTabStyle());

    setSliderButtonIcon();
    showImage(currentIndex);
}

void StandartTab::setSliderButtonIcon()
{
    ui->SliderRightArrow->setIcon(QIcon(":/resource/SliderRightArrow.png"));
    ui->SliderRightArrow->setIconSize(QSize(65, 65));
    ui->SliderLeftArrow->setIcon(QIcon(":/resource/SliderLeftArrow.png"));
    ui->SliderLeftArrow->setIconSize(QSize(65, 65));
}

void StandartTab::CreateDialogWindowListOfImage()
{
    dialogWindowListOfImage = new DialogWindowListOfImage(this->dbManager,imageManager,interfaceAddition,this);
    connect(interfaceAddition, &InterfaceAddition::imageSelected, this, &StandartTab::updateImage);
    dialogWindowListOfImage->setStyleSheet(Style::getTabsStyle());
}

void StandartTab::displayImageInLabel(QLabel *label, const QString &filePath)
{
    QPixmap pixmap(filePath);
    if (!pixmap.isNull()) {
        label->setPixmap(pixmap.scaled(label->size(), Qt::KeepAspectRatio));
        label->setScaledContents(true);
        qDebug() << "Pixmap loaded successfully, Size:" << pixmap.size();
    } else {
        qDebug() << "Failed to load pixmap.";
    }
}


void StandartTab::on_StandartTabChooseButton_clicked(){
    dialogWindowListOfImage ->showDialogWindow();
}
void StandartTab::on_StandartTabAddButton_clicked() {
    if(imageLoader->ChooseImageFromFiles()){
        imageManager ->getImagesFromTable();

    int imageId = imageManager->getImages().last().getId();
       if (imageId != -1) {  // Перевірте, що ID є дійсним
           currentIndex = imageManager->findImageById(imageId); // Вам потрібно написати цю функцію
           if (currentIndex != -1) { // Переконайтеся, що індекс існує
               displayImageInLabel(ui->SliderImage, imageManager->GetImageByIndex(currentIndex).getUrl());
               showImage(currentIndex);
           }
       }
}else{
        qDebug() << "Image not loadet!";
      }
}
void StandartTab::on_SliderLeftArrow_clicked()
{
    previousImage();
}

void StandartTab::on_SliderRightArrow_clicked()
{
    nextImage();
}


void StandartTab::on_StandartTabSetButton_clicked()
{
    wlapperSetter-> setWallpaper(imageManager->GetImageByIndex(currentIndex).getUrl());
}

void StandartTab::on_StandartTabDeleteButton_clicked()
{
    imageManager->deleteImageByIndex(currentIndex);

    nextImage();
}

void StandartTab::updateImage(int index)
{
    currentIndex = index;
    showImage(currentIndex);
    dialogWindowListOfImage ->hide();
}

