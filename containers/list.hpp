#ifndef LIST_HPP
#define LIST_HPP

#include <memory>
#include <limits>
// #include <list>
// #include <iterator>
#include "DoublyLinkedNode.hpp"
#include "Iterator.hpp"
#include "Utils.hpp"

namespace ft
{
template <typename Tp, class Alloc = std::allocator<Tp> >
class   list
{
    public:
        typedef DoublyLinkedNode<Tp> node;

        template <typename Tp_>
        class ListIterator : public iterator<bidirectional_iterator_tag, Tp_>
        {
            public:
                typedef iterator<bidirectional_iterator_tag, Tp_> base;
                typedef typename base::iterator_category          iterator_category;
                typedef typename base::value_type                 value_type;
                typedef typename base::difference_type            difference_type;
                typedef typename base::pointer                    pointer;
                typedef typename base::reference                  reference;

            private:
                template<class, class> friend class list;

                typedef typename remove_const<Tp_>::type non_const_Tp;
                typedef ListIterator<non_const_Tp>       non_const_iterator;

                node* node_;

            public:
                ListIterator()                              : node_(NULL)     {}
                ListIterator(node* node_)                   : node_(node_)    {}
                ListIterator(const non_const_iterator& li)  : node_(li.node_) {}
                virtual ~ListIterator()                                       {}

                ListIterator& operator=(const ListIterator& li)
                {
                    node_ = li.node_;
                    return *this;
                }

                ListIterator& operator++()
                {
                    node_ = node_->getNext();
                    return *this;
                }

                ListIterator& operator--()
                {
                    node_ = node_->getPrev();
                    return *this;
                }

                ListIterator operator++(int)
                {
                    ListIterator tmp(*this);
                    ++(*this);
                    return tmp;
                }

                ListIterator operator--(int)
                {
                    ListIterator tmp(*this);
                    --(*this);
                    return tmp;
                }

                reference operator*() const
                {
                    return **node_;
                }

                pointer operator->() const
                {
                    return &(operator*());
                }

                bool operator==(const ListIterator& rhs) const // ?
                {
                    return (node_ == rhs.node_);
                }

                bool operator!=(const ListIterator& rhs) const // ?
                {
                    return (node_ != rhs.node_);
                }
        };

    public:
        /* member type */
        typedef Tp                                       value_type;
        typedef Alloc                                    allocator_type;
        typedef typename allocator_type::reference       reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer         pointer;
        typedef typename allocator_type::const_pointer   const_pointer;
        typedef ListIterator<Tp>                         iterator;
        typedef ListIterator<const Tp>                   const_iterator;
        typedef ft::reverse_iterator<iterator>           reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>     const_reverse_iterator;
        typedef ptrdiff_t                                difference_type;
        typedef size_t                                   size_type;

        /* constructor */
        explicit list(const allocator_type& alloc_ = allocator_type())
            : allocator_(alloc_),
              size_(0)
        {
            initDefaultNode();
        }

        explicit list(
            size_type n_,
            const value_type& val_ = value_type(),
            const allocator_type& alloc_ = allocator_type())
            : allocator_(alloc_),
              size_(0)
        {
            initDefaultNode();
            for (size_type i = 0; i < n_; i++)
                push_back(val_);
        }

        template <class InputIterator>
        list(
            InputIterator first, InputIterator last,
            const allocator_type& alloc_ = allocator_type(),
            typename disable_if<is_integral<InputIterator>::value>::type* = 0)
            : allocator_(alloc_),
              size_(0)
        {
            initDefaultNode();
            for (; first != last; ++first)
                push_back(*first);
        }

        list (const list& x)
            : size_(0)
        {
            initDefaultNode();
            *this = x;
        }

        /* destructor */
        ~list()
        {
            clear();
            delete beginOfNode_;
            delete endOfNode_;
        }

        /* operator */
        list& operator=(const list& x)
        {
            allocator_ = x.allocator_;
            clear();
            const_iterator it = x.begin();
            const_iterator ite = x.end();
            for (; it != ite; it++)
                push_back(*it);
            return *this;
        }

        /* iterator */
        iterator begin()
        {
            if (size_ == 0)
                return end();
            return iterator(beginOfNode_->getNext());
        }

        const_iterator begin() const
        {
            if (size_ == 0)
                return end();
            return const_iterator(beginOfNode_->getNext());
        }

        iterator end()
        {
            return iterator(endOfNode_);
        }

        const_iterator end() const
        {
            return const_iterator(endOfNode_);
        }

        reverse_iterator rbegin()
        {
            if (size_ == 0)
                return rend();
            return reverse_iterator(endOfNode_);
        }

        const_reverse_iterator rbegin() const
        {
            if (size_ == 0)
                return rend();
            return const_reverse_iterator(endOfNode_);
        }

        reverse_iterator rend()
        {
            return reverse_iterator(beginOfNode_->getNext());
        }

        const_reverse_iterator rend() const
        {
            return const_reverse_iterator(beginOfNode_->getNext());
        }

        /* capacity */
        bool empty() const
        {
            return size_ == 0;
        }

        size_type size() const
        {
            return size_;
        }
        size_type max_size () const
        {
            return std::numeric_limits<difference_type>::max(); // ??
        }

        /* element access */
        reference       front()
        {
            return **(beginOfNode_->getNext());
        }
        const_reference front() const
        {
            return **(beginOfNode_->getNext());
        }
        reference       back()
        {
            return **(endOfNode_->getPrev());
        }
        const_reference back() const
        {
            return **(endOfNode_->getPrev());
        }


        /* modifiers */
        template <class InputIterator>
        void assign (InputIterator first, InputIterator last,
                     typename disable_if<is_integral<InputIterator>::value>::type* = 0)
        {
            clear();
            for (; first != last; ++first)
                push_back(*first);
        }

        void assign (size_type n, const value_type& val)
        {
            clear();
            for (size_type i = 0; i < n; i++)
                push_back(val);
        }

        void push_front (const value_type & val_)
        {
            beginOfNode_->insertNext(new node(val_));
            size_++;
        }

        void pop_front()
        {
            node* begin_ = beginOfNode_->getNext();
            beginOfNode_->linkNext(begin_->getNext());
            delete begin_;
            size_--;
        }

        void push_back(const value_type& val_)
        {
            endOfNode_->insertPrev(new node(val_));
            size_++;
        }

        void pop_back()
        {
            node* end_ = endOfNode_->getPrev();
            endOfNode_->linkPrev(end_->getPrev());
            delete end_;
            size_--;
        }

        iterator insert(iterator position, const value_type& val_)
        {
            position.node_->insertPrev(new node(val_));
            size_++;
            return iterator(position.node_->getPrev());
        }
        void insert(iterator position, size_type n, const value_type& val_)
        {
            for (size_type i = 0; i < n; i++)
                insert(position, val_);
        }

        template <class InputIterator>
        void insert(iterator position, InputIterator first, InputIterator last,
                    typename disable_if<is_integral<InputIterator>::value>::type* = 0)
        {
            for (; first != last; first++)
                insert(position, *first);
        }

        iterator erase(iterator position)
        {
            node* prev = position.node_->getPrev();
            node* next = position.node_->getNext();
            prev->linkNext(next);
            delete position.node_;
            --size_;
            return iterator(next);
        }

        iterator erase(iterator first, iterator last)
        {
            while (first != last)
                first = erase(first);
            return last;
        }

        void swap(list& x)
        {
            ft::swap(beginOfNode_, x.beginOfNode_);
            ft::swap(endOfNode_, x.endOfNode_);
            ft::swap(size_, x.size_);
        }

        void resize(size_type n, value_type val = value_type())
        {
            if (size_ < n)
                while (size_ != n)
                    push_back(val);
            else
                while (size_ != n)
                    pop_back();
        }

        void clear()
        {
            while (size_)
                pop_back();
        }

        /* operations */
        void splice(iterator position, list& x)
        {
            splice(position, x, x.begin(), x.end());
        }

        void splice(iterator position, list& x, iterator i)
        {
            splice(position, x, i, next(i));
        }

        void splice(iterator position, list& x, iterator first, iterator last)
        {
            difference_type dist = distance(first, last);
            position.node_->getPrev()->swapNextLink(first.node_->getPrev());
            position.node_->swapPrevLink(last.node_);
            x.size_ -= dist;
            size_ += dist;
        }

        void remove(const value_type& val)
        {
            iterator begin_ = begin();
            while (begin_ != end())
            {
                if (*begin_ == val)
                    begin_ = erase(begin_);
                else
                    ++begin_;
            }
        }

        template <class Predicate>
        void remove_if(Predicate pred)
        {
            iterator begin_ = begin();
            while (begin_ != end())
            {
                if (pred(*begin_))
                    begin_ = erase(begin_);
                else
                    ++begin_;
            }
        }

        void unique()
        {
            unique(isSame);
        }

        template <class BinaryPredicate>
        void unique(BinaryPredicate binary_pred)
        {
            if (size_ <= 1)
                return ;

            iterator uniq = begin();
            iterator pos = next(uniq);
            while (pos != end())
            {
                if (binary_pred(*uniq, *pos))
                    pos = erase(pos);
                else
                {
                    ++uniq;
                    ++pos;
                }
            }
        }

        void merge(list& x)
        {
            merge(x, isLess);
        }

        template <class Compare>
        void merge(list& x, Compare comp)
        {
            if (&x == this)
                return ;

            iterator begin_ = begin();
            while (begin_ != end() && x.begin() != x.end())
            {
                if (comp(*x.begin(), *begin_))
                    splice(begin_, x, x.begin());
                else
                    ++begin_;
            }
            if (!x.empty())
                splice(end(), x);
        }

        void sort()
        {
            sort(isLess);
        }

        template <class Compare>
        void sort (Compare comp)
        {
            for (iterator first = begin(); first != end(); ++first)
                for (iterator second = next(first); second != end(); ++second)
                    if (!comp(*first, *second))
                        ft::swap(*first, *second);
        }

        void reverse()
        {
            size_type cnt = size_ / 2;
            iterator first = begin();
            iterator last  = --end();
            for (size_type i = 0; i < cnt; i++, ++first, --last)
                ft::swap(*first, *last);
        }

        allocator_type get_allocator() const
        {
            return allocator_;
        }

    private:
        allocator_type allocator_;
        size_type      size_;
        node*          beginOfNode_;
        node*          endOfNode_;

        void initDefaultNode()
        {
            beginOfNode_ = new node();
            endOfNode_ = new node();
            beginOfNode_->linkNext(endOfNode_);
        }

        static bool isSame(const size_type& v1, const size_type& v2)
        {
            return v1 == v2;
        }

        static bool isLess(const size_type& v1, const size_type& v2)
        {
            return v1 < v2;
        }
};

template <class T, class Alloc>
void swap(list<T,Alloc>& x, list<T,Alloc>& y)
{
    x.swap(y);
}

template <class T, class Alloc>
bool operator==(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
{
    if (lhs.size() != rhs.size())
        return false;

    typename list<T,Alloc>::const_iterator lit = lhs.begin(), rit = rhs.begin();
    while (lit != lhs.end())
    {
        if (*lit != *rit)
            return false;
        ++lit;
        ++rit;
    }
    return true;
}

template <class T, class Alloc>
bool operator!=(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
{
    return !(lhs == rhs);
}

template <class T, class Alloc>
bool operator<(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
{
    typename list<T,Alloc>::const_iterator lit = lhs.begin(), rit = rhs.begin();
    while (lit != lhs.end() && rit != rhs.end())
    {
        if (*lit > *rit)
            return false;
        if (*lit < *rit)
            return true;
        ++lit;
        ++rit;
    }
    return (lit == lhs.end()) && (rit != rhs.end());
}

template <class T, class Alloc>
bool operator<= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
{
    return (lhs < rhs) || (lhs == rhs);
}

template <class T, class Alloc>
bool operator>(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
{
    typename list<T,Alloc>::const_iterator lit = lhs.begin(), rit = rhs.begin();
    while (lit != lhs.end() && rit != rhs.end())
    {
        if (*lit < *rit)
            return false;
        if (*lit > *rit)
            return true;
        ++lit;
        ++rit;
    }
    return (lit != lhs.end()) && (rit == rhs.end());
}

template <class T, class Alloc>
bool operator>=(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
{
    return (lhs > rhs) || (lhs == rhs);
}

};

#endif // LIST_HPP
