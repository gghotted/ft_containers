#ifndef DOUBLYLINKEDNODE_HPP
#define DOUBLYLINKEDNODE_HPP

#include <memory>
#include "Iterator.hpp"

namespace   ft
{
    template    <typename Tp>
    class DoublyLinkedNode
    {
        public:
            typedef DoublyLinkedNode<Tp> node;
        private:
            Tp    content_;
            node* prev_;
            node* next_;
        public:
            DoublyLinkedNode()
                : content_(Tp()),
                  prev_(NULL),
                  next_(NULL)
            {
            };
            DoublyLinkedNode(const Tp& content_)
                : content_(content_),
                  prev_(NULL),
                  next_(NULL)
            {
            };
            DoublyLinkedNode(const DoublyLinkedNode& node_);
            virtual ~DoublyLinkedNode() {};
            DoublyLinkedNode& operator=(const DoublyLinkedNode& node_);

            Tp&       content()
            {
                return content_;
            }
            const Tp& content() const
            {
                return content_;
            }
            void linkNext(node* newNode_)
            {
                next_ = newNode_;
                newNode_->prev_ = this;
            }
            void linkPrev(node* newNode_)
            {
                prev_ = newNode_;
                newNode_->next_ = this;
            }

            virtual DoublyLinkedNode* getNext()
            {
                return next_;
            }
            virtual DoublyLinkedNode* getPrev()
            {
                return prev_;
            }
            virtual Tp&               operator*()
            {
                return content_;
            }
    };
}

#endif // DOUBLYLINKEDNODE_HPP
