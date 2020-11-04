#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

#include <QtGui/QSurfaceFormat>
#include <QtQuick/QQuickWindow>
#include <QtQuick/QQuickView>
#include <QtQml/QQmlEngine>

#include "wordcounter.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQuickView viewer(QUrl("qrc:/MainWindow.qml"));
    //QObject *item = view.rootObject();

    //QObject::connect(viewer.engine(), &QQmlEngine::quit, &viewer, &QWindow::close);

    viewer.setTitle(QStringLiteral("QML Chart"));

    viewer.show();
/*

    QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qCritical() << "file not found or not correct type";
            return 0;
        }


    QTextStream in(&file);
    WordCounter mWC;
    int counter = 0;
    QString threadStringBlock("");
    QList<QFuture<WordCounter>> futureList;
    futureList.clear();
    while (!in.atEnd()) {
        if(counter++ < 100)
            threadStringBlock += in.readLine();
        else {
            QFuture<WordCounter> pFut = QtConcurrent::run(wordCounterCreator, threadStringBlock);
            futureList.append(pFut);
            counter = 0;
            threadStringBlock = "";
        }
    }

    file.close();
    if(threadStringBlock.size()>0)
        mWC.addWord(threadStringBlock);



//![1]

    QBarSeries *series = new QBarSeries();
    for(auto itr: mWC.topStr) {
        qInfo() << itr.getStr() << " : " << itr.position;
        QBarSet *lSet = new QBarSet(itr.getStr());
        *lSet << itr.position;
        series->append(lSet);
    }
//![3]
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Top Word in");
    chart->setAnimationOptions(QChart::SeriesAnimations);
//![3]

//![4]
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0,mWC.topStr.rbegin()->position);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
//![4]

//![5]
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
//![5]

//![6]
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
//![6]

//![7]
    window.setCentralWidget(chartView);
    window.update();
//![7]
*/
    return app.exec();
}
