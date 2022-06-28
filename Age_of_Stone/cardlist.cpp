#include "cardlist.h"
#include <QPainter>
#include <QDebug>
CardList::CardList()
{
    lastCard = nullptr;
    setData(GD_Type,CLIST);
}

bool CardList::enableCard(Card *card) const
{
    /* 不妨设计成只有地点卡牌打头阵或者全是普通牌时才可以接龙 */
    if(lastCard == nullptr)
        return true;
    else
    {
        int MIN = Military_Academy + 1;
        for (Card* c : lastCard->cardList->cardlist)
            if (c->cardNum < MIN) {
                MIN = c->cardNum;
                break;
            }
        if (MIN <= Military_Academy)
        //if(int(lastCard->getCardNum()) >= Military_Academy + Scout + 2 +Wood)
            return lastCard->getCardNum() <= card->getCardNum(); //是因为木头、石头刚好是最后两号
        return false;
    }
}

void CardList::insertCard(Card *card)
{
    qDebug() << "insertCard()";
    cardlist.append(card);
//    for(int i = 0; i < cardlist.size()-1; i ++)
//    {
//        //把前面的卡片都设置成不可拖动
//        cardlist[i]->setFlag(ItemIsMovable,false);
//        cardlist[i]->setTop(false);
//    }
    if(lastCard != nullptr)
        card->setZValue(lastCard->zValue() + 1);
    lastCard = card;
    update();
}


void CardList::removeCard() //清理被移除的最后一张纸牌
{
    qDebug() << "removeCard()";

    if(cardlist.isEmpty())
        lastCard = nullptr;
    else
    {
        cardlist.removeLast();
        if(cardlist.isEmpty())
            lastCard = nullptr;
        else {
            lastCard = cardlist.last();
            qDebug() << "after remove, old cardlist's last Card:" << Card::m_Profile[lastCard->category][lastCard->cardNum];
            lastCard->setFlag(ItemIsMovable,true);
            //lastCard->setTop(true);
            lastCard->nextCard = nullptr;
        }
    }
    update();
}


void CardList::removeCardLink(Card *begincard)  //清理被移除的整个纸牌链
{
    qDebug() << "removeCardLink";
    int beginIndex = 0;
    for(int i = 0; i < cardlist.size(); i++)
    {
        if(cardlist.at(i) == begincard)
        {
            beginIndex = i;
            break;
        }
    }
    if(beginIndex == 0)
    {
        cardlist.clear();
        lastCard = nullptr;
    }
    else
    {
        int nums = cardlist.size() - beginIndex;
        while(nums--)
        {
            cardlist.removeLast();
        }
        lastCard = cardlist.last();
        lastCard->setFlag(ItemIsMovable,true);
        //lastCard->setTop(true);
        lastCard->nextCard = nullptr;
    }

    update();
}

Card *CardList::getLastCard() const
{
    return lastCard;
}

void CardList::appendCard(Card *newCard)
{
    cardlist.append(newCard);
}

Card *CardList::getCard(int i)
{
    if(i > cardlist.size())
        return nullptr;
    return cardlist[i];
}

int CardList::getCardNums() const
{
    return cardlist.size();
}

void CardList::initCardsZValue()
{
    for(int i = 0; i < cardlist.size(); i++)
    {
        cardlist[i]->setZValue(i+1);
       // qDebug() <<"z:" <<cardlist[i]->zValue();
    }
}

QRectF CardList::boundingRect() const
{
    qreal ht = CARD_HEIGHT + cardlist.size() * CARD_LIST_LEAP;
    qreal hw = CARD_WIDTH;

    return QRectF(0,0,hw,ht);
}

void CardList::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    qDebug() << "paint()";
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->save();
    painter->setPen(QPen(QColor(255,180,100),6));
    painter->drawRect(0,0,CARD_WIDTH,CARD_HEIGHT);
    painter->restore();
}

// 用于碰撞检测
QPainterPath CardList::shape() const
{
    qDebug() << "shape()";
    QPainterPath path;
    path.addRect(0,cardlist.size()*CARD_LIST_LEAP,CARD_WIDTH,CARD_HEIGHT);
    return path;

}
bool CardList::CardToList(Card* card, CardList* cardList) {
    qDebug() << "CardToList()";
    if(card->cardList == cardList){
        qDebug() << "同一个CardList";
        return false;
    }

    if(cardList->enableCard(card))
    {
        if(card->cardList != nullptr)  //卡牌来自其他牌区
            card->clearCardList();

        //更新位置
        if(cardList->lastCard != nullptr) {
            QPointF posi= cardList->getLastCard()->pos();
            qDebug() << posi;
            qreal y_new = posi.y() + CARD_LIST_LEAP;
            posi.setY(y_new);
            qDebug() << posi;
            card->setPos(posi);
            card->stackBefore(cardList->lastCard);

            //实现同时拖动多张纸牌
            cardList->getLastCard()->nextCard = card;
        }
        else
        {
            QPointF a = cardList->pos();
            card->setPos(cardList->pos());
            card->setZValue(1);
        }

        //插入cardList
        if(card->nextCard == NULL)
        {
            cardList->insertCard(card);
            card->cardList = cardList;
        }
        else
        {
            Card *p = card;
            while(p != NULL)
            {
                p->cardList = cardList;
                cardList->insertCard(p);
                p = p->nextCard;
            }
        }
        return true;
    }
    return false;
}

bool CardList::CardToList(Card* card, Card* card_) {
    qDebug() << "CardToList()";
    if(card->cardList == card_->cardList && card->cardList != nullptr){
        qDebug() << "同一个CardList";
        return false;
    }

    if(card_->cardList->enableCard(card))
    {
        if(card->cardList != nullptr)  //卡牌来自其他牌区
            card->clearCardList();

        //更新位置
        if(card_->cardList->lastCard != nullptr) {
            QPointF posi= card_->cardList->getLastCard()->pos();
            qDebug() << posi;
            qreal y_new = posi.y() + CARD_LIST_LEAP;
            posi.setY(y_new);
            qDebug() << posi;
            card->setPos(posi);
            card->stackBefore(card_->cardList->lastCard);

            //实现同时拖动多张纸牌
            card_->cardList->getLastCard()->nextCard = card;
        }
        else
        {
            card->setPos(card_->cardList->pos());
            card->setZValue(1);
        }

        //插入cardList
        if(card->nextCard == nullptr)
        {
            card_->cardList->insertCard(card);
            card->cardList = card_->cardList;
        }
        else
        {
            Card *p = card;
            while(p != nullptr)
            {
                p->cardList = card_->cardList;
                card_->cardList->insertCard(p);
                p = p->nextCard;
            }
        }
        return true;
    }
    return false;
}
