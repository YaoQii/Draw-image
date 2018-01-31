#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setupPlot();
    void drawPts(QVector<double> x, QVector<double> y_pts);

  private:
    Ui::MainWindow *ui;
  private slots:
    void on_pushButton_Save_clicked();
    void on_pushButton_ReadK_clicked();
    void on_pushButton_ReadPts_clicked();
    void on_pushButton_Test_clicked();
};

#endif // MAINWINDOW_H
