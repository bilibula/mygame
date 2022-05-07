#include "card.h"
Card::Card(double x, double y): x(x), y(y), m_StateFlag(DEFAULT_FLAG)
{
    setAcceptHoverEvents(true);
    setAcceptDrops(true);
    /* 求得卡牌坐标 */
    old_pos = pos = xy2pos(x, y);
    /* 在指定位置绘制长方形形状的卡牌 */
    this->setRect(pos.x(), pos.y(), width, height);
    /* 加阴影 */
    shadow = new QGraphicsDropShadowEffect();
    shadow->setOffset(0,0);
    shadow->setBlurRadius(15);
    this->setGraphicsEffect(shadow);
    this->setBrush(QBrush(Qt::darkGreen));
    this->setPen(Qt::NoPen);
}

void Card::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button()==Qt::LeftButton) {
        m_StateFlag = MOV_RECT;
        old_pos = event->pos();
        emit cardClick(old_pos);
    }
    else m_StateFlag = DEFAULT_FLAG;
        //Card::mouseReleaseEvent(event);
    //}
    //else Card::mousePressEvent(event);
    //if (event->button()==Qt::MouseButton::)
}

void Card::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    //QPointF startPoint=event->lastScenePos();
    //QPointF moveToPoint=event->pos();
    //pos+=moveToPoint-startPoint;
    QPointF delta = event->pos() - old_pos;
    if (m_StateFlag == MOV_RECT) {
        setCursor(Qt::CursorShape::ClosedHandCursor);
        moveBy(delta.x(),delta.y());
        pos += delta;
        emit cardMove(old_pos, pos);
        //old_pos=pos;
        update();
    }
    else m_StateFlag = DEFAULT_FLAG;
}

void Card::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button()==Qt::LeftButton) {
        if (m_StateFlag == MOV_RECT) {
            setCursor(Qt::CursorShape::ArrowCursor);
            pos = event->pos();
            //setPos(pos);
            emit cardRelease(pos);
        }
    }
    //else Card::mouseReleaseEvent(event);
    m_StateFlag = DEFAULT_FLAG;
}

void Card::mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event) {
    if (event->button()==Qt::LeftButton) {
        emit cardDoubleClick(event->pos());
        qDebug()<<"Double Click!";
    }
}

/*
void Card::dragEnterEvent(QGraphicsSceneDragDropEvent* event) {
    old_pos=event->scenePos();
    dragMoveEvent(event);
    event->acceptProposedAction();
}
void Card::dragMoveEvent(QGraphicsSceneDragDropEvent * event) {
    //setAcceptDrops(true);
    //event->accept();
    setPos(event->scenePos());
    event->accept();
    dropEvent(event);
}
void Card::dropEvent(QGraphicsSceneDragDropEvent *event) {
    pos=event->scenePos();
    moveBy((pos-old_pos).x(),(pos-old_pos).y());
}

*/
QPointF Card::xy2pos(const double& x, const double& y) {
    return {x, y};
}

Card::~Card() {
    delete shadow;
}
