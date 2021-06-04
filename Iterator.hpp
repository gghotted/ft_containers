#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iterator>
#include <cstddef>

namespace ft
{
template <class Category, class Tp, class Distance = std::ptrdiff_t,
          class Pointer = Tp*, class Reference = Tp&>
struct iterator
{
    typedef Tp        value_type;
    typedef Distance  differnce_type;
    typedef Pointer   pointer;
    typedef Reference reference;
    typedef Category  iterator_category;
};

template <class Tp, class Distance = std::ptrdiff_t,
          class Pointer = Tp*, class Reference = Tp&>
class BidirectionIterator : public iterator<std::bidirectional_iterator_tag, Tp, Distance, Pointer, Reference>
{
    protected:
        // typedef BidirectionIterator<std::bidirectional_iterator_tag, Tp, Distance, Pointer, Reference> biIterator;
        Pointer p;

    public:
        BidirectionIterator()
            : p(NULL)
        {
        }
        BidirectionIterator(Pointer p)
            : p(p)
        {
        }
        BidirectionIterator(const BidirectionIterator& bi)
            : p(bi.p)
        {
        }
        virtual ~BidirectionIterator()
        {
        }
        BidirectionIterator& operator=(const BidirectionIterator& bi)
        {
            p = bi.p;
        }

        bool operator==(const BidirectionIterator& rhs) const
        {
            return (p == rhs.p);
        }
        bool operator!=(const BidirectionIterator& rhs) const
        {
            return (p != rhs.p);
        }
        Reference operator*()
        {
            return **p;
        }
        BidirectionIterator operator++(int)
        {
            biIterator tmp(*this);
            operator++();
            return tmp;
        }
        BidirectionIterator operator--(int)
        {
            biIterator tmp(*this);
            operator--();
            return tmp;
        }
        BidirectionIterator& operator++()
        {
            // p = &(*p + 1);
        }
        BidirectionIterator& operator--()
        {
            // p = &(--*p);
        }
};
}

#endif // ITERATOR_HPP
