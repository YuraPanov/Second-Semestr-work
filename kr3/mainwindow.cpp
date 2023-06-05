#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
#include <QDebug>
#include <QPoint>
#include <QVector>
#include <cstdlib>
#include <iostream>
#include <math.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setMouseTracking(true);
    centralWidget()->setMouseTracking(true);
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QRect screen = contentsRect();
    int h = screen.height(),w = screen.width();
    for(int x = 0; x <= screen.width(); x += sizeResch){
       painter.drawLine(QPoint(x,0), QPoint(x,h));
        for(int y = 0; y <= screen.height(); y += sizeResch){
            painter.drawLine(QPoint(0,y), QPoint(w,y));
        }
    }

    painter.setBrush(QColor(120,40,0));

    if(!tree.center.isNull())
        painter.drawEllipse(tree.center,tree.radius,tree.radius);

    QPen pen(Qt::blue, 10),pen1(Qt::red, 10);
    pen.setWidth(10);
    painter.setPen(pen);

    if(!ant.isNull())
        painter.drawPoint(ant);

    painter.setPen(pen1);

    if(!fly.isNull())
        painter.drawPoint(fly);


    for (int i = 0; i <= min_p.size() - 1; i++){
        QPen brush(Qt::red);
        brush.setWidth(4);
        painter.setPen(brush);
        painter.drawLine(ant,min_p[1]);
        painter.drawLine(min_p[i], min_p[i + 1]);
    }

//    if(count >= 2){
//        painter.drawRect(200,200,200,200);
//    }

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (!(Qt::ControlModifier & event->modifiers())&&(Qt::AltModifier & event->modifiers())&&(Qt::LeftButton & event->buttons()) && count == 0){

        ant = ((event->pos() / sizeResch) * sizeResch) ;
        ant_move = ant;
        count += 1;
        repaint();
        }


    if (!(Qt::ControlModifier & event->modifiers())&&!(Qt::AltModifier & event->modifiers())&&(Qt::LeftButton & event->buttons())&& count == 1){
        tree.center = event->pos();
        tree.radius = 35 + (rand() % 130);
        count += 1;
        repaint();
    }

    if ((Qt::ControlModifier & event->modifiers())&&!(Qt::AltModifier & event->modifiers())&&(Qt::LeftButton & event->buttons()) && count == 2){

        fly = ((event->pos() / sizeResch) * sizeResch);

   }
    if(count > 2){
        min_p.clear();
        while(ant_move != fly){
            move[0] = ant_move + QPoint(0, -sizeResch);
            move[1] = ant_move + QPoint(0, sizeResch);
            move[2] = ant_move + QPoint(-sizeResch, 0);
            move[3] = ant_move + QPoint(sizeResch, 0);
            min_p.append(ant_move);
            int min = 99999999;
            QPoint truemove;
            for (int k = 0; k < 4; k++)
                for (int j = 0; j < min_p.size(); j++)
                    if(point_in_circle(move[k],tree) && move[k] != min_p[j]){
                    int dlina = dlina_1(fly, move[k]);
                        if (dlina < min){
                            min = dlina;
                            truemove = move[k];
                        }
                    }
            ant_move = truemove;
        }
        min_p.append(fly);
    }
    repaint();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *)
{

}

void MainWindow::mouseMoveEvent(QMouseEvent *)
{

}

bool MainWindow::point_in_circle(QPoint p, Circle c){
    if (dlina_1(c.center,p) <= c.radius)
        return false;
    return true;
}

bool  MainWindow::dlina_1(QPoint p1,QPoint p2){
    QPoint point_dlina = p1 - p2;
    return sqrt(pow(point_dlina.x(), 2)+ pow(point_dlina.y(),2));
}


