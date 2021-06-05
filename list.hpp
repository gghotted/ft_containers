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

        class IteratorObject : public BidirectionIterableObject<Tp, node*>
        {
            public:
                typedef Tp    value_type;
                typedef node* create_by_type;

            private:
                create_by_type node_;

                template<class, class> friend class list;

            public:
                IteratorObject()                                             {}
                IteratorObject(create_by_type node_)      : node_(node_)     {}
                IteratorObject(const IteratorObject& obj) : node_(obj.node_) {}
                virtual ~IteratorObject()                                    {}
                IteratorObject& operator=(const IteratorObject& obj)
                {
                    node_ = obj.node_;
                    return *this;
                }
                create_by_type getNode() { return node_; }
                virtual value_type& operator*() { return **node_; }
                virtual const void* id() const  { return node_; }
                virtual void        increase()  { node_ = node_->getNext(); }
                virtual void        decrease()  { node_ = node_->getPrev(); }
        };

    public:
        typedef Tp                                        value_type;
        typedef Alloc                                     allocator_type;
        typedef typename allocator_type::reference        reference;
        typedef typename allocator_type::const_reference  const_reference;
        typedef typename allocator_type::pointer          pointer;
        typedef typename allocator_type::const_pointer    const_pointer;
        typedef BidirectionIterator<IteratorObject>       iterator;

        // const_iterator;
        typedef BidirectionIterator<IteratorObject, true> reverse_iterator;
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
            {
                end_->linkNext(newNode);
                end_ = newNode;
                end_->linkNext(&endOfNode_);
            }
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

        iterator begin()
        {
            if (begin_ == NULL)
                return end();
            return iterator(begin_);
        }
        iterator end()
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
            (void)position.iteratorObj.node_;
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
