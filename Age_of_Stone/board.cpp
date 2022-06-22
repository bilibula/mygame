#include "board.h"
#include <QGraphicsView>
#include <algorithm>
#include <QDebug>
using namespace std;

Board::Board(QObject *parent) : QObject(parent)
{
    /* 这一段是在初始化科技树及其前置要求 */
    for (int i = RECORD; i <= GOD_DESCEND; ++i)
        Tech[i].push_back(RECORD);

    QString path = QDir::currentPath();
    QDir dir(":/card/images/");
            foreach (QFileInfo img, dir.entryInfoList()){
            Card* c = new Card(img.filePath(),0,0);
            allCards.append(c);
            scene.addItem(c);
        }
    /*
    for(int i = 0, cnt = 0; i < M; i++)
    {
        cardList[i] = new CardList();
        for(int j = 0; j < list_card_num[i]; j++)
        {
            cardList[i]->appendCard(allcards[cnt++]);
        }
    }
    */
    /*
    cardList[0] = new CardList();
    for (int i = 0; i < allCards.size(); ++i) cardList[0]->appendCard(allCards[i]);
    scene.addItem(cardList[0]);

    cardList[0]->setPos(CARD_LIST_X,CARD_LIST_Y);
    */
    view.setScene(&scene);
    /* 抗锯齿 */
    view.setRenderHints(QPainter::Antialiasing);
    /*
    for (Card*& card_ : card) {
        card_ = new Card(,0,0);
        card_->setFlag(QGraphicsItem::ItemIsMovable,true);
        scene.addItem(card_);
        connect(card_, SIGNAL(cardDoubleClick(QPointF)),this,SIGNAL(userDoubleClick(QPointF)));
    }
    */
    view.setBaseSize(view.sizeHint());
    view.setFixedSize(800,600);

}

QGraphicsView* Board::View() {
    return &view;
}

void Board::cardClick(const QPointF &startPos) {

}

void Board::cardMove(const QPointF &startPos, const QPointF &endPos){}
void Board::cardRelease(const QPointF &endPos){}
void Board::cardDoubleClick(const QPointF &pos){}
void Board::cardDragAndDrop(const QPointF &startPos, const QPointF &endPos){}

/* 根据card[]的值更新视图 */
void Board::updateView() {

}

void Board::reset() {

}

void Board::enable() {
    enabled = true;
}

void Board::disable() {
    enabled = false;
}

Board::~Board() {
    for (Card*& card_ : card) delete card_;

}