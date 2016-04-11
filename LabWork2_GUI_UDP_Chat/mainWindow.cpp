#include "mainWindow.h"
#include "ui_mainwindow.h"



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
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //MainMenu();

    //
    QGridLayout* pgrdLayout = new QGridLayout;
    //
    QLabel* lblGroupIP = new QLabel("Multicast IP (Group: All-Hosts) : ");
    CustomIpEditor* myIpEdGroupIP = new CustomIpEditor;
    QLabel* lblGroupPort = new QLabel("Multicast Port (Group: All-Hosts) : ");
    PortValidatorWidget* grpPort = new PortValidatorWidget;
    //
    QLabel* lblThisHostUserIP = new QLabel("My IP : ");
    CustomIpEditor* myIpEdThisHostUserIP = new CustomIpEditor;
    QLabel* lblThisHostUserPort = new QLabel("My Port : ");
    PortValidatorWidget* thisUserPort = new PortValidatorWidget;
    //
    QLabel* lblRemotePeerIP = new QLabel("Peer IP : ");
    CustomIpEditor* myIpEdRemotePeerIP = new CustomIpEditor;
    QLabel* lblRemotePeerPort = new QLabel("Peer Port : ");
    PortValidatorWidget* rmtPeerPort = new PortValidatorWidget;
    //
    pgrdLayout->addWidget(lblGroupIP, 0, 0);
    pgrdLayout->addWidget(myIpEdGroupIP, 0, 1);
    pgrdLayout->addWidget(lblGroupPort, 0, 2);
    pgrdLayout->addWidget(grpPort, 0, 3);
    //
    pgrdLayout->addWidget(lblThisHostUserIP, 1, 0);
    pgrdLayout->addWidget(myIpEdThisHostUserIP, 1, 1);
    pgrdLayout->addWidget(lblThisHostUserPort, 1, 2);
    pgrdLayout->addWidget(thisUserPort, 1, 3);
    //
    pgrdLayout->addWidget(lblRemotePeerIP, 2, 0);
    pgrdLayout->addWidget(myIpEdRemotePeerIP, 2, 1);
    pgrdLayout->addWidget(lblRemotePeerPort, 2, 2);
    pgrdLayout->addWidget(rmtPeerPort, 2, 3);

    centralWidget()->setLayout(pgrdLayout);

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
