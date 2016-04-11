#ifndef __IP_VALIDATOR_H__
#define __IP_VALIDATOR_H__

#include "Libs.h"

//=============================================================================
class CustomIpEditor : public QFrame
{
    Q_OBJECT
public:
    explicit CustomIpEditor(QWidget *parent = 0);
    virtual ~CustomIpEditor() {}
};

//=============================================================================
class CustomLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit CustomLineEdit(const QString & contents = "", QWidget *parent = 0);
    virtual ~CustomLineEdit() {}

signals:
    void jumpForward();
    void jumpBackward();

public slots:
    void jumpIn();

protected:
    virtual void focusInEvent(QFocusEvent *event);
    virtual void keyPressEvent(QKeyEvent * event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

private:
    bool selectOnMouseRelease;
};

#endif // __IP_VALIDATOR_H__

