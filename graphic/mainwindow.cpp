#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>
#include <QPainterPath>
#include <QPainter>
#include <QPen>
#include "poland.h"
#include <QChar>
#include <QPoint>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    button = new QPushButton(this);
    button->setGeometry(width() - 105, 5, 100, 50);
    button->setText("build");
    connect(button, SIGNAL(clicked()), this, SLOT(myClicked()));


}

void MainWindow::myClicked(){
    ui->label->setGeometry(5, 5, width() - 115, height() - 10);
    QPixmap pm(width() - 115, height() - 10);
    pm.fill(Qt::darkCyan);
    QString xmi = ui->lineEdit->text();
    QString xmx = ui->lineEdit_3->text();
    QString ymi = ui->lineEdit_6->text();
    QString ymx = ui->lineEdit_5->text();
    double xmin = xmi.toDouble();
    double xmax = xmx.toDouble();
    double ymin = ymi.toDouble();
    double ymax = ymx.toDouble();
    QString n = ui->lineEdit_2->text();
    double x, y;
    double ans = 0;
    int xgmin = 0, xgmax = pm.width();
    int ygmin = 0, ygmax = pm.height();
    x = xmin;
    double step = (xmax - xmin) / (xgmax - xgmin);
    double kx = (xgmax - xgmin) / (xmax - xmin);
    double ky = (ygmin - ygmax) / (ymax - ymin);
    double xn, yn;
    xn = xgmin - kx * xmin;
    yn = ygmin - ky * ymax;
    QPainterPath path;
    QPainter painter;
    painter.begin(&pm);
    x = xmin;
    n.replace('x', "(" + QString::number(x) +")");
    calc(n.toStdString(), ans);
    y = ans;
    QPen pen;
    QPen peno;
    pen.setWidth(1);
    peno.setColor(Qt::lightGray);
    peno.setWidth(1);
    painter.setPen(peno);
    painter.drawLine(0, yn, xgmax, yn);
    painter.drawLine(xn, 0, xn, ygmax);
    painter.setPen(pen);
    double xg = xgmin + kx * (x - xmin);
    double yg = ygmin + ky * (y - ymax);
    path.moveTo(xg, yg);
    for(int i = xgmin; i < xgmax; i ++){
        double yold = y;
        x += step;
        if(x >= xmax){
            break;
        }
        QString n = ui->lineEdit_2->text();
        n.replace('x', "(" + QString::number(x) +")");
        ans = 0;
        calc(n.toStdString(), ans);
        y = ans;
        xg = xgmin + kx * (x - xmin);
        yg = ygmin + ky * (y - ymax);
        if(yold < ymin or yold > ymax){
            path.moveTo(xg, yg);

        }else{
            path.lineTo(xg, yg);
        }
    }
    painter.drawPath(path);
    ui->label->setPixmap(pm);
}

MainWindow::~MainWindow()
{
    delete ui;
}
