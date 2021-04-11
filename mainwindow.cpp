#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"qstack.h"
#include"QQueue"
#include <time.h>
#include"algorithm"
#include"math.h"
#define P QPair<int,int>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Search");

    QPalette label_palette;
    label_palette.setColor(QPalette::Background, QColor("white"));
    for(int i=0;i<Mx;i++){
        for(int j=0;j<My;j++){
            state[i][j]=0;
            Mylabel *lab=new Mylabel(this);
            lab->setAutoFillBackground(true); //这句很关键，否则背景色被默认windows替代
            lab->setPalette(label_palette);
            vlabel.append(lab);
            ui->qgLayout->addWidget(lab,i,j,1,1);
            lab->mw=this;
        }
    }
    ui->qgLayout->setVerticalSpacing(1);
    ui->qgLayout->setHorizontalSpacing(1);
    ui->qgLayout->setContentsMargins(10, 10, 10, 10);
    fs=ft=fq=f=0;
    sx=sy=tx=ty=-1;
}


MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_5_clicked()
{
    f=0;
    fs=ft=fq=f=0;
    sx=sy=tx=ty=-1;
    QPalette label_palette;
    label_palette.setColor(QPalette::Background, QColor("white"));
    for(int i=0;i<Mx;i++){
        for(int j=0;j<My;j++){
            state[i][j]=0;
            vlabel[i*My+j]->f=0;
            vlabel[i*My+j]->setPalette(label_palette);
        }
    }
}


void MainWindow::on_pushButton_clicked()
{
    ft=0;
    fq=0;
    fs=1;
}

void MainWindow::on_pushButton_2_clicked()
{
    fs=0;
    fq=0;
    ft=1;
}

void MainWindow::on_pushButton_3_clicked()
{
    fq=1;
    ft=fs=0;
}
//路径up 1,down 2,left 3,right 4
int dir(int i,int j){
    if(i==-1) return 1;
    if(i==1) return 2;
    if(j==-1) return 3;
    if(j==1) return 4;
}

int MainWindow::back()
{
   int k=0,x=tx,y=ty;
   while (1) {
       if(state[x][y]==1)x++;
       else if(state[x][y]==2)x--;
       else if(state[x][y]==3)y++;
       else if(state[x][y]==4)y--;
       k++;
       if(x==sx&&y==sy)break;
       vlabel[x*My+y]->setPalette({QPalette::Background, QColor("yellow")});
   }
   return k;
}

void MainWindow::clear()
{
    f=0;
    for(int i=0;i<Mx;i++){
        for(int j=0;j<My;j++){
            state[i][j]=0;
            if(vlabel[i*My+j]->f==0)
                vlabel[i*My+j]->setPalette({QPalette::Background, QColor("white")});
            }
    }
}

void MainWindow::DFS(){
    clear();
    QStack<P>st;
    int k=1,ff=0;
    st.push(P(sx,sy));
    state[sx][sy]=1;
    clock_t start,end;
    start = clock();
    while (st.size()) {
        int x=st.top().first;
        int y=st.top().second;
        st.pop();
        for(int i=-1;i<2;i++){
            for(int j=-1;j<2;j++){
                int xx=x+i;
                int yy=y+j;
                if(i*j==0&&i!=j){
                    if(xx>=0&&xx<Mx&&yy>=0&&yy<My&&state[xx][yy]==0&&vlabel[xx*My+yy]->f!=-1){
                        st.push(P(xx,yy));
                        state[xx][yy]=dir(i,j);
                        k++;
                        if(xx==tx&&yy==ty){ff=1;break;}
                        vlabel[xx*My+yy]->setPalette({QPalette::Background, QColor("blue")});
                    }
                }
            }
            if(ff)break;
        }
        if(ff)break;
    }
    end = clock();
    back();
    if(!ff)ui->textBrowser->append(QString("DFS:\n拓展节点数：%1\n时间：%2ms\n未到达终点！！！\n\n").arg(k).arg((double)(end-start)/CLK_TCK));
    else ui->textBrowser->append(QString("DFS:\n拓展节点数：%1\n时间：%2ms\n\n").arg(k).arg((double)(end-start)/CLK_TCK));
}

void MainWindow::BFS(){
        clear();
    QQueue<P>q;
    int k=1,ff=0;
    q.push_back(P(sx,sy));
    state[sx][sy]=1;
    clock_t start,end;
    start = clock();
    while (q.size()) {
        int x=q[0].first;
        int y=q[0].second;
        q.pop_front();
        for(int i=-1;i<2;i++){
            for(int j=-1;j<2;j++){
                int xx=x+i;
                int yy=y+j;
                if(i*j==0&&i!=j){
                    if(xx>=0&&xx<Mx&&yy>=0&&yy<My&&state[xx][yy]==0&&vlabel[xx*My+yy]->f!=-1){
                        q.push_back(P(xx,yy));
                        state[xx][yy]=dir(i,j);
                        k++;
                        if(xx==tx&&yy==ty){ff=1;break;}
                        vlabel[xx*My+yy]->setPalette({QPalette::Background, QColor("blue")});
                    }
                }
            }
            if(ff)break;
        }
        if(ff)break;
    }
  end = clock();
  int kk=0;
  if(ff)kk=back();
    if(!ff)ui->textBrowser->append(QString("BFS:\n拓展节点数：%1\n时间：%2ms\n未到达终点！！！\n\n").arg(k).arg((double)(end-start)/CLK_TCK));
    else ui->textBrowser->append(QString("BFS:\n拓展节点数：%1\n时间：%2ms\n最短路径：%3步\n\n").arg(k).arg((double)(end-start)/CLK_TCK).arg(kk));
}

struct note{
    int x,y,k,m;
    note(int a,int b,int c,int d){
        x=a;y=b;k=c;m=d;
    }
};

int MainWindow::Heuristic(int x,int y,int k){
    return k+abs(tx-x)+abs(ty-y);
}

void MainWindow::AStar(){
    clear();
    int di[Mx][My]={0};//状态
    QList<note>q;
    int k=1,ff=0;
    q.push_back(note(sx,sy,0,Heuristic(sx,sy,0)));
    clock_t start,end;
    start = clock();
    while (q.size()) {
        int x=q[0].x;
        int y=q[0].y;
        int bu=q[0].k+1;
        q.pop_front();
        di[x][y]=2;
        for(int i=-1;i<2;i++){
            for(int j=-1;j<2;j++){
                int xx=x+i;
                int yy=y+j;
                if(i*j==0&&i!=j){
                    if(xx>=0&&xx<Mx&&yy>=0&&yy<My&&(di[xx][yy]==0||di[xx][yy]==1)&&vlabel[xx*My+yy]->f!=-1){
                       int r=Heuristic(xx,yy,bu),fr=0;
                       if(di[xx][yy]==0){
                           for(int l=0;l<q.size();l++){
                               if(r<=q[l].m){
                                   q.insert(l,note(xx,yy,bu,r));
                                   fr=1;
                                   break;
                               }
                           }
                           if(!fr)q.push_back(note(xx,yy,bu,r));
                           di[xx][yy]=1;
                           state[xx][yy]=dir(i,j);
                           k++;
                       }
                       else{
                           for(int l=0;l<q.size();l++){
                               if(q[l].x==xx&&q[l].y==yy){
                                   if(r<q[l].m){
                                      q.removeAt(l);
                                      fr=1;
                                       break;
                                   }
                               }
                           }
                           if(fr){
                               fr=0;
                               for(int l=0;l<q.size();l++){
                                   if(r<=q[l].m){
                                       q.insert(l,note(xx,yy,bu,r));
                                       fr=1;
                                       break;
                                   }
                               }
                               if(!fr)q.push_back(note(xx,yy,bu,r));
                               di[xx][yy]=1;
                               state[xx][yy]=dir(i,j);
                           }
                       }

                        if(xx==tx&&yy==ty){ff=1;break;}
                        vlabel[xx*My+yy]->setPalette({QPalette::Background, QColor("blue")});
                    }
                }
            }
            if(ff)break;
        }
        if(ff)break;
    }
  end = clock();
  int kk=0;
  if(ff)kk=back();
    if(!ff)ui->textBrowser->append(QString("A*:\n拓展节点数：%1\n时间：%2ms\n未到达终点！！！\n\n").arg(k).arg((double)(end-start)/CLK_TCK));
    else ui->textBrowser->append(QString("A*:\n拓展节点数：%1\n时间：%2ms\n最短路径：%3步\n\n").arg(k).arg((double)(end-start)/CLK_TCK).arg(kk));
}

void MainWindow::on_pushButton_4_clicked()
{
    if(f)return;
    if(ui->comboBox->currentText()=="DFS"){
        DFS();
    }
    if(ui->comboBox->currentText()=="BFS"){
        BFS();
    }
    if(ui->comboBox->currentText()=="A*"){
        AStar();
    }
}
