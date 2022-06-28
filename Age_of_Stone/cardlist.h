#ifndef CARDLIST_H
#define CARDLIST_H

#include "card.h"
#include <QList>
//卡牌放置区 用链表实现
class CardList : public QGraphicsItem
{

private:
    QList<Card*> cardlist;
public:
    friend class Card;
    CardList();
    Card *lastCard;

    //以下是用来被GameController调用的
    bool enableCard(Card *card) const;
    void insertCard(Card *card);   //在尾端插入一张纸牌
    void removeCard();   // 移走CardList后进行的更新

    Card* getLastCard() const;
    void appendCard(Card* newCard);

    Card* getCard(int i);
    int getCardNums() const;
    void initCardsZValue();
    bool CardToList(Card* card, CardList* cardList);
    bool CardToList(Card* card, Card* card_);
    //移除Card链
    void removeCardLink(Card *begincard);

protected:

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QPainterPath shape() const override;

};

#endif // CARDLIST_H
