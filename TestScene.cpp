#include <QBrush>
#include <QDebug>
#include <QFont>
#include <QPen>
#include "TestScene.h"

static const char CHARACTERS[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789      \n";
static const int NUM_CHARACTERS = sizeof(CHARACTERS) / sizeof(CHARACTERS[0]) - 1;

TestScene::TestScene(const int& charCount)
  : QGraphicsScene::QGraphicsScene(),
    m_charCount(charCount)
{
    m_sti = addSimpleText("sadjfhakjshdfkasjhdf");
    m_sti->setBrush(QBrush(Qt::blue));
    m_sti->setPen(QPen(Qt::red));
    QFont f(m_sti->font());
    f.setBold(true);
    f.setPointSize(24);
    m_sti->setFont(f);
}

void TestScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    if(m_last.isValid()) qDebug() << (1 / (m_last.elapsed()/1000.0f));
    m_last.restart();

    char* rand_str = new char[m_charCount + 1];
    for(char* c = rand_str, *ce = rand_str + m_charCount; c != ce; ++c)
    {
        *c = CHARACTERS[qrand() % NUM_CHARACTERS];
    }
    rand_str[m_charCount] = '\0';
    m_sti->setText(rand_str);
    delete[] rand_str;
    QGraphicsScene::mouseMoveEvent(mouseEvent);
}
