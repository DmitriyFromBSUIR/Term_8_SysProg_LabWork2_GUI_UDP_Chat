#ifndef __PORTVALIDATOR_H__
#define __PORTVALIDATOR_H__

#include "Libs.h"

//class PortValidatorWidget: public QWidget {
class PortValidatorWidget: public QLineEdit {
    Q_OBJECT

private:
    QLineEdit* _intPortEdit;

    virtual void focusOutEvent(QFocusEvent *e) {
        if(isModified()) {
            this->clearFocus();
            setReadOnly(true);
            emit textChanged();
            //return 1;
        }

        setReadOnly(true);
        //this->clearFocus();
        //return 0;
    }
/*
    virtual void focusInEvent(QFocusEvent *e) {

        setReadOnly(false);

    }
*/
    virtual void mousePressEvent(QMouseEvent *e) {

        setReadOnly(false);

    }
protected:
    virtual void mouseReleaseEvent(QMouseEvent *event) {
        QLineEdit::mouseReleaseEvent(event);
    }

public:
    //PortValidatorWidget( QWidget* parent = 0 ) : QWidget( parent ) {
    PortValidatorWidget( QWidget* parent = 0 ) : QLineEdit( parent ) {
        //setStyle(new QLineEditStyle(style()));
        //_intPortEdit = new QLineEdit(this);
        // Валидатор целых чисел от 1024 до 49151
        setValidator( new QIntValidator( 1024, 49151 ) );
        setMinimumSize(QSize(60, 10));
        setStyleSheet("QFrame { background-color: white;  border: 1px solid white; border-radius: 15px; }");
        connect( this, SIGNAL( textChanged() ), SLOT( onCheckUp() ) );
    }

signals:
    void textChanged();

private slots:
    void onCheckUp() {
        if( hasAcceptableInput() ) {
            // Если условие валидатора выполнено
            //_intPortEdit->setText(intEdit);
            //qDebug() << e->text();
            setText(text());
        } else {

            // Если условие валидатора нарушено
            //_intPortEdit->setText("");
            setText("");
            // qDebug() << "Invalid";
        }
    }
};



#endif // __PORTVALIDATOR_H__

