#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include <utility>
#include "TreeNode.hpp"
#include "Utils.hpp"
#include "Iterator.hpp"

namespace ft
{

template <
    class Key,
    class T,
    class Compare = less<Key>,
    class Alloc = std::allocator<pair<const Key,T> > >
class map
{
    private:
        typedef TreeNode<pair<const Key,T> > node;

    public:
        template <class Tp>
        class MapIterator : public iterator<bidirectional_iterator_tag, Tp>
        {
            public:
                typedef iterator<bidirectional_iterator_tag, Tp> base;
                typedef typename base::iterator_category         iterator_category;
                typedef typename base::value_type                value_type;
                typedef typename base::difference_type           difference_type;
                typedef typename base::pointer                   pointer;
                typedef typename base::reference                 reference;

            private:
                template<class, class, class, class> friend class map;

                typedef typename remove_const<Tp>::type non_const_Tp;
                typedef MapIterator<non_const_Tp>       non_const_iterator;

                node* node_;

            public:
                MapIterator()
                    : node_(NULL)
                {
                }

                MapIterator(node* node_)
                    : node_(node_)
                {
                }

                MapIterator(const non_const_iterator& mi)
                {
                    *this = mi;
                }

                virtual ~MapIterator()
                {
                }

                MapIterator& operator=(const MapIterator& mi)
                {
                    node_ = mi.node_;
                    return *this;
                }

                MapIterator& operator++()
                {
                    if (node_->getRight())
                        node_ = node_->getRight()->getMinNode();

                    else if (node_->getParentRelation() == node::ParentRelation::LEFT_CHILD)
                        node_ = node_->getParent();

                    else if (node_->getParentRelation() == node::ParentRelation::RIGHT_CHILD)
                    {
                        node_ = node_->getParent_if(node::hasRightParent);
                        node_ = node_ ? node_->getParent() : NULL;
                    }
                    return *this;
                }

                MapIterator& operator--()
                {
                    if (node_->getLeft())
                        node_ = node_->getLeft()->getMaxNode();

                    else if (node_->getParentRelation() == node::ParentRelation::RIGHT_CHILD)
                        node_ = node_->getParent();

                    else if (node_->getParentRelation() == node::ParentRelation::LEFT_CHILD)
                    {
                        node_ = node_->getParent_if(node::hasLeftParent);
                        node_ = node_ ? node_->getParent() : NULL;
                    }
                    return *this;
                }

                MapIterator operator++(int)
                {
                    MapIterator tmp(*this);
                    ++(*this);
                    return tmp;
                }

                MapIterator operator--(int)
                {
                    MapIterator tmp(*this);
                    --(*this);
                    return tmp;
                }

                reference operator*() const
                {
                    return node_->getContent();
                }

                pointer operator->() const
                {
                    return &(operator*());
                }

                bool operator==(const MapIterator& rhs) const
                {
                    return (node_ == rhs.node_);
                }

                bool operator!=(const MapIterator& rhs) const
                {
                    return (node_ != rhs.node_);
                }
        };

        typedef Key                                      key_type;
        typedef T                                        mapped_type;
        typedef pair<const key_type,mapped_type>         value_type;
        typedef Compare                                  key_compare;
        typedef Alloc                                    allocator_type;
        typedef typename allocator_type::reference       reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer         pointer;
        typedef typename allocator_type::const_pointer   const_pointer;
        typedef MapIterator<value_type>                  iterator;
        typedef MapIterator<const value_type>            const_iterator;
        typedef ft::reverse_iterator<iterator>           reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>     const_reverse_iterator;
        typedef ptrdiff_t                                difference_type;
        typedef size_t                                   size_type;

        /* constructor */
        explicit map(const key_compare &comp = key_compare(),
                     const allocator_type &alloc = allocator_type())
            : root_(NULL), minNode_(NULL), maxNode_(NULL), size_(0), comp_(comp), alloc_(alloc)
        {
        }

        template <class InputIterator>
        map(InputIterator first, InputIterator last,
            const key_compare &comp = key_compare(),
            const allocator_type &alloc = allocator_type())
            : root_(NULL), minNode_(NULL), maxNode_(NULL), size_(0), comp_(comp), alloc_(alloc)
        {
            for (; first != last; ++first)
                insert(*first);
        }

        // map(const map &x);

        // /* destructor */
        // ~map();

        // /* assignation */
        // map &operator=(const map &x);

        // /* iterator */
        // iterator begin();

        // const_iterator begin() const;

        // iterator end();

        // const_iterator end() const;

        // reverse_iterator rbegin();

        // const_reverse_iterator rbegin() const;

        // reverse_iterator rend();

        // const_reverse_iterator rend() const;

        // /* capacity */
        // bool empty() const;

        // size_type size() const;

        // size_type max_size() const;

        // /* element access */
        // mapped_type &operator[](const key_type &k);

        /* modifier */
        pair<iterator, bool> insert(const value_type &val)
        {
            if (root_ == NULL)
            {
                root_ = new node(val);
                size_++;
                return pair<iterator, bool>(iterator(root_), true);
            }

            node* cur = root_;
            while (1)
            {
                if (cur->getContent().first < val.first)
                {
                    if (cur->getRight() == NULL)
                    {
                        cur->LinkRight(new node(val));
                        size_++;
                        return iterator(cur->getRight());
                    }
                    else
                        cur = cur->getRight();
                }
                else if (cur->getContent().first > val.first)
                {
                    if (cur->getLeft() == NULL)
                    {
                        cur->LinkLeft(new node(val));
                        size_++;
                        return iterator(cur->getLeft());
                    }
                    else
                        cur = cur->getLeft();
                }
                else
                    return pair<iterator, bool>(iterator(cur), false);
            }
            return pair<iterator, bool>(iterator(NULL), false);
        }

        // iterator insert(iterator position, const value_type &val);

        // template <class InputIterator>
        // void insert(InputIterator first, InputIterator last);

        // void erase(iterator position);

        // size_type erase(const key_type &k);

        // void erase(iterator first, iterator last);

        // void swap(map &x);

        // void clear();

        // /* observers */
        // key_compare key_comp() const;

        // value_compare value_comp() const;

        // /* operations */
        // iterator find(const key_type &k);

        // const_iterator find(const key_type &k) const;

        // size_type count(const key_type &k) const;

        // iterator lower_bound(const key_type &k);

        // const_iterator lower_bound(const key_type &k) const;

        // iterator upper_bound(const key_type &k);

        // const_iterator upper_bound(const key_type &k) const;

        // pair<const_iterator, const_iterator> equal_range(const key_type &k) const;

        // pair<iterator, iterator> equal_range(const key_type &k);

        // /* allocator */
        // allocator_type get_allocator() const;

    private:
        node*           root_;
        node*           minNode_;
        node*           maxNode_;
        size_type       size_;
        key_compare     comp_;
        allocator_type  alloc_;
};

}

#endif // MAP_HPP
