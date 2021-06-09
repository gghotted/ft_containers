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
    private:
        typedef DoublyLinkedNode<Tp> node;

        template <typename Tp_, bool reverse = false>
        class ListIterator : public iterator<bidirectional_iterator_tag, Tp_>
        {
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
                    if (reverse) node_ = node_->getPrev();
                    else         node_ = node_->getNext();
                    return *this;
                }

                ListIterator& operator--()
                {
                    if (reverse) node_ = node_->getNext();
                    else         node_ = node_->getPrev();
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

                Tp_& operator*() const
                {
                    return **node_;
                }

                bool operator==(const ListIterator& rhs) const
                {
                    return (node_ == rhs.node_);
                }

                bool operator!=(const ListIterator& rhs) const
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
        // insert
        iterator erase (iterator position)
        {
            (void)position.node_;
            return position;
        }
        // swap
        // resize
        void clear()
        {
            while (size_)
                pop_back();
        }

        /* operations */
        // splice
        // remove
        // remove_if
        // unique
        // merge
        // sort
        // reverse

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
};
};

#endif // LIST_HPP
