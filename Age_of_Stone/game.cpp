#include "game.h"

Game::Game(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Age of Stone");
    layoutTop = new QHBoxLayout;
    layout = new QVBoxLayout;
    layoutBottom = new QHBoxLayout;
    label = new QLabel;
    easyRadio = new QRadioButton("简单");
    normalRadio = new QRadioButton("普通");
    hardRadio = new QRadioButton("困难");
    startBtn = new QPushButton("开始游戏");
    pauseBtn = new QPushButton("暂停游戏");
    hardnessSpin = new QSpinBox;
    hardnessSpin ->setRange(1,3);
    label->setBuddy(hardnessSpin);
    layoutTop->addWidget(startBtn);
    layoutTop->addWidget(pauseBtn);
    layoutTop->addWidget(easyRadio);
    layoutTop->addWidget(normalRadio);
    normalRadio->setChecked(true);
    layoutTop->addWidget(hardRadio);
    layoutTop->addWidget(label);

    connect(startBtn, SIGNAL(clicked(bool)), this, SLOT(startBtnClick()));
    connect(pauseBtn, SIGNAL(clicked(bool)), this, SLOT(pauseBtnClick()));
    connect(&board, SIGNAL(userDoubleClick(QPointF)), this, SLOT(userDoubleClick(QPointF)));
    /*
    QMenuBar* bar = new QMenuBar;
    bar->addMenu("Menu");
    QMenu* menu1 = new QMenu;
    QMenu* menu2 = new QMenu;
    menu1->show();
    menu2->show();
    menu1->setTitle("1");
    menu2->setTitle("2");
    bar->addMenu(menu1);
    bar->addMenu(menu2);
    layoutTop->addWidget(bar);
    */
    layout->addLayout(layoutTop);
    layout->addWidget(board.View());
    setLayout(layout);
    //setFixedSize(sizeHint());
}
/*
Game::~Game() {
    layout->
    delete layoutTop;
    delete layoutVertical;
    delete layoutBottom;
    delete label;
    delete pauseRadio;
    easyRadio;
    normalRadio;
    hardRadio;
    startBtn;
    hardnessSpin;
}
*/
void Game::userDoubleClick(const QPointF& pos) {
    Content* content = new Content(this);
    /*使其以模态显示*/
    content->showNormal();
}
void Game::startBtnClick() {

}
void Game::pauseBtnClick() {

}
