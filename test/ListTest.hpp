#ifndef LISTTESTER_HPP
#define LISTTESTER_HPP

#include <sstream>

#define LIST_TEST(FNC) ct.run("list::" #FNC, "STD", "FT ", \
                              list_test::FNC<STD>, list_test::FNC<FT>)

namespace list_test
{

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

template <class list>
void push_back(std::stringstream& out)
{
    list lst(0);

    lst.push_back(42);
    out << lst.front();
}

}
#endif // LISTTESTER_HPP
