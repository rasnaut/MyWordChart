#ifndef FILEREADER_H
#define FILEREADER_H

#include <QObject>
#include <QFuture>
#include <QList>
#include <QVariantMap>

#include <QtGui>
#include <QSharedPointer>
#include <QtQuick/QQuickWindow>
#include <QtQuick/QQuickView>
#include <QtQml/QQmlEngine>
//#include <Decl

#include "wordcounter.h"

class FileReader : public QObject
{
    Q_OBJECT
public:
    FileReader();

    Q_INVOKABLE QVariantMap getTopOfWords() {
        QVariantMap rval;
        for (auto itr: mWC.topStr) { rval[itr.getStr()] = itr.position; }
        return rval;
    }

    void createWindow();


public slots:
    void readFile(QString fileName);
    void countWords();

private:
    QObject* windowItem;
    QSharedPointer<QQuickView> viewPoint;

    WordCounter mWC;
    QList<QFuture<WordCounter>> futureList;

};

#endif // FILEREADER_H
