#include "interfunc.h"
#include <QGraphicsDropShadowEffect>
#include "block.h"

Content::Content(QWidget *parent) : parent(parent) {
    setParent(parent);
    /*删除以下行会导致窗口不独立出去*/
    setWindowFlags(Qt::WindowType::Window);
    /*默认模态为NonModal，但是我们需要设为存在，以便使得子窗口关闭前不能对父窗口进行操作*/
    setWindowModality(Qt::WindowModality::ApplicationModal);
    setAttribute(Qt::WA_ShowModal,true);
    /*默认并不会，所以手动设置关闭时释放内存，以防内存泄漏*/
    setAttribute(Qt::WA_DeleteOnClose,true);
    QGraphicsItem::setVisible(true);
    QWidget::setVisible(true);
    setWindowTitle("Test");
    confirm = new QPushButton;
    reset = new QPushButton;
    cancel = new QPushButton;

    boxLayout = new QHBoxLayout;
    boxLayout->addWidget(new QCalendarWidget);
    layout = new QHBoxLayout;
    layout->setObjectName("test");
    layout->addLayout(boxLayout);
    setLayout(layout);
    //QGraphicsItem::show();
    //QWidget::show();
}
Content::~Content() noexcept {

}
