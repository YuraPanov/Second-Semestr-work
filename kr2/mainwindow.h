#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:    
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent*);

    void mousePressEvent(QMouseEvent *event);

private:
    Ui::MainWindow *ui;
    QPoint dot1;
    QRect r = QRect(100,100,400,200);
    QVector <QPoint> Clumba, ClumbaCV;
};
#endif // MAINWINDOW_H

