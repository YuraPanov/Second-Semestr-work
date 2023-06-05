#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
#include <QDebug>
#include <QPoint>
#include <QVector>
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
    QImage Flower(":/img/rrr/chamomiles.jpg");
    QImage Water(":/img/rrr/water_texture2378.jpg");
    QImage Grass(":/img/rrr/trava_grass_gazon_lawn.jpg");
    QBrush Brush;
    Brush.setTextureImage(Grass);
    painter.setBrush(Brush);
    painter.drawRect(contentsRect());
    Brush.setTextureImage(Water);
    painter.setBrush(Brush);
    painter.drawRect(100,100,400,200);
    for (int i = 0; i < Clumba.length(); i++){
        if(i % 2 == 0){
            Brush.setTextureImage(Flower);
            painter.setBrush(Brush);
            painter.drawEllipse(Clumba[i],20,20);
        }
        else{
            Brush.setTextureImage(Flower);
            painter.setBrush(Brush);
            painter.drawRect(Clumba[i].x() - 15 ,Clumba[i].y() - 15,33,33);
        }
    }
    }

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (!(Qt::AltModifier & event->modifiers())&&(Qt::LeftButton & event->buttons())){
        dot1 = event->pos();
        bool match = false;
        if((dot1.x() < r.right()) && (dot1.x() > r.left()) && (dot1.y() > r.top()) && (dot1.y() < r.bottom()))
            return;
        for(int i = 0; i < Clumba.length(); i++){
            QPoint diff = dot1 - Clumba[i];
            double length = sqrt(diff.x() * diff.x() + diff.y() * diff.y());
            if(length < 20 * 2)
                match = true;
        }
        if(match)
            return;
        Clumba.append(dot1);
        repaint();
    }
}
