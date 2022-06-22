#ifndef BOARD_H
#define BOARD_H
#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "card.h"
class Board : public QObject
{
Q_OBJECT
public:
    explicit Board(QObject *parent = 0);
    ~Board();
    /*N暂定为最大的牌数量*/
    static const int N = 52, M = 52;
    /* 返回用于渲染的QGraphicsView* */
    QGraphicsView* View();

    /* 重置为开局状态 */
    void reset();
    /* 允许用户操作 */
    void enable();
    /* 不允许用户操作 */
    void disable();
private:
    /* 渲染用的容器 */
    QGraphicsScene scene;
    QGraphicsView view;

    /* 卡牌 */
    Card* card[N];
    CardList* cardList[M];
    QList<Card*> allCards;

    bool lifted; /* 是否拿起一张卡牌 */
    int liftX, liftY; /* 拿起卡牌坐标 */
    /* 根据card[]更新颜色 */
    void updateView(); /* update view according to card[] */
    /* 是否允许用户操作 */
    bool enabled;
signals:
    /* 用户操作消息 */
    void userPut(int r, int c, int nr, int nc); /* signal passed to game */
    void userClick(const QPointF& startPos);
    void userMove(const QPointF &startPos, const QPointF &endPos);
    void userRelease(const QPointF &endPos);
    void userDoubleClick(const QPointF &pos);
    void userDragAndDrop(const QPointF &startPos, const QPointF &endPos);
private slots:
    /* 处理鼠标点击的slot */
    void cardClick(const QPointF& startPos);
    void cardMove(const QPointF &startPos, const QPointF &endPos);
    void cardRelease(const QPointF &endPos);
    void cardDoubleClick(const QPointF &pos);
    void cardDragAndDrop(const QPointF &startPos, const QPointF &endPos);
};

#endif // BOARD_H
