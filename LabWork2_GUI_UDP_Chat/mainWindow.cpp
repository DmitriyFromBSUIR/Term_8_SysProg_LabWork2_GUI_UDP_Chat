#include "mainWindow.h"
#include "ui_mainwindow.h"

//#include "Peers.hpp"

/*
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
*/
/*
void MainMenu(QMainWindow* mainWin) {

}
*/

void MainWindow:: messageTransfer() {
    QString msg = _lnedMessage->text();
    QByteArray bArr = msg.toLocal8Bit();
    string userMsg = string(bArr.data(), bArr.size());
    _peer->setCurrrentMessage(userMsg);
}

void MainWindow:: clickedSlot(){
    messageTransfer();
    _peer->run();
}

MainWindow::MainWindow(int argc, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //MainMenu();

    if(argc == 2)
        _peer = new Peer("192.168.0.12", "37000");
    else
        _peer = new Peer("192.168.0.12", "38000");

    //
    _pgrdLayout = new QGridLayout;
    //
    QLabel* lblGroupIP = new QLabel("Multicast IP (Group: All-Hosts) : ");
    CustomIpEditor* myIpEdGroupIP = new CustomIpEditor;
    QLabel* lblGroupPort = new QLabel("             Multicast Port (Group: All-Hosts) : ");
    PortValidatorWidget* grpPort = new PortValidatorWidget;
    //
    QLabel* lblThisHostUserIP = new QLabel("My IP : ");
    CustomIpEditor* myIpEdThisHostUserIP = new CustomIpEditor;
    QLabel* lblThisHostUserPort = new QLabel("              My Port : ");
    PortValidatorWidget* thisUserPort = new PortValidatorWidget;
    //
    QLabel* lblThisUserNickname = new QLabel("My Nickname : ");
    QLineEdit* thisUserNickname = new QLineEdit;
    QLabel* lblThisUserPassword = new QLabel("              My Password : ");
    QLineEdit* thisUserPassword = new QLineEdit;
    thisUserPassword->setEchoMode(QLineEdit::Password);
    QLabel* lblUserDataSpacer = new QLabel("    ");
    QPushButton* btnLogin = new QPushButton("LOGIN");
    btnLogin->setMinimumSize(QSize(100,40));
    btnLogin->setMaximumSize(QSize(100,40));
    //
    QLabel* lblRemotePeerIP = new QLabel("Peer IP : ");
    CustomIpEditor* myIpEdRemotePeerIP = new CustomIpEditor;
    QLabel* lblRemotePeerPort = new QLabel("                Peer Port : ");
    PortValidatorWidget* rmtPeerPort = new PortValidatorWidget;
    QLabel* lblPeerDataSpacer = new QLabel("    ");
    QPushButton* btnSendToPeerByIP = new QPushButton("Send");
    btnSendToPeerByIP->setMinimumSize(QSize(100,40));
    btnSendToPeerByIP->setMaximumSize(QSize(100,40));
    //
    QLabel* lblMessage = new QLabel("                       Message: ");
    _lnedMessage = new QLineEdit;
    _lnedMessage->setMinimumSize(QSize(100, 30));
    //QLabel* lblPeerName = new QLabel("Peer Name: ");
    //QLineEdit* lnedPeerName = new QLineEdit;
    QPushButton* btnSendToPeerByName = new QPushButton("Send");
    //btnSendToPeerByName->setText("Send");
    btnSendToPeerByName->setMinimumSize(QSize(100,40));
    btnSendToPeerByName->setMaximumSize(QSize(100,40));
    //
    QObject:: connect(btnSendToPeerByIP, SIGNAL(clicked()), this, SLOT(clickedSlot()));
    //
    QLabel* lblPeersNicknamesList = new QLabel("The List of Online Users: ");
    QListWidget* lwListOfPeers = new QListWidget;
    //QListWidget lwListOfPeers;
    //QStringList slListOfPeers = new QStringList;
    QListWidgetItem* lwListOfPeersItem = 0;
    QStringList slListOfPeers;
    //slListOfPeers << "Windows" << "Lunux" << "MacOS_X" ;
    foreach(QString item, slListOfPeers) {
        lwListOfPeersItem = new QListWidgetItem(item, lwListOfPeers);
        //lwListOfPeersItem->setIcon
    }
    //
    QLabel* lblLog = new QLabel("Log:");
    QTextEdit* txtedLog = new QTextEdit;

    //
    _pgrdLayout->addWidget(lblGroupIP, 0, 0);
    _pgrdLayout->addWidget(myIpEdGroupIP, 0, 1);
    _pgrdLayout->addWidget(lblGroupPort, 0, 2);
    _pgrdLayout->addWidget(grpPort, 0, 3);
    //
    _pgrdLayout->addWidget(lblThisHostUserIP, 1, 0);
    _pgrdLayout->addWidget(myIpEdThisHostUserIP, 1, 1);
    _pgrdLayout->addWidget(lblThisHostUserPort, 1, 2);
    _pgrdLayout->addWidget(thisUserPort, 1, 3);
    //
    _pgrdLayout->addWidget(lblThisUserNickname, 2, 0);
    _pgrdLayout->addWidget(thisUserNickname, 2, 1);
    _pgrdLayout->addWidget(lblThisUserPassword, 2, 2);
    _pgrdLayout->addWidget(thisUserPassword, 2, 3);
    _pgrdLayout->addWidget(lblUserDataSpacer, 2, 4);
    _pgrdLayout->addWidget(btnLogin, 2, 5);
    //
    _pgrdLayout->addWidget(lblRemotePeerIP, 3, 0);
    _pgrdLayout->addWidget(myIpEdRemotePeerIP, 3, 1);
    _pgrdLayout->addWidget(lblRemotePeerPort, 3, 2);
    _pgrdLayout->addWidget(rmtPeerPort, 3, 3);
    _pgrdLayout->addWidget(lblPeerDataSpacer, 3, 4);
    _pgrdLayout->addWidget(btnSendToPeerByIP, 3, 5);
    //
    _pgrdLayout->addWidget(lblMessage, 4, 0);
    //pgrdLayout->addWidget(lnedMessage, 4, 1, 1, 4, Qt:: AlignCenter);
    _pgrdLayout->addWidget(_lnedMessage, 4, 1, 1, 5);
    //
    _pgrdLayout->addWidget(lblPeersNicknamesList, 0, 6);
    _pgrdLayout->addWidget(lwListOfPeers, 1, 6, 8, 6);
    //
    _pgrdLayout->addWidget(lblLog, 5, 0);
    _pgrdLayout->addWidget(txtedLog, 6, 0, 5, 6);


    centralWidget()->setLayout(_pgrdLayout);

    //centralWidget()->layout()->addWidget(myEditor);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//=============================================================================
CustomLineEdit::CustomLineEdit(const QString & contents, QWidget *parent) :
    QLineEdit(contents, parent), selectOnMouseRelease(false)
{
    QIntValidator *valid = new QIntValidator(0, 255, this);
    setValidator(valid);
}

void CustomLineEdit::jumpIn()
{
    setFocus();

    selectOnMouseRelease = false;
    selectAll();
}

void CustomLineEdit::focusInEvent(QFocusEvent *event)
{
    QLineEdit::focusInEvent(event);
    selectOnMouseRelease = true;
}

void CustomLineEdit::keyPressEvent(QKeyEvent * event)
{
    int key = event->key();
    int cursorPos = cursorPosition();

    // Jump forward by Space
    if (key == Qt::Key_Space) {
        emit jumpForward();
        event->accept();
        return;
    }

    // Jump Backward only from 0 cursor position
    if (cursorPos == 0) {
        if ((key == Qt::Key_Left) || (key == Qt::Key_Backspace)) {
            emit jumpBackward();
            event->accept();
            return;
        }
    }

    // Jump forward from last postion by right arrow
    if (cursorPos == text().count()) {
        if (key == Qt::Key_Right) {
            emit jumpForward();
            event->accept();
            return;
        }
    }

    // After key is placed cursor has new position
    QLineEdit::keyPressEvent(event);
    int freshCurPos = cursorPosition();

    if ((freshCurPos == 3) && (key != Qt::Key_Right))
        emit jumpForward();
}

void CustomLineEdit::mouseReleaseEvent(QMouseEvent *event)
{
    if(!selectOnMouseRelease)
        return;

    selectOnMouseRelease = false;
    selectAll();

    QLineEdit::mouseReleaseEvent(event);
}

//=============================================================================
void makeCommonStyle(QLineEdit* line) {
    line->setContentsMargins(0, 0, 0, 0);
    line->setAlignment(Qt::AlignCenter);
    line->setStyleSheet("QLineEdit { border: 0px none; }");
    line->setFrame(false);
    line->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
}

QLineEdit* makeIpSpliter() {
    QLineEdit *spliter = new QLineEdit(".");
    makeCommonStyle(spliter);

    spliter->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spliter->setMaximumWidth(10);
    spliter->setReadOnly(true);
    spliter->setFocusPolicy(Qt::NoFocus);
    return spliter;
}

CustomIpEditor::CustomIpEditor(QWidget *parent) :
    QFrame(parent)
{
    setContentsMargins(0, 0, 0, 0);
    setStyleSheet("QFrame { background-color: white;  border: 1px solid white; border-radius: 15px; }");

    QList <CustomLineEdit *>  lines;
    QList <CustomLineEdit *>::iterator linesIterator;

    lines.append(new CustomLineEdit);
    lines.append(new CustomLineEdit);
    lines.append(new CustomLineEdit);
    lines.append(new CustomLineEdit);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setSpacing(0);
    setLayout(mainLayout);

    for (linesIterator = lines.begin(); linesIterator != lines.end(); ++linesIterator) {
        makeCommonStyle(*linesIterator);
        mainLayout->addWidget(*linesIterator);

        if (*linesIterator != lines.last()) {
            connect(*linesIterator, &CustomLineEdit::jumpForward,
                    *(linesIterator+1), &CustomLineEdit::jumpIn);
            mainLayout->addWidget(makeIpSpliter());
        }
        if (*linesIterator != lines.first()) {
            connect(*linesIterator, &CustomLineEdit::jumpBackward,
                    *(linesIterator-1), &CustomLineEdit::jumpIn);
        }
    }

}
