#include "filereader.h"

#include <QFutureWatcher>
#include <QtConcurrent/QtConcurrent>
#include <QFileDialog>


FileReader::FileReader()
{
    futureList.clear();
}

WordCounter wordCounterCreator(QString str) {
    return WordCounter(str);
}

void FileReader::readFile(QString fileName)
{
    QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qCritical() << "file not found or not correct type";
            //return 0;
        }

    QTextStream in(&file);
    int counter = 0;
    QString threadStringBlock("");

    while (!in.atEnd()) {
        if(counter++ < 100)
            threadStringBlock += in.readLine();
        else {
            QFutureWatcher<WordCounter> watcher;
            QObject::connect(&watcher, SIGNAL(finished()), this, SLOT(countWords()));
            QFuture<WordCounter> pFut = QtConcurrent::run(wordCounterCreator, threadStringBlock);
            futureList.append(pFut);
            counter = 0;
            threadStringBlock = "";
        }
    }

    file.close();
    if(threadStringBlock.size()>0)
        mWC.addWord(threadStringBlock);
}

void FileReader::countWords()
{
    QFutureWatcher<WordCounter> *watcher = (QFutureWatcher<WordCounter>*)sender();
    mWC += watcher->result();
}
