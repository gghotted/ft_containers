#ifndef ITERATORRELATIONTEST_HPP
#define ITERATORRELATIONTEST_HPP

#include <sstream>

#define ITER_REL(FNC) ct.run("map::" #FNC, "STD", "FT ", \
                             iter_rel_test::FNC<STD>, iter_rel_test::FNC<FT>)

namespace iter_rel_test
{

template <class Container>
void equal_const_nonConst(std::stringstream& out)
{
    Container       c;
    const Container cc;
    out << (c.begin() == cc.begin());
    out << (c.begin() != cc.begin());

    out << (cc.begin() == c.begin());
    out << (cc.begin() != c.begin());
}

template <class Container>
void equal_reverse_constReverse(std::stringstream& out)
{
    Container       c;
    const Container cc;
    out << (c.rbegin() == cc.rbegin());
    out << (c.rbegin() != cc.rbegin());

    out << (cc.rbegin() == c.rbegin());
    out << (cc.rbegin() != c.rbegin());
}

template <class Container>
void sizeCompaire_const_nonConst(std::stringstream& out)
{
    Container       c;
    const Container cc;
    out << (c.begin() < cc.begin());
    out << (c.begin() <= cc.begin());
    out << (c.begin() > cc.begin());
    out << (c.begin() >= cc.begin());

    out << (cc.begin() < c.begin());
    out << (cc.begin() <= c.begin());
    out << (cc.begin() > c.begin());
    out << (cc.begin() >= c.begin());
}

template <class Container>
void sizeCompaire_reverse_constReverse(std::stringstream& out)
{
    Container       c;
    const Container cc;
    out << (c.rbegin() < cc.rbegin());
    out << (c.rbegin() <= cc.rbegin());
    out << (c.rbegin() > cc.rbegin());
    out << (c.rbegin() >= cc.rbegin());

    out << (cc.rbegin() < c.rbegin());
    out << (cc.rbegin() <= c.rbegin());
    out << (cc.rbegin() > c.rbegin());
    out << (cc.rbegin() >= c.rbegin());
}

template <class Container>
void sub_const_nonConst_reverse_constReverse(std::stringstream& out)
{
    Container       c;
    const Container cc;

    out << (c.begin() - c.begin());
    out << (cc.begin() - cc.begin());

    out << (c.begin() - cc.begin());
    out << (cc.begin() - c.begin());

    out << (c.rbegin() - cc.rbegin());
    out << (cc.rbegin() - c.rbegin());
}

}

#endif // ITERATORRELATIONTEST_HPP
