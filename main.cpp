//
// Created by omarm on 01/01/2022.
//
#include "AVLnode.h"

 void printNode(const std::shared_ptr<AVL_node<int,int>>& root){
    if(root== nullptr)
    {
        std::cout << "nullptr" ;
    }
    else
    {
        std::cout << root->getKey() << " " ;
    }


 }

//void printNode(const std::shared_ptr<AVL_node<player,LevelAndId>>& root)
//{
//    std::cout<< "(" << root->getKey().getLevel() << " , "<< root->getKey().getId()<< ")" << "  " ;
//}

int main()
{
    //****************************************************************
    //check that clone really creates a new tree thats not related to the tree thats being cloned

     std::shared_ptr<AVL_node<int,int>> root;

     root = root->insert(root,2,2);
     root = root->treeBalance(root->find(root,2));
     root = root->insert(root,1,1);
     root = root->treeBalance(root->find(root,1));
     root = root->insert(root,5,5);
     root = root->treeBalance(root->find(root,5));
     root = root->insert(root,6,6);
     root = root->treeBalance(root->find(root,6));
     root = root->insert(root,7,7);
     root = root->treeBalance(root->find(root,7));
     root = root->insert(root,10,10);
     root = root->treeBalance(root->find(root,10));
     root = root->insert(root,3,3);
     root = root->treeBalance(root->find(root,3));


//    std::shared_ptr<AVL_node<int,int>> root2;
//    root2 = root2->insert(root2,12,12);
//    root2 = root2->treeBalance(root2->find(root2,12));
//    root2 = root2->insert(root2,11,11);
//    root2 = root2->treeBalance(root2->find(root2,11));
//    root2 = root2->insert(root2,15,15);
//    root2 = root2->treeBalance(root2->find(root2,15));
//    root2 = root2->insert(root2,16,16);
//    root2 = root2->treeBalance(root2->find(root2,16));
//    root2 = root2->insert(root2,17,17);
//    root2 = root2->treeBalance(root2->find(root2,17));
//    root2 = root2->insert(root2,110,110);
//    root2 = root2->treeBalance(root2->find(root2,110));
//    root2 = root2->insert(root2,13,13);
//    root2 = root2->treeBalance(root2->find(root2,13));
//
//
//    int arr[14];
//    std::shared_ptr<AVL_node<int,int>> root3 = root->mergeAvlTrees(root,root2,arr,7,7);


//     root->inOrder(root3,printNode);
//     std::cout << std::endl ;
//     root->preOrder(root3,printNode);

//    std::shared_ptr<AVL_node<int,int>> node = root3->select(root3,7);

//    std::shared_ptr<AVL_node<int,int>> node = root->findClosestNodeFromAbove(root,0);


    std::shared_ptr<AVL_node<int,int>> node = root->select(root,5);
    printNode(node);
    std::cout << root->findSumOfMHighestLevels(root, node) << std::endl ;

    std::cout << std::endl ;
     std::cout << "****************************************************************************************************" ;
     std::cout << std::endl ;

//     root2->inOrder(root2,printNode);
//     std::cout << std::endl ;
//     root2->preOrder(root2,printNode);

     root->postOrderAndDestroy(root);
//     root2->postOrderAndDestroy(root2);

    //****************************************************************

    return 0;
}
