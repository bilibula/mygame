#ifndef INTERFUNC_H
#define INTERFUNC_H
#include <QtWidgets>
#include <QGraphicsItem>
#include <QPen>
#include <QBrush>
#include <vector>
/* 枚举 */
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 900

#define CARD_LIST_Y 400
#define CARD_LIST_X 40

#define TOTAL_CARDS 52

#define CARD_WIDTH 105
#define CARD_HEIGHT 150



#define CARD_LIST_LEAP 25  //牌区两张牌之间的间隔
#define CARD_LIST_WIDTH_LEAP 30  //不同牌区的间距
#define CARD_LIST_NUM 8  //多少个CARD_LIST

#define CARD_TEMP_NUM 4
#define CARD_TEMP_X 40
#define CARD_TEMP_Y 10

#define CARD_DEST_NUM 4
#define CARD_DEST_X 600
#define CARD_DEST_Y 10

#define SCORE_PER_CARD 1000  //每张卡的得分
#define TIME_DEC 10  //时间得分惩罚
/* 用来实现卡牌点开后的内部功能(internal function) */
enum GameObjectsData {
    GD_Type
};
enum Techniques {
    RECORD = 0,
    FAITH,
    HUNTING_I,
    HUNTING_II,
    AGRICULTURE_I,
    AGRICULTURE_II,
    COLLECTION_I,
    LOGGING_I,
    LOGGING_II,
    STONE_TOOL,
    TEMPLE,
    PRIEST,
    THEOLOGY_I,
    THEOLOGY_II,
    THEOLOGY_III,
    NATURAL_HISTORY_I,
    NATURAL_HISTORY_II,
    BATTLE_I,
    BATTLE_II,
    MINING_I,
    MINING_II,
    FIRE,
    LANGUAGE,
    ANIMAL_HUSBANDRY,
    TAMING,
    SCHOOL,
    LAB,
    CHURCH,
    PRIOR_PRIEST,
    MEDICINE_I,
    MEDICINE_II,
    MATH_I,
    MATH_II,
    MATH_III,
    COMMON_LANGUAGE,
    SOCIOLOGY,
    COMMUNICATION,
    ORGANIZATION_I,
    ORGANIZATION_II,
    COMMERCE_I,
    COMMERCE_II,
    PHILOSOPHY_I,
    PHILOSOPHY_II,
    PHYSICS_I,
    PHYSICS_II,
    PHYSICS_III,
    GOD_FAVOR,
    GOD_POWER,
    GOD_GIFT,
    POPE,
    GOD_DESCEND,
};
enum CardTempTypes {
    EMPTY,   //可以被放入纸牌
    FULL,     //不可以放入纸牌
    CLIST,   //Card List区
    CDEST  //终点区
};
class Card;
class CardList;
static std::vector<Techniques> Tech[60];
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
