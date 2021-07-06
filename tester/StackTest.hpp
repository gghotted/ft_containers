#ifndef STACKTEST_HPP
#define STACKTEST_HPP

#include <sstream>
#include "Util.hpp"

#define STACK_TEST(FNC) ct.run("stack::" #FNC, "STD", "FT ", \
                               stack_test::FNC<STD>, stack_test::FNC<FT>)

namespace stack_test
{

template <class stack>
static void info(std::stringstream& out, const stack& s)
{
    keyval(out, "size", s.size());
    keyval(out, "top", s.top());
}

/* constructor */
template <class stack>
void constructor(std::stringstream& out)
{
    stack s;
    keyval(out, "size", s.size());

    s.push(42);
    info(out, s);
}

template <class stack>
void copyConstructor(std::stringstream& out)
{
    stack s;
    s.push(42);

    stack s2(s);
    info(out, s2);
}

template <class stack>
void assignation(std::stringstream& out)
{
    stack s;
    s.push(42);

    stack s2;
    s2 = s;
    info(out, s2);
}

template <class stack>
void capacity(std::stringstream& out)
{
    stack s;
    out << s.empty();
    out << s.size();

    s.push(42);
    out << s.empty();
    out << s.size();
    out << s.top();

    const stack cs = s;
    out << s.empty();
    out << s.size();
    out << s.top();
}

template <class stack>
void push_pop(std::stringstream& out)
{
    stack s;
    s.push(1);
    s.push(2);
    out << s.size();
    out << s.top();

    s.pop();
    s.pop();
    out << s.size();
}

template <class stack>
static void printRelation(std::stringstream& out, const stack& a, const stack& b)
{
    if (a == b) out << "(a == b)";
    if (a != b) out << "(a != b)";
    if (a <= b) out << "(a <= b)";
    if (a >= b) out << "(a >= b)";
    if (a < b) out << "(a < b)";
    if (a > b) out << "(a > b)";
}

template <class stack>
void relationOperation(std::stringstream& out)
{
    typedef typename stack::container_type container;

    printRelation(out, stack(container()), stack(container()));
    printRelation(out, stack(container(3)), stack(container(4)));
    printRelation(out, stack(container(4)), stack(container(3)));
    printRelation(out, stack(container(range, range + 2)), stack(container(range + 2, range + 4)));
}

}

#endif // STACKTEST_HPP
