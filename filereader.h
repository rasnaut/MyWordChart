#ifndef FILEREADER_H
#define FILEREADER_H

#include <QObject>
#include <QFuture>
#include <QList>

#include <QtGui>
//#include <Decl

#include "wordcounter.h"

class FileReader : public QObject
{
    Q_OBJECT
public:
    FileReader();


public slots:
    void readFile(QString fileName);
    void countWords();

private:
    WordCounter mWC;
    QList<QFuture<WordCounter>> futureList;
};

#endif // FILEREADER_H
