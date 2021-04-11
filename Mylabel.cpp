#include"Mylabel.h"
Mylabel::Mylabel(QWidget* parent)
    :QLabel(parent)
{
     connect(this, SIGNAL(clicked()), this, SLOT(slotClicked()));
     connect(this,SIGNAL(Move(QMouseEvent *)),this,SLOT(slotMove(QMouseEvent *)));
     f=0;
}



void Mylabel::slotClicked()
{
    if(mw->fs){
        f=1;
        setPalette({QPalette::Background, QColor("green")});
        if(mw->sx!=-1){
            mw->vlabel[mw->sx*My+mw->sy]->setPalette({QPalette::Background, QColor("white")});
            mw->vlabel[mw->sx*My+mw->sy]->f=0;
        }
        mw->fs=0;
        for(int i=0;i<Mx;i++)
            for(int j=0;j<My;j++)
                if(mw->vlabel[i*My+j]->f==1)
                {
                    mw->sx=i;
                    mw->sy=j;
                    return;
                }
    }
    else if(mw->ft){
        f=2;
        setPalette({QPalette::Background, QColor("red")});
        if(mw->tx!=-1){
            mw->vlabel[mw->tx*My+mw->ty]->setPalette({QPalette::Background, QColor("white")});
            mw->vlabel[mw->tx*My+mw->ty]->f=0;
        }
        mw->ft=0;
        for(int i=0;i<Mx;i++)
            for(int j=0;j<My;j++)
                if(mw->vlabel[i*My+j]->f==2)
                {
                    mw->tx=i;
                    mw->ty=j;
                    return;
                }
    }
    else if(mw->fq){
        if(this->f==-1)
        {setPalette({QPalette::Background, QColor("white")});this->f=0;}
        else if(this->f==0)
           { setPalette({QPalette::Background, QColor("brown")});this->f=-1;}
    }
}
void Mylabel::mousePressEvent(QMouseEvent* event)
{
    emit clicked();
}


