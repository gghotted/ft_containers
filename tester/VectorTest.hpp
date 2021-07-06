#ifndef VECTORTEST_HPP
#define VECTORTEST_HPP

#include <sstream>
#include <list>
#include "Util.hpp"
#include "IteratorRelationTest.hpp"
#include "CompareTester.hpp"

#define VECTOR_TEST(FNC) ct.run("vector::" #FNC, "STD", "FT ", \
                                vector_test::FNC<STD>, vector_test::FNC<FT>)

namespace vector_test
{

template <class vector>
void info(std::stringstream& out, const vector& v)
{
    keyval(out, "size", v.size());
    keyval(out, "capacity", v.capacity());
    printIter(out, v);
}

/* constructor */
template <class vector>
void constructor0(std::stringstream& out)
{
    vector v;

    info(out, v);

    v.push_back(42);
    info(out, v);
}

template <class vector>
void constructor1(std::stringstream& out)
{
    vector v(2);
    info(out, v);

    vector v2(3, 42);
    info(out, v2);
}

template <class vector>
void constructor2(std::stringstream& out)
{
    vector v(range, range + 10);
    info(out, v);

    std::list<int> rrange = getRandomRange<std::list<int> >(10);
    vector v2(rrange.begin(), rrange.end());
    info(out, v2);
}

template <class vector>
void copyConstructor(std::stringstream& out)
{
    vector v;
    vector v2(range, range + 10);

    info(out, vector(v));
    info(out, vector(v2));
}

/* destructor test in all case */

template <class vector>
void assignation(std::stringstream& out)
{
    vector v(range, range + 5);
    vector v2(nrange, nrange + 10);

    v2 = v;
    info(out, v2);
}

/* test iterator begin, end, also const iterator */
template <class vector>
void begin_end(std::stringstream& out)
{
    vector v(range, range + 5);
    printIter(out, v.begin(), v.end());

    const vector v2(v);
    printIter(out, v2.begin(), v2.end());

    const vector v3;
    printIter(out, v2.begin(), v2.end());
}

/* test reverse iterator rbegin, rend, also const reverse iterator */
template <class vector>
void rbegin_rend(std::stringstream& out)
{
    vector v(range, range + 5);
    printIter(out, v.rbegin(), v.rend());

    const vector v2(v);
    printIter(out, v2.rbegin(), v2.rend());

    const vector v3;
    printIter(out, v2.rbegin(), v2.rend());
}

/* capacity */
template <class vector>
void size_capacity(std::stringstream& out)
{
    vector v;
    info(out, v);
    v.push_back(1);
    info(out, v);
    v.push_back(2);
    info(out, v);
    v.push_back(3);
    info(out, v);

    vector v2(v);
    info(out, v2);
    v2.push_back(4);
    info(out, v2);
}

template <class vector>
void max_size(std::stringstream &out)
{
    vector v;
    out << CompareTester::DontNeedToSame << "-> ";
    keyval(out, "max_size", v.max_size());
}

template <class vector>
void resize(std::stringstream &out)
{
    vector v;

    v.resize(2);
    info(out, v);

    v.resize(4, 42);
    info(out, v);

    v.resize(0);
    info(out, v);
}

template <class vector>
void empty(std::stringstream &out)
{
    vector v;
    out << v.empty();

    v.push_back(42);
    out << v.empty();

    v.reserve(0);
    out << v.empty();

    v.resize(0);
    out << v.empty();

    v.push_back(42);
    v.clear();
    out << v.empty();
}

template <class vector>
void reserve(std::stringstream &out)
{
    vector v;

    v.reserve(0);
    info(out, v);

    v.reserve(2);
    info(out, v);

    v.resize(4, 42);
    v.reserve(1);
    info(out, v);
}

template <class vector>
void reserveExcept(std::stringstream &out)
{
    vector v;

    try
    {
        v.reserve(v.max_size() + 1);
    }
    catch(const std::length_error& e)
    {
        out << CompareTester::DontNeedToSame << "-> ";
        out << e.what();
    }
}

/* element access */
template< class vector>
void accessOperator(std::stringstream &out)
{
    vector v;

    v.push_back(3);
    out << v[0];

    v[0] = 42;
    out << v[0];

    const vector cv(3);
    out << cv[0];
}

template< class vector>
void at(std::stringstream &out)
{
    vector v;

    v.push_back(3);
    out << v.at(0);

    v.at(0) = 42;
    out << v.at(0);

    const vector cv(3);
    out << cv.at(0);
}

template< class vector>
void atExcept(std::stringstream &out)
{
    vector v(1);

    try
    {
        v.at(1);
    }
    catch(const std::out_of_range& e)
    {
        out << CompareTester::DontNeedToSame << "-> ";
        out << e.what();
    }
}

template< class vector>
void front_back(std::stringstream &out)
{
    vector v(1);
    v.front() = 4;
    out << v.front() << v.back();

    v.push_back(2);
    out << v.front() << v.back();

    const vector cv(v);
    out << v.front() << v.back();
}

/* modifiers */

template< class vector>
void assign0(std::stringstream &out)
{
    vector v(3);

    v.assign(2, 1);
    info(out, v);

    v.assign(4, 2);
    info(out, v);

    v.assign(0, 3);
    info(out, v);
}

template< class vector>
void assign1(std::stringstream &out)
{
    vector v(3);

    v.assign(range, range + 2);
    info(out, v);

    v.assign(range, range + 4);
    info(out, v);

    v.assign(range, range);
    info(out, v);

    std::list<int> rrange = getRandomRange<std::list<int> >(10);
    v.assign(rrange.begin(), rrange.end());
}

template< class vector>
void push_back(std::stringstream &out)
{
    vector v;
    for (int i = 0; i < 5; i++)
    {
        v.push_back(i);
        out << v.capacity();
    }
    info(out, v);

    vector v2(3);
    for (int i = 0; i < 5; i++)
    {
        v2.push_back(i);
        out << v2.capacity();
    }
    info(out, v2);
}

template< class vector>
void pop_back(std::stringstream &out)
{

    vector v(range, range + 5);
    info(out, v);

    while (!v.empty())
    {
        v.pop_back();
        info(out, v);
    }
}

template< class vector>
void insert0(std::stringstream &out)
{

    vector v;

    typename vector::iterator it = v.insert(v.end(), 2);
    out << *it;

    it = v.insert(v.begin(), 4);
    out << *it;
    info(out, v);

    v.assign(4, 3);
    v.insert(v.begin(), 1);
    info(out, v);
}

template< class vector>
void insert1(std::stringstream &out)
{

    vector v;

    v.insert(v.end(), 3, 1);
    v.insert(v.end() - 2, 3, 2);
    info(out, v);
}

template< class vector>
void insert2(std::stringstream &out)
{

    vector v;

    v.insert(v.end(), range, range + 5);
    v.insert(v.begin(), range + 5, range + 10);

    std::list<int> rrange = getRandomRange<std::list<int> >(10);
    v.insert(v.begin(), rrange.begin(), rrange.end());

    info(out, v);
}

template< class vector>
void erase0(std::stringstream &out)
{

    vector v(range, range + 5);

    out << *v.erase(v.begin() + 3);
    out << *v.erase(v.begin());
    info(out, v);
}

template< class vector>
void erase1(std::stringstream &out)
{

    vector v(range, range + 5);

    out << *v.erase(v.begin() + 1, v.begin() + 3);
    info(out, v);

    v.erase(v.begin(), v.end());
    info(out, v);
}

template< class vector>
void swap(std::stringstream &out)
{

    vector a;
    vector b(range, range + 2);
    a.swap(b);
    info(out, a);
    info(out, b);

    vector c(range + 2, range + 4);
    vector d(range + 4, range + 6);
    c.push_back(1);
    c.swap(d);
    info(out, c);
    info(out, d);
}

template< class vector>
void clear(std::stringstream &out)
{

    vector v;

    v.clear();
    info(out, v);

    v.assign(5, 42);
    v.clear();
    info(out, v);
}

template <class vector>
void nonMemberSwap(std::stringstream& out)
{
    vector a(range, range + 5);
    vector b(range + 5, range + 10);
    swap(a, b);

    info(out, a);
    info(out, b);
}

template <class vector>
static void printRelation(std::stringstream& out, const vector& a, const vector& b)
{
    if (a == b) out << "(a == b)";
    if (a != b) out << "(a != b)";
    if (a <= b) out << "(a <= b)";
    if (a >= b) out << "(a >= b)";
    if (a < b) out << "(a < b)";
    if (a > b) out << "(a > b)";
}

template <class vector>
void relationOperation(std::stringstream& out)
{
    printRelation(out, vector(), vector());
    printRelation(out, vector(3), vector(4));
    printRelation(out, vector(4), vector(3));
    printRelation(out, vector(range, range + 2), vector(range + 2, range + 4));
}

template <class Iter>
static void printIteratorRelation(std::stringstream& out, const Iter& a, const Iter& b)
{
    if (a == b) out << "(a == b)";
    if (a != b) out << "(a != b)";
    if (a <= b) out << "(a <= b)";
    if (a >= b) out << "(a >= b)";
    if (a < b) out << "(a < b)";
    if (a > b) out << "(a > b)";
}

template <class vector>
void iteratorRelationOperation(std::stringstream& out)
{
    vector v;
    printIteratorRelation(out, v.begin(), v.end());
    printIteratorRelation(out, v.rbegin(), v.rend());

    v.assign(5, 1);
    printIteratorRelation(out, v.begin(), v.end());
    printIteratorRelation(out, v.rbegin(), v.rend());

    printIteratorRelation(out, v.end(), v.begin());
    printIteratorRelation(out, v.rend(), v.rbegin());

    /* check compile */
    iter_rel_test::equal_const_nonConst<vector>(out);
    iter_rel_test::equal_reverse_constReverse<vector>(out);
    iter_rel_test::sizeCompaire_const_nonConst<vector>(out);
    iter_rel_test::sizeCompaire_reverse_constReverse<vector>(out);
    iter_rel_test::sub_const_nonConst_reverse_constReverse<vector>(out);
}

}

#endif // VECTORTEST_HPP
