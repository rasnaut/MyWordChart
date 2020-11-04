#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtConcurrent/QtConcurrent>
#include <QFuture>
#include <QList>
#include <QFileDialog>

#include "wordcounter.h"

QT_CHARTS_USE_NAMESPACE


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow window;

    window.resize(420, 300);
    window.show();

    QString fileName = QFileDialog::getOpenFileName(&window,
        "Open Text File", "/home/", "Text Files (*.txt)");

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

    if(!futureList.empty()) {
        for(auto itrFuture: futureList) {
            itrFuture.waitForFinished();
            mWC += itrFuture.result();
        }
    }

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
    chart->setTitle("Simple barchart example");
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

    return a.exec();
}
