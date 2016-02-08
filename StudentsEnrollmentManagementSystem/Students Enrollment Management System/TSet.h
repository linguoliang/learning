#pragma once

#include <set>

template<class T>
class TSet
{
public:
    TSet();
    virtual ~TSet();

    std::set<T> getSet(){ return Set; }
    void addSetItem(T item);
    void deleteSetItem(T item);
    int getSetSize(){ return Set.size(); }

protected:
    std::set<T> Set;
};

template<class T>
TSet<T>::TSet()
{
}

template<class T>
TSet<T>::~TSet()
{
}

template<class T>
void TSet<T>::addSetItem(T item)
{
    Set.insert(item);
}

template<class T>
void TSet<T>::deleteSetItem(T item)
{
    auto pt = Set.find(item);
    Set.erase(pt);
}
