#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_Send_pushButton_clicked();

private:
    Ui::Widget *ui;
    void QTSTRtoMAC(QString str, char *mac);
};

#endif // WIDGET_H
