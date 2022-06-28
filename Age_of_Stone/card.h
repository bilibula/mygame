#ifndef CARD_H
#define CARD_H
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneMoveEvent>
//#include <QGraphicsSceneDragDropEvent>
//#include <QGraphicsSceneEvent>
#include <QList>
#include <QPen>
#include <QBrush>
#include <QCursor>
#include "interfunc.h"
#include "cardlist.h"
//#include <QDockWidget>
enum STATE_FLAG{
    DEFAULT_FLAG=0,
    MOV_LEFT_LINE,//标记当前为用户按下矩形的左边界区域
    MOV_TOP_LINE,//标记当前为用户按下矩形的上边界区域
    MOV_RIGHT_LINE,//标记当前为用户按下矩形的右边界区域
    MOV_BOTTOM_LINE,//标记当前为用户按下矩形的下边界区域
    MOV_RIGHTBOTTOM_RECT,//标记当前为用户按下矩形的右下角
    MOV_RECT,//标记当前为鼠标拖动图片移动状态
    ROTATE//标记当前为旋转状态
};
enum CardType : int {
    Nothing = -1,
    Lumber = 0,
    Hunter_House = 1,
    Farm = 2,
    Mine = 3,
    Pasture = 4,
    Temple = 5,
    Prior_Temple = 6,
    Church = 7,
    Prior_Church = 8,
    School = 9,
    Lab = 10,
    Hospital = 11,
    Military_Academy = 12,
};
enum Career : int {
    //Nothing = -1,
    Person = 0,
    Lumberjack = 1,
    Farmer = 2,
    Miner = 3,
    Herdsmen = 4,
    Priest = 5,
    Prior_Priest = 6,
    Enchanter = 7,
    Pope = 8,
    Teacher = 9,
    Researcher = 10,
    Doctor = 11,
    Infantry = 12,
    Cavalry = 13,
    Slinger = 14,
    Scout = 15,
};
enum Resource : int {
    //Nothing = -1,
    Money = 0,
    Wheat = 1,
    Bread = 2,
    Raw_Meat = 3,
    Cooked_Meat = 4,
    Wooden_Axe = 5,
    Stone_Axe = 6,
    Wooden_Pickaxe = 7,
    Stone_Pickaxe = 8,
    Wooden_Hoe = 9,
    Stone_Hoe = 10,
    Wooden_Sword = 11,
    Stone_Sword = 12,
    Horse = 13,
    Wood = 14,
    Stone = 15,
};
class Card: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:

    ~Card();
    static const int height = 46, width = 28, gapWidth = 8;//卡牌的长、宽、（间距）
    /* 图片 */
    QPixmap* pic;

    CardList *cardList;
    Card *nextCard;  //在CardList中形成的Card链，为了实现同时拖动多张卡片
    /* 边界矩形框 */
    QRectF boundingRect() const;
    /* 画图 */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    /* 增加边界 */
    QPainterPath shape() const;
    int category = 0;//0为建筑物，1为不同职业的人，2为资源
    /* Card的种类 */
    CardType cardType=CardType::Nothing;
    Career career=Career::Person;
    Resource resource=Resource::Money;
    int cardNum = 0, durable = 0;
    int getCardNum() const;
    /*不同种类card的简介*/
    static constexpr char m_Profile[100][3][50]{
            {"伐木场","普通人","钱"},
            {"猎人小屋","伐木工","小麦"},
            {"农场","农民","面包"},
            {"矿山","矿工","生肉"},
            {"牧场","牧民","熟肉"},
            {"神庙","神官","木斧"},
            {"高级神庙","高级神官","石斧"},
            {"教堂","魔法师","木镐"},
            {"高级教堂","教皇","石镐"},
            {"学校","教师","木锄"},
            {"研究所","研究员","石锄"},
            {"医院","医生","木棍"},
            {"军事院校","步兵","石剑"},
            {"","骑兵","马"},
            {"","投石兵"},
            {"","侦察兵"},
            {"","",""},
            {"","",""}
    };
    Card(const QString &path, double x = 0, double Y = 0);
    bool handleCollisions();  //拖拽鼠标松开时进行碰撞检测
    void clearCardList();   //从CardList上移出

    void updateCardLinkPosi(); //**移到GameController
private:
    double x, y;
    /*阴影*/
    QGraphicsDropShadowEffect *shadow;
    /*浮点数坐标*/
    //QPointF pos;
    /*记录旧坐标*/
    QPointF old_pos;
    /* 记录Z值（决定层叠次序） */
    double oldZValue;
    /*cursor状态*/
    STATE_FLAG m_StateFlag;

signals:
    /*分别是单击、移动、释放、双击、拖放（已经弃用）鼠标的信号*/
    void cardClick(const QPointF &startPos);
    void cardMove(const QPointF &startPos, const QPointF &endPos);
    void cardRelease(const QPointF &endPos);
    void cardDoubleClick(const QPointF &pos);
    //void cardDragAndDrop(const QPointF &startPos, const QPointF &endPos);
protected:
    /*分别是单击、移动、释放、双击、拖放（已经弃用）鼠标的事件，检测到相应事件后会立即调用这些函数*/
    void mousePressEvent(QGraphicsSceneMouseEvent * event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent * event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    //void dragEnterEvent(QGraphicsSceneDragDropEvent* event);
    //void dragMoveEvent(QGraphicsSceneDragDropEvent * event);
    //void dropEvent(QGraphicsSceneDragDropEvent* event);
};

#endif // CARD_H