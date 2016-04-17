#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include <QMainWindow>

#include "Libs.h"

#include <IP_Validator.h>
#include <portValidator.h>

#include "Peers.hpp"

/// Тип сообщения
///-->
enum MessageType {
  USUAL_MESSAGE, // Обычный текст
  PERSON_ONLINE, // Сообщение "Я-онлайн"
  WHO_IS_ONLINE, // Запрос о статусе пользователей
};
///<--

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(int argc, QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow* ui;
    Peer* _peer;
    QGridLayout* _pgrdLayout;
    QLineEdit* _lnedMessage;

    void messageTransfer();

public slots:
    void clickedSlot();

};



#endif // __MAINWINDOW_H__
