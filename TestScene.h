#pragma once

#include <QGraphicsScene>
#include <QGraphicsSimpleTextItem>
#include <QTime>

class TestScene
  : public QGraphicsScene
{
    Q_OBJECT;

public:
    QGraphicsSimpleTextItem* m_sti;

    TestScene(const int& charCount);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);

protected:
    const int m_charCount;
    QTime m_last;
};
