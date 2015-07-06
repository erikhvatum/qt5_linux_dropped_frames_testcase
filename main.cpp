#include <cctype>
#include <cstdlib>
#include <iostream>
#include <QApplication>
#include <QDebug>
#include <QDesktopWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMessageBox>
#include <QOpenGLContext>
#include <QOpenGLWidget>
#include <QString>
#include <QSurfaceFormat>

#include "TestScene.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    if(argc < 2)
    {
        QMessageBox::critical(0, "", "Supply an integer for random string char count as first command-line argument.\n"
                                     "Other accepted arguments that may appear after the first argument:\n"
                                     "--doublebuffer\n"
                                     "--triplebuffer\n"
                                     "--swapinterval_0\n"
                                     "--swapinterval_-1\n"
                                     "--samplecount_0\n"
                                     "By default:\n"
                                     "    Single buffering is requested.\n"
                                     "    Swap interval of 1 is requested.\n"
                                     "    Sample count of 4 is requested.\n");
        return -1;
    }
    for(char* c = argv[1];;)
    {
        if(*c == '\0')
        {
            if(c == argv[1])
            {
                QMessageBox::critical(0, "", "First argument must not be \"\" :)");
                return -1;
            }
            break;
        }
        if(std::isdigit(*c))
        {
            ++c;
        }
        else
        {
            QMessageBox::critical(0, "", "First arugment must consist entirely of digits.");
            return -1;
        }
    }
    const int charCount = atoi(argv[1]);
    QSurfaceFormat fmt;
    fmt.setRenderableType(QSurfaceFormat::OpenGL);
    fmt.setProfile(QSurfaceFormat::CompatibilityProfile);
    if(QCoreApplication::arguments().contains(QStringLiteral("--doublebuffer")))
    {
        fmt.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
    }
    else if(QCoreApplication::arguments().contains(QStringLiteral("--triplebuffer")))
    {
        fmt.setSwapBehavior(QSurfaceFormat::TripleBuffer);
    }
    else
    {
        fmt.setSwapBehavior(QSurfaceFormat::SingleBuffer);
    }
    if(QCoreApplication::arguments().contains(QStringLiteral("--swapinterval_0")))
    {
        fmt.setSwapInterval(0);
    }
    else if(QCoreApplication::arguments().contains(QStringLiteral("--swapinterval_-1")))
    {
        fmt.setSwapInterval(-1);
    }
    else
    {
        fmt.setSwapInterval(1);
    }
    if(QCoreApplication::arguments().contains(QStringLiteral("--samplecount_0")))
    {
        fmt.setSamples(0);
    }
    else
    {
        fmt.setSamples(4);
    }
    fmt.setVersion(2, 1);

    QOpenGLWidget* gl_widget = new QOpenGLWidget;
    gl_widget->setFormat(fmt);

    QGraphicsScene* gs = new TestScene(charCount);
    QGraphicsView* gv = new QGraphicsView;
    gv->setViewport(gl_widget);
    gv->setScene(gs);
    gv->setMouseTracking(true);

    gv->show();

    QOpenGLContext* c = gl_widget->context();
    fmt = c->format();
    qDebug() << "swapInterval:" << fmt.swapInterval();
    QString str;
    switch(fmt.swapBehavior())
    {
    default:
        str = "unknown";
        break;
    case QSurfaceFormat::SingleBuffer:
        str = "SingleBuffer";
        break;
    case QSurfaceFormat::DoubleBuffer:
        str = "DoubleBuffer";
        break;
    case QSurfaceFormat::TripleBuffer:
        str = "TripleBuffer";
        break;
    }
    qDebug() << "swapBehavior:" << str;
    qDebug() << "samples:" << fmt.samples();
    
    return app.exec();
}
