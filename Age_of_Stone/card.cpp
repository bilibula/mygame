#include "card.h"
Card::Card(const QString &path, double x, double y): x(x), y(y), m_StateFlag(DEFAULT_FLAG)
{
    setAcceptHoverEvents(true);
    setAcceptDrops(true);
    /* 确定种类信息 */
    //从图片文件的路径中提取出纸牌的花色和大小
    QStringList strlist = path.split('/');
    QString filename = strlist.last();
    QString num,color;
    //qDebug() << filename;
    int i;
    for(i = 0; i < filename.size(); i++) {
        if(filename[i] == '_')
            break;
        num = num + filename[i];
    }
    for(i = i+1; i < filename.size(); i++) {
        if(filename[i] == '.')
            break;
        color = color + filename[i];
    }
    category = num.toInt();
    cardNum = color.toInt();
    switch (category) {
        case 0: cardType = CardType(cardNum);break;
        case 1: career = Career(cardNum);break;
        case 2: resource = Resource(cardNum);break;
    }
    /* 求得卡牌坐标 */
    old_pos = pos();
    /*导入图片*/
    pic = new QPixmap(path);
    cardList = nullptr;/**不知对不对*/
    cardList = new CardList();
    if (category == 0)
        cardList->lastCard = this;
    //cardList->lastCard = this;
    nextCard = nullptr;
    setFlag(ItemIsMovable,true);  // 取消 : setFlag(ItemIsMovable,false);
    setFlag(ItemSendsGeometryChanges);
    /* 在指定位置绘制长方形形状的卡牌 */
    //this->setRect(pos.x(), pos.y(), width, height);
    /* 加阴影 */
    shadow = new QGraphicsDropShadowEffect();
    shadow->setOffset(0,0);
    shadow->setBlurRadius(15);
    this->setGraphicsEffect(shadow);
    this->setBrush(QBrush(Qt::darkGreen));
    this->setPen(Qt::NoPen);
    this->setZValue(0);

}

int Card::getCardNum() const {
    switch (this->category) {
        case 0: return this->cardType;
        case 1: return Military_Academy + 1 + this->career;
        case 2: return Military_Academy + Scout + 2 + this->resource;
        default: return -1;
    }
}

QRectF Card::boundingRect() const {
    QRectF bound = QRectF(0,0,pic->width(),pic->height());
    return bound;
}

void Card::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->save();
    painter->drawPixmap(0,0,pic->width(),pic->height(),*pic);
    painter->restore();
}

QPainterPath Card::shape() const {
    QPainterPath path;
    path.addRect(0,0,pic->width(),pic->height());
    return path;
}

void Card::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    update();
    if (event->button()==Qt::LeftButton) {
        m_StateFlag = MOV_RECT;
        emit cardClick(old_pos);
    }
    else m_StateFlag = DEFAULT_FLAG;
    oldZValue = this->zValue();
    old_pos = event->pos();

    this->setZValue(2000);
    qDebug() << "this.ZValue:" << this->zValue();
    QGraphicsItem::mousePressEvent(event);
}

void Card::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (m_StateFlag == MOV_RECT) {
        setCursor(Qt::CursorShape::ClosedHandCursor);
        emit cardMove(old_pos, event->pos());
        //qDebug() << "从坐标" << old_pos << "移动到" << event->pos();
    }
    else m_StateFlag = DEFAULT_FLAG;
    QGraphicsItem::mouseMoveEvent(event);
}

void Card::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button()==Qt::LeftButton) {
        if (m_StateFlag == MOV_RECT) {
            setCursor(Qt::CursorShape::ArrowCursor);
            //setPos(event->pos());

            /*
            if(handleCollisions() == false)  //没把牌移到了其他地方
            {
                setPos(old_pos);
                this->setZValue(oldZValue);
            }
            */
            //old_pos = event->pos();
            //oldZValue=this->zValue();
            handleCollisions();
            updateCardLinkPosi();
            //setPos(pos);
            qDebug() << "现在移动到了" << old_pos;
            emit cardRelease(old_pos);
        }
    }
    //else Card::mouseReleaseEvent(event);
    m_StateFlag = DEFAULT_FLAG;
    update();

//    if(cardtemp != NULL)
//        this->setZValue(oldZValue);
//    else if(cardlist != NULL && cardlist->getCardNums() == 1)
//    {
//        this->setZValue(2);
//    }
    QGraphicsItem::mouseReleaseEvent(event);
}

void Card::mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event) {
    if (event->button()==Qt::LeftButton) {
        emit cardDoubleClick(event->pos());
        qDebug()<<"Double Click!";
    }
}



void Card::clearCardList()
{
    if(cardList != nullptr)
    {
        if(this->nextCard == nullptr)
        {
            cardList->removeCard();
            cardList = nullptr;
        }
        else
        {
            //清除CardLink
            cardList->removeCardLink(this);
        }
    }
}
/*
void Card::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() != Qt::LeftButton)
    {
        event->ignore();
        return;
    }
    if(this->cardList != nullptr && cardList->getLastCard() != this && this->nextCard == nullptr)
    {
        event->ignore();
        return;
    }


    oldZValue = this->zValue();
    old_pos = pos();

    this->setZValue(2000);
    qDebug() << "this.ZValue:" << this->zValue();
    update();
    QGraphicsItem::mousePressEvent(event);
}
*/

bool Card::handleCollisions() //碰撞检测
{
    QList<QGraphicsItem *> collisions = collidingItems();
    qDebug() << collisions;
            foreach (QGraphicsItem *collidingItem, collisions)
        {
            /*
              if(collidingItem->data(GD_Type) == EMPTY)
              {
                  //控制，使得卡牌放入Temp
                  qDebug() << "检测碰撞到CardTemp";
                  if(this->nextCard != NULL)
                      return false;
                  return controller.CardToTemp(this,dynamic_cast<CardTemp*>(collidingItem));

              }
              */
            //if(collidingItem->data(GD_Type) == CLIST)
            {
                //移动到CardList
                qDebug() << "碰撞到CardList";
                return cardList->CardToList(this,dynamic_cast<Card*>(collidingItem));
            }
            /*
            else if(collidingItem->data(GD_Type) == CDEST)
            {
                qDebug() << "碰撞到CardDest";
                if(this->nextCard != NULL)
                    return false;
                return cardList->CardToDest(this,dynamic_cast<CardDest*>(collidingItem));
            }
            */
        }
    return false;
}

void Card::updateCardLinkPosi() {
    if (this->nextCard == nullptr) return;
    Card *p = this,*pn = nextCard;
    QPointF posi = this->pos();
    while(pn != nullptr) {
        qreal y_new = posi.y() + CARD_LIST_LEAP;
        posi.setY(y_new);
        pn->setPos(posi);
        pn->setZValue(p->zValue() + 1);
        p = pn;
        pn = pn->nextCard;
    }
}

QVariant Card::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    switch(change)
    {
        case ItemPositionChange:
        {
            updateCardLinkPosi();
        }
            break;
        default:
            break;

    }
    return QGraphicsItem::itemChange(change, value);
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

Card::~Card() {
    delete shadow;
}