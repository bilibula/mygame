#ifndef CARD_H
#define CARD_H
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneMoveEvent>
#include <QGraphicsSceneDragDropEvent>
//#include <QGraphicsSceneEvent>
#include <QPen>
#include <QBrush>
#include <QCursor>

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
class Card: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Card(double x = 0, double Y = 0);
    ~Card();
    static const int height = 46, width = 28, gapWidth = 8;//卡牌的长、宽、（间距）
private:
    double x, y;
    /*阴影*/
    QGraphicsDropShadowEffect *shadow;
    /*浮点数坐标*/
    QPointF pos;
    /*记录旧坐标*/
    QPointF old_pos;
    /* 通过(x,y)计算坐标 */
    static QPointF xy2pos(const double& x, const double& y);
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
    //void dragEnterEvent(QGraphicsSceneDragDropEvent* event);
    //void dragMoveEvent(QGraphicsSceneDragDropEvent * event);
    //void dropEvent(QGraphicsSceneDragDropEvent* event);
};

#endif // CARD_H
