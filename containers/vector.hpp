#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include "iterator.hpp"

namespace ft
{

template < class Tp, class Alloc = std::allocator<Tp> >
class vector
{
    private:
        template <typename Tp_>
        class VectorIterator : public iterator<random_access_iterator_tag, Tp_>
        {
            private:
                template<class, class> friend class vector;

                typedef typename remove_const<Tp_>::type non_const_Tp;
                typedef VectorIterator<non_const_Tp>     non_const_iterator;
                typedef non_const_Tp*                    data;

                data* ptr_;

            public:
                VectorIterator() : ptr_(NULL) {}
                VectorIterator(data* ptr_) : ptr_(ptr_) {}
                VectorIterator(const non_const_iterator& vi) : ptr_(vi.ptr_) {}
                virtual ~VectorIterator()

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

                Tp_& operator*() const
                {
                    return *ptr_;
                }

                bool operator==(const VectorIterator& v)
                {
                    return ptr_ == v.ptr_;
                }

                bool operator!=(const VectorIterator& v)
                {
                    return ptr_ != v.ptr_;
                }


        }
};

}

#endif // VECTOR_HPP
