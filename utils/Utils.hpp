#ifndef UTILS_HPP
#define UTILS_HPP

namespace ft
{

template <class _Tp> struct remove_const { typedef _Tp type; };
template <class _Tp> struct remove_const<const _Tp> { typedef _Tp type; };

template <bool B, typename T = void>
struct enable_if
{};

template <typename T>
struct enable_if<true, T>
{ typedef T type; };

template <bool B, typename T = void>
struct disable_if
{ typedef T type; };

template <typename T>
struct disable_if<true, T>
{};

template <typename N>
struct is_integral
{ static const bool value = false; };

template <>
struct is_integral<bool>
{ static const bool value = true; };

template <>
struct is_integral<char>
{ static const bool value = true; };

template <>
struct is_integral<signed char>
{ static const bool value = true; };

template <>
struct is_integral<unsigned char>
{ static const bool value = true; };

template <>
struct is_integral<wchar_t>
{ static const bool value = true; };

template <>
struct is_integral<short>
{ static const bool value = true; };

template <>
struct is_integral<unsigned short>
{ static const bool value = true; };

template <>
struct is_integral<int>
{ static const bool value = true; };

template <>
struct is_integral<unsigned int>
{ static const bool value = true; };

template <>
struct is_integral<long>
{ static const bool value = true; };

template <>
struct is_integral<unsigned long>
{ static const bool value = true; };

template <>
struct is_integral<long long>
{ static const bool value = true; };

template <>
struct is_integral<unsigned long long>
{ static const bool value = true; };

template <>
struct is_integral<__int128_t>
{ static const bool value = true; };

template <>
struct is_integral<__uint128_t>
{ static const bool value = true; };

template <class Tp>
void swap(Tp& lhs, Tp& rhs)
{
    Tp tmp = lhs;
    lhs = rhs;
    rhs = tmp;
}

template <class Iter>
typename Iter::difference_type distance(Iter first, Iter last)
{
    typename Iter::difference_type dist = 0;
    for (; first != last; ++first, ++dist) ;
    return dist;
}

template <class Iter>
Iter next(Iter it, typename Iter::difference_type n = 1)
{
    for (typename Iter::difference_type i = 0; i < n; i++)
        ++it;
    return it;
}

template <class InputIterator, class OutputIterator>
OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result)
{
    for (; first != last; ++first, ++result)
        *result = *first;
    return (result - 1);
}

template <class ForwardIterator, class T>
void fill(ForwardIterator first, ForwardIterator last, const T& val)
{
    for (; first != last; ++first)
        *first = val;
}

template <class OutIter, class InIter>
void fill(OutIter res, InIter first, InIter last)
{
    for (; first != last; ++first, ++res)
        *res = *first;
}

template <class Arg1, class Arg2, class Result>
struct binary_function {
    typedef Arg1   first_argument_type;
    typedef Arg2   second_argument_type;
    typedef Result result_type;
};

template <class T> struct less : binary_function <T,T,bool> {
    bool operator() (const T& x, const T& y) const {return x<y;}
};

template <class T1, class T2>
struct pair
{
    typedef T1 first_type;
    typedef T2 second_type;

    first_type  first;
    second_type second;

    pair(const first_type& f, const second_type& s)
        : first(f),
          second(s)
    {
    }
    pair operator()(const first_type& f, const second_type& s)
    {
        return pair(f, s);
    }
};

}

#endif // UTILS_HPP
