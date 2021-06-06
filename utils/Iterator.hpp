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
    typedef Distance  differnce_type;
    typedef Pointer   pointer;
    typedef Reference reference;
    typedef Category  iterator_category;
};
}

#endif // ITERATOR_HPP
