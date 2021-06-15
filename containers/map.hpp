#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include <utility>
#include "TreeNode.hpp"
#include "Utils.hpp"

namespace ft
{

template <
    class Key,
    class T,
    class Compare = less<Key>,
    class Alloc = std::allocator<std::pair<const Key,T> > >
class map
{
    // class mapIterator

    public:
        typedef Key key_type;
        typedef T mapped_type;
        typedef std::pair<const key_type,mapped_type> value_type;
        typedef Compare key_compare;
        typedef Alloc allocator_type;
        typedef Alloc                                    allocator_type;
        typedef typename allocator_type::reference       reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer         pointer;
        typedef typename allocator_type::const_pointer   const_pointer;
        // typedef ListIterator<Tp>                         iterator;
        // typedef ListIterator<const Tp>                   const_iterator;
        // typedef ft::reverse_iterator<iterator>           reverse_iterator;
        // typedef ft::reverse_iterator<const_iterator>     const_reverse_iterator;
        typedef ptrdiff_t                                difference_type;
        typedef size_t                                   size_type;

        /* constructor */
        explicit map(const key_compare &comp = key_compare(),
                     const allocator_type &alloc = allocator_type())
            : root(NULL), minNode(NULL), maxNode(NULL), size_(0), comp_(comp), alloc_(alloc)
        {
        }

        template <class InputIterator>
        map(InputIterator first, InputIterator last,
            const key_compare &comp = key_compare(),
            const allocator_type &alloc = allocator_type())
            : root(NULL), minNode(NULL), maxNode(NULL), size_(0), comp_(comp), alloc_(alloc)
        {
            for (; first != last; ++first)
                insert(*first);
        }

        map(const map &x);

        /* destructor */
        ~map();

        /* assignation */
        map &operator=(const map &x);

        /* iterator */
        iterator begin();

        const_iterator begin() const;

        iterator end();

        const_iterator end() const;

        reverse_iterator rbegin();

        const_reverse_iterator rbegin() const;

        reverse_iterator rend();

        const_reverse_iterator rend() const;

        /* capacity */
        bool empty() const;

        size_type size() const;

        size_type max_size() const;

        /* element access */
        mapped_type &operator[](const key_type &k);

        /* modifier */
        std::pair<iterator, bool> insert(const value_type &val)
        {
            if (root_ == NULL)
            {
                root_ = new TreeNode(val);
                size_++;
                return std::pair<iterator, bool>(iterator(root_), true);
            }

            TreeNode* cur = root_;
            while (1)
            {
                if (cur->getContent().first < val.first)
                {
                    if (cur->getRight() == NULL)
                    {
                        cur->LinkRight(new TreeNode(val));
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
                        cur->LinkLeft(new TreeNode(val));
                        size_++;
                        return iterator(cur->getLeft());
                    }
                    else
                        cur = cur->getLeft();
                }
                else
                    return std::pair<iterator, bool>(iterator(cur), false);
            }
        }

        iterator insert(iterator position, const value_type &val);

        template <class InputIterator>
        void insert(InputIterator first, InputIterator last);

        void erase(iterator position);

        size_type erase(const key_type &k);

        void erase(iterator first, iterator last);

        void swap(map &x);

        void clear();

        /* observers */
        key_compare key_comp() const;

        value_compare value_comp() const;

        /* operations */
        iterator find(const key_type &k);

        const_iterator find(const key_type &k) const;

        size_type count(const key_type &k) const;

        iterator lower_bound(const key_type &k);

        const_iterator lower_bound(const key_type &k) const;

        iterator upper_bound(const key_type &k);

        const_iterator upper_bound(const key_type &k) const;

        pair<const_iterator, const_iterator> equal_range(const key_type &k) const;

        pair<iterator, iterator> equal_range(const key_type &k);

        /* allocator */
        allocator_type get_allocator() const;

    private:
        TreeNode*       root_;
        TreeNode*       minNode_;
        TreeNode*       maxNode_;
        size_type       size_;
        key_compare     comp_;
        allocator_type  alloc_;
};

}

#endif // MAP_HPP
