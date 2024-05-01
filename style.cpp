#include "style.h"

QString Style::getMainWindowStyle()
{
    return "QMainWindow{"
           "background-color: rgb(83, 190, 120);"
           "font-family:'Inter';"
           "}";
}

QString Style::getMainMenuButtonsStyle(){
    return "QPushButton{"
           "color:#ffffff;"
           "background:none;"
           "background-color: rgb(83, 190, 120);"
           "border: 1px solid rgb(255, 255, 255);"
           "border-radius: 20px;"
           "font-size:16px;"
           "font-weight:800;"
           "}"
           "QPushButton::hover{"
           "background-color: #FFFFFF;"
           "color:rgb(83, 190, 120);"
           "}";
}

QString Style::getTabsStyle()
{
    return "QWidget{"
           "background-color: rgb(255, 255, 255);"
           "border-top-left-radius: 50px;"
           " border-bottom-left-radius: 50px;"
           "}";
}

QString Style::getStandartTabStyle()
{
    return "QWidget{"
           "background-color: rgb(232, 248, 238);"
           "border-radius: 20px;"
           "}"
           "QPushButton{"
           "background-color: rgb(83, 190, 120);"
           "border-radius: 15px;"
           "font-family:'Inter';"
           "font-size:16px;"
           "font-weight:800;"
           "color: rgb(255, 255, 255);"
           "}"
           "QPushButton::hover{"
           "background-color: rgba(83, 190, 120, 200)"
           "}"

           "QPushButton#StandartTabDeleteButton{"
           "background-color: rgb(226, 123, 141);"
           "}"
           "QPushButton#StandartTabDeleteButton::hover{"
           "background-color: rgba(226, 123, 141,200);"
           "}"

           "QPushButton#StandartTabChooseButton{"
           " background-color: rgb(249, 177, 105);"
           "}"
           "QPushButton#StandartTabChooseButton::hover{"
           " background-color: rgba(249, 177, 105,200);"
           "}"

           "QPushButton#StandartTabSetButton{"
           "background-color: rgb(123, 145, 223);"
           "}"
           "QPushButton#StandartTabSetButton::hover{"
           "background-color: rgba(123, 145, 223,200);"
           "}"

           "QPushButton#SliderRightArrow,QPushButton#SliderLeftArrow{"
           "background-color: rgba(225, 225, 225,0);"
           "}"
           "QPushButton#SliderRightArrow,QPushButton#SliderLeftArrow::hover{"
           "background-color: rgba(225, 225, 225,40);"
           "}"
            ;
}

QString Style::getTimeTabStyle()
{
    return "QWidget{"
           "background-color: rgb(232, 248, 238);"
           "border-radius: 20px;"
           "}";

}

QString Style::getMenuBarStyle()
{
    return
            "QWidget{"
            "background-color: rgb(232, 248, 238);"

            "border-radius: 20px;"
            "}"
            "QPushButton{"
            "color :rgb(182, 184, 186);"

            "font-size:14px;"
            "} "
            "QPushButton::hover{"
            "color :rgb(182, 184, 186);"
            "text-decoration: underline;"
            "} "
            "QPushButton#TimeTabMenuBarPlusButton,QPushButton#ListOfImageMenuBarPlusButton{"
            "background-color: rgb(226, 123, 141);"
            "color :rgb(255, 255, 255);"
            "font-size: 40px;"
            " padding-bottom: 10px;"
            "} "
            "QPushButton#TimeTabMenuBarPlusButton,QPushButton#ListOfImageMenuBarPlusButton::hover{"
            "background-color: rgba(226, 123, 141,200);"
            "} ";
}

QString Style::getImageListStyle()
{
return             "QWidget{"
                   "background-color: rgb(232, 248, 238);"
                   "border-radius: 10px;}"
                   "";
}





