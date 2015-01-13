#ifndef W_DIALOG_H
#define W_DIALOG_H

#include <QWidget>

class WidgetDialog : public QWidget
{
    Q_OBJECT
public:
    WidgetDialog(QWidget *parent = 0);
    void setText(QString text);
    void paintEvent(QPaintEvent *);

signals:

public slots:

private:
    QString text;

};

#endif // W_DIALOG_H
