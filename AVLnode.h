#ifndef AVL_NODE_H
#define AVL_NODE_H
#include <iostream>
#include <memory>
#include <cmath>


#define INVALID_BF 2

template <class T, class S>
class AVL_node
{
private:

    int BF;
    T info;
    S key;
    int num_of_children;
    int height;
    std::shared_ptr<AVL_node<T,S>> father; // maybe delete class
    std::shared_ptr<AVL_node<T,S>> left_son;
    std::shared_ptr<AVL_node<T,S>> right_son;



protected:
    int getBF();
    int getHeight();
    int max(int h1, int h2);
    std::shared_ptr<AVL_node<T,S>> getNextInOrderVal();
    void SwapInfoAndKey(std::shared_ptr<AVL_node<T,S>> avl_node);

public:
    AVL_node() : BF(0) , info(), key(), height(0), father(nullptr),left_son(nullptr), right_son(nullptr){}; //constructor
    AVL_node(S& key, T& info) : BF(0) , info(info), key(key), height(0), father(nullptr),left_son(nullptr), right_son(nullptr){} ; //constructor
    ~AVL_node() = default; //destructor
    AVL_node(const AVL_node&); //copy constructor
    AVL_node& operator=(const AVL_node& other); // avl_node1= avl_node2

    std::shared_ptr<AVL_node<T,S>> insert(std::shared_ptr<AVL_node<T,S>> root,S key,T info); // change other to sharedptr
    std::shared_ptr<AVL_node<T,S>> deleteNode(std::shared_ptr<AVL_node<T,S>> root, S key);
    std::shared_ptr<AVL_node<T,S>> find(std::shared_ptr<AVL_node<T,S>> root,S key);
    std::shared_ptr<AVL_node<T,S>> leftRotation(std::shared_ptr<AVL_node<T,S>> root);
    std::shared_ptr<AVL_node<T,S>> rightRotation(std::shared_ptr<AVL_node<T,S>> root);
    std::shared_ptr<AVL_node<T,S>> treeBalance(std::shared_ptr<AVL_node<T,S>> avl_node);
    void updateHeight();
    void updateBF();
    T& getInfo();
    std::shared_ptr<AVL_node<T,S>>  getNodeWithBiggestKey(std::shared_ptr< AVL_node<T,S> > root);

    void setInfo(T new_info);
    void setKey(S new_key);

    S getKey();
    std::shared_ptr<AVL_node<T,S>> getFather();
    std::shared_ptr<AVL_node<T,S>> getLeft_son();
    std::shared_ptr<AVL_node<T,S>> getRight_son();


    template<class DoSomething>
    void inOrder(std::shared_ptr<AVL_node<T,S>> root, DoSomething doSomething);

    template<class DoSomething>
    void preOrder(std::shared_ptr<AVL_node<T,S>> root, DoSomething doSomething);

    void postOrderAndDestroy(std::shared_ptr<AVL_node<T,S>> root);
    void NodePointSiblingsToNull(const std::shared_ptr<AVL_node<T,S>>& root);
    void updateHeightAndBF();
    void printBFAndHeight();

    std::shared_ptr<AVL_node<T,S>> deleteNodeHelper(std::shared_ptr<AVL_node<T,S>> node_to_delete, std::shared_ptr<AVL_node<T,S>> root);

    std::shared_ptr<AVL_node<T,S>> clone(const std::shared_ptr<AVL_node<T,S>> root, const std::shared_ptr<AVL_node<T,S>> parent);
    void reverseInOrderNumTimes(std::shared_ptr<AVL_node<T,S>> avlNode, int Players[], int *numOfPlayers,int count);
    void InOrderNumTimes(std::shared_ptr<AVL_node<T,S>> avlNode, int Players[], int *numOfPlayers,int count);
    void storeInorder(std::shared_ptr<AVL_node<T,S>> avlNode, T inorderInfoArr[], S inorderKeyArr[], int *index_ptr);
    S * merge(T arr1Info[], S arr1Key[],T arr2Info[], S arr2Key[], T mergedInfoArr[],int m, int n);
    std::shared_ptr<AVL_node<T,S>> sortedArrayToAVLtree(T infoArr[], S keyArr[],int start, int end,std::shared_ptr<AVL_node<T,S>> father);
    std::shared_ptr<AVL_node<T,S>> mergeAvlTrees(std::shared_ptr<AVL_node<T,S>> root1, std::shared_ptr<AVL_node<T,S>> root2,
                                                 T mergedInfoArr[] ,int m, int n);

    void swapNodes(std::shared_ptr<AVL_node<T,S>> node_to_delete,std::shared_ptr<AVL_node<T,S>> NextInOrderVal);
    void swapHeightAndBF(std::shared_ptr<AVL_node<T,S>> node_to_delete,std::shared_ptr<AVL_node<T,S>> NextInOrderVal);

};

template <class T, class S>
void AVL_node<T,S>::setKey(S new_key)
{
    this->key = new_key;
}


template <class T, class S>
std::shared_ptr<AVL_node<T,S>> AVL_node<T,S>::mergeAvlTrees(std::shared_ptr<AVL_node<T,S>> root1, std::shared_ptr<AVL_node<T,S>> root2,
                                                            T mergedInfoArr[] ,int m, int n)
{
    S *arr1keys = new S[m];
    T *arr1Info = new T[m];
    int i = 0;

    storeInorder(root1, arr1Info,arr1keys, &i);

    S *arr2keys = new S[n];
    T *arr2Info = new T[n];
    int j = 0;
    storeInorder(root2, arr2Info,arr2keys, &j);

    S *mergedkeyArr = merge(arr1Info,arr1keys, arr2Info, arr2keys,mergedInfoArr, m, n);

    std::shared_ptr<AVL_node<T,S>> mergedTrees = sortedArrayToAVLtree (mergedInfoArr,mergedkeyArr, 0, m + n - 1, nullptr);

    delete [] arr1keys;
    delete [] arr1Info;
    delete [] arr2keys;
    delete [] arr2Info;
    delete [] mergedkeyArr;

    return mergedTrees;
}


template <class T, class S>
std::shared_ptr<AVL_node<T,S>> AVL_node<T,S>::sortedArrayToAVLtree(T infoArr[], S keyArr[],int start, int end,std::shared_ptr<AVL_node<T,S>> father)
{
    if(start > end)
        return NULL;

    int mid = (start+end)/2;
    std::shared_ptr<AVL_node<T,S>> node = (std::make_shared<AVL_node>(keyArr[mid],infoArr[mid]));
    node->father = father;
    node->left_son = sortedArrayToAVLtree(infoArr, keyArr,start, mid -1, node);
    node->right_son = sortedArrayToAVLtree(infoArr,keyArr, mid + 1, end, node);
    node->updateHeight();
    node->updateBF();
    return node;
}

template <class T, class S>
void AVL_node<T,S>::storeInorder(std::shared_ptr<AVL_node<T,S>> avlNode, T inorderInfoArr[], S inorderKeyArr[], int *index_ptr)
{
    if (avlNode == NULL)
        return;

    storeInorder(avlNode->left_son, inorderInfoArr,inorderKeyArr, index_ptr);

    inorderInfoArr[*index_ptr] = avlNode->info;
    inorderKeyArr[*index_ptr] = avlNode->key;
    (*index_ptr)++;

    storeInorder(avlNode->right_son, inorderInfoArr,inorderKeyArr, index_ptr);
}

template <class T, class S>
S * AVL_node<T,S>::merge(T arr1Info[], S arr1Key[],T arr2Info[], S arr2Key[], T mergedInfoArr[],int m, int n)
{
    S *mergedKeyArr = new S[m + n];
    int i = 0, j = 0, k = 0;
    while (i < m && j < n)
    {
        if (arr1Key[i] < arr2Key[j])
        {

            mergedKeyArr[k] = arr1Key[i];
            mergedInfoArr[k] = arr1Info[i];
            i++;
        }
        else
        {
            mergedKeyArr[k] = arr2Key[j];
            mergedInfoArr[k] = arr2Info[j];
            j++;
        }
        k++;
    }
    while (i < m)
    {
        mergedKeyArr[k] = arr1Key[i];
        mergedInfoArr[k] = arr1Info[i];
        i++; k++;
    }
    while (j < n)
    {
        mergedKeyArr[k] = arr2Key[j];
        mergedInfoArr[k] = arr2Info[j];
        j++; k++;
    }
    return mergedKeyArr;
}

template <class T, class S>
void AVL_node<T,S>::InOrderNumTimes(std::shared_ptr<AVL_node<T,S>> avlNode, int Players[], int *numOfPlayers,int count)
{
    if (avlNode == nullptr || *numOfPlayers >= count )
    {
        return;
    }
    if(*numOfPlayers < count  )
    {
        InOrderNumTimes(avlNode->getLeft_son(), Players, numOfPlayers,count);
        if(*numOfPlayers >= count )
        {
            return;
        }
        Players[*numOfPlayers] = avlNode->getInfo().getId();
        (*numOfPlayers)++; // increase index for next entry
        if(*numOfPlayers >= count )
        {
            return;
        }
        InOrderNumTimes(avlNode->getRight_son(), Players, numOfPlayers,count);

    }

}

template <class T, class S>
void AVL_node<T,S>::reverseInOrderNumTimes(std::shared_ptr<AVL_node<T,S>> avlNode, int Players[], int *numOfPlayers,int count)
{
    if (avlNode == nullptr || *numOfPlayers == count)
    {
        return;
    }

    reverseInOrderNumTimes(avlNode->getRight_son(), Players, numOfPlayers,count);

    Players[*numOfPlayers] = avlNode->getInfo().getId();
    (*numOfPlayers)++; // increase index for next entry

    reverseInOrderNumTimes(avlNode->getLeft_son(), Players, numOfPlayers,count);
}

template <class T, class S>
std::shared_ptr<AVL_node<T,S>>  AVL_node<T,S>::getNodeWithBiggestKey(std::shared_ptr< AVL_node<T,S> > root)
{
    std::shared_ptr<AVL_node<T,S>> tmp = root;

    while(tmp->getRight_son() != nullptr)
    {
        tmp = tmp->getRight_son();
    }

    return tmp;

}

template <class T, class S>
void AVL_node<T,S>::setInfo(T new_info)
{
    this->info = new_info;
}

template <class T, class S>
int AVL_node<T,S>::getBF()
{
    return this->BF;
}

template <class T, class S>
T& AVL_node<T,S>::getInfo()
{
    return this->info;
}

template <class T, class S>
S AVL_node<T,S>::getKey()
{
    return this->key;
}

template <class T, class S>
int AVL_node<T,S>::getHeight()
{
    return this->height;
}

template <class T, class S>
int AVL_node<T,S>::max(int h1, int h2){
    if(h1 < h2){
        return h2;
    }
    return h1;
}
template <class T, class S>
void AVL_node<T,S>::updateHeight(){

    int left_height = -1  ;
    if(this->getLeft_son() != nullptr){
        left_height = this->getLeft_son()->getHeight();
    }

    int right_height = -1;
    if(this->getRight_son() != nullptr)
    {
        right_height = this->getRight_son()->getHeight();
    }
    this->height = 1+max(left_height, right_height);

}

template <class T, class S>
void AVL_node<T,S>::updateBF(){

    int left_height = -1  ;
    if(this->getLeft_son() != nullptr){
        left_height = this->getLeft_son()->getHeight();
    }

    int right_height = -1;
    if(this->getRight_son() != nullptr)
    {
        right_height = this->getRight_son()->getHeight();
    }
    this->BF = left_height - right_height;
}



template <class T, class S>
std::shared_ptr<AVL_node<T,S>> AVL_node<T,S>::getFather()
{
    return this->father;
}

template <class T, class S>
std::shared_ptr<AVL_node<T,S>> AVL_node<T,S>::getLeft_son()
{
    return left_son;
}

template <class T, class S>
std::shared_ptr<AVL_node<T,S>> AVL_node<T,S>::getRight_son()
{
    return right_son;
}


template<class T,class S>
AVL_node<T,S>::AVL_node(const AVL_node<T,S>& other) : BF(other.BF) ,info(other.info), key(other.key), height(other.height),
                                                      father(other.father), left_son(other.left_son), right_son(other.right_son) {} // copy constructor



template<class T,class S>
AVL_node<T,S>& AVL_node<T,S>::operator=(const AVL_node<T,S>& other)
{
    BF = other.BF;
    info = other.info;
    key = other.key;
    height = other.height;
    father = other.father;
    left_son = other.left_son;
    right_son=other.right_son;

    return *this;
}



template<class T,class S>
std::shared_ptr<AVL_node<T,S>> AVL_node<T,S>::insert(std::shared_ptr< AVL_node<T,S> > root,S key,T info)
{
    if(root == nullptr)
    {
        std::shared_ptr<AVL_node<T,S>> root = (std::make_shared<AVL_node>(key,info));
        return root;
    }
    if(key < root->key)
    {
        root->left_son = insert(root->getLeft_son(), key, info);
        if(root->getLeft_son()->key == key)
        {
            root->left_son->father = root;
        }
    }
    if(key > root->key)
    {

        root->right_son = insert(root->getRight_son(), key, info);
        if(root->right_son->key == key)
        {
            root->right_son->father = root;
        }
    }
    return root;
}

template<class T,class S>
std::shared_ptr<AVL_node<T,S>>  AVL_node<T,S>::treeBalance(std::shared_ptr<AVL_node<T,S>> avl_node) // where to get avlnode from?
{
    if(avl_node->father)
    {
        avl_node->father->updateHeight();
        avl_node->father->updateBF();
        if(avl_node->father->father)
        {
            avl_node->father->father->updateHeight();
            avl_node->father->father->updateBF();
        }
    }
    std::shared_ptr<AVL_node<T,S>> tmp = avl_node;
    while(avl_node != nullptr)
    {
        avl_node->updateHeightAndBF();   ///change function's name
        int bf = avl_node->BF;
        if( bf == INVALID_BF )
        {
            if(avl_node->getLeft_son()->getBF() == -1)
            {
                std::shared_ptr<AVL_node<T,S>> trash = leftRotation(avl_node->left_son); // LR
            }
            avl_node = rightRotation(avl_node); //LL
        }
        if(bf == -INVALID_BF)
        {
            if(avl_node->getRight_son()->getBF() == 1)
            {
                std::shared_ptr<AVL_node<T,S>> trash = rightRotation(avl_node->right_son); // RL
            }
            avl_node = leftRotation(avl_node); //RR
        }
        avl_node->updateHeightAndBF();
        tmp = avl_node;
        avl_node= avl_node->father;
    }
    return tmp;
}

template<class T,class S>
std::shared_ptr<AVL_node<T,S>> AVL_node<T,S>::leftRotation(std::shared_ptr<AVL_node<T,S>> root)
{
    std::shared_ptr<AVL_node<T,S>> root_old_father = root->getFather(); // check if father is equal to NULL
    std::shared_ptr<AVL_node<T,S>> new_root = root->getRight_son();
    std::shared_ptr<AVL_node<T,S>> new_root_left_son = new_root->getLeft_son();     // chaged from root->getFather() to

    if(root_old_father != nullptr)
    {

        if(root_old_father->getLeft_son() == root)
        {
            root_old_father->left_son = new_root;

        }

        if(root_old_father->getRight_son() == root)
        {
            root_old_father->right_son = new_root;
        }

    }
    new_root->father = root_old_father;

    root->father = new_root;
    new_root->left_son = root;

    root->right_son = new_root_left_son;
    if(new_root_left_son != nullptr){
        new_root_left_son->father = root;

    }
    return new_root;

}

template<class T,class S>
std::shared_ptr<AVL_node<T,S>> AVL_node<T,S>::rightRotation(std::shared_ptr<AVL_node<T,S>> root)
{
    std::shared_ptr<AVL_node<T,S>> root_old_father = root->getFather();
    std::shared_ptr<AVL_node<T,S>> new_root = root->getLeft_son();
    std::shared_ptr<AVL_node<T,S>> new_root_right_son = new_root->getRight_son();

    if(root_old_father != nullptr)
    {

        if(root_old_father->getLeft_son() == root)
        {
            root_old_father->left_son = new_root;

        }

        if(root_old_father->getRight_son() == root)
        {
            root_old_father->right_son = new_root;
        }

    }

    new_root->father = root_old_father;

    root->father = new_root;
    new_root->right_son = root;

    root->left_son = new_root_right_son;
    if(new_root_right_son != nullptr)
    {
        new_root_right_son->father = root;
    }

    return new_root;
}


template<class T,class S>
std::shared_ptr<AVL_node<T,S>> AVL_node<T,S>::find(std::shared_ptr<AVL_node<T,S>> root,S key)
{
    std::shared_ptr<AVL_node<T,S>> tmp = root;


    while(tmp != nullptr)
    {
        if(tmp->key == key)
        {
            return tmp;
        }
        if(tmp->key < key)
        {
            tmp = tmp->right_son;
        }
        else
        {
            tmp = tmp->left_son;
        }
    }
    return nullptr;
}

template<class T,class S>
std::shared_ptr<AVL_node<T,S>> AVL_node<T,S>::deleteNode(std::shared_ptr<AVL_node<T,S>> root, S key)
{
    if(!root)
    {
        return nullptr;
    }
    std::shared_ptr<AVL_node<T,S>> node_to_delete = root->find(root ,key);

    if(node_to_delete == nullptr)
    {
        return root;
    }

    if(node_to_delete->left_son == NULL ||node_to_delete->right_son == NULL)
    {

        return deleteNodeHelper(node_to_delete,root);

    }
    else
    {
        std::shared_ptr<AVL_node<T,S>> NextInOrderVal = node_to_delete->getNextInOrderVal();
        swapNodes(node_to_delete, NextInOrderVal);
        swapHeightAndBF(node_to_delete, NextInOrderVal);

        return deleteNodeHelper(node_to_delete,root);
    }

    return root; // not supposed to get here bcus all option are taken care of

}

template<class T,class S>
void AVL_node<T,S>::swapNodes(std::shared_ptr<AVL_node<T,S>> node_to_delete,std::shared_ptr<AVL_node<T,S>> NextInOrderVal)
{
    std::shared_ptr<AVL_node<T,S>> node_to_delete_father = node_to_delete->father;
    std::shared_ptr<AVL_node<T,S>> node_to_delete_right_son = node_to_delete->right_son;
    std::shared_ptr<AVL_node<T,S>> node_to_delete_left_son = node_to_delete->left_son;

    std::shared_ptr<AVL_node<T,S>>  NextInOrderVal_father= NextInOrderVal->father;
    std::shared_ptr<AVL_node<T,S>>  NextInOrderVal_right_son= NextInOrderVal->right_son;
    std::shared_ptr<AVL_node<T,S>>  NextInOrderVal_left_son= NextInOrderVal->left_son;

    //********************************************************
    NextInOrderVal->father = node_to_delete_father;
    node_to_delete->right_son = NextInOrderVal_right_son;
    node_to_delete->left_son = NextInOrderVal_left_son;
    NextInOrderVal->left_son = node_to_delete_left_son;
    node_to_delete_left_son->father = NextInOrderVal;
    //********************************************************


    //if NTD has father or not
    if(node_to_delete_father == nullptr)
    {
        //if there is straight-connection or not
        if(node_to_delete_right_son == NextInOrderVal) //straight-connection Next is NTD right son
        {
            //********************************************************
            NextInOrderVal->right_son = node_to_delete;
            node_to_delete->father = NextInOrderVal;
            //********************************************************

            //if Next has a right son or not
            if(NextInOrderVal_right_son != nullptr) // Next has right son
            {
                NextInOrderVal_right_son->father = node_to_delete;
            }
        }
        else // Next is his father's left son
        {
            //********************************************************
            NextInOrderVal->right_son = node_to_delete_right_son;
            node_to_delete->father = NextInOrderVal_father;
            NextInOrderVal_father->left_son = node_to_delete;
            node_to_delete_right_son->father = NextInOrderVal;
            //********************************************************

            //if Next has a right son or not
            if(NextInOrderVal_right_son != nullptr) // Next has right son
            {
                NextInOrderVal_right_son->father = node_to_delete;
            }
        }
    }
    else // NTD HAS a father
    {
        if(node_to_delete_father->right_son == node_to_delete) // NTD is his fathers right
        {
            //if there is straight-connection or not
            if(node_to_delete_right_son == NextInOrderVal) //straight-connection
            {
                //********************************************************
                NextInOrderVal->right_son = node_to_delete;
                node_to_delete->father = NextInOrderVal;
                node_to_delete_father->right_son = NextInOrderVal;
                //********************************************************

                //if Next has a right son or not
                if(NextInOrderVal_right_son != nullptr) // Next has right son
                {
                    NextInOrderVal_right_son->father = node_to_delete;
                }
            }
            else // Next is his father's left son
            {
                //********************************************************
                NextInOrderVal->right_son = node_to_delete_right_son;
                node_to_delete->father = NextInOrderVal_father;
                NextInOrderVal_father->left_son = node_to_delete;
                node_to_delete_right_son->father = NextInOrderVal;
                node_to_delete_father->right_son = NextInOrderVal;
                //********************************************************

                //if Next has a right son or not
                if(NextInOrderVal_right_son != nullptr) // Next has right son
                {
                    NextInOrderVal_right_son->father = node_to_delete;
                }
            }
        }
        else // NTD is his fathers left
        {
            //if there is straight-connection or not
            if(node_to_delete_right_son == NextInOrderVal) //straight-connection
            {
                //********************************************************
                NextInOrderVal->right_son = node_to_delete;
                node_to_delete->father = NextInOrderVal;
                node_to_delete_father->left_son = NextInOrderVal;
                //********************************************************

                //if Next has a right son or not
                if(NextInOrderVal_right_son != nullptr) // Next has right son
                {
                    NextInOrderVal_right_son->father = node_to_delete;  // (*)
                }
            }
            else // Next is his father's left son
            {
                //********************************************************
                NextInOrderVal->right_son = node_to_delete_right_son;
                node_to_delete->father = NextInOrderVal_father;
                NextInOrderVal_father->left_son = node_to_delete;
                node_to_delete_right_son->father = NextInOrderVal;
                node_to_delete_father->left_son = NextInOrderVal;
                //********************************************************

                //if Next has a right son or not
                if(NextInOrderVal_right_son != nullptr) // Next has right son
                {
                    NextInOrderVal_right_son->father = node_to_delete;
                }
            }
        }
    }

    node_to_delete_father = nullptr;
    node_to_delete_right_son = nullptr;
    node_to_delete_left_son = nullptr;

    NextInOrderVal_father= nullptr;
    NextInOrderVal_right_son= nullptr;
    NextInOrderVal_left_son= nullptr;

}

template<class T,class S>
void AVL_node<T,S>::swapHeightAndBF(std::shared_ptr<AVL_node<T,S>> node_to_delete,std::shared_ptr<AVL_node<T,S>> NextInOrderVal)
{
    int tmp_height = node_to_delete->height;
    int tmp_BF = node_to_delete->BF;

    node_to_delete->height = NextInOrderVal->height;
    node_to_delete->BF = NextInOrderVal->BF;

    NextInOrderVal->height = tmp_height;
    NextInOrderVal->BF = tmp_BF;
}


template<class T,class S>
std::shared_ptr<AVL_node<T,S>> AVL_node<T,S>::getNextInOrderVal()
{
    std::shared_ptr<AVL_node<T,S>> tmp = this->right_son;
    while(tmp->left_son !=nullptr)
    {
        tmp = tmp->left_son;

    }
    return tmp;
}

template<class T,class S>
void AVL_node<T,S>::SwapInfoAndKey(std::shared_ptr<AVL_node<T,S>> avl_node)
{
    S tmp_key = this->key;
    T tmp_info = this->info;

    this->key = avl_node->key;
    this->info = avl_node->info;

    avl_node->key = tmp_key;
    avl_node->info = tmp_info;

}

template<class T,class S>
template<class DoSomething>
void AVL_node<T,S>::inOrder(std::shared_ptr<AVL_node<T,S>> root, DoSomething doSomething)
{
    if(root == nullptr)
    {
        return;
    }
    inOrder(root->left_son, doSomething);
    doSomething(root);
    inOrder(root->right_son, doSomething);
}

template<class T,class S>
void AVL_node<T,S>::updateHeightAndBF()
{
    if(this->left_son != nullptr)
    {
        this->left_son->updateHeight();
        this->left_son->updateBF();
    }
    if(this->right_son != nullptr)
    {
        this->right_son->updateHeight();
        this->right_son->updateBF();
    }

    this->updateHeight();
    this->updateBF();

}


template<class T,class S>
template<class DoSomething>
void AVL_node<T,S>::preOrder(std::shared_ptr<AVL_node<T,S>> root, DoSomething doSomething)
{
    if(root == nullptr) return;

    doSomething(root);
    preOrder(root->left_son,doSomething);
    preOrder(root->right_son, doSomething);

}


template<class T,class S>
void AVL_node<T,S>::postOrderAndDestroy(std::shared_ptr<AVL_node<T,S>> root)
{
    if(root == nullptr) return;
    postOrderAndDestroy(root->left_son);
    postOrderAndDestroy(root->right_son);
    root->NodePointSiblingsToNull(root);
}


template<class T,class S>
void AVL_node<T,S>::NodePointSiblingsToNull(const std::shared_ptr<AVL_node<T,S>>& root)
{
    root->left_son = NULL;
    root->right_son= NULL;
    root->father = NULL;
}


template<class T,class S>
void AVL_node<T,S>::printBFAndHeight()
{
    std::cout << this->BF<<" " << this->height << std::endl;
    std::cout << " **************** " << std::endl;
}


template<class T,class S>
std::shared_ptr<AVL_node<T,S>> AVL_node<T,S>::deleteNodeHelper(std::shared_ptr<AVL_node<T,S>> node_to_delete, std::shared_ptr<AVL_node<T,S>> root)
{

    std::shared_ptr<AVL_node<T,S>> tmp = node_to_delete->left_son ? node_to_delete->left_son :
                                         node_to_delete->right_son ;

    std::shared_ptr<AVL_node<T,S>> node_to_delete_father = node_to_delete->father;
    if(tmp == nullptr) //no children
    {
        if(node_to_delete->father == nullptr) // we are at root
        {
            root = nullptr;
            return nullptr;
        }
        else  //leaf
        {
            //std::shared_ptr<AVL_node<T,S>> node_to_delete_father = node_to_delete->get().father;
            if(node_to_delete->father->left_son == node_to_delete)
            {
                node_to_delete->father->left_son = nullptr;
            }
            else
            {
                node_to_delete->father->right_son = nullptr;
            }

            node_to_delete->father = nullptr;
            root = node_to_delete_father->treeBalance(node_to_delete_father);
            // update height and bf for all nodes in the searching path and treeBalance
            return root;
        }
    }
    else if(node_to_delete->left_son != nullptr)  //one child case (left son)
    {
        if(node_to_delete->father == nullptr) // we are at root
        {
            root = node_to_delete->left_son;
            root->father = nullptr;
            node_to_delete->left_son = nullptr;
            return root;  //child height and bf doesnt change
        }
        if(node_to_delete->father->left_son == node_to_delete)
        {
            node_to_delete->father->left_son = node_to_delete->left_son;
        }
        else
        {
            node_to_delete->father->right_son = node_to_delete->left_son;
        }
        node_to_delete->left_son->father =  node_to_delete->father;
        node_to_delete->left_son = nullptr;
        node_to_delete->father = nullptr;

        root = node_to_delete_father->treeBalance(node_to_delete_father);
        // update height and bf for all nodes in the searching path and treeBalance
        return root;

    }
    else if(node_to_delete->right_son != nullptr)  //one child case (right son)
    {
        if(node_to_delete->father == nullptr) // we are at root
        {
            root = root->right_son;
            root->father = nullptr;
            node_to_delete->right_son = nullptr;
            return root; //child height and bf doesnt change
        }

        if(node_to_delete->father->left_son == node_to_delete)
        {
            node_to_delete->father->left_son = node_to_delete->right_son;
        }
        else
        {
            node_to_delete->father->right_son = node_to_delete->right_son;
        }
        node_to_delete->right_son->father =  node_to_delete->father;
        node_to_delete->right_son = nullptr;
        node_to_delete->father = nullptr;

        root = node_to_delete_father->treeBalance(node_to_delete_father);
        // update height and bf for all nodes in the searching path and treeBalance
        return root;
    }

    return root;
}

template<class T,class S>
std::shared_ptr<AVL_node<T,S>> AVL_node<T,S>::clone(const std::shared_ptr<AVL_node<T,S>> root
        , const std::shared_ptr<AVL_node<T,S>> parent)
{

    if(root == nullptr)
    {
        return nullptr;
    }

    std::shared_ptr<AVL_node<T,S>> temp = (std::make_shared<AVL_node>(*root));
    temp->key  = root->key;
    temp->info = root->info;
    temp->father = parent;
    temp->left_son = clone(root->left_son,temp);
    temp->right_son = clone(root->right_son, temp);
    return temp;

}

#endif
