#ifndef TREENODE_HPP
#define TREENODE_HPP

namespace ft
{

template <class Tp>
class TreeNode
{
    public:
        enum ParentRelation
        {
            LEFT_CHILD,
            RIGHT_CHILD,
            NULL_PARENT
        };

    private:
        TreeNode* parent_;
        TreeNode* left_;
        TreeNode* right_;
        Tp        content_;

    public:
        TreeNode()
            : parent_(NULL),
              left_(NULL),
              right_(NULL),
              content_(Tp())
        {
        }

        TreeNode(const Tp& content_)
            : parent_(NULL),
              left_(NULL),
              right_(NULL),
              content_(content_)
        {
        }

        TreeNode(const TreeNode& tn)
        {
            *this = tn;
        }

        ~TreeNode()
        {
        }

        TreeNode& operator=(const TreeNode& tn)
        {
            parent_ = tn.parent_;
            left_ = tn.left_;
            right_ = tn.right_;
            content_ = tn.content_;
            return *this;
        }

        void linkRight(TreeNode* tn)
        {
            right_ = tn;
            tn->parent_ = this;
        }

        void linkLeft(TreeNode* tn)
        {
            left_ = tn;
            tn->parent_ = this;
        }

        TreeNode* getRight() const
        {
            return right_;
        }

        TreeNode* getleft() const
        {
            return left_;
        }

        TreeNode* getParent() const
        {
            return parent_;
        }

        template<class Predicate>
        TreeNode* getParent_if(Predicate pred) const
        {
            parent_ = this->parent_;
            while (parent_ && pred(parent_) == false)
                parent_ = parent_->getParent();
            return parent_;
        }

        Tp& getContent() // Tp& vs Tp ??
        {
            return content_;
        }

        bool hasChild() const
        {
            return (left_ || right_);
        }

        static bool hasRightParent(const TreeNode* tn_)
        {
            return tn_->getParentRelation() == LEFT_CHILD;
        }

        static bool hasLeftParent(const TreeNode* tn_)
        {
            return tn_->getParentRelation() == RIGHT_CHILD;
        }

        ParentRelation getParentRelation() const
        {
            if (!parent_)                    return NULL_PARENT;
            if (parent_->getleft() == this)  return LEFT_CHILD;
            if (parent_->getRight() == this) return LEFT_CHILD;
        }

        TreeNode* getMinNode() const
        {
            minNode_ = this;
            while (minNode_->getLeft())
                minNode_ = minNode_->getLeft();
            return minNode_;
        }

        TreeNode* getMaxNode() const
        {
            maxNode_ = this;
            while (maxNode_->getRight())
                maxNode_ = maxNode_->getRight();
            return maxNode_;
        }
};

}

#endif // TREENODE_HPP
