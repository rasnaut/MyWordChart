#ifndef WORDCOUNTER_H
#define WORDCOUNTER_H
#include <string>
#include <QMap>
#include <set>
#include <QString>
#include <QtDebug>

#include <QObject>
class myChart
{
public:
    myChart(QString _str, int _pos) : position(_pos), str(_str) {}
    ~myChart(){}


    QString getStr() const {
        return str;
    }

    friend bool operator<(const myChart& left, const myChart& right);
    friend bool operator==(const myChart& left, const myChart& right);

    int position;
private:
    QString str;

};

class WordCounter : public QObject
{
    Q_OBJECT
public:
    WordCounter();
    WordCounter(QString str);

    void addWord(QString str);

    WordCounter& operator+=(const WordCounter& right);

    std::set<myChart> topStr;


signals:
    void wordCountChanged(int wordCount);
    void progressChanged(int progress);
private:
    QString incStr;
    QMap<QString, int> strMap;
    int wordCount;
    int progress;

};

#endif // WORDCOUNTER_H
