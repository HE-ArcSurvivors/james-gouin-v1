#include "w_dialog.h"
#include <QPainter>
#include <QDebug>

#include <QFormLayout>
#include <QLabel>
#include <QStyleOption>

WidgetDialog::WidgetDialog(QWidget *parent)
{
    resize(300,200);
    this->setStyleSheet(
                        "text-align: center;"
                        "color: #2e2e2e;"
                        "background-color: #ffffff;"
                        "border-style: solid;"
                        "border-color: #d3d3d3;"
                        "border-width: 1px;"
                        "border-radius: 8px;"
                        "font-family: Century Gothic;"
                        );

    QVBoxLayout* layout = new QVBoxLayout;
    title = new QLabel(tr("Ordre de mission de James Gouin"));
    title->setStyleSheet(
                "font: bold 20px;"
                "border-style: none;"
                );

    text = new QLabel();
    text->setStyleSheet(
                "font-size: 14px;"
                "border-style: none;"
                );
    text->setWordWrap(true);

    escapeText = new QLabel(tr("Espace pour continuer"));
    escapeText->setStyleSheet(
                "font: bold 12px;"
                "border-style: none;"
                );

    escapeText->setAlignment(Qt::AlignCenter);

    title->setAlignment(Qt::AlignCenter);

    layout->addWidget(title);
    layout->addWidget(text);
    layout->addStretch(1);
    layout->addWidget(escapeText);

    this->setLayout(layout);
}

void WidgetDialog::setText(QString text, int type)
{
    this->type = type;
    this->text->setText(text);
}

void WidgetDialog::paintEvent(QPaintEvent *pe)
{
  QStyleOption o;
  o.initFrom(this);
  QPainter p(this);
  style()->drawPrimitive(
  QStyle::PE_Widget, &o, &p, this);
}

