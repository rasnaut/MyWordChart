#include <vector>
#include "wordcounter.h"

WordCounter::WordCounter() : wordCount(0), progress(0)
{
    strMap.clear();
    topStr.clear();
}

WordCounter::WordCounter(QString str) : incStr(str), wordCount(0), progress(0)
{
    strMap.clear();
    topStr.clear();
    addWord(incStr);
}

void WordCounter::addWord(QString str)
{
    QStringList strList = str.split(' ');
    if(strList.size() < 2) { strMap.insert(str, 1);}
    wordCount += strList.size();
    emit wordCountChanged(wordCount);
    for(auto itr: strList)
    {
        emit progressChanged(++progress);
        auto fWordItr = strMap.find(itr);
        if(fWordItr != strMap.end())
        {
            myChart tmpCh(fWordItr.key(),fWordItr.value());
            fWordItr.value()++;
            auto itrTop = topStr.find(tmpCh);
            if(itrTop != topStr.end())
            {
                topStr.erase(itrTop);
                tmpCh.position++;
                topStr.insert(tmpCh);
            }
            else
            {
                tmpCh.position++;
                topStr.insert(tmpCh);
                if(topStr.size()>15) { topStr.erase(topStr.begin()); }
            }
        } else {
            strMap.insert(itr, 1);
            if(topStr.size()<15) { topStr.emplace(itr,1); }
        }
    }
}

WordCounter& WordCounter::operator+=(const WordCounter& right)
{
    std::vector<myChart> newTopStr;
    newTopStr.clear();
    for(auto itr: topStr) {
        auto itrStrMap = right.strMap.find(itr.getStr());
        if(itrStrMap != right.strMap.end()) {
            int newPos = itr.position + itrStrMap.value();
            newTopStr.push_back(myChart(itr.getStr(), newPos));
        }
    }
    for(auto itr: right.topStr) {
        auto itrStrMap = strMap.find(itr.getStr());
        if(itrStrMap != strMap.end()) {
            if(topStr.find(myChart(itrStrMap.key(), itrStrMap.value())) == topStr.end()) {
                int newPos = itr.position + itrStrMap.value();
                itrStrMap.value() = newPos;
                newTopStr.push_back(myChart(itr.getStr(), newPos));
            }
        } else {
            newTopStr.push_back(myChart(itr.getStr(), itr.position));
        }

    }
    std::sort(newTopStr.begin(), newTopStr.end());
    for(auto itr: newTopStr) { strMap.find(itr.getStr()).value() = itr.position; }
    if(newTopStr.size()>15) {
        newTopStr.erase(newTopStr.begin(), newTopStr.end()-15);
    }
    topStr.clear();
    for(auto itr: newTopStr) { topStr.insert(itr); }
    return *this;
}

bool operator<(const myChart& left, const myChart& right) {
    if(left.position < right.position) return true;
    else if(left.position == right.position &&
            left.getStr() < right.getStr())
        return true;

    return false;
}

bool operator==(const myChart& left, const myChart& right) {
    if(left.position == right.position &&
       left.getStr() == right.getStr()) return true;

    return false;
}
