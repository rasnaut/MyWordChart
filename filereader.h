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

#include "wordcounter.h"

typedef QSharedPointer<WordCounter> sharedP_WCounter;

class FileReader : public QObject
{
    Q_OBJECT
    Q_PROPERTY(float progress READ progress NOTIFY progressChanged)
    Q_PROPERTY(QVariant topWords READ getTopOfWords NOTIFY topWordsReadyChanged)
public:
    FileReader();

    QVariant getTopOfWords() {
        QVariantMap rval;
        for (auto itr: mWC.topStr) { rval.insert(itr.getStr(), itr.position); }
        return QVariant::fromValue(rval);
    }

    void createWindow();

    float progress(){ return 0.0; }

signals:
    void progressChanged(float progress);
    void topWordsReadyChanged(bool isReady);

public slots:
    void readFile(QString fileName);
    void countWords();

private:
    QObject* windowItem;
    QSharedPointer<QQuickView> viewPoint;
    int threadCount;

    WordCounter mWC;
};

#endif // FILEREADER_H
