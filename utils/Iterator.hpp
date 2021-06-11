#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iterator>
#include <cstddef>
#include "list.hpp"

namespace ft
{
struct input_iterator_tag                                             {};
struct output_iterator_tag                                            {};
struct forward_iterator_tag       : public input_iterator_tag         {};
struct bidirectional_iterator_tag : public forward_iterator_tag       {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template <class Category, class Tp, class Distance = std::ptrdiff_t,
          class Pointer = Tp*, class Reference = Tp&>
struct iterator
{
    typedef Tp        value_type;
    typedef Distance  difference_type;
    typedef Pointer   pointer;
    typedef Reference reference;
    typedef Category  iterator_category;
};

template <class Iterator>
class reverse_iterator;

// Non-member function overloads
template <class Iterator>
bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
    return lhs.pos == rhs.pos;
}

template <class Iterator>
bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
    return lhs.pos != rhs.pos;
}

template <class Iterator>
bool operator<  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
    return lhs.pos < rhs.pos;
}

template <class Iterator>
bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
    return lhs.pos <= rhs.pos;
}

template <class Iterator>
bool operator>  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
    return lhs.pos > rhs.pos;
}
template <class Iterator>
bool operator>=  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
    return lhs.pos >= rhs.pos;
}

/* http://www.cplusplus.com/reference/iterator/reverse_iterator/ */
/* real e 1 2 3 4 5 e  */
/* base   1 2 3 4 5 e  */
/* pos  e 5 4 3 2 1    */
template <class Iterator>
class reverse_iterator
{
    Iterator pos;

    public:
        typedef Iterator                             iterator_type;
        typedef typename Iterator::iterator_category iterator_category;
        typedef typename Iterator::value_type        value_type;
        typedef typename Iterator::difference_type   difference_type;
        typedef typename Iterator::pointer           pointer;
        typedef typename Iterator::reference         reference;

        reverse_iterator()
        {
        }

        explicit reverse_iterator (iterator_type it) : pos(--it)
        {
        }

        template <class Iter>
        reverse_iterator (const reverse_iterator<Iter>& rev_it) : pos(rev_it.pos)
        {
        }

        iterator_type base() const
        {
            iterator_type base_(pos);
            return (++base_);
        }

        reference operator*() const
        {
            return *pos;
        }


        reverse_iterator& operator++()
        {
            --pos;
            return *this;
        }

        reverse_iterator  operator++(int)
        {
            reverse_iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        reverse_iterator& operator--()
        {
            ++pos;
            return *this;
        }

        reverse_iterator  operator--(int)
        {
            reverse_iterator tmp = *this;
            --(*this);
            return tmp;
        }

        pointer operator->() const
        {
            return &(operator*());
        }

        reference operator[] (difference_type n) const
        {
            return pos[n];
        }

        reverse_iterator operator+(difference_type n) const
        {
            return (reverse_iterator(base() - n));
        }

        reverse_iterator& operator+=(difference_type n)
        {
            pos -= n;
            return *this;
        }

        reverse_iterator operator-(difference_type n) const
        {
            return (reverse_iterator(base() + n));
        }

        reverse_iterator& operator-= (difference_type n)
        {
            pos += n;
            return *this;
        }

        template <class Iter>
        friend bool operator== (const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs);

        template <class Iter>
        friend bool operator!= (const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs);

        template <class Iter>
        friend bool operator<  (const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs);

        template <class Iter>
        friend bool operator<= (const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs);

        template <class Iter>
        friend bool operator>  (const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs);
        template <class Iter>
        friend bool operator>=  (const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs);
};

}

#endif // ITERATOR_HPP
