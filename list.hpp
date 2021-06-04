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
        typedef typename DoublyLinkedNode<Tp>::node node;

    public:
        typedef Tp                                       value_type;
        typedef Alloc                                    allocator_type;
        typedef typename allocator_type::reference       reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer         pointer;
        typedef typename allocator_type::const_pointer   const_pointer;
        typedef typename BidirectionIterator<node>       iterator;
        // const_iterator;
        // reverse_iterator;
        // const_reverse_iterator;
        // difference_type;
        typedef size_t                                   size_type;

        explicit list (
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

        void push_back(const value_type& val_)
        {
            node* newNode = new node(val_);
            if (end_ == NULL)
                setFirstNode(newNode);
            else
                end_->linkNext(newNode);
            size_++;
        }

        reference       front()
        {
            return begin_->content();
        }
        const_reference front() const
        {
            return begin_->content();
        }
        reference       back()
        {
            return end_->content();
        }
        const_reference back() const
        {
            return end_->content();
        }

    private:
        allocator_type allocator_;
        size_type      size_;
        node*          begin_;
        node*          end_;

        void setFirstNode(node* node_)
        {
            begin_ = node_;
            end_ = node_;
        }
};
};

#endif // LIST_HPP
