/*
 * @Author: Shuai Wang
 * @Github: https://github.com/wsustcid
 * @Version: 1.0.0
 * @Date: 2021-11-16 10:24:24
 * @LastEditTime: 2021-11-16 16:51:59
 */

template <typename valType> class BTnode; // BTnode class template 前置声明
template <typename Type> class BinaryTree; // BinaryTree class 前置声明


// BinaryTree
template <typename elemType>
class BinaryTree{
public:
    BinaryTree();
    BinaryTree(const BinaryTree&);
    ~BinaryTree();
    BinaryTree& operator=(const BinaryTree&);

    bool empty() {return _root==0; }
    void clear() {if (_root) {clear(_root); _root=0;}}

    insert(const elemType&);
    remove(const elemType&);
    remove_root();
   

private:
    BTnode<elemType>* _root; // 这里使用BTnode就需要以模板参数列表加以限定
    //将src所指的子树复制到tar所指子树
    void copy(BTnode<elemType>* tar, BTnode<elemType>* src);
    void clear(BTnode<elemType>*); 
};

template <typename elemType>
inline BinaryTree<elemType>::BinaryTree() : _root(0) {}

template <typename elemType>
inline BinaryTree<elemType>::BinaryTree(const BinaryTree& rhs) {copy(_root, rhs._root);}

template <typename elemType>
inline BinaryTree<elemType>::~BinaryTree() { clear(); }

template <typename elemType>
inline BinaryTree<elemType>& BinaryTree<elemType>::operator=(const BinaryTree& rhs)
{
    if (this != &rhs) // 注意引用是实参的别名，并不是实际的地址
    {
        clear();
        copy(_root, rhs._root);
    }
    return *this;
}

template <typename elemType>
inline BinaryTree<elemType>::insert(const elemType& elem)
{
    if (!_root) _root = new BTnode<elemType>(elem); // new: 开辟内存，返回指针，并初始化
    else _root->insert_value(elem);
}

tempalte <typename elemType>
inline BinaryTree<elemType>::remove(const elemType& elem)
{
    if (_root)
    {
        if (_root->_val == elem) remove_root();
        else _root->remove_value(elem, _root);
    }
}

template <typename elemType>
inline BinaryTree<elemType>::remove_root()
{
    if (!_root) return;
    BTnode<elemType> *tmp = _root;
    if (_root->_rchild)
    {
        _root = _root->_rchild; // 删除根节点
        //将左子树搬移到右子节点左子树的底部
        if (tmp->_lchild)
        {
            BTnode<elemType> *lc = tmp->_lchild;
            BTnode<elemType> *newlc = _root->_lchild;
            if (!newlc) _root->_lchild = lc;
            else BTnode<elemType>::lchild_leaf(lc, newlc);
        }
    }
    else _root = _root->_lchild;

    delete tmp; //真正安全的删除根节点
}

template <typename elemType>
void BinaryTree<elemType>::clear(BTnode<elemType> *pt)
{
    if (pt)
    {
        clear(pt->_lchild);
        clear(pt->_rchild);
        delete pt;
    }
}



// BTnode
template <typename valType>
class BTnode{
    friend class BinaryTree<valType>; // 希望两个class相互合作
public:
    BTnode();
    BTnode(const valType&);
    ~BTnode();

    insert_val(const valType&);
    lchild_leaf(BTnode *leaf, BTnode *subtree);
    remove_value(const valType &val, BTnode* &prev); 
    void preorder(BTnode* pt, ostream &os) const;

private:
    valType _val;
    int     _cnt;
    BTnode* _lchild;
    BTnode* _rchild; // 在模板类及其成员的定义中，使用BTnode不需要用模板参数化列表限定
    // 但其他场合就需要以参数化列表限定
};

template <typename valType>
inline BTnode<valType>::BTnode(const valType &val) : _val(val)
{
    _cnt = 1;
    _lchild = _rchild = 0;
}

template <typename valType>
inline BTnode<elemType>::insert_value(const valType& val)
{
    if (val == _val) {_cnt++; return;}
    if (val < _val)
    {
        if (!_lchild) _lchild = new BTnode(val);
        else _lchild.insert_val(val);
    }
    else
    {
        if (!_rchild) _rchild = new BTnode(val);
        else _rchild.insert_val(val);
    }
}

template <typename valType>
inline BTnode::lchild_leaf(BTnode *leaf, BTnode *subtree)
{   
    // 搬移左子节点，使它成为右子节点左子树的叶节点
    while(subtree->_lchild) subtree = subtree->_lchild;
    subtree->_lchild = leaf;
}

template<typename valType>
inline BTnode::remove_value(const valType &val, BTnode* &prev)
{
    if (val < _val)
    {
        if (!_lchild) return;
        else _lchild->remove_val(val, _lchild);
    }
    else if (val > _val)
    {
        if (!_rchild) return;
        else _rchild->remove_val(val, _rchild);
    }
    else
    {
        // 找到了，重置此树，然后删除此节点
        if (_rchild)
        {
            prev = _rchild;
            if (_lchild)
            {
                if (!prev->_lchild) prev->_lchild = _lchild;
                else BTnode<valType>::lchild_leaf(_lchild, prev->_lchild);
            }
        }
        else prev = _lchild;
        delete this;
    }
}

template<typename valType>
inline void BTnode<valType>::preorder(BTnode *pt, ostream &os) const
{
    if (pt)
    {
        display_val(pt, os);
        if (pt->_lchild) preorder(pt->_lchild, os);
        if (pt->_rchild) preorder(pt->_rchild, os);
    }
}

template<typename valType>
inline void BTnode<valType>::inorder(BTnode *pt, ostream &os) const
{
    if (pt)
    {
        if (pt->_lchild) preorder(pt->_lchild, os);
        display_val(pt, os);
        if (pt->_rchild) preorder(pt->_rchild, os);
    }
}

template<typename valType>
inline void BTnode<valType>::postorder(BTnode *pt, ostream &os) const
{
    if (pt)
    {
        if (pt->_lchild) preorder(pt->_lchild, os);
        if (pt->_rchild) preorder(pt->_rchild, os);
        display_val(pt, os);
    }
}