#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iterator>
#include <cstddef>
#include "list.hpp"

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

template <class BidirectionIterableObject, bool reverse = false>
class BidirectionIterator
{
    public:
        typedef typename BidirectionIterableObject::value_type value_type;
        typedef std::ptrdiff_t                                 differnce_type;
        typedef value_type*                                    pointer;
        typedef value_type&                                    reference;
        typedef std::bidirectional_iterator_tag                iterator_category;

    private:
        typedef typename BidirectionIterableObject::create_by_type create_by_type;

        BidirectionIterableObject iteratorObj;
        template<class, class> friend class list;

    public:
        BidirectionIterator()
        {
        }
        BidirectionIterator(create_by_type tp)
            : iteratorObj(tp)
        {
        }
        BidirectionIterator(const BidirectionIterator& bi)
            : iteratorObj(bi.iteratorObj)
        {
        }
        virtual ~BidirectionIterator()
        {
        }
        BidirectionIterator& operator=(const BidirectionIterator& bi)
        {
            iteratorObj = bi.iteratorObj;
        }

        bool operator==(const BidirectionIterator& rhs) const
        {
            return (iteratorObj.id() == rhs.iteratorObj.id());
        }
        bool operator!=(const BidirectionIterator& rhs) const
        {
            return (iteratorObj.id() != rhs.iteratorObj.id());
        }
        value_type& operator*()
        {
            return *iteratorObj;
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
            if (reverse) iteratorObj.decrease();
            else         iteratorObj.increase();
            return *this;
        }
        BidirectionIterator& operator--()
        {
            if (reverse) iteratorObj.increase();
            else         iteratorObj.decrease();
            return *this;
        }
};

template <class ValueTp, class CreateByTp = ValueTp>
class BidirectionIterableObject
{
    public:
        virtual ~BidirectionIterableObject() {};

        virtual ValueTp&    operator*() = 0;
        virtual const void* id() const = 0;
        virtual void        increase() = 0;
        virtual void        decrease() = 0;
};
}

#endif // ITERATOR_HPP
