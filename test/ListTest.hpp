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
    typename Iterable::iterator it = iterable.begin();
    typename Iterable::iterator ite = iterable.end();
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
void push_back(std::stringstream& out)
{
    list lst(0);

    lst.push_back(42);
    out << lst.front();
}

}
#endif // LISTTESTER_HPP
