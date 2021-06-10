#ifndef LISTTESTER_HPP
#define LISTTESTER_HPP

#include <sstream>

#define LIST_TEST(FNC) ct.run("list::" #FNC, "STD", "FT ", \
                              list_test::FNC<STD>, list_test::FNC<FT>)

namespace list_test
{

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

int compABS(int v1, int v2)
{
    return std::abs(v1) < std::abs(v2);
}

/* constructor */
template <class list>
void constructor0(std::stringstream& out)
{
    list lst;

    keyval(out, "size", lst.size());
    lst.push_back(42);
    keyval(out, "size", lst.size());
    keyval(out, "front", lst.front());
}

template <class list>
void constructor1(std::stringstream& out)
{
    list lst(3);
    keyval(out, "size", lst.size());
    keyval(out, "front", lst.front());
    keyval(out, "back", lst.back());

    list lst2(3, 42);
    keyval(out, "size", lst2.size());
    keyval(out, "front", lst2.front());
    keyval(out, "back", lst2.back());
}

template <class list>
void constructor2(std::stringstream& out)
{
    list lst;
    for (int i = 0; i < 10; i++)
        lst.push_back(i);
    list lst2(lst.begin(), lst.end());
    printIter(out, lst2);

    int arr[] = {42, 24, 0};
    list lst3(arr, arr + 3);
    printIter(out, lst3);
}

template <class list>
void copyConstructor(std::stringstream& out)
{
    list lst;
    for (int i = 0; i < 10; i++)
        lst.push_back(i);

    list lst2(lst);
    printIter(out, lst2);
}

/* destructor will be test in all test case */

template <class list>
void assignation(std::stringstream& out)
{
    list lst(3, 42);
    list lst2(3, 24);
    lst2 = lst;
    printIter(out, lst2);
}

/* iterator */
/* test begin end,  also const */
template <class list>
void begin_end(std::stringstream& out)
{
    list lst;
    printIter(out, lst);

    list lst2(2, 42);
    printIter(out, lst2);

    const list lst3(lst2);
    printIter(out, lst3);
}

/* test rbegin rend,  also const */
template <class list>
void rbegin_rend(std::stringstream& out)
{
    list lst;
    printIter(out, lst.rbegin(), lst.rend());

    list lst2(2, 42);
    printIter(out, lst2.rbegin(), lst2.rend());

    const list lst3(lst2);
    printIter(out, lst3.rbegin(), lst3.rend());
}

/* capacity */
template <class list>
void empty(std::stringstream& out)
{
    list lst;
    out << lst.empty();

    list lst2(0);
    out << lst2.empty();

    lst.push_back(42);
    out << lst.empty();
}

template <class list>
void max_size(std::stringstream &out)
{
    list lst;
    out << CompareTester::DontNeedToSame << "-> ";
    keyval(out, "max_size", lst.max_size());
}

/* modifiers */
template <class list>
void assign0(std::stringstream &out)
{
    list lst(10, 42);
    list lst2;
    lst2.assign(lst.begin(), lst.end());
    printIter(out, lst2);

    int arr[] = {1, 2 ,3};
    lst2.assign(arr, arr + 3);
    printIter(out, lst2);
}

template <class list>
void assign1(std::stringstream &out)
{
    list lst(5);

    lst.assign(10, 42);
    printIter(out, lst);
}

template <class list>
void push_front(std::stringstream& out)
{
    list lst;

    lst.push_front(0);
    lst.push_front(1);
    keyval(out, "size", lst.size());
    printIter(out, lst);
}

template <class list>
void pop_front(std::stringstream& out)
{
    list lst;

    lst.push_front(0);
    lst.push_front(1);
    lst.pop_front();
    keyval(out, "size", lst.size());
    printIter(out, lst);
}

template <class list>
void push_back(std::stringstream& out)
{
    list lst;

    lst.push_back(0);
    lst.push_back(1);
    keyval(out, "size", lst.size());
    printIter(out, lst);
}

template <class list>
void pop_back(std::stringstream& out)
{
    list lst;

    lst.push_front(0);
    lst.push_front(1);
    lst.pop_back();
    keyval(out, "size", lst.size());
    printIter(out, lst);
}

template <class list>
void insert0(std::stringstream& out)
{
    list lst;
    typename list::iterator it = lst.insert(lst.end(), 42);
    printIter(out, lst);

    lst.insert(it, 24);
    printIter(out, lst);

    keyval(out, "size", lst.size());
}

template <class list>
void insert1(std::stringstream& out)
{
    list lst(10, 42);
    typename list::iterator it = lst.begin();
    ++it;
    lst.insert(it, 3, 0);
    printIter(out, lst);
}

template <class list>
void insert2(std::stringstream& out)
{
    list lst(10, 42);
    list lst2;
    lst2.insert(lst2.end(), lst.begin(), lst.end());

    int arr[] = {1, 2, 3};
    lst2.insert(lst2.end(), arr, arr + 3);

    printIter(out, lst2);
}

template <class list>
void erase0(std::stringstream& out)
{
    list lst;
    for (int i = 0; i < 5; i++)
        lst.push_back(i);
    lst.erase(--lst.end());
    typename list::iterator it = lst.erase(lst.begin());
    lst.erase(it);

    keyval(out, "size", lst.size());
    printIter(out, lst);
}

template <class list>
void erase1(std::stringstream& out)
{
    list lst;
    for (int i = 0; i < 5; i++)
        lst.push_back(i);
    typename list::iterator it = lst.erase(lst.begin(), --lst.end());

    keyval(out, "size", lst.size());
    keyval(out, "next", *it);
}

template <class list>
void swap(std::stringstream& out)
{
    list lst(5, 42);
    list lst2(3, -1);

    lst.swap(lst2);
    keyval(out, "size", lst.size());
    printIter(out, lst);
    keyval(out, "size", lst2.size());
    printIter(out, lst2);
}

template <class list>
void resize(std::stringstream& out)
{
    list lst(2);

    lst.resize(4, 1);
    keyval(out, "size", lst.size());
    printIter(out, lst);

    lst.resize(6, 2);
    keyval(out, "size", lst.size());
    printIter(out, lst);

    lst.resize(0);
    keyval(out, "size", lst.size());
    printIter(out, lst);
}

template <class list>
void clear(std::stringstream& out)
{
    list lst;
    lst.clear();
    keyval(out, "size", lst.size());
    printIter(out, lst);

    lst.assign(10, 5);
    lst.clear();
    keyval(out, "size", lst.size());
    printIter(out, lst);
}

/* operations */
template <class list>
void splice0(std::stringstream& out)
{
    list  lst(range    , range + 5 );
    list lst2(range + 5, range + 10);

    lst.splice(lst.begin(), lst2);
    keyval(out, "size", lst.size());
    printIter(out, lst);
    keyval(out, "size", lst2.size());
    printIter(out, lst2);
}

template <class list>
void splice1(std::stringstream& out)
{
    list  lst(range    , range + 5 );
    list lst2(range + 5, range + 10);

    lst.splice(++lst.begin(), lst2, --lst2.end());
    keyval(out, "size", lst.size());
    printIter(out, lst);
    keyval(out, "size", lst2.size());
    printIter(out, lst2);
}

template <class list>
void splice2(std::stringstream& out)
{
    list  lst(range    , range + 5 );
    list lst2(range + 5, range + 10);

    lst.splice(++lst.begin(), lst2, ++lst2.begin(), --lst2.end());
    keyval(out, "size", lst.size());
    printIter(out, lst);
    keyval(out, "size", lst2.size());
    printIter(out, lst2);
}

template <class list>
void remove(std::stringstream& out)
{

    list lst;

    lst.push_back(0);
    lst.push_back(42);
    lst.push_back(1);
    lst.push_back(42);
    lst.push_back(2);
    lst.push_back(42);
    lst.remove(42);
    keyval(out, "size", lst.size());
    printIter(out, lst);
}

template <class list>
void remove_if(std::stringstream& out)
{

    list lst(range, range + 10);

    lst.remove_if(inRange<4, 7>);
    keyval(out, "size", lst.size());
    printIter(out, lst);

    lst.remove_if(inRange<0, 9>);
    keyval(out, "size", lst.size());
    printIter(out, lst);
}

template <class list>
void unique0(std::stringstream& out)
{

    list lst;
    keyval(out, "size", lst.size());
    printIter(out, lst);

    lst.insert(lst.end(), 5, 42);
    lst.insert(lst.begin(), range, range + 5);
    lst.unique();
    keyval(out, "size", lst.size());
    printIter(out, lst);

    lst.clear();
    lst.assign(42, 42);
    lst.unique();
    keyval(out, "size", lst.size());
    printIter(out, lst);
}

template <class list>
void unique1(std::stringstream& out)
{

    list lst;
    keyval(out, "size", lst.size());
    printIter(out, lst);

    lst.insert(lst.end(), 5, 42);
    lst.insert(lst.begin(), range, range + 5);
    lst.unique(isSame<int>);
    keyval(out, "size", lst.size());
    printIter(out, lst);

    lst.clear();
    lst.assign(42, 42);
    lst.unique(isSame<int>);
    keyval(out, "size", lst.size());
    printIter(out, lst);
}

template <class list>
void merge0(std::stringstream& out)
{

    list first, second;

    first.push_back (1);
    first.push_back (2);
    first.push_back (5);

    second.assign(range, range + 10);
    first.merge(second);

    keyval(out, "size", first.size());
    printIter(out, first);
    keyval(out, "size", second.size());
    printIter(out, second);
}


/* double */

bool mycomparison (double first, double second)
{ return ( int(first)<int(second) ); }

template <class list>
void merge1(std::stringstream& out)
{

    list first, second;

    first.push_back(1.4);
    first.push_back(2.2);
    first.push_back(2.9);
    first.push_back(3.1);
    first.push_back(3.7);
    first.push_back(7.1);
    second.push_back(2.1);

    first.merge(second, mycomparison);
    keyval(out, "size", first.size());
    printIter(out, first);
    keyval(out, "size", second.size());
    printIter(out, second);
}

}
#endif // LISTTESTER_HPP
