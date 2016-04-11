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
            emit textChanged();
            //return 1;
        }
        this->clearFocus();
        //return 0;
    }

protected:
    virtual void mouseReleaseEvent(QMouseEvent *event) {
        QLineEdit::mouseReleaseEvent(event);
    }

public:
    //PortValidatorWidget( QWidget* parent = 0 ) : QWidget( parent ) {
    PortValidatorWidget( QWidget* parent = 0 ) : QLineEdit( parent ) {

        _intPortEdit = new QLineEdit;
        // Валидатор целых чисел от 1024 до 49151
        setValidator( new QIntValidator( 1024, 49151 ) );
        _intPortEdit->setStyleSheet("QFrame { background-color: white;  border: 1px solid white; border-radius: 15px; }");
        connect( this, SIGNAL( textChanged() ), SLOT( onCheckUp() ) );
        //connect( _intPortEdit, SIGNAL( textEdited() ), SLOT( onCheckUp() ) );
        //connect( _intPortEdit, SIGNAL( selectionChanged() ), SLOT( onCheckUp() ) );
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

