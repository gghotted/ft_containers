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

        TreeNode(const TreeNode& tn_)
        {
            *this = tn_;
        }

        ~TreeNode()
        {
            // unLinkParent();

        }

        TreeNode& operator=(const TreeNode& tn_)
        {
            parent_ = tn_.parent_;
            left_ = tn_.left_;
            right_ = tn_.right_;
            content_ = tn_.content_;
            return *this;
        }

        void linkRight(TreeNode* tn_)
        {
            right_ = tn_;
            if (tn_)
                tn_->parent_ = this;
        }

        void linkLeft(TreeNode* tn_)
        {
            left_ = tn_;
            if (tn_)
                tn_->parent_ = this;
        }

        void linkParent(TreeNode* tn_, ParentRelation relation)
        {
            if (relation == LEFT_CHILD)  tn_->linkLeft(this);
            if (relation == RIGHT_CHILD) tn_->linkRight(this);
            if (relation == NULL_PARENT) parent_ = NULL;
        }

        void unLinkParent()
        {
            ParentRelation relation = getParentRelation();
            if (relation == LEFT_CHILD)  getParent()->linkLeft(NULL);
            if (relation == RIGHT_CHILD) getParent()->linkRight(NULL);
        }

        TreeNode*& getRight()
        {
            return right_;
        }

        TreeNode*& getLeft()
        {
            return left_;
        }

        TreeNode*& getParent()
        {
            return parent_;
        }

        template<class Predicate>
        TreeNode* getParent_if(Predicate pred) const
        {
            TreeNode* parent_ = this->parent_;
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
            if (parent_->getLeft() == this)  return LEFT_CHILD;
            if (parent_->getRight() == this) return RIGHT_CHILD;
            return NULL_PARENT;
        }

        TreeNode* getMinNode()
        {
            TreeNode* minNode_ = this;
            while (minNode_->getLeft())
                minNode_ = minNode_->getLeft();
            return minNode_;
        }

        TreeNode* getMaxNode()
        {
            TreeNode* maxNode_ = this;
            while (maxNode_->getRight())
                maxNode_ = maxNode_->getRight();
            return maxNode_;
        }

        TreeNode* getNewParent()
        {
            return left_ ? left_->getMaxNode()
                         : right_->getMinNode();
        }
};

}

#endif // TREENODE_HPP
