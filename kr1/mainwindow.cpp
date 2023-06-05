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

int MainWindow::classify(QLineF L, QPointF p2)
{
    QPointF p0 = L.p1();
    QPointF p1 = L.p2();
    QPointF a = p1 - p0;
    QPointF b = p2 - p0;
    int Shearh = a.x() * b.y() - b.x() * a.y();
    if (Shearh > 0)
        return RIGHT;
    if (Shearh < 0)
        return LEFT;
    return UNDIFINE;
}


void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QBrush yellow(QColor(255,255,0,100));
    if(!dot2.isNull()){
        QPoint Bdot(dot2-dot1);
        QPoint Norm1(-1 * Bdot.y(),Bdot.x());
        QPoint Norm2(Bdot.y(),-1 * Bdot.x());
        QLine CentrLine(dot1,dot2);
        QLineF CentreLineF = CentrLine.toLineF();
        QLineF CentreLineF2 = CentrLine.toLineF();
        painter.drawLine(dot1,dot2);
        painter.drawLine(dot2,Norm1+dot2);
        painter.drawLine(dot2,Norm2+dot2);
        CentreLineF2.setAngle(CentreLineF.angle() + 15);
        CentreLineF.setAngle(CentreLineF.angle() - 15);
        painter.drawLine(CentreLineF);
        painter.drawLine(CentreLineF2);
        painter.setBrush(QBrush(yellow));
        QPointF u(CentreLineF2.p2());
        QPointF y(CentreLineF.p2());
        QPointF t[] = {QPointF(dot1), QPointF(u), QPointF(y)};
        painter.drawPolygon(t,3);
    }
}
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (!(Qt::AltModifier & event->modifiers())&&(Qt::LeftButton & event->buttons()))
        dot1 = event->pos();
    if (Qt::RightButton & event->buttons())
        dot2 = event->pos();
    if ((Qt::AltModifier & event->modifiers())&&(Qt::LeftButton & event->buttons())){
        int Verd = classify(QLine(dot1, dot2), event->pos());
        QPoint Bdot(dot2-dot1);
        QPoint Norm1(-1 * Bdot.y(),Bdot.x());
        QPoint Norm2(Bdot.y(),-1 * Bdot.x());
        QLine Front(dot2+Norm1, dot2+Norm2);
        QLine Back(dot1+Norm2, dot1+Norm1);
        int f1 = classify(Front, event->pos());
        int f2 = classify(Back, event->pos());
        qDebug("%s", Verd == LEFT ? "Left" : Verd == RIGHT ? "Right" : "Undefine");
        qDebug("%s", f1 == RIGHT ? "Front" : f2 == RIGHT ? "Back" : (f1 && f2) == LEFT ? "Side" : "Undefine");
    }
    repaint();
}
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    repaint();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    repaint();
}
