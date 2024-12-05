#ifndef MY_MAP_H
#define MY_MAP_H
#include <stdint.h>
#include <QRect>
#include <QVector>
#include <map>
#include <QMap>
#include "log.h"

/* icon宏 */
#define ICON_MINE     ":/icon/mine.png"
#define ICON_GRID     ":/icon/grid.png"

#define ICON_NO_1     ":/icon/m1.png"
#define ICON_NO_2     ":/icon/m2.png"
#define ICON_NO_3     ":/icon/m3.png"
#define ICON_NO_4     ":/icon/m4.png"

#define ICON_NO_5     ":/icon/m5.png"
#define ICON_NO_6     ":/icon/m6.png"
#define ICON_NO_7     ":/icon/m7.png"
#define ICON_NO_8     ":/icon/m8.png"


#define GRID_GAP      3
#define rep(i, a, b)  for(int i=(int)a; i<(int)b; i++)

using namespace std;

/* 网格种类enum */
enum grid_e{
    GRID_NORMAL,
    GRID_MINE,  /* 地雷 */
    GRID_BOMB,   /* 触雷（标红） */
    GRID_CHECKED,  /* 已查明（数字或空白） */
    GRID_CHK_1,
    GRID_CHK_2,
    GRID_CHK_3,
    GRID_CHK_4,
    GRID_CHK_5,
    GRID_CHK_6,
    GRID_CHK_7,
    GRID_CHK_8,

    GRID_FLAG,  /* 插旗子 */
    GRID_TBD,  /* ? 待定 */
};

/* 网格struct */
typedef struct grid_tag{
    uint8_t r;
    uint8_t c;
    grid_tag(){
        r = 0;
        c = 0;
    }
    grid_tag(uint8_t _r, uint8_t _c){
        r = _r;
        c = _c;
    }
    /* 重载比较运算符 */
    bool operator<(const grid_tag& other) const {
         if (r != other.r) {
             return r < other.r;
         } else {
             return c < other.c;
         }
     }
}grid_t;



/* 地图信息strut */
typedef struct map_tag{
    uint8_t rows;  /* 行 */
    uint8_t cols;  /* 列 */
    uint8_t mines; /* 地雷数 */
    uint8_t init_px;  /* 起始坐标y */
    uint8_t init_py;  /* 起始坐标x */
    uint8_t grid_len;   /* 网格边长 */
    QVector<QVector<QRect>> rts; /* 所有网格rect向量 */
    //QVector<QVector<grid_e>> gds;

    //QMap<grid_t, grid_e> gds;

    vector<vector<int>> gds;

    map_tag(){
        rows = 9;
        cols = 9;
        mines = 10;
        init_px = 0;
        init_py = 0;
        rts.clear();

        gds.clear();
        rep(i, 0, rows){
            vector<int> c(cols, GRID_NORMAL);
            gds.push_back(c);
        }
        MDEBUG("rows = %d", gds.size());
        MDEBUG("cols = %d", gds[0].size());
    }
    void set(uint8_t r, uint8_t c, uint8_t m){
        rows = r;
        cols = c;
        mines = m;

        gds.clear();
        rep(i, 0, rows){
            vector<int> c(cols, GRID_NORMAL);
            gds.push_back(c);
        }
    }
    /* p起始点； len边长 */
    void init_rts(QPoint p, double len){

        init_px = p.x();
        init_py = p.y();
        grid_len = len;

        rep(i, 0, cols){
            QVector<QRect> rt_v;
            rep(j, 0, rows){
                QRect rect(p.x() + i*len, p.y() +j*len, len -GRID_GAP, len -GRID_GAP);
                rt_v.push_back(rect);
                gds[j][i] = GRID_NORMAL;
            }
            rts.push_back(rt_v);
        }
    }


    bool check_click(int px, int py){
        if(px>=init_px && px<=init_px+cols*grid_len &&\
           py>=init_py && py<=init_py+rows*grid_len){
            grid_t gd;
            gd.r = (py -init_py) /grid_len;
            gd.c = (px -init_px) /grid_len;
            //gds[gd] = GRID_MINE;
            gds[gd.c][gd.r] = GRID_MINE;
            MDEBUG("click grid = [%d, %d]", gd.r, gd.c);
            return true;
        }
        return false;
    }
}map_t;

/* 网格单元icon映射 */
static map<grid_e, char*> icon_map{
    {GRID_MINE, (char*) ICON_MINE},
    {GRID_NORMAL, (char*) ICON_GRID},
    {GRID_CHK_1, (char*) ICON_NO_1},
    {GRID_CHK_2, (char*) ICON_NO_2},
    {GRID_CHK_3, (char*) ICON_NO_3},
    {GRID_CHK_4, (char*) ICON_NO_4},

    {GRID_CHK_5, (char*) ICON_NO_5},
    {GRID_CHK_6, (char*) ICON_NO_6},
    {GRID_CHK_7, (char*) ICON_NO_7},
    {GRID_CHK_8, (char*) ICON_NO_8},
};





#endif // MY_MAP_H
