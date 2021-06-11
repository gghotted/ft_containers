#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <stdexcept>
#include "Iterator.hpp"

namespace ft
{

template < class Tp, class Alloc = std::allocator<Tp> >
class vector
{
    public:
        template <typename Tp_>
        class VectorIterator : public iterator<random_access_iterator_tag, Tp_>
        {
            public:
                typedef iterator<random_access_iterator_tag, Tp_> base;
                typedef typename base::iterator_category          iterator_category;
                typedef typename base::value_type                 value_type;
                typedef typename base::difference_type            difference_type;
                typedef typename base::pointer                    pointer;
                typedef typename base::reference                  reference;

            private:
                template<class, class> friend class vector;

                typedef typename remove_const<Tp_>::type          non_const_Tp;
                typedef VectorIterator<non_const_Tp>              non_const_iterator;

                pointer ptr_;

            public:
                VectorIterator() : ptr_(NULL) {}
                VectorIterator(pointer ptr_) : ptr_(ptr_) {}
                VectorIterator(const non_const_iterator& vi) : ptr_(vi.ptr_) {}
                virtual ~VectorIterator() {}

                VectorIterator& operator=(const VectorIterator& vi)
                {
                    ptr_ = vi.ptr_;
                    return *this;
                }

                VectorIterator& operator++()
                {
                    ++ptr_;
                    return *this;
                }

                VectorIterator& operator--()
                {
                    --ptr_;
                    return *this;
                }

                VectorIterator operator++(int)
                {
                    VectorIterator tmp(*this);
                    ++(*this);
                    return tmp;
                }

                VectorIterator operator--(int)
                {
                    VectorIterator tmp(*this);
                    --(*this);
                    return tmp;
                }

                reference operator*() const // reference??
                {
                    return *ptr_;
                }

                pointer operator->() const
                {
                    return &(operator*());
                }

                bool operator==(const VectorIterator& v) const
                {
                    return ptr_ == v.ptr_;
                }

                bool operator!=(const VectorIterator& v) const
                {
                    return ptr_ != v.ptr_;
                }

                bool operator<(const VectorIterator& v) const
                {
                    return ptr_ < v.ptr_;
                }

                bool operator>(const VectorIterator& v) const
                {
                    return ptr_ > v.ptr_;
                }

                bool operator<=(const VectorIterator& v) const
                {
                    return ptr_ <= v.ptr_;
                }

                bool operator>=(const VectorIterator& v) const
                {
                    return ptr_ >= v.ptr_;
                }

                reference operator[](difference_type n) const
                {
                    return ptr_[n];
                }

                /* (n + iterator) define outside */
                VectorIterator operator+(difference_type n) const
                {
                    return VectorIterator(ptr_ + n);
                }

                VectorIterator& operator+=(difference_type n)
                {
                    ptr_ += n;
                    return *this;
                }

                VectorIterator operator-(difference_type n) const
                {
                    return VectorIterator(ptr_ - n);
                }

                difference_type operator-(const VectorIterator& v) const
                {
                    return (ptr_ - v.ptr_);
                }

                VectorIterator& operator-=(difference_type n)
                {
                    ptr_ -= n;
                    return *this;
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
        typedef VectorIterator<Tp>                       iterator;
        typedef VectorIterator<const Tp>                 const_iterator;
        typedef ft::reverse_iterator<iterator>           reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>     const_reverse_iterator;
        typedef ptrdiff_t                                difference_type;
        typedef size_t                                   size_type;

        /* constructor */
        explicit vector(const allocator_type& alloc = allocator_type())
            : allocator_(alloc),
              size_(0),
              capacity_(0),
              data_(NULL)
        {
        }

        explicit vector(size_type n, const value_type& val = value_type(),
                        const allocator_type& alloc = allocator_type())
            : allocator_(alloc),
              size_(0),
              capacity_(0),
              data_(NULL)
        {
            reserve(n);
            for (size_type i = 0; i < n; i++)
                push_back(val);
        }

        template <class InputIterator>
        vector(InputIterator first, InputIterator last,
               const allocator_type& alloc = allocator_type(),
               typename disable_if<is_integral<InputIterator>::value>::type* = 0)
            : allocator_(alloc),
              size_(0),
              capacity_(0),
              data_(NULL)
        {
            reserve(last - first);
            push_back(first, last);
        }

        vector(const vector& x)
            : allocator_(x.alloc),
              size_(0),
              capacity_(0),
              data_(NULL)
        {
            *this = x;
        }

        /* destructor */
        ~vector()
        {
            destroyData();
        }

        /* operator */
        vector& operator=(const vector& x)
        {
            allocator_ = x.allocator_;
            capacity_ = x.capacity_;
            clear();
            push_back(x.begin(), x.end());
            return *this;
        }

        /* iterator */
        iterator begin()
        {
            if (data_) return iterator(&front());
            else       return iterator(NULL);
        }

        const_iterator begin() const
        {
            if (data_) return const_iterator(&front());
            else       return const_iterator(NULL);
        }

        iterator end()
        {
            if (data_) return iterator(&back() + 1);
            else       return iterator(NULL);
        }

        const_iterator end() const
        {
            if (data_) return const_iterator(&back() + 1);
            else       return const_iterator(NULL);
        }

        reverse_iterator rbegin()
        {
            if (data_) return reverse_iterator(&back());
            else       return reverse_iterator(NULL);
        }

        const_reverse_iterator rbegin() const
        {
            if (data_) return const_reverse_iterator(&back());
            else       return const_reverse_iterator(NULL);
        }

        reverse_iterator rend()
        {
            if (data_) return reverse_iterator(&front() - 1);
            else       return reverse_iterator(NULL);
        }

        const_reverse_iterator rend() const
        {
            if (data_) return const_reverse_iterator(&front() - 1);
            else       return const_reverse_iterator(NULL);
        }

        /* capacity */
        size_type size() const
        {
            return size_;
        }

        size_type max_size () const
        {
            return std::numeric_limits<difference_type>::max(); // ??
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

        size_type capacity() const
        {
            return capacity_;
        }

        bool empty() const
        {
            return size_ == 0;
        }

        void reserve(size_type n)
        {
            if (n > max_size())
                throw std::length_error("lengh error");
            if (n <= capacity_)
                return ;
            moveData(new value_type[n]);
            capacity_ = n;
        }

        /* element access */
        reference operator[] (size_type n)
        {
            return data_[n];
        }

        const_reference operator[] (size_type n) const
        {
            return data_[n];
        }

        reference at(size_type n)
        {
            if (n >= size_)
                throw std::out_of_range("out of range");
            return data_[n];
        }

        const_reference at(size_type n) const
        {
            if (n >= size_)
                throw std::out_of_range("out of range");
            return data_[n];
        }

        reference front()
        {
            return data_[0];
        }

        const_reference front() const
        {
            return data_[0];
        }
        reference back()
        {
            return data_[size_ - 1];
        }

        const_reference back() const
        {
            return data_[size_ - 1];
        }

        /* modifiers */
        template <class InputIterator>
        void assign(InputIterator first, InputIterator last)
        {
            clear();
            push_back(first, last);
        }

        void assign(size_type n, const value_type& val)
        {
            clear();
            for (size_type i = 0; i < n; i++)
                push_back(val);
        }

        void push_back(const value_type& val)
        {
            doubling(size_ + 1);
            data_[size_++] = val;
        }

        void pop_back()
        {
            allocator_.destroy(&back());
            --size_;
        }

        iterator insert(iterator position, const value_type& val)
        {
            insert(position, 1, val);
        }

        void insert(iterator position, size_type n, const value_type& val)
        {
            difference_type idx = position - begin();
            doubling(size_ + n);
            position = iterator(data_ + idx);
            shiftRight(position, n);
            fill(position, position + n, val);
            size_ += n;
        }

        template <class InputIterator>
        void insert(iterator position, InputIterator first, InputIterator last)
        {
            difference_type n = last - first;
            difference_type idx = position - begin();
            doubling(size_ + n);
            position = iterator(data_ + idx);
            shiftRight(position, n);
            fill(position, first, last);
            size_ += n;
        }

        iterator erase(iterator position)
        {
            shiftLeft(position + 1, 1);
            pop_back();
            return position;
        }

        iterator erase(iterator first, iterator last)
        {
            shiftLeft(last, last - first);
            pop_back(last - first);
            return first;
        }

        void swap(vector& x)
        {
            ft::swap(size_, x.size_);
            ft::swap(capacity_, x.capacity_);
            ft::swap(data_, x.data_);
        }

        void clear()
        {
            while (size_)
                pop_back();
        }

        /* allocator */
        allocator_type get_allocator() const
        {
            return allocator_;
        }

    private:
        allocator_type allocator_;
        size_type      size_;
        size_type      capacity_;
        pointer        data_;

        void doubling()
        {
            if (capacity_ == 0)
                reserve(1);
            else
                reserve(capacity_ * 2);
        }

        void doubling(size_type requireMin)
        {
            while (capacity_ < requireMin)
                doubling();
        }

        void shiftRight(iterator position, difference_type n)
        {
            copy(rbegin(), reverse_iterator(position), rbegin() - n);
        }

        void shiftLeft(iterator position, difference_type n)
        {
            copy(position, end(), position - n);
        }

        void moveData(pointer newSpace)
        {
            if (!data_)
            {
                data_ = newSpace;
                return ;
            }
            copy(begin(), end(), newSpace);
            destroyData();
            data_ = newSpace;
        }

        void destroyData()
        {
            if (!data_)
                return ;
            clear();
            allocator_.deallocate(data_, capacity_);
        }

        template <class InputIterator>
        void push_back(InputIterator first, InputIterator last)
        {
            for (; first != last; ++first)
                push_back(*first);
        }

        void pop_back(size_type n)
        {
            for (size_type i = 0; i < n; i++)
                pop_back();
        }
};

template <class Tp>
typename vector<Tp>::iterator operator+(typename vector<Tp>::iterator::difference_type n, const typename vector<Tp>::iterator& v)
{
    return (v + n);
}

}

#endif // VECTOR_HPP
