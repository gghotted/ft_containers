#ifndef DOUBLYLINKEDNODE_HPP
#define DOUBLYLINKEDNODE_HPP

#include <cstddef>

namespace   ft
{
    template    <typename Tp>
    class DoublyLinkedNode
    {
        private:
            Tp                content_;
            DoublyLinkedNode* prev_;
            DoublyLinkedNode* next_;

        public:
            virtual ~DoublyLinkedNode() {}

            DoublyLinkedNode()
                : content_(Tp()),
                  prev_(NULL),
                  next_(NULL)
            {
            }
            DoublyLinkedNode(const Tp& content_)
                : content_(content_),
                  prev_(NULL),
                  next_(NULL)
            {
            }
            DoublyLinkedNode(const DoublyLinkedNode& node_)
            {
                *this = node_;
            }

            DoublyLinkedNode& operator=(const DoublyLinkedNode& node_)
            {
                content_ = node_.content_;
                prev_ = node_.prev_;
                next_ = node_.next_;
                return *this;
            }
            Tp&               operator*()
            {
                return content_;
            }

            void linkNext(DoublyLinkedNode* newNode_)
            {
                next_ = newNode_;
                if (newNode_)
                    newNode_->prev_ = this;
            }
            void linkPrev(DoublyLinkedNode* newNode_)
            {
                prev_ = newNode_;
                if (newNode_)
                    newNode_->next_ = this;
            }

            void insertNext(DoublyLinkedNode* newNode_)
            {
                newNode_->linkNext(next_);
                linkNext(newNode_);
            }

            void insertPrev(DoublyLinkedNode* newNode_)
            {
                newNode_->linkPrev(prev_);
                linkPrev(newNode_);
            }

            DoublyLinkedNode* getNext()
            {
                return next_;
            }

            DoublyLinkedNode* getPrev()
            {
                return prev_;
            }

            void swapNextLink(DoublyLinkedNode* node_)
            {
                DoublyLinkedNode* tmp = next_;
                linkNext(node_->next_);
                node_->linkNext(tmp);
            }

            void swapPrevLink(DoublyLinkedNode* node_)
            {
                DoublyLinkedNode* tmp = prev_;
                linkPrev(node_->prev_);
                node_->linkPrev(tmp);
            }
    };
}

#endif // DOUBLYLINKEDNODE_HPP
