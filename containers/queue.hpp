#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "list.hpp"

namespace ft
{

template <class T, class Container = list<T> >
class queue;

template <class T, class Container>
bool operator== (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
{
    return lhs.c == rhs.c;
}

template <class T, class Container>
bool operator!= (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
{
    return lhs.c != rhs.c;
}

template <class T, class Container>
bool operator<  (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
{
    return lhs.c < rhs.c;
}

template <class T, class Container>
bool operator<= (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
{
    return lhs.c <= rhs.c;
}

template <class T, class Container>
bool operator>  (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
{
    return lhs.c > rhs.c;
}

template <class T, class Container>
bool operator>= (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
{
    return lhs.c >= rhs.c;
}

template <class T, class Container>
class queue
{
    template <class T_, class Container_>
    friend bool operator== (const queue<T_,Container_>& lhs, const queue<T_,Container_>& rhs);

    template <class T_, class Container_>
    friend bool operator!= (const queue<T_,Container_>& lhs, const queue<T_,Container_>& rhs);

    template <class T_, class Container_>
    friend bool operator<  (const queue<T_,Container_>& lhs, const queue<T_,Container_>& rhs);

    template <class T_, class Container_>
    friend bool operator<= (const queue<T_,Container_>& lhs, const queue<T_,Container_>& rhs);

    template <class T_, class Container_>
    friend bool operator>  (const queue<T_,Container_>& lhs, const queue<T_,Container_>& rhs);

    template <class T_, class Container_>
    friend bool operator>= (const queue<T_,Container_>& lhs, const queue<T_,Container_>& rhs);

    public:
        typedef T         value_type;
        typedef Container container_type;
        typedef size_t    size_type;

        explicit queue(const container_type& c = container_type())
            : c(c)
        {
        }

        queue(const queue& s)
            : c(s.c)
        {
        }

        ~queue()
        {
        }

        queue& operator=(const queue& q)
        {
            c = q.c;
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

        value_type& front()
        {
            return c.front();
        }

        const value_type& front() const
        {
            return c.front();
        }

        value_type& back()
        {
            return c.back();
        }

        const value_type& back() const
        {
            return c.back();
        }

        void push (const value_type& val)
        {
            c.push_back(val);
        }

        void pop()
        {
            c.pop_front();
        }

    private:
        container_type c;
};

}

#endif // QUEUE_HPP
