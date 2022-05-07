#ifndef GAME_H
#define GAME_H
#include <QWidget>
#include <QtWidgets>
#include <QObject>
#include "board.h"
#include "interfunc.h"
using namespace std;

class Game : public QWidget {
    Q_OBJECT
public:
    explicit Game(QWidget *parent = nullptr);

private:
    Board board;
    QHBoxLayout *layoutTop;
    QVBoxLayout *layout;
    QHBoxLayout *layoutBottom;
    QLabel *label;
    QRadioButton *easyRadio;
    QRadioButton *normalRadio;
    QRadioButton *hardRadio;
    QPushButton *startBtn;
    QPushButton *pauseBtn;
    QSpinBox *hardnessSpin;
    /* 游戏模式 */


signals:
    void click();
public slots:
    /* 接受来自board的用户操作 */
    void userDoubleClick(const QPointF& pos);
private slots:
    /* 开始按键按下的操作 */
    void startBtnClick();
    /* 暂停按键按下的操作 */
    void pauseBtnClick();
};


#endif // GAME_H
