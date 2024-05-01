#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "style.h"
#include <QStyleOption>
#include <QDebug>
#include <QFontDatabase>
MainWindow::MainWindow(DBManager* dbManager,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), dbManager(dbManager)
{
    ui->setupUi(this);

    setInterfaceStyle();
    standartTab = new StandartTab(this->dbManager,this);
    standartTab ->show();
    standartTab ->move(165, 0);
   // standartTab->setStyleSheet(Style::getTabsStyle());

//    timeTab = new TimeTab(this->dbManager,this);
//    timeTab->show();
//    timeTab->move(165, 0);

}

//void MainWindow::addNewImage()
//{
//    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Wlapper"), "/wlapper", tr("Image Files (*.png *.jpg *.bmp *.jpeg)"));
//    qDebug() << "File selected:" << fileName;

//    if (!fileName.isEmpty()) {
//        QImage image = loadImage(fileName);
//        if (!image.isNull()) {
//            auto wlapperImage = createWlapperImage(fileName, image);
//            displayImageInLabel(ui->SliderImage, fileName);

//            if (!dbManager->insertIntoImageTable(*wlapperImage)) {
//                qDebug() << "Error inserting data into the database.";
//            }
//        }
//    } else {
//        qDebug() << "No file selected.";
//    }
//}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::PaintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(event);
}


void MainWindow::setInterfaceStyle()
{
    int fontId = QFontDatabase::addApplicationFont(":/resource/fonts/Inter-Regular.ttf");
    QString family = QFontDatabase::applicationFontFamilies(fontId).at(0);

    this->setStyleSheet(Style::getMainWindowStyle());
    ui->mainMenuStandartButton->setStyleSheet(Style::getMainMenuButtonsStyle());
    ui->mainMenuTimeButton->setStyleSheet(Style::getMainMenuButtonsStyle());
    ui->mainMenuMoodButton->setStyleSheet(Style::getMainMenuButtonsStyle());
    ui->mainMenuFutureButton->setStyleSheet(Style::getMainMenuButtonsStyle());

}

