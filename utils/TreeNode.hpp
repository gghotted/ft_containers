#ifndef TREENODE_HPP
#define TREENODE_HPP

namespace ft
{

template <class Tp>
class TreeNode
{
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

        Tp& getContent() // Tp& vs Tp ??
        {
            return content_;
        }
};

}

#endif // TREENODE_HPP
