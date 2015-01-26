#ifndef W_DIALOG_H
#define W_DIALOG_H

#include <QWidget>
class QLabel;

class WidgetDialog : public QWidget
{
    Q_OBJECT
public:
    WidgetDialog(QWidget *parent = 0);
    void setText(QString text, int type);
    QString getText();
    void paintEvent(QPaintEvent *);

signals:

public slots:

private:
    int type;
    QLabel* title;
    QLabel* text;
    QLabel* escapeText;

};

#endif // W_DIALOG_H
