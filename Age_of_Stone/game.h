#ifndef GAME_H
#define GAME_H
#include <QWidget>
#include <QtWidgets>
#include <QObject>
#include <QTime>
#include <QTimer>
#include "board.h"
#include "interfunc.h"
using namespace std;

class Game : public QWidget {
Q_OBJECT
public:
    explicit Game(QWidget *parent = nullptr);
    void startGame();
private:
    Board board;
    //QGraphicsScene* side;
    QTime* time;
    QTimer* timer;
    QGraphicsView* side;
    QHBoxLayout *layoutTop;
    QHBoxLayout *layoutBottom;
    QHBoxLayout *layoutSide;
    QVBoxLayout *layout;
    QLabel *label;
    QRadioButton *easyRadio;
    QRadioButton *normalRadio;
    QRadioButton *hardRadio;
    QPushButton *startBtn;
    QPushButton *pauseBtn;
    QPushButton *turnBtn;
    QSpinBox *hardnessSpin;
    /* 游戏模式 */
    int usedTime = 0;

signals:
    void click();
public slots:
    /* 接受来自board的用户操作 */
    void userDoubleClick(const QPointF& pos);
private slots:
    void updateTime();
    /* 开始按键按下的操作 */
    void startBtnClick();
    /* 暂停按键按下的操作 */
    void pauseBtnClick();
    /* 下一回合按钮按下的操作 */
    void nextTurnBtnClick();
};


#endif // GAME_H
