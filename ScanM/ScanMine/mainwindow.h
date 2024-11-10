#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <vector>
#include "my_map.h"

namespace Ui {
class MainWindow;
}



class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTimer* tm;
    uint64_t tm_s;
    map_t mp;
    //vector<grid_t> ch_grids;
    bool fresh_flag = true;

    void init_widget();
    void init_grids();
    virtual void paintEvent(QPaintEvent* e) override;
    virtual void mousePressEvent(QMouseEvent* e) override;

private slots:
    void tm_count();
    void on_func_btn_clicked();
};

#endif // MAINWINDOW_H
