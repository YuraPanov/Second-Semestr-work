#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

struct Circle{
    QPoint center;
    int radius;
};

public:    
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent*);

    void mousePressEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *);

    void mouseMoveEvent(QMouseEvent *);
private:
    Ui::MainWindow *ui;
    QVector <QPoint> min_p;
    QPoint ant, ant_move, fly, move[4];
    int treeR, sizeResch = 20, count = 0;
    Circle tree;
    bool contains(Circle c, QPoint p);
    bool point_in_circle(QPoint p, Circle q);
    bool dlina_1(QPoint p1,QPoint p2);
};
#endif // MAINWINDOW_H

