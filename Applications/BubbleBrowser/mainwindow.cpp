//----------------------------------------------------------------------
// BubbleBrowser - an internet browser for Project Sope
// Copyright (C) 2009 Melon Development Team
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//----------------------------------------------------------------------
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    state = 0;
    status_label = new QLabel(this);
    btn_zoom_in = new QPushButton("+", this);
    btn_zoom_out = new QPushButton("-", this);
    btn_zoom_normal = new QPushButton("Normal", this);
    progress_bar = new QProgressBar(this);
    ui->statusBar->insertWidget(0, status_label, 1);
    ui->statusBar->insertWidget(1, btn_zoom_in, 0);
    ui->statusBar->insertWidget(2, btn_zoom_normal, 0);
    ui->statusBar->insertWidget(3, btn_zoom_out, 0);
    ui->statusBar->insertWidget(4, progress_bar, 0);
    connect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(set_website()));
    connect(ui->btn_stop, SIGNAL(clicked()), this, SLOT(btn_stop_pressed()));
    connect(btn_zoom_in, SIGNAL(clicked()), this, SLOT(zoom_in()));
    connect(btn_zoom_out, SIGNAL(clicked()), this, SLOT(zoom_out()));
    connect(btn_zoom_normal, SIGNAL(clicked()), this, SLOT(zoom_normal()));
    connect(ui->webView, SIGNAL(iconChanged()), this, SLOT(icon_changed()));
    connect(ui->webView, SIGNAL(linkClicked(QUrl)), this, SLOT(link_clicked(QUrl)));
    connect(ui->webView, SIGNAL(loadFinished(bool)), this, SLOT(load_finished(bool)));
    connect(ui->webView, SIGNAL(loadProgress(int)), this, SLOT(load_progress(int)));
    connect(ui->webView, SIGNAL(loadStarted()), this, SLOT(load_started()));
    connect(ui->webView, SIGNAL(selectionChanged()), this, SLOT(selection_changed()));
    connect(ui->webView, SIGNAL(statusBarMessage(QString)), this, SLOT(status_bar_message(QString)));
    connect(ui->webView, SIGNAL(titleChanged(QString)), this, SLOT(title_changed(QString)));
    connect(ui->webView, SIGNAL(urlChanged(QUrl)), this, SLOT(url_changed(QUrl)));
    normal_zoom = ui->webView->zoomFactor();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete status_label;
    delete progress_bar;
    delete btn_zoom_in;
    delete btn_zoom_out;
    delete btn_zoom_normal;
}

void MainWindow::resizeEvent()
{
    ui->centralWidget->resize(this->x(), this->y());
    ui->webView->resize(this->x(), this->y());
}

void MainWindow::set_website()
{
    QString str = ui->lineEdit->text();
    if (!str.startsWith("http://"))
        str.insert(0, "http://");
    ui->webView->setUrl(QUrl(str));
}

void MainWindow::btn_stop_pressed()
{
    if (state == 0)
        ui->webView->reload();
    else if (state == 1)
        ui->webView->stop();
}

void MainWindow::icon_changed()
{
    this->setWindowIcon(ui->webView->icon());
}

void MainWindow::link_clicked(QUrl url)
{
    ui->webView->setUrl(url);
}

void MainWindow::load_finished(bool ok)
{
    state = 0;
    if (ok)
        status_label->setText("Page loaded.");
    else
        status_label->setText("Page loaded, but with errors.");
    ui->btn_stop->setText("Refresh");
    progress_bar->hide();
}

void MainWindow::load_progress(int progress)
{
    progress_bar->setValue(progress);
}

void MainWindow::load_started()
{
    state = 1;
    ui->btn_stop->setText("X");
    progress_bar->setValue(0);
    progress_bar->show();
}

void MainWindow::selection_changed()
{
    status_label->setText(ui->webView->selectedText());
}

void MainWindow::status_bar_message(QString text)
{
    status_label->setText(text);
}

void MainWindow::title_changed(QString title)
{
    QString t = title;
    t.append(" - Bubble Browser");
    this->setWindowTitle(t);
}

void MainWindow::url_changed(QUrl url)
{
    ui->lineEdit->setText(url.toString());
}

void MainWindow::zoom_in()
{
    ui->webView->setZoomFactor(ui->webView->zoomFactor() + 0.1);
}

void MainWindow::zoom_out()
{
    ui->webView->setZoomFactor(ui->webView->zoomFactor() - 0.1);
}

void MainWindow::zoom_normal()
{
    ui->webView->setZoomFactor(normal_zoom);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    int dx = 0;
    int dy = 0;
    ui->webView->scroll(dx, dy);
}
