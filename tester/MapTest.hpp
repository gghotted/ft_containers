#ifndef MAPTEST_HPP
#define MAPTEST_HPP

#include <sstream>
#include <vector>
#include "Util.hpp"
#include "CompareTester.hpp"
#include "IteratorRelationTest.hpp"

#define MAP_TEST(FNC) ct.run("map::" #FNC, "STD", "FT ", \
                             map_test::FNC<STD>, map_test::FNC<FT>)

namespace map_test
{

template <class Iter>
Iter next(Iter it, typename Iter::difference_type n = 1)
{
    for (typename Iter::difference_type i = 0; i < n; i++)
        ++it;
    return it;
}

template <class pair>
void printPair(std::stringstream& out, const pair& pair_)
{
    out << "[" << pair_.first << ":" << pair_.second << "] ";
}

template <class iterator>
void printIterMap(std::stringstream& out, iterator it, iterator ite)
{
    for (; it != ite; ++it)
        printPair(out, *it);
}

template <class map>
void info(std::stringstream& out, const map& m)
{
    keyval(out, "size", m.size());
    printIterMap(out, m.begin(), m.end());
}

/* constructor */
template <class map>
void constructor0(std::stringstream& out)
{
    typedef typename map::value_type make_pair;

    map m;
    m.insert(make_pair(1, 1));
    m.insert(make_pair(2, 2));
    m.insert(make_pair(3, 3));
    info(out, m);
}

template <class map>
void constructor1(std::stringstream& out)
{
    typedef typename map::value_type make_pair;

    map m;
    m.insert(make_pair(1, 1));
    m.insert(make_pair(2, 2));
    m.insert(make_pair(3, 3));

    map m2(m.begin(), m.end());
    info(out, m2);
}

template <class map>
void copyConstructor(std::stringstream& out)
{
    typedef typename map::value_type make_pair;

    map m;
    m.insert(make_pair(1, 1));
    m.insert(make_pair(2, 2));
    m.insert(make_pair(3, 3));

    map m2(m);
    info(out, m2);
}

template <class map>
void assignation(std::stringstream& out)
{
    typedef typename map::value_type make_pair;

    map m;
    m.insert(make_pair(1, 1));
    m.insert(make_pair(2, 2));
    m.insert(make_pair(3, 3));

    map m2;
    m.insert(make_pair(3, 3));
    m.insert(make_pair(1, 1));
    m.insert(make_pair(2, 2));
    m2 = m;
    info(out, m2);
}

/* iterator */
template <class map>
void begin_end(std::stringstream& out)
{
    typedef typename map::value_type make_pair;

    map m;
    m.insert(make_pair(3, 3));
    m.insert(make_pair(2, 2));
    m.insert(make_pair(1, 1));
    m.insert(make_pair(4, 4));
    m.insert(make_pair(5, 5));
    info(out, m);

    const map cm(m);
    info(out, cm);
}

template <class map>
void rbegin_rend(std::stringstream& out)
{
    typedef typename map::value_type make_pair;

    map m;
    m.insert(make_pair(3, 3));
    m.insert(make_pair(2, 2));
    m.insert(make_pair(1, 1));
    m.insert(make_pair(4, 4));
    m.insert(make_pair(5, 5));
    printIterMap(out, m.rbegin(), m.rend());

    const map cm(m);
    printIterMap(out, cm.rbegin(), cm.rend());
}

/* capacity */
template <class map>
void empty(std::stringstream& out)
{
    typedef typename map::value_type make_pair;

    map m;
    keyval(out, "empty", m.empty());
    m.insert(make_pair(3, 3));
    m.insert(make_pair(2, 2));
    m.insert(make_pair(1, 1));
    m.insert(make_pair(4, 4));
    m.insert(make_pair(5, 5));
    keyval(out, "empty", m.empty());
}

template <class map>
void size(std::stringstream &out)
{
    typedef typename map::value_type make_pair;

    map m;
    keyval(out, "size", m.size());

    m.insert(make_pair(1, 1));
    keyval(out, "size", m.size());

    m.clear();
    keyval(out, "size", m.size());
}

template <class map>
void max_size(std::stringstream &out)
{
    map m;
    out << CompareTester::DontNeedToSame << "-> ";
    keyval(out, "max_size", m.max_size());
}

/* element access */
template <class map>
void accessOperator(std::stringstream &out)
{
    typedef typename map::value_type make_pair;

    map m;
    m.insert(make_pair(3, 3));
    m.insert(make_pair(2, 2));
    m.insert(make_pair(1, 1));
    m.insert(make_pair(4, 4));
    m.insert(make_pair(5, 5));
    for (int i = 6; i <= 10; i++)
        m[i] = i;
    for (int i = 1; i <= 10; i++)
        out << m[i] << " ";
}

/* modifiers */
template <class map>
void insert0(std::stringstream &out)
{
    typedef typename map::value_type make_pair;

    map m;
    for (size_t i = 0; i < 10; i++)
        m.insert(make_pair(range[i], range[i]));
    info(out, m);
}

template <class map>
void insert1(std::stringstream &out)
{
    typedef typename map::value_type make_pair;

    map m;
    m.insert(m.end(), make_pair(1, 1));
    typename map::iterator it = m.insert(m.end(), make_pair(2, 2));
    info(out, m);
    printPair(out, *it);
}

template <class map>
void insert2(std::stringstream &out)
{
    typedef typename map::value_type make_pair;

    map m;
    for (size_t i = 0; i < 10; i++)
        m.insert(make_pair(range[i], range[i]));

    map m2;
    m2.insert(m.begin(), m.end());
    info(out, m2);
}

/*
1
 2
  3
   4
    5
*/
template <class map>
void erase0(std::stringstream& out)
{
    typedef typename map::value_type make_pair;

    map m;
    m.insert(make_pair(1, 1));
    m.insert(make_pair(2, 2));
    m.insert(make_pair(3, 3));
    m.insert(make_pair(4, 4));
    m.insert(make_pair(5, 5));

    m.erase(m.begin());
    m.erase(++m.begin());
    m.erase(--m.end());
    info(out, m);
}

/*
  3
 2 4
1   5
*/
template <class map>
void erase0_0(std::stringstream& out)
{
    typedef typename map::value_type make_pair;

    map m;
    m.insert(make_pair(3, 3));
    m.insert(make_pair(2, 2));
    m.insert(make_pair(1, 1));
    m.insert(make_pair(4, 4));
    m.insert(make_pair(5, 5));

    m.erase(m.begin());
    m.erase(++m.begin());
    m.erase(--m.end());
    info(out, m);
}

template <class map>
void erase1(std::stringstream& out)
{
    typedef typename map::value_type make_pair;

    map m;
    m.insert(make_pair(3, 3));
    m.insert(make_pair(2, 2));
    m.insert(make_pair(1, 1));
    m.insert(make_pair(4, 4));
    m.insert(make_pair(5, 5));

    keyval(out, "erased", m.erase(1));
    m.erase(3);
    m.erase(5);
    keyval(out, "erased", m.erase(6));
    info(out, m);
}

template <class map>
void erase2(std::stringstream& out)
{
    typedef typename map::value_type make_pair;

    map m;
    m.insert(make_pair(3, 3));
    m.insert(make_pair(2, 2));
    m.insert(make_pair(1, 1));
    m.insert(make_pair(4, 4));
    m.insert(make_pair(5, 5));

    m.erase(++m.begin(), m.end());
    info(out, m);
}

template <class map>
void swap(std::stringstream& out)
{
    typedef typename map::value_type make_pair;

    map m;
    m.insert(make_pair(3, 3));
    m.insert(make_pair(2, 2));
    m.insert(make_pair(1, 1));
    m.insert(make_pair(4, 4));
    m.insert(make_pair(5, 5));

    map m2;
    m2.insert(make_pair(6, 6));
    m2.insert(make_pair(7, 7));

    m.swap(m2);
    info(out, m);
    info(out, m2);
}

template <class map>
void clear(std::stringstream& out)
{
    typedef typename map::value_type make_pair;

    map m;
    m.clear();
    info(out, m);

    m.insert(make_pair(3, 3));
    m.insert(make_pair(2, 2));
    m.insert(make_pair(1, 1));
    m.insert(make_pair(4, 4));
    m.insert(make_pair(5, 5));
    m.clear();
    info(out, m);
}

/* observers */
template <class map>
void key_comp(std::stringstream& out)
{
    map m;

    out << m.key_comp()(1, 2);
    out << m.key_comp()(2, 1);
}

template <class map>
void value_comp(std::stringstream& out)
{
    map m;

    typename map::value_type v1(1, 2);
    typename map::value_type v2(2, 1);
    out << m.value_comp()(v1, v2);
    out << m.value_comp()(v2, v1);
}

/* operations */
template <class map>
void find(std::stringstream& out)
{
    typedef typename map::value_type make_pair;

    map m;
    m.insert(make_pair(3, 3));
    m.insert(make_pair(2, 2));
    m.insert(make_pair(1, 1));
    m.insert(make_pair(5, 5));
    m.insert(make_pair(4, 4));
    for (int i = 1; i <= 5; i++)
        printPair(out, *m.find(i));
    keyval(out, "is_end", m.find(6) == m.end());

    const map cm(m);
    for (int i = 1; i <= 5; i++)
        printPair(out, *cm.find(i));
    keyval(out, "is_end", cm.find(6) == cm.end());
}

template <class map>
void count(std::stringstream& out)
{
    map m;

    m[1];
    out << m.count(1) << m.count(2);
}

template <class map>
void lower_bound(std::stringstream& out)
{
    typedef typename map::value_type make_pair;

    map m;
    m.insert(make_pair(50, 50));
    m.insert(make_pair(20, 20));
    m.insert(make_pair(10, 10));
    m.insert(make_pair(30, 30));
    m.insert(make_pair(80, 80));
    m.insert(make_pair(70, 70));
    m.insert(make_pair(90, 90));
    m.insert(make_pair(75, 75));
    m.insert(make_pair(29, 29));

    const int test[] = {40, 25, 100, 70, 74, 0, 10, 29, 35, 78, 51};
    for (int i = 0; i < 11; i++)
    {
        typename map::iterator it = m.lower_bound(test[i]);
        if (it != m.end())
            out << "[" << test[i] << " " << it->first << ":"<< it->second << "] ";
    }

    const map cm(m);
    for (int i = 0; i < 11; i++)
    {
        typename map::const_iterator it = cm.lower_bound(test[i]);
        if (it != cm.end())
            out << "[" << test[i] << " " << it->first << ":"<< it->second << "] ";
    }
}

template <class map>
void upper_bound(std::stringstream& out)
{
    typedef typename map::value_type make_pair;

    map m;
    m.insert(make_pair(50, 50));
    m.insert(make_pair(20, 20));
    m.insert(make_pair(10, 10));
    m.insert(make_pair(30, 30));
    m.insert(make_pair(80, 80));
    m.insert(make_pair(70, 70));
    m.insert(make_pair(90, 90));
    m.insert(make_pair(75, 75));
    m.insert(make_pair(29, 29));

    const int test[] = {40, 25, 100, 70, 74, 0, 10, 29, 35, 78, 51};
    for (int i = 0; i < 11; i++)
    {
        typename map::iterator it = m.upper_bound(test[i]);
        if (it != m.end())
            out << "[" << test[i] << " " << it->first << ":"<< it->second << "] ";
    }

    const map cm(m);
    for (int i = 0; i < 11; i++)
    {
        typename map::const_iterator it = cm.lower_bound(test[i]);
        if (it != cm.end())
            out << "[" << test[i] << " " << it->first << ":"<< it->second << "] ";
    }
}

template <class map>
void equal_range(std::stringstream& out)
{
    typedef typename map::value_type make_pair;

    map m;
    m.insert(make_pair(50, 50));
    m.insert(make_pair(20, 20));
    m.insert(make_pair(10, 10));
    m.insert(make_pair(30, 30));
    m.insert(make_pair(80, 80));
    m.insert(make_pair(70, 70));
    m.insert(make_pair(90, 90));
    m.insert(make_pair(75, 75));
    m.insert(make_pair(29, 29));

    const int test[] = {40, 25, 100, 70, 74, 0, 10, 29, 35, 78, 51};
    for (int i = 0; i < 11; i++)
    {
        typename map::iterator lower = m.equal_range(test[i]).first;
        typename map::iterator upper = m.equal_range(test[i]).second;
        if (lower != m.end())
            out << "[" << test[i] << " " << lower->first << "]";
        if (upper != m.end())
            out << "[" << test[i] << " " << upper->first << "]";
    }

    const map cm(m);
    for (int i = 0; i < 11; i++)
    {
        typename map::const_iterator lower = cm.equal_range(test[i]).first;
        typename map::const_iterator upper = cm.equal_range(test[i]).second;
        if (lower != cm.end())
            out << "[" << test[i] << " " << lower->first << "]";
        if (upper != cm.end())
            out << "[" << test[i] << " " << upper->first << "]";
    }
}

/* non member */
template <class map>
void nonMemberSwap(std::stringstream& out)
{
    map a, b;
    a[4] = 4;
    b[2] = 2;

    swap(a, b);
    info(out, a);
    info(out, b);
}

template <class map>
static void printRelation(std::stringstream& out, const map& a, const map& b)
{
    if (a == b) out << "(a == b)";
    if (a != b) out << "(a != b)";
    if (a <= b) out << "(a <= b)";
    if (a >= b) out << "(a >= b)";
    if (a < b) out << "(a < b)";
    if (a > b) out << "(a > b)";
    out << " ";
}

template <class map>
void relationOperation(std::stringstream& out)
{
    map m1, m2, m3, m4;
    m2[4] = 4;
    m2[2] = 3;

    m3[4] = 4;
    m3[2] = 4;

    m4[1] = 1;
    printRelation(out, m1, m1);
    printRelation(out, m2, m3);
    printRelation(out, m3, m2);
    printRelation(out, m3, m2);
    printRelation(out, m4, m3);
}

template <class Iter>
static void printIteratorRelation(std::stringstream& out, const Iter& a, const Iter& b)
{
    if (a == b) out << "(a == b)";
    if (a != b) out << "(a != b)";
}

template <class map>
void iteratorRelationOperation(std::stringstream& out)
{
    map m;
    printIteratorRelation(out, m.begin(), m.end());
    printIteratorRelation(out, m.rbegin(), m.rend());

    m[1] = 1;
    printIteratorRelation(out, m.begin(), m.end());
    printIteratorRelation(out, m.rbegin(), m.rend());

    /* check compile */
    iter_rel_test::equal_const_nonConst<map>(out);
    iter_rel_test::equal_reverse_constReverse<map>(out);
}

/* random case */
template <class map>
void erase_random_case(std::stringstream& out)
{
    static std::vector<int> rrange = getRandomRange<std::vector<int> >(10);
    map m;
    for (size_t i = 0; i < rrange.size(); i++)
        m[rrange[i]] = rrange[i];

    while (!m.empty())
    {
        typename map::iterator it = map_test::next(m.begin(), (rand() % m.size()));
        m.erase(it);
        info(out, m);
    }
}

template <class map>
void insert_random_case0(std::stringstream& out)
{
    typedef typename map::value_type make_pair;

    static std::vector<int> rrange = getRandomRange<std::vector<int> >(10);
    map m;
    for (size_t i = 0; i < rrange.size(); i++)
    {
        if (i % 2)
            keyval(out, "key", m.insert(make_pair(rrange[i], rrange[i])).first->first);
        else
            keyval(out, "success", m.insert(make_pair(rrange[i], rrange[i])).second);
    }
    info(out, m);
}

template <class map>
void insert_random_case1(std::stringstream& out)
{
    typedef typename map::value_type make_pair;

    static std::vector<int> rrange = getRandomRange<std::vector<int> >(10);
    map m;
    for (size_t i = 0; i < rrange.size(); i++)
    {
        typename map::iterator it;
        if (i % 2)
            it = map_test::next(m.begin(), (rand() % (m.size()+1) ));
        else
            it = m.upper_bound(rrange[i]);
        m.insert(it, make_pair(rrange[i], rrange[i]));
    }
    info(out, m);
}

}

#endif // MAPTEST_HPP
