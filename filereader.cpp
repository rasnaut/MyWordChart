#include "filereader.h"

#include <QFutureWatcher>
#include <QtConcurrent/QtConcurrent>
#include <QtQuick/QQuickItem>
#include <QQmlContext>

#include <QFileDialog>
#include <QMainWindow>

FileReader::FileReader() : threadCount(0)
{

}

sharedP_WCounter wordCounterCreator(QString str, FileReader *fileReader) {
    sharedP_WCounter pWCounter = sharedP_WCounter(new WordCounter(str));
    QObject::connect(pWCounter.data(), SIGNAL(wordCountChanged(int)) , fileReader, SLOT(wordCountChanged(int)));
    QObject::connect(pWCounter.data(), SIGNAL(progressChanged(int)) , fileReader, SLOT(progressCounter(int)));
    return pWCounter;
}

void FileReader::createWindow()
{
    viewPoint = QSharedPointer<QQuickView>(new QQuickView(QUrl("qrc:/MainWindow.qml")));
    windowItem = viewPoint->rootObject();
    viewPoint->engine()->rootContext()->setContextProperty("fileReader", this);

    QObject::connect(windowItem, SIGNAL(fileUrlSignal(QString)) , this, SLOT(readFile(QString)));

    viewPoint->setTitle(QStringLiteral("QML Chart"));

    viewPoint->show();
}

void FileReader::readFile(QString fileName)
{
    QFile file(QUrl(fileName).toLocalFile());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qCritical() << "file not found or not correct type";
        //return 0;
    }

    QTextStream in(&file);
    int counter = 0;
    QString threadStringBlock("");

    while (!in.atEnd()) {
        if(counter++ < 100) {
            threadStringBlock += in.readLine();
        } else {
            threadCount++;
            QFutureWatcher<sharedP_WCounter>* watcher = new QFutureWatcher<sharedP_WCounter>();
            watcher->setFuture(QtConcurrent::run(wordCounterCreator, threadStringBlock, this));
            QObject::connect(watcher, SIGNAL(finished()), this, SLOT(countWords()));

            counter = 0;
            threadStringBlock = "";
        }
    }

    file.close();
    if(threadStringBlock.size()>0) mWC.addWord(threadStringBlock);

    if(threadCount == 0) { emit topWordsReadyChanged(true); }
}

void FileReader::countWords()
{
    QFutureWatcher<sharedP_WCounter> *watcher = (QFutureWatcher<sharedP_WCounter>*)sender();
    mWC += *(watcher->result());
    delete watcher;
    if(--threadCount <= 0) {
        emit topWordsReadyChanged(true);
    }
}
