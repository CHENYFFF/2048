#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPainter>
#include <QKeyEvent>
#include<time.h>
#include<QDebug>
#include "qmessagebox.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void drawPieces();
    void BackGround();
    void paintEvent(QPaintEvent *e);//重写绘制函数
    void keyPressEvent(QKeyEvent *e);//重写键盘函数
    void  Rand2();
    void  Judge();//以及满格的情况下 判断是否还能继续
    //键盘响应函数:
    void Down();
    void Up();
    void Right();
    void Left();

    void Init();

    Ui::MainWindow *ui;
    int Edge=50;//边缘

    //存储16个棋子上的数字是2的多少幂次 第一个空白格为0
    //对应位图的显示格数
    int pieces[4][4];
    QPixmap * imgs[4][4];
    bool over;//游戏结束标识 主要为了 失败后按键无效
    bool win;
};
#endif // MAINWINDOW_H
