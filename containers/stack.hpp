#ifndef STACK_HPP
#define STACK_HPP

#include "list.hpp"

namespace ft
{

template <class T, class Container = list<T> >
class stack;

template <class T, class Container>
bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
{
    return lhs.c == rhs.c;
}

template <class T, class Container>
bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
{
    return lhs.c != rhs.c;
}

template <class T, class Container>
bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
{
    return lhs.c < rhs.c;
}

template <class T, class Container>
bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
{
    return lhs.c <= rhs.c;
}

template <class T, class Container>
bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
{
    return lhs.c > rhs.c;
}

template <class T, class Container>
bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
{
    return lhs.c >= rhs.c;
}

template <class T, class Container>
class stack
{
    template <class T_, class Container_>
    friend bool operator== (const stack<T_,Container_>& lhs, const stack<T_,Container_>& rhs);

    template <class T_, class Container_>
    friend bool operator!= (const stack<T_,Container_>& lhs, const stack<T_,Container_>& rhs);

    template <class T_, class Container_>
    friend bool operator<  (const stack<T_,Container_>& lhs, const stack<T_,Container_>& rhs);

    template <class T_, class Container_>
    friend bool operator<= (const stack<T_,Container_>& lhs, const stack<T_,Container_>& rhs);

    template <class T_, class Container_>
    friend bool operator>  (const stack<T_,Container_>& lhs, const stack<T_,Container_>& rhs);

    template <class T_, class Container_>
    friend bool operator>= (const stack<T_,Container_>& lhs, const stack<T_,Container_>& rhs);

    public:
        typedef T         value_type;
        typedef Container container_type;
        typedef size_t    size_type;

        explicit stack(const container_type& c = container_type())
            : c(c)
        {
        }

        stack(const stack& s)
            : c(s.c)
        {
        }

        ~stack()
        {
        }

        stack& operator=(const stack& s)
        {
            c = s.c;
            return *this;
        }


        bool empty() const
        {
            return c.empty();
        }

        size_type size() const
        {
            return c.size();
        }

        value_type& top()
        {
            return c.back();
        }

        const value_type& top() const
        {
            return c.back();
        }

        void push (const value_type& val)
        {
            c.push_back(val);
        }

        void pop ()
        {
            c.pop_back();
        }

    private:
        container_type c;
};

}

#endif // STACK_HPP
