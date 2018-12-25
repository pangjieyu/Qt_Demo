#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPoint points[6];
    points[0] = (QPoint(ui->lineEdit_x0->text().toInt(),ui->lineEdit_y0->text().toInt()));
    points[1] = (QPoint(ui->lineEdit_x1->text().toInt(),ui->lineEdit_y1->text().toInt()));
    points[2] = (QPoint(ui->lineEdit_x2->text().toInt(),ui->lineEdit_y2->text().toInt()));
    points[3] = (QPoint(ui->lineEdit_x3->text().toInt(),ui->lineEdit_y3->text().toInt()));
    points[4] = (QPoint(ui->lineEdit_x4->text().toInt(),ui->lineEdit_y4->text().toInt()));
    points[5] = (QPoint(ui->lineEdit_x5->text().toInt(),ui->lineEdit_y5->text().toInt()));
    QVector<QPoint> pointv;
    int n = ui->lineEdit_n->text().toInt();
    for(int i=0; i<n; ++i) {
        pointv.append(points[i]);
    }
    colorOne = ui->frame_color1->palette().background().color();
    colorTwo = ui->frame_color2->palette().background().color();
    ui->widget_draw->setPoints(pointv);
    ui->widget_draw->setColorOne(colorOne);
    ui->widget_draw->setColorTwo(colorTwo);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_ok_clicked()
{
  ui->widget_draw->ang = 0;
  //设置points
    QPoint points[6];
    points[0] = (QPoint(ui->lineEdit_x0->text().toInt(),ui->lineEdit_y0->text().toInt()));
    points[1] = (QPoint(ui->lineEdit_x1->text().toInt(),ui->lineEdit_y1->text().toInt()));
    points[2] = (QPoint(ui->lineEdit_x2->text().toInt(),ui->lineEdit_y2->text().toInt()));
    points[3] = (QPoint(ui->lineEdit_x3->text().toInt(),ui->lineEdit_y3->text().toInt()));
    points[4] = (QPoint(ui->lineEdit_x4->text().toInt(),ui->lineEdit_y4->text().toInt()));
    points[5] = (QPoint(ui->lineEdit_x5->text().toInt(),ui->lineEdit_y5->text().toInt()));
    QVector<QPoint> pointv;
    int n = ui->lineEdit_n->text().toInt();
    for(int i=0; i<n; ++i) {
        pointv.append(points[i]);
    }
    ui->widget_draw->setPoints(pointv);

    //设置剪裁矩形
    ui->widget_draw->setClip(true);
    QRect rect(ui->lineEdit_X->text().toInt(),ui->lineEdit_Y->text().toInt(),ui->lineEdit_width->text().toInt(),ui->lineEdit_height->text().toInt());
    ui->widget_draw->setClipRect(rect);

    //设置圆
    ui->widget_draw->setR(ui->lineEdit_r->text().toInt());
    ui->widget_draw->setC(QPoint(ui->lineEdit_cx->text().toInt(),ui->lineEdit_cy->text().toInt()));


    ui->widget_draw->update();
}

void MainWindow::on_pushButton_color1_clicked()
{
    colorOne = QColorDialog::getColor();
    ui->frame_color1->setPalette(QPalette(colorOne));
    ui->frame_color1->update();
    ui->widget_draw->setColorOne(colorOne);
    ui->widget_draw->update();
}

void MainWindow::on_pushButton_color2_clicked()
{
    colorTwo = QColorDialog::getColor();
    ui->frame_color2->setPalette(QPalette(colorTwo));
    ui->frame_color2->update();
    ui->widget_draw->setColorTwo(colorTwo);
    ui->widget_draw->update();

}
