#ifndef INTERFUNC_H
#define INTERFUNC_H
#include <QtWidgets>
#include <QGraphicsItem>
#include <QPen>
#include <QBrush>
enum PieceType { Black = 0, White = 1, None = 2 } ;
/*用来实现卡牌点开后的内部功能(internal function)*/

class Content : public QWidget, public QGraphicsRectItem {
    Q_OBJECT
public:
    explicit Content(QWidget* parent=0);
    ~Content();

private:
    QWidget* parent;
    QPushButton* confirm;
    QPushButton* reset;
    QPushButton* cancel;
    QHBoxLayout* boxLayout;
    QHBoxLayout* layout;

};

#endif // INTERFUNC_H
