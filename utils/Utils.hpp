#ifndef UTILS_HPP
#define UTILS_HPP

namespace ft
{

template <class _Tp> struct remove_const { typedef _Tp type; };
template <class _Tp> struct remove_const<const _Tp> { typedef _Tp type; };

}


#endif // UTILS_HPP
