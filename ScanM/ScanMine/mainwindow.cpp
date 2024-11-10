#include <QPainter>
#include <QMouseEvent>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "log.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
    /* 在窗口位置 && 不可缩放 */
    this->resize(800, 600);

    init_widget();
    tm = new QTimer(this);
    connect(tm, &QTimer::timeout, this, &MainWindow::tm_count);
    //tm->start(1000);
    MDEBUG("map rows = %d", mp.rows);
    MDEBUG("map cols = %d", mp.cols);
    MDEBUG("map mines = %d", mp.mines);
    mp.init_rts(QPoint(30, 100), 40);
    //init_grids();
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::init_widget(){
    tm_s = 0;
    ui->tm_lb->clear();
    ui->m_nums_lb->clear();
}


void MainWindow::init_grids(){
#if 0
    for(uint8_t i=0; i<mp.rows; i++){
        for(uint8_t j=0; j<mp.cols; j++){
            grid_t grid(i, j, GRID_NORMAL);
            ch_grids.push_back(grid);
        }
    }
    update();
#endif
}

void MainWindow::paintEvent(QPaintEvent* e){

    QPainter painter(this);
    rep(i, 0, mp.rows){
        rep(j, 0, mp.cols){
            QRect rt = mp.rts[i][j];
            grid_e gd_e = (grid_e)mp.gds[i][j];
            QPixmap pix(icon_map[gd_e]);
            painter.drawPixmap(rt, pix);
        }
    }

}

void MainWindow::mousePressEvent(QMouseEvent* e){

#if 0
    ch_grids.clear();
    grid_t grid;
    if(mp.ch_click_grid(e->x(), e->y(), grid)){
        ch_grids.push_back(grid);
        /* bfs图搜索 */
        /* .... */
        update();
    }
#endif

#if 1
    if(mp.check_click(e->x(), e->y())){
        MDEBUG("click here");
    }
    update();


#endif
    if(e->button() == Qt::LeftButton){
        MDEBUG("left clicked");
    }else if (e->button() == Qt::RightButton) {
        MDEBUG("right clicked");
    }
}

void MainWindow::tm_count(){
    tm_s ++;
    //MDEBUG("tm_s = %d", tm_s);
    ui->tm_lb->setText(QString::number(tm_s));

}

#if 1
void MainWindow::on_func_btn_clicked(){

    rep(i, 0, mp.rows){
        rep(j, 0, mp.cols){
            MDEBUG("[%d][%d] = %d", i, j, mp.gds[i][j]);
        }
    }
}
#endif
