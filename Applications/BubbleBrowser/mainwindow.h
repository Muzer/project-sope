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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QProgressBar>
#include <QtGui/QMouseEvent>
#include <QtCore/QUrl>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int state; // 0 = page loaded, 1 = page loading
    QLabel *status_label;
    QPushButton *btn_zoom_in;
    QPushButton *btn_zoom_out;
    QPushButton *btn_zoom_normal;
    QProgressBar *progress_bar;
    unsigned int normal_zoom;

private slots:
    void set_website();
    void icon_changed();
    void link_clicked(QUrl url);
    void load_finished(bool ok);
    void load_progress(int progress);
    void load_started();
    void selection_changed();
    void status_bar_message(QString text);
    void title_changed(QString title);
    void url_changed(QUrl url);
    void btn_stop_pressed();
    void zoom_in();
    void zoom_out();
    void zoom_normal();

protected:
    void resizeEvent();
    void mousePressEvent(QMouseEvent *event);
};

#endif // MAINWINDOW_H
