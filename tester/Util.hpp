#ifndef UTIL_HPP
#define UTIL_HPP

#include <ctime>
#include <cstdlib>

const int range[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
const int nrange[] = {0, -1, -2, -3, -4, -5, -6, -7, -8, -9, -10};

template <class Out, class Key, class Val>
void keyval(Out& out, Key key, Val val)
{
    out << "[ " << key << ":" << val << " ] ";
}

template <class Out, class Iterable>
void printIter(Out& out, Iterable& iterable)
{
    typename Iterable::const_iterator it = iterable.begin();
    typename Iterable::const_iterator ite = iterable.end();
    for (; it != ite; ++it)
        out << *it << ' ';
}

template <class Out, class Iterator>
void printIter(Out& out, Iterator it, Iterator ite)
{
    for (; it != ite; ++it)
        out << *it << ' ';
}

template <int start, int end>
bool inRange(const int& val)
{
    return (start <= val && val <= end);
}

template <class Tp>
bool isSame(const Tp& v1, const Tp& v2)
{
    return v1 == v2;
}

template <class Container>
Container getRandomRange(int size)
{
    srand(time(0));
    Container v;
    for (int i = 0; i < size; i++)
        v.push_back(rand() % 1000);
    return v;
}

#endif // UTIL_HPP
