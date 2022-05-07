#include "board.h"
#include <QGraphicsView>
#include <algorithm>
#include <QDebug>
using namespace std;

Board::Board(QObject *parent) : QObject(parent)
{
    view.setScene(&scene);
    /* 抗锯齿 */
    view.setRenderHints(QPainter::Antialiasing);
    for (Card*& card_ : card) {
        card_ = new Card(0,0);
        card_->setFlag(QGraphicsItem::ItemIsMovable,true);
        scene.addItem(card_);
        connect(card_, SIGNAL(cardDoubleClick(QPointF)),this,SIGNAL(userDoubleClick(QPointF)));
    }

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

/* 将(r,c)上的棋放到(nr, nc)上, flipTurn == true时反转turn */
void Board::put(int r, int c, int nr, int nc, bool flipTurn) {
/* 判断非法情况 */


}


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
