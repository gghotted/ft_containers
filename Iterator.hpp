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

template <class NodeTp, class Distance = std::ptrdiff_t,
          class Pointer = NodeTp*, class Reference = NodeTp&>
class BidirectionIterator : public iterator<std::bidirectional_iterator_tag, NodeTp, Distance, Pointer, Reference>
{
    private:
        // typedef BidirectionIterator<std::bidirectional_iterator_tag, NodeTp, Distance, Pointer, Reference> biIterator;
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
        typename NodeTp::content_type& operator*()
        {
            return **p;
        }
        BidirectionIterator operator++(int)
        {
            BidirectionIterator tmp(*this);
            operator++();
            return tmp;
        }
        BidirectionIterator operator--(int)
        {
            BidirectionIterator tmp(*this);
            operator--();
            return tmp;
        }
        BidirectionIterator& operator++()
        {
            p = p->getNext();
            return *this;
        }
        BidirectionIterator& operator--()
        {
            p = p->getPrev();
            return *this;
        }
};

template <class NodeTp, class ContentTp>
class BidirectionIterable
{
    public:
        typedef ContentTp content_type;

        virtual NodeTp*    getNext() = 0;
        virtual NodeTp*    getPrev() = 0;
        virtual ContentTp& operator*() = 0;
};
}

#endif // ITERATOR_HPP
