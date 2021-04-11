#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"QVector"
#include"Mylabel.h"

#define Mx 20
#define My 20
QT_BEGIN_NAMESPACE
class Mylabel;
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    friend class Mylabel;
private slots:
    void on_pushButton_5_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    int sx,sy,tx,ty,state[Mx][My];
    int fs,fq,ft,f;

    QVector<Mylabel*>vlabel;
    int back();
    void DFS();
    void BFS();
    void clear();
    void AStar();
    int Heuristic(int x,int y,int k);
};
#endif // MAINWINDOW_H
