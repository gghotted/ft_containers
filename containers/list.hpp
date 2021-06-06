#ifndef LIST_HPP
#define LIST_HPP

#include <memory>
// #include <list>
// #include <iterator>
#include "DoublyLinkedNode.hpp"
#include "Iterator.hpp"

namespace ft
{
template <typename Tp, class Alloc = std::allocator<Tp> >
class   list
{
    private:
        typedef DoublyLinkedNode<Tp> node;

        class ListIterator : BidirectionIteratorBase<ListIterator, Tp>
        {
            private:
                template<class, class> friend class list;

                node* node_;

            public:
                ListIterator()                        : node_(NULL)     {}
                ListIterator(node* node_)             : node_(node_)    {}
                ListIterator(const ListIterator& li)  : node_(li.node_) {}
                virtual ~ListIterator()                                 {}

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
                Tp& operator*()
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
        typedef Tp                                                       value_type;
        typedef Alloc                                                    allocator_type;
        typedef typename allocator_type::reference                       reference;
        typedef typename allocator_type::const_reference                 const_reference;
        typedef typename allocator_type::pointer                         pointer;
        typedef typename allocator_type::const_pointer                   const_pointer;
        typedef BidirectionIterator<ListIterator, Tp, node*>             iterator;
        typedef BidirectionIterator<ListIterator, const Tp, node*>       const_iterator;
        typedef BidirectionIterator<ListIterator, Tp, node*, true>       reverse_iterator;
        typedef BidirectionIterator<ListIterator, const Tp, node*, true> const_reverse_iterator;
        typedef ptrdiff_t                                                difference_type;
        typedef size_t                                                   size_type;

        /* constructor */
        explicit list(const allocator_type& alloc_ = allocator_type())
            : allocator_(alloc_),
              size_(0),
              begin_(NULL),
              end_(NULL)
        {
        }

        explicit list(
            size_type n_,
            const value_type& val_ = value_type(),
            const allocator_type& alloc_ = allocator_type())
            : allocator_(alloc_),
              size_(0),
              begin_(NULL),
              end_(NULL)
        {
            for (size_type i = 0; i < n_; i++)
                push_back(val_);
        }

        template <class InputIterator>
        list(
            InputIterator first, InputIterator last,
            const allocator_type& alloc_ = allocator_type())
            : allocator_(alloc_),
              size_(0),
              begin_(NULL),
              end_(NULL)
        {
            for (; first != last; first++)
                push_back(*first);
        }

        void push_back(const value_type& val_)
        {
            node* newNode = new node(val_);
            if (end_ == NULL)
                setFirstNode(newNode);
            else
            {
                end_->linkNext(newNode);
                end_ = newNode;
                end_->linkNext(&endOfNode_);
            }
            size_++;
        }

        reference       front()
        {
            return **begin_;
        }
        const_reference front() const
        {
            return **begin_;
        }
        reference       back()
        {
            return **end_;
        }
        const_reference back() const
        {
            return **end_;
        }

        iterator begin()
        {
            if (begin_ == NULL)
                return end();
            return iterator(begin_);
        }
        const_iterator begin() const
        {
            if (begin_ == NULL)
                return end();
            return iterator(begin_);
        }
        iterator end()
        {
            return iterator(&endOfNode_);
        }
        const_iterator end() const
        {
            return iterator(&endOfNode_);
        }
        reverse_iterator rbegin()
        {
            if (end_ == NULL)
                return rend();
            return reverse_iterator(end_);
        }
        reverse_iterator rend()
        {
            return reverse_iterator(&beginOfNode_);
        }

        size_type size() const
        {
            return size_;
        }

        // Modifiers
        iterator erase (iterator position)
        {
            (void)position.node_;
            return position;
        }

    private:
        allocator_type allocator_;
        size_type      size_;
        node*          begin_;
        node*          end_;
        node           beginOfNode_;
        node           endOfNode_;

        void setFirstNode(node* node_)
        {
            begin_ = node_;
            end_ = node_;
            begin_->linkPrev(&beginOfNode_);
            end_->linkNext(&endOfNode_);
        }
};
};

#endif // LIST_HPP
