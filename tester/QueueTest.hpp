#ifndef QUEUETEST_HPP
#define QUEUETEST_HPP

#include <sstream>
#include "Util.hpp"

#define QUEUE_TEST(FNC) ct.run("queue::" #FNC, "STD", "FT ", \
                               queue_test::FNC<STD>, queue_test::FNC<FT>)

namespace queue_test
{

template <class queue>
static void info(std::stringstream& out, const queue& q)
{
    keyval(out, "size", q.size());
    keyval(out, "front", q.front());
    keyval(out, "back", q.back());
}

template <class queue>
void constructor(std::stringstream& out)
{
    queue q;
    keyval(out, "size", q.size());

    q.push(42);
    info(out, q);
}

template <class queue>
void copyConstructor(std::stringstream& out)
{
    queue q;
    q.push(42);

    queue q2(q);
    info(out, q2);
}

template <class queue>
void assignation(std::stringstream& out)
{
    queue q;
    q.push(42);

    queue q2;
    q2 = q;
    info(out, q2);
}

template <class queue>
void capacity(std::stringstream& out)
{
    queue q;
    out << q.empty();
    out << q.size();

    q.push(42);
    info(out, q);

    const queue cq = q;
    info(out, cq);
}

template <class queue>
void push_pop(std::stringstream& out)
{
    queue q;
    q.push(1);
    q.push(2);
    info(out , q);

    q.pop();
    q.pop();
    keyval(out, "size", q.size());
}

template <class queue>
static void printRelation(std::stringstream& out, const queue& a, const queue& b)
{
    if (a == b) out << "(a == b)";
    if (a != b) out << "(a != b)";
    if (a <= b) out << "(a <= b)";
    if (a >= b) out << "(a >= b)";
    if (a < b) out << "(a < b)";
    if (a > b) out << "(a > b)";
}

template <class queue>
void relationOperation(std::stringstream& out)
{
    typedef typename queue::container_type container;

    printRelation(out, queue(container()), queue(container()));
    printRelation(out, queue(container(3)), queue(container(4)));
    printRelation(out, queue(container(4)), queue(container(3)));
    printRelation(out, queue(container(range, range + 2)), queue(container(range + 2, range + 4)));
}

}

#endif // QUEUETEST_HPP
