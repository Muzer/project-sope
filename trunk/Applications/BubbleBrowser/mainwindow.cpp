#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(set_website()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent()
{
    ui->centralWidget->resize(this->x(), this->y());
    ui->webView->resize(this->x(), this->y());
}
