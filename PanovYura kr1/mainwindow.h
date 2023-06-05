#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
enum{LEFT,RIGHT,UNDIFINE};
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:    
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int classify(QLineF L,QPointF p2);
    void paintEvent(QPaintEvent*);

    void mousePressEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);
private:
    Ui::MainWindow *ui;
    QPoint dot1, dot2;
    QPoint Norm1, Norm2;
};
#endif // MAINWINDOW_H

