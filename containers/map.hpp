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
                    : node_(mi.node_)
                {
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
                    else if (node_->getParentRelation() == node::LEFT_CHILD)
                        node_ = node_->getParent();
                    else if (node_->getParentRelation() == node::RIGHT_CHILD)
                        node_ = node_->getParent_if(node::hasRightParent)->getParent();
                    return *this;
                }

                MapIterator& operator--()
                {
                    if (node_->getLeft())
                        node_ = node_->getLeft()->getMaxNode();
                    else if (node_->getParentRelation() == node::RIGHT_CHILD)
                        node_ = node_->getParent();
                    else if (node_->getParentRelation() == node::LEFT_CHILD)
                        node_ = node_->getParent_if(node::hasLeftParent)->getParent();
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
        template <class Key, class T, class Compare, class Alloc>
        class value_compare : public binary_function<value_type, value_type, bool>
        {
            friend class map;
        protected:
            Compare comp;
            value_compare(Compare c) : comp(c) {}
        public:
            typedef bool result_type;
            typedef value_type first_argument_type;
            typedef value_type second_argument_type;
            bool operator()(const value_type &x, const value_type &y) const
            {
                return comp(x.first, y.first);
            }
        }

        /* constructor */
        explicit map(const key_compare &comp = key_compare(),
                     const allocator_type &alloc = allocator_type())
            : minNode_(NULL), maxNode_(NULL), size_(0), comp_(comp), alloc_(alloc)
        {
            initDefaultNode();
        }

        template <class InputIterator>
        map(InputIterator first, InputIterator last,
            const key_compare &comp = key_compare(),
            const allocator_type &alloc = allocator_type())
            : minNode_(NULL), maxNode_(NULL), size_(0), comp_(comp), alloc_(alloc)
        {
            initDefaultNode();
            for (; first != last; ++first)
                insert(*first);
        }

        map(const map &x)
            : minNode_(NULL), maxNode_(NULL), size_(0), alloc_(x.alloc_)
        {
            initDefaultNode();
            *this = x;
        }

        // /* destructor */
        ~map()
        {
            clear();
            delete maxNode_;
            delete minNode_;
        }

        // /* assignation */
        map &operator=(const map &x)
        {
            clear();
            insert(x.begin(), x.end());
            return *this;
        }

        // /* iterator */
        iterator begin()
        {
            return empty() ? end()
                           : iterator(root()->getMinNode());
        }

        const_iterator begin() const
        {
            return empty() ? end()
                           : const_iterator(root()->getMinNode());
        }

        iterator end()
        {
            return iterator(maxNode_);
        }

        const_iterator end() const
        {
            return const_iterator(maxNode_);
        }

        reverse_iterator rbegin()
        {
            return empty() ? rend()
                           : reverse_iterator(maxNode_);
        }

        const_reverse_iterator rbegin() const
        {
            return empty() ? rend()
                           : const_reverse_iterator(maxNode_);
        }

        reverse_iterator rend()
        {
            return reverse_iterator(root()->getMinNode());
        }

        const_reverse_iterator rend() const
        {
            return const_reverse_iterator(root()->getMinNode());
        }

        // /* capacity */
        bool empty() const
        {
            return (size_ == 0);
        }

        size_type size() const
        {
            return size_;
        }

        size_type max_size () const
        {
            return std::numeric_limits<difference_type>::max(); // ??
        }

        // /* element access */
        mapped_type &operator[](const key_type &k)
        {
            iterator it = find(k);
            return it == end() ? insert(value_type(k, mapped_type())).first->second
                               : it->second;
        }

        /* modifier */
        pair<iterator, bool> insert(const value_type &val)
        {
            if (root() == NULL)
            {
                maxNode_->linkLeft(new node(val));
                size_++;
                return pair<iterator, bool>(iterator(root()), true);
            }

            node* cur = root();
            while (1)
            {
                if (cur->getContent().first == val.first)
                    return pair<iterator, bool>(iterator(cur), false);
                else if (comp_(val.first, cur->getContent().first))
                {
                    if (cur->getLeft() == NULL)
                    {
                        cur->linkLeft(new node(val));
                        size_++;
                        return pair<iterator, bool>(iterator(cur->getLeft()), true);
                    }
                    else
                        cur = cur->getLeft();
                }
                else
                {
                    if (cur->getRight() == NULL)
                    {
                        cur->linkRight(new node(val));
                        size_++;
                        return pair<iterator, bool>(iterator(cur->getRight()), true);
                    }
                    else
                        cur = cur->getRight();
                }
            }
            return pair<iterator, bool>(iterator(NULL), false);
        }

        iterator insert(iterator position, const value_type &val)
        {
            (void)position;
            insert(val);
            return find(val.first);
        }

        template <class InputIterator>
        void insert(InputIterator first, InputIterator last)
        {
            for (; first != last; ++first)
                insert(*first);
        }

        void erase(iterator position)
        {
            --size_;
            if (!position.node_->hasChild())
            {
                position.node_->unLinkParent();
                delete position.node_;
                return ;
            }

            node* newParent = position.node_->getNewParent();
            node* left      = position.node_->getLeft();
            node* right     = position.node_->getRight();

            if (left  == newParent) left  = left->getLeft();
            if (right == newParent) right = right->getRight();

            if (comp_(position.node_->getContent().first, newParent->getContent().first))
                newParent->getParent()->linkLeft(newParent->getRight());
            else
                newParent->getParent()->linkRight(newParent->getLeft());

            newParent->linkParent(position.node_->getParent(), position.node_->getParentRelation());
            newParent->linkLeft(left);
            newParent->linkRight(right);
            delete position.node_;
        }

        size_type erase(const key_type &k)
        {
            iterator it = find(k);
            if (it == end())
                return 0;
            erase(it);
            return 1;
        }

        void erase(iterator first, iterator last)
        {
            if (first == last)
                return ;
            while (first != last)
            {
                iterator next = ft::next(first);
                erase(first);
                first = next;
            }
        }

        void swap(map &x)
        {
            ft::swap(minNode_, x.minNode_);
            ft::swap(maxNode_, x.maxNode_);
            ft::swap(size_, x.size_);
        }

        void clear()
        {
            erase(begin(), end());
        }

        /* observers */
        key_compare key_comp() const
        {
            return comp_;
        }

        value_compare value_comp() const
        {
            return value_compare(comp_);
        }

        /* operations */
        iterator find(const key_type &k)
        {
            node* node_ = root();
            while (node_ && node_->getContent().first != k)
            {
                if (comp_(k, node_->getContent().first))
                    node_ = node_->getLeft();
                else
                    node_ = node_->getRight();
            }
            return node_ ? iterator(node_)
                         : end();
        }

        const_iterator find(const key_type &k) const
        {
            node* node_ = root();
            while (node_ && node_->getContent().first != k)
            {
                if (comp_(k, node_->getContent().first))
                    node_ = node_->getLeft();
                else
                    node_ = node_->getRight();
            }
            return node_ ? const_iterator(node_)
                         : end();
        }

        size_type count(const key_type &k) const
        {
            const_iterator it = find(k);
            return it != end();
        }

        iterator lower_bound(const key_type &k)
        {
            node* node_ = root();
            while (node_)
            {
                if (k == node_->getContent().first)
                    return iterator(node_);
                else if (comp_(k, node_->getContent().first)) // k가 작음
                {
                    if (!node_->getLeft())
                        return iterator(node_);
                    node_ = node_->getLeft();
                }
                else // k가 큼
                {
                    if (!node_->getRight())
                        return ++iterator(node_);
                    node_ = node_->getRight();
                }
            }
            return end();
        }

        const_iterator lower_bound(const key_type &k) const
        {
            node* node_ = root();
            while (node_)
            {
                if (k == node_->getContent().first)
                    return const_iterator(node_);
                else if (comp_(k, node_->getContent().first)) // k가 작음
                {
                    if (!node_->getLeft())
                        return const_iterator(node_);
                    node_ = node_->getLeft();
                }
                else // k가 큼
                {
                    if (!node_->getRight())
                        return ++const_iterator(node_);
                    node_ = node_->getRight();
                }
            }
            return end();
        }

        iterator upper_bound(const key_type &k)
        {
            iterator it = lower_bound(k);
            if (it == end())
                return end();
            if (it->first == k)
                ++it;
            return it;
        }

        const_iterator upper_bound(const key_type &k) const
        {
            const_iterator it = lower_bound(k);
            if (it == end())
                return end();
            if (it->first == k)
                ++it;
            return it;
        }

        pair<iterator, iterator> equal_range(const key_type &k)
        {
            return pair<iterator, iterator>(lower_bound(k), upper_bound(k));
        }

        pair<const_iterator, const_iterator> equal_range(const key_type &k) const
        {
            return pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));
        }


        // /* allocator */
        // allocator_type get_allocator() const;

    private:
        node*           minNode_;
        node*           maxNode_;
        size_type       size_;
        key_compare     comp_;
        allocator_type  alloc_;

        node*& root()
        {
            return maxNode_->getLeft();
        }

        node* root() const
        {
            return maxNode_->getLeft();
        }

        void initDefaultNode()
        {
            minNode_ = new node(value_type(key_type(), mapped_type()));
            maxNode_ = new node(value_type(key_type(), mapped_type()));
            minNode_->linkRight(maxNode_);
        }
};

}

#endif // MAP_HPP
