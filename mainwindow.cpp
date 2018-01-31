#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iostream"
#include <string>
#include <fstream>
#include "curve_3.h"
MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  QDesktopWidget *desktop = QApplication::desktop(); // =qApp->desktop();也可以
//  setGeometry(deskWgt->width()/2-640, deskWgt->height()/2 - 240, 645, 472);
  move((desktop->width() - this->width())/4, (desktop->height() - this->height())/2);
  //  setupPlot();
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_pushButton_Save_clicked()
{
  //  std::cout<<"hello"<<std::endl;
  QString fileName = QFileDialog::getSaveFileName(0,"Save file", "", ("Only Files (*.pdf)"));
  ui->customplot->savePdf(fileName);
}

void MainWindow::on_pushButton_ReadK_clicked()
{
  QString filename = QFileDialog::getOpenFileName (this, tr ("open Curvature file"), "./", tr ("Curvature data (*.txt)"));
  //  std::string file = filename.toStdString ();
  std::ifstream curvaturefile(filename.toStdString ());
  if(!curvaturefile)
    std::cerr<<"ERROR!! can't open the curvature file "<<filename.toStdString ()<<std::endl;
  float x, y;
  std::vector<QPointF > pts;
  while(curvaturefile.good())
  {
    curvaturefile >> x >> y;
    if(curvaturefile.good())
    {
      pts.push_back(QPointF(x, y) );
    }
  }
  int size = pts.size();
  QVector<double> x_pts(size), y_pts(size);
  for(int i = 0; i < size; ++i)
  {
    x_pts[i] = pts[i].x();
    y_pts[i] = pts[i].y();
  }
  curvaturefile.close();
  drawPts(x_pts, y_pts);

}

void MainWindow::on_pushButton_ReadPts_clicked()
{
  QString filename = QFileDialog::getOpenFileName (this, tr ("open Curvature file"), "./", tr ("Curvature data (*.txt)"));
  //  std::string file = filename.toStdString ();
  std::ifstream curvaturefile(filename.toStdString ());
  if(!curvaturefile)
    std::cerr<<"ERROR!! can't open the curvature file "<<filename.toStdString ()<<std::endl;
  float x, y;
  std::vector<QPointF> pts;
  while(curvaturefile.good())
  {
    curvaturefile >> x >> y;
    if(curvaturefile.good())
    {
      pts.push_back(QPointF(x, y) );
    }
  }
  curvaturefile.close();

  int size = pts.size();
  QVector<double> x_pts(size), kappa_pts(size);
  for(int i = 1; i < size - 1; ++i)
  {
    x_pts.push_back(i);
    kappa_pts.push_back(mathself::curvatureCal(pts[i-1], pts[i] ,pts[i + 1]));
  }
  drawPts(x_pts, kappa_pts);
}

void MainWindow::setupPlot()
{
  // The following plot setup is mostly taken from the plot demos:
  ui->customplot->clearGraphs();
  ui->customplot->addGraph();
  ui->customplot->graph()->setPen(QPen(Qt::blue));
  ui->customplot->graph()->setBrush(QBrush(QColor(0, 0, 255, 20)));
  ui->customplot->addGraph();
  ui->customplot->graph()->setPen(QPen(Qt::red));
  QVector<double> x(500), y0(500), y1(500);
  for (int i=0; i<500; ++i)
  {
    x[i] = (i/499.0-0.5)*10;
    y0[i] = qExp(-x[i]*x[i]*0.25)*qSin(x[i]*5)*5;
    y1[i] = qExp(-x[i]*x[i]*0.25)*5;
  }
  ui->customplot->graph(0)->setData(x, y0);
  ui->customplot->graph(1)->setData(x, y1);
  ui->customplot->axisRect()->setupFullAxesBox(true);
  ui->customplot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}

void MainWindow::on_pushButton_Test_clicked()
{
  setupPlot();
}

void MainWindow::drawPts(QVector<double> x_pts, QVector<double> y_pts)
{
  ui->customplot->clearGraphs();
  ui->customplot->addGraph();
  ui->customplot->graph()->setPen( QPen( Qt::red ) );
  ui->customplot->graph()->setData(x_pts, y_pts, true);
  ui->customplot->graph()->setLineStyle((QCPGraph::LineStyle)(1));
  QFont serifFont("Times", QFont::Normal);
  serifFont.setPixelSize(10);
  ui->customplot->xAxis->setTickLabelFont(serifFont);
  ui->customplot->yAxis->setTickLabelFont(serifFont);

  ui->customplot->xAxis->setLabelFont(serifFont);
  ui->customplot->axisRect()->setupFullAxesBox(true);
  ui->customplot->yAxis->setLabelFont(serifFont);

  ui->customplot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
//  ui->customplot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
  ui->customplot->replot();
}
