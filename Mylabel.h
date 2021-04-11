#ifndef MYLABEL_H
#define MYLABEL_H
#include"QLabel"
#include"mainwindow.h"

class MainWindow;
class Mylabel:public QLabel
{
    Q_OBJECT
public:
    Mylabel(QWidget *parent=0);
    ~Mylabel(){}
    int f;
    MainWindow *mw;
signals:
    void clicked();

public slots:
    void slotClicked();

protected:
    void mousePressEvent(QMouseEvent* event);

};

#endif // MYLABEL_H
