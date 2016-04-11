#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include <QMainWindow>

#include "Libs.h"

#include <IP_Validator.h>
#include <portValidator.h>

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
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};



#endif // __MAINWINDOW_H__
