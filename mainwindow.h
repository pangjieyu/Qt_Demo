#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColor>
#include <QColorDialog>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

private slots:
        void on_pushButton_ok_clicked();

        void on_pushButton_color1_clicked();

        void on_pushButton_color2_clicked();

private:
        Ui::MainWindow *ui;
        QColor colorOne;
        QColor colorTwo;


};

#endif // MAINWINDOW_H
