#ifndef DOUBLYLINKEDNODE_HPP
#define DOUBLYLINKEDNODE_HPP

#include <memory>

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
                  prev(NULL),
                  next(NULL)
            {
            };
            DoublyLinkedNode(const Tp& content_)
                : content_(content_),
                  prev(NULL),
                  next(NULL)
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
            Tp& operator*()
            {
                return content_;
            }
            void linkNext(node* newNode_)
            {
                next_ = newNode_;
                newNode->prev_ = this;
            }
            void linkPrev(node* newNode_)
            {
                prev_ = newNode_;
                newNode->next_ = this;
            }

    };
}

#endif // DOUBLYLINKEDNODE_HPP
