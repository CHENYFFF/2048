#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //初始化每个QPixmap 位图
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++){
            imgs[i][j]=new QPixmap("D:/CodeField/Qt/2048/2048/2048.bmp");
        }
    }

    Init();
    setWindowTitle(tr("2048ByFF"));//设置软件标题
    resize(475,475);//窗口

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Init(){
    over=false;
    win=false;

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            pieces[i][j]=0;
        }
    }
    //随机初始化面板 生成一个2
    Rand2();
}

void MainWindow::paintEvent(QPaintEvent *e){
    BackGround();
    drawPieces();

    update();
}

void MainWindow::drawPieces(){
    QPainter p(this);
//   pixmap = pixmap.scaled(392,392.00/pixmap.width()*pixmap.height());//按照宽度等比例放大
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
          QPixmap img=*imgs[i][j];
          p.drawPixmap(QRect(Edge+i*95,Edge+j*95,90,90),img,QRect(pieces[i][j]*90,0,90,90));//第一个参数是在窗口显示的位置 第三个参数是位图的显示矩形
        }
    }
}

//绘制白色背景
void MainWindow::BackGround(){
      QPainter p(this);
      p.setBrush(Qt::white);
      p.setPen(Qt::white);
      p.drawRect(20,20,435,435);
}

void  MainWindow::keyPressEvent(QKeyEvent *e)
{
    if(over){
        return;//已结束 按键无效
    }
    switch (e->key()) {
        case Qt::Key_Up: Up(); break;
        case Qt::Key_Down: Down(); break;
        case Qt::Key_Right: Right(); break;
        case Qt::Key_Left: Left(); break;
        default: return;//除了4个箭头 其他按键不起作用
    }

    if(win==true){
        QMessageBox::information(NULL,"GAME OVER","游戏胜利", QMessageBox::Ok);
        Init();
        return;
    }
    //每移动一次  随机生成新的2 然后judge是否结束
    Rand2();

}

void MainWindow::Left(){
     qDebug()<<"left"<<endl;
    //实现移动
    for(int i=1;i<4;i++){
        for(int j=0;j<4;j++){
            //为0跳过 不做操作
            if(pieces[i][j]!=0){
               //找到前面最远的空位[m][j]
               for(int m=0;m<3;m++){
                   if(pieces[m][j]==0){
                      pieces[m][j]=pieces[i][j];
                      pieces[i][j]=0;
                      break;
                   }
               }
            }
        }
    }
    //实现相邻的同种色块相消  从上往下消
    for(int i=0;i<3;i++){
        for(int j=0;j<4;j++){
            if(pieces[i][j]==0){continue;};
            if(pieces[i][j]==pieces[i+1][j])//相消
            {
                pieces[i][j]+=1;
                pieces[i+1][j]=0;
            }
            if( pieces[i][j]==11){
                win=true;
                over=true;
            }
        }
    }

    //相消完成后再衔接一次移动 否则会出现 2222->4040  应该是4400
    for(int i=1;i<4;i++){
        for(int j=0;j<4;j++){
           //为0跳过 不做操作
           if(pieces[i][j]==0){continue;}
           //找到前面最远的空位[m][j]
           for(int m=0;m<3;m++){
               if(pieces[m][j]==0){
                  pieces[m][j]=pieces[i][j];
                  pieces[i][j]=0;
                  break;
               }
           }
            }
    }
}

void MainWindow::Right()
{
    qDebug()<<"right"<<endl;
   //实现移动
   for(int i=2;i>=0;i--){
       for(int j=0;j<4;j++){
           //为0跳过 不做操作
           if(pieces[i][j]!=0){
              //找到前面最远的空位[m][j]
              for(int m=3;m>0;m--){
                  if(pieces[m][j]==0){
                     pieces[m][j]=pieces[i][j];
                     pieces[i][j]=0;
                     break;
                  }
              }
           }
       }
   }
   //实现相邻的同种色块相消 从左往右消
   for(int i=3;i>0;i--){
       for(int j=0;j<4;j++){
           if(pieces[i][j]==0){continue;};
           if(pieces[i][j]==pieces[i-1][j])//相消
           {
               pieces[i][j]+=1;
               pieces[i-1][j]=0;
           }
           if( pieces[i][j]==11){
               win=true;
               over=true;
           }
       }
   }

   //相消完成后再衔接一次移动 否则会出现 2222->4040  应该是4400
   for(int i=2;i>=0;i--){
         for(int j=0;j<4;j++){
           //为0跳过 不做操作
           if(pieces[i][j]!=0){
              //找到前面最远的空位[m][j]
              for(int m=3;m>0;m--){
                  if(pieces[m][j]==0){
                     pieces[m][j]=pieces[i][j];
                     pieces[i][j]=0;
                     break;
                  }
              }
           }
       }
   }
}

void MainWindow::Up()
{
    qDebug()<<"up"<<endl;
   //实现移动
   for(int j=1;j<4;j++){
       for(int i=0;i<4;i++){
           //为0跳过 不做操作
           if(pieces[i][j]!=0){
              //找到前面最远的空位[m][j]
              for(int m=0;m<3;m++){
                  if(pieces[i][m]==0){
                     pieces[i][m]=pieces[i][j];
                     pieces[i][j]=0;
                     break;
                  }
              }
           }
       }
   }
   //实现相邻的同种色块相消  从上往下消
   for(int j=0;j<3;j++){
       for(int i=0;i<4;i++){
           if(pieces[i][j]==0){continue;};
           if(pieces[i][j]==pieces[i][j+1])//相消
           {
               pieces[i][j]+=1;
               pieces[i][j+1]=0;
           }
           if( pieces[i][j]==11){
               win=true;
               over=true;
           }
       }
   }

   //相消完成后再衔接一次移动 否则会出现 2222->4040  应该是4400
   for(int j=1;j<4;j++){
       for(int i=0;i<4;i++){
           //为0跳过 不做操作
           if(pieces[i][j]!=0){
              //找到前面最远的空位[m][j]
              for(int m=0;m<3;m++){
                  if(pieces[i][m]==0){
                     pieces[i][m]=pieces[i][j];
                     pieces[i][j]=0;
                     break;
                  }
              }
           }
       }
   }
}

void MainWindow::Down()
{
    qDebug()<<"Down"<<endl;
   //实现移动
    for(int j=3;j>=0;j--){
        for(int i=0;i<4;i++){
            //为0跳过 不做操作
            if(pieces[i][j]!=0){
               //找到前面最远的空位[m][j]
               for(int m=3;m>=0;m--){
                   if(pieces[i][m]==0){
                      pieces[i][m]=pieces[i][j];
                      pieces[i][j]=0;
                      break;
                   }
               }
            }
        }
    }
    //实现相邻的同种色块相消  从下往上消
    for(int j=3;j>0;j--){
        for(int i=0;i<4;i++){
            if(pieces[i][j]==0){continue;};
            if(pieces[i][j]==pieces[i][j-1])//相消
            {
                pieces[i][j]+=1;
                pieces[i][j-1]=0;
            }
            if( pieces[i][j]==11){
                win=true;
                over=true;
                }
            }
        }

    //相消完成后再衔接一次移动 否则会出现 2222->4040  应该是4400
    for(int j=3;j>=0;j--){
        for(int i=0;i<4;i++){
            //为0跳过 不做操作
            if(pieces[i][j]!=0){
               //找到前面最远的空位[m][j]
               for(int m=3;m>=0;m--){
                   if(pieces[i][m]==0){
                      pieces[i][m]=pieces[i][j];
                      pieces[i][j]=0;
                      break;
                   }
               }
            }
        }
    }
}

void MainWindow::Rand2(){
    int empty=0;//统计非空格子数
    int xEmpty[15];
    int yEmpty[15];
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(pieces[i][j]==0){
                //记录空格子的索引和总数
                xEmpty[empty]=i;
                yEmpty[empty]=j;
                empty++;
            }
         }
    }
    if(empty==0){
        Judge();
    }

    srand((unsigned)time(NULL));
//    qDebug()<<empty<<endl;
    int RandEmpty=(rand() % empty);//产生0到empty之间的随机数
//    qDebug()<<RandEmpty<<endl;
    int xrand=xEmpty[RandEmpty];
    int yrand=yEmpty[RandEmpty];
    qDebug()<<xrand<<yrand<<endl;
    pieces[xrand][yrand]=1;//空格随机产生2
}

//判断是否死局
void  MainWindow::Judge(){
    for(int i=0;i<4;i++){
        for(int j=0;j<3;j+=2){
        if(pieces[i][j]==pieces[i][j+1]){
            return;//有救
        }
      }
    }
    for(int j=0;j<4;j++){
        for(int i=0;i<3;i+=2){
        if(pieces[i][j]==pieces[i+1][j]){
            return;//有救
        }
      }
    }
    over=true;//走到这里没救了
    QMessageBox::information(NULL,"GAME OVER","本局结束", QMessageBox::Ok);
    Init();
}
