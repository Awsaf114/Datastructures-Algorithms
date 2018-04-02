#include<stdio.h>
#include<stdlib.h>
#include<iostream>

#define FALSE_VALUE 0
#define TRUE_VALUE 1
#define RED 100
#define BLACK -100

using namespace std;

struct treeNode
{
    int item;
    int Color;
    struct treeNode * left; //points to left child
    struct treeNode * right; //points to right child
    struct treeNode * parent; // points to parent
};

struct treeNode * root;


void initializeTree()
{
    root = 0;
}


struct treeNode * searchItem(struct treeNode * node, int item)
{
    if(node==0) return 0;
    if(node->item==item) return node; //found, return node
    struct treeNode * t = 0;
    if(item < node->item)
        t = searchItem(node->left, item); //search in the left sub-tree
    else
        t = searchItem(node->right, item); //search in the right sub-tree
    return t;
};


struct treeNode * makeTreeNode(int item)
{
    struct treeNode * node ;
    node = (struct treeNode *)malloc(sizeof(struct treeNode));
    node->Color = RED;
    node->item = item;
    node->left = 0;
    node->right = 0;
    node->parent = 0;
    return node;
};

struct treeNode * leftrotate(struct treeNode *node)
{
    struct treeNode *y = node->right;
    node->right = y->left;
    if(y->left !=0)
        y->left->parent = node;
    y->parent = node->parent;
    if(node->parent == 0)
        root = y;
    else if(node == node->parent->left)
        node->parent->left = y;
    else
        node->parent->right = y;

    y->left = node;
    node->parent = y;

    return node;

}

struct treeNode * rightrotate(struct treeNode *node)
{
    struct treeNode *y = node->left;
    node->left = y->right;
    if(y->right !=0)
        y->right->parent = node;
    y->parent = node->parent;
    if(node->parent == 0)
        root = y;
    else if(node == node->parent->left)
        node->parent->left = y;
    else
        node->parent->right = y;

    y->right = node;
    node->parent = y;

    return node;

}



struct treeNode * insertItemFixup(struct treeNode *node)
{
    if(node->parent == 0){
        node->Color = BLACK;
        return node;
    }

    while(node->parent!=0 && node->parent->Color == RED){
        struct treeNode *parent = node->parent;
        struct treeNode *grandParent = parent->parent;

        //Case 1: z is the right subtree
        if(grandParent->left == parent ){
            struct treeNode *uncle = grandParent->right;
            if(uncle == 0){
                if(node == parent->right){
                    node = leftrotate(parent);
                }
                node->parent->Color = BLACK;
                node->parent->parent->Color = RED ;
                rightrotate(node->parent->parent);
            }
            else{
                if(grandParent->right->Color == BLACK){
                    if(node == parent->right){
                        node = leftrotate(parent);
                    }
                    node->parent->Color = BLACK;
                    node->parent->parent->Color = RED ;
                    rightrotate(node->parent->parent);
                }
                else{
                    parent->Color = BLACK;
                    grandParent->Color = RED;
                    uncle->Color = BLACK;
                    node = grandParent;

                }
            }
        }
        else{
            struct treeNode *uncle = grandParent->left;
            if(uncle == 0){
                if(node == parent->left){
                    node = rightrotate(parent);
                }

                node->parent->Color = BLACK;
                node->parent->parent->Color = RED ;
                leftrotate(node->parent->parent);
            }
            else{
                if(uncle->Color == BLACK){

                    if(node == parent->left){
                    node = rightrotate(parent);
                    }
                    node->parent->Color = BLACK;
                    node->parent->parent->Color = RED ;
                    leftrotate(node->parent->parent);
                }
                else{
                    parent->Color = BLACK;
                    grandParent->Color = RED;
                    uncle->Color = BLACK;
                    node = grandParent;
//                    cout<<"Left"<<node->parent;

                }
            }

        }

    }
    root->Color = BLACK;
    return node;
}


struct treeNode * insertItem(struct treeNode *node, int item)
{
    if(node==0) //insert as the root as the tree is empty
    {
        struct treeNode * newNode = makeTreeNode(item);
        root = newNode;
        root->Color = BLACK;
        return newNode;
    }

//    if(node->item==item) return 0; //already an item exists, so return NULL

    if(item < node->item && node->left==0) //insert as the left child
    {
        struct treeNode * newNode = makeTreeNode(item);
        node->left = newNode;
        newNode->parent = node;
        newNode = insertItemFixup(newNode);
        return newNode;
    }

    if(item >= node->item && node->right==0) //insert as the right child
    {
        struct treeNode * newNode = makeTreeNode(item);
        node->right = newNode;
        newNode->parent = node;
        newNode = insertItemFixup(newNode);
        return newNode;
    }
    if(item == node->item && node->right!=0) //insert as the right child
    {
        struct treeNode * newNode = makeTreeNode(item);
        struct treeNode * tmp = node->right;
        node->right = newNode;
        newNode->right = tmp;
        newNode->parent = node;
        tmp->parent = newNode;
        newNode = insertItemFixup(newNode);
        return newNode;
    }

    if(item < node->item)  /// Recursive definition to traverse to end of tree shifting right or left
        return insertItem(node->left, item); //insert at left sub-tree
    else
        return insertItem(node->right, item); //insert at right sub-tree

}


void reColor(struct treeNode *node)
{
    if(node==0) return;
    if(node->Color == RED)
        node->Color = BLACK;
    else
        node->Color = RED;
}

int calcNodeHeight(struct treeNode * node) ///return height of a node
{
    if(node==0) return -1;
    int l, r;
    l = calcNodeHeight(node->left);
//    printf("%d  %d\n",l,r);
    r = calcNodeHeight(node->right);
//    printf("%d  %d\n",l,r);
    if(l>r) return l+1;
    else return r+1;
}


int calcHeight(int item) ///return height of an item in the tree
{
    struct treeNode * node = 0;
    node = searchItem(root, item);
    if(node==0) return -1; //not found
    else return calcNodeHeight(node);
}

int getSize(struct treeNode * node)
{
    if(node==0) return 1;

    //print left sub-tree
    int sl = getSize(node->left);

//    printf("%03d\n",node->item);

    int sr = getSize(node->right);
    return sl+sr;
}

int calcNodeDepth(struct treeNode * node) //return depth of a node
{
    if( node == root)
        return 0;
    struct treeNode *snode = root;
    int count =0;
    while(snode!=0){
    if(snode->item==node->item) return count; //found, return node

    if(snode->item < node->item){
        snode = snode->right;
        count++;
    }
    else{
        snode = snode->left;
        count++;
    }

    }
    return count;

}

int calcDepth(int item)//return depth of an item in the tree
{
    struct treeNode * node = 0;
    node = searchItem(root, item);
    if(node==0) return -1; //not found
    else return calcNodeDepth(node);
}

struct treeNode * deleteFixUp(struct treeNode *node, struct treeNode *parent ){
    while(node==0 && node!= root){
//        cout<<"Empty Node";
        if(parent->left != 0){
            struct treeNode * sibling = parent->left;
            if(sibling->Color == BLACK && parent->Color == RED){
                parent->Color = BLACK;
                sibling->Color = RED;
                return sibling;
            }
            if(sibling->Color == RED){
                sibling->Color = BLACK;
                parent->Color = RED;
                parent = leftrotate(parent);
                sibling = parent->right;
            }
            if(sibling->left == 0 && sibling->right == 0){
                sibling->Color = RED;
                sibling = parent;
            }
            else if(sibling->left != 0 && sibling->right != 0){
                if(sibling->left->Color == BLACK && sibling->right->Color == BLACK){
                    sibling->Color = RED;
                    sibling = node->parent;
                }
                else{
                if(sibling->right->Color == BLACK){
                    sibling->left->Color = BLACK;
                    sibling->Color = RED;
                    rightrotate(sibling);
                    sibling = parent->right;
                }
                sibling->Color = parent->Color;
                parent->Color = BLACK;
                sibling->right->Color = BLACK;
                parent = leftrotate(parent);
                node = root;
                }
            }
            else{
                if(sibling->right == 0){

                }
            }



        }
        else if(parent ->right != 0){
            struct treeNode * sibling = parent->right;
            if(sibling->Color == RED){
                sibling->Color = BLACK;
                parent->Color = RED;
                parent = leftrotate(parent);
                sibling = parent->right;

            }
            else{
                if(sibling->left == 0 && sibling->right == 0){
                    sibling->Color = RED;
                    sibling = parent;
                }
                else if(sibling->left == 0 && sibling->right !=0){
                    if(sibling->right->Color == BLACK){
                        sibling->Color = RED;
                        node = parent;
                    }
                    else{
                        sibling->Color = parent->Color;
                        parent->Color = BLACK;
                        parent = leftrotate(parent);
                        node = root;
                    }
                }
                else if(sibling->left != 0 && sibling->right == 0){
                    if(sibling->left->Color == BLACK){ ///Case 2
                        sibling->Color = RED;
                        node = parent;
                    }
                    else{ ///Case 3
                        sibling->left->Color = BLACK;
                        sibling->Color = RED;
                        sibling = parent->right;
                    }
                }
                else{
                    if(sibling->left->Color == BLACK && sibling->right->Color == BLACK){
                        sibling->Color = RED;
                        node = parent;
                    }
                }

            }
        }
        else{
            parent->Color = BLACK;
            parent = leftrotate(parent);
            node = root;
        }
        return node;
    }

    while(node->Color == BLACK && node != root){
        cout<<"Fixup loop\n";
        parent = node->parent;
        if(node == parent->left){
            struct treeNode * sibling = parent->right;
            if(sibling->Color == RED){
                sibling->Color = BLACK;
                parent->Color = RED;
                parent = leftrotate(parent);
                sibling = parent->right;
            }
            if(sibling->left == 0 && sibling->right == 0){
                sibling->Color = RED;
                sibling = parent;
            }
            else if(sibling->left == 0 && sibling->right != 0 ){
                if(sibling->right->Color == BLACK){
                    sibling->Color = RED;
                    sibling = parent;
                }
                else{
                    sibling->Color = parent->Color;
                    parent->Color = BLACK;
                    sibling->right->Color = BLACK;
                    parent = leftrotate(parent);
                    node = root;
                }
            }
            else if ( sibling->right ==0 && sibling->left !=0){
                if(sibling->left->Color == BLACK){
                    sibling->Color = RED;
                    sibling = parent;
                }
                else{
                    sibling->left->Color = BLACK;
                    sibling->Color = RED;
                    rightrotate(sibling);
                    sibling = parent->right;

                    sibling->Color = parent->Color;
                    parent->Color = BLACK;
                    sibling->right->Color = BLACK;
                    parent = leftrotate(parent);
                    node = root;
                }
            }
            else{
                if(sibling->left->Color == BLACK && sibling->right->Color == BLACK){
                sibling->Color = RED;
                sibling = node->parent;
                }
                else{
                    if(sibling->right->Color == BLACK){ /// sibling left color = RED
                        sibling->left->Color = BLACK;
                        sibling->Color = RED;
                        rightrotate(sibling);
                        sibling = parent->right;
                    }
                    sibling->Color = parent->Color;/// sibling right= red, left==black | both red
                    parent->Color = BLACK;
                    sibling->right->Color = BLACK;
                    parent = leftrotate(parent);
                    node = root;
                }
            }
        }
        else{
            struct treeNode * sibling = parent->left;
            if(sibling->Color == RED){
                sibling->Color = BLACK;
                parent->Color = RED;
                parent = leftrotate(parent);
                sibling = parent->right;
            }
            if(sibling->left == 0 && sibling->right == 0){
                sibling->Color = RED;
                sibling = parent;
            }
            else if(sibling->left == 0 && sibling->right != 0 ){
                if(sibling->right->Color == BLACK){
                    sibling->Color = RED;
                    sibling = parent;
                }
                else{
                    sibling->Color = parent->Color;
                    parent->Color = BLACK;
                    sibling->right->Color = BLACK;
                    parent = rightrotate(parent);
                    node = root;
                }
            }
            else if ( sibling->right ==0 && sibling->left !=0){
                if(sibling->left->Color == BLACK){
                    sibling->Color = RED;
                    sibling = parent;
                }
                else{
                    sibling->left->Color = BLACK;
                    sibling->Color = RED;
                    leftrotate(sibling);
                    sibling = parent->left;

                    sibling->Color = parent->Color;
                    parent->Color = BLACK;
                    sibling->right->Color = BLACK;
                    parent = rightrotate(parent);
                    node = root;
                }
            }
            else{
                if(sibling->left->Color == BLACK && sibling->right->Color == BLACK){
                sibling->Color = RED;
                sibling = node->parent;
                }
                else{
                    if(sibling->right->Color == BLACK){ /// sibling left color = RED
                        sibling->left->Color = BLACK;
                        sibling->Color = RED;
                        leftrotate(sibling);
                        sibling = parent->left;
                    }
                    sibling->Color = parent->Color;/// sibling right= red, left==black | both red
                    parent->Color = BLACK;
                    sibling->right->Color = BLACK;
                    parent = rightrotate(parent);
                    node = root;
                }
            }
        }

    }
    node->Color = BLACK;
    return node;
}

struct treeNode* RBSuccessor(struct treeNode * node, int item) {
     //otherwise, go to right child, and then all left children
     struct treeNode * succ, * t;
     if( node->right != 0 ){
        succ = node->right ;
        while( succ->left!=0 ){
            succ = succ->left ;
        }
        return succ ;
    }
    else  {
    //search the item, during searching, track the successor
    succ = 0 ;
    t = root ;
    while( t!= 0 ){
        if (node->item == t->item ){
            return succ ;
        }
        else if (node->item < t->item ){
            succ = t ;
            t = t->left ;
        }
        else {
            t = t->right ;
        }
    }
    return 0 ;
    }
}

struct treeNode * Successor(struct treeNode *node , int item){

    if(node==0) return node;

    //left sub-tree
    Successor(node->left , item);
    cout<<node->item<<" ";
    if(node->item == item && node->right != 0){
        if(node->right->item == item){return node->right;}
//        else{ Successor(node->right , node->item);}
    }
    else if(node->item == item && node->right == 0){
        return node;
    }
     if(node->item > item && node->right != 0){
            return node;
//        Successor(node , node->item);
    }
    else if(node->item >item && node->right == 0){
//        cout<<"break"<<endl;
        return node;
    }

    //right sub-tree
    Successor(node->right, item);

//    struct treeNode * tmp = node;
//    tmp = tmp->right;
//    if(tmp == 0){return node;}
//    else if(tmp->item == item){return tmp;}
//    else{
//        while(true){
//            if(tmp->right == 0){return tmp;}
//            else{
//                if(tmp->left == 0)
//
//            }
//        }
//
//    }


}

int RBdeleteItem(struct treeNode * node, int item)
{
    struct treeNode * res = 0;
    res = searchItem(node, item);
    if(res==0){
        return 0;
    }

    bool flag = false;
    struct treeNode * r = node;
    struct treeNode * temp = 0;
    struct treeNode * par = 0;
//    temp = node;
    node = res;
    if(node == 0){return 1;}

    if(node->left == 0 || node->right == 0){
        r = node;
        flag = true;
    }
    else{
        r = RBSuccessor(node , node->item); ///internal node
    }
    cout<<r->item<<endl;
    if(r->left != 0 ){
        temp = r->left;
        temp->parent = r->parent;
        par = temp->parent;
    }
    else if(r->right !=0){
        temp = r->right;
        temp->parent = r->parent;
        par = temp->parent;
    }
    else{
        par = r->parent;
//        temp = r;
    }
    if(r->parent == 0){
        root = temp;

    }
    else if( r == r->parent->left){
        r->parent->left = temp;
    }
    else{
        r->parent->right = temp;
    }
    if( r != node){
        node->item = r->item;
    }
    if(r->Color == BLACK){
        deleteFixUp(temp , par);
    }

    free(r);

    return 1;

}



int deleteItem(struct treeNode * node, int item)
{
//    struct treeNode * res = searchItem(node, item);
    struct treeNode * res = 0;
    res = searchItem(node, item);
    if(res==0){
        return 0;
    }


    struct treeNode * r = node;
    struct treeNode * temp;
    temp = node;

    if(node == 0){return 1;}

    while(r!=0){

    if(item < r->item){
        temp = r;
        r = r->left;
    }
    else if(item > r->item){
        temp = r;
        r = r->right;
    }

    if(r->item==item){
            if( (r->right == 0 && r->left == 0) && r == root){
                free(r);
                initializeTree();
                break;
            }
            if(r->left == 0 && r == root){
                root = r->right;
                free(r);
                break;
            }
            if(r->right == 0 && r == root){
                root = r->left;
                free(r);
                break;
            }
            if(r->right == 0){ // No right node for root
                if(temp->item >item){ // left node exists
                    temp->left = r->left;
                    free(r);
                    break;

                }
                else{
                    temp->right = r->left;
                    free(r);
                    break;
                }

            }
            else if(r->left == 0){
                if(temp->item >item){ // left node exists
                    temp->left = r->right;
                    free(r);
                    break;

                }
                else{
                    temp->right = r->right;
                    free(r);
                    break;
                }
            }
            else{
                temp = r;
                r = r->right;
                if(r->left == 0){
                        temp->item = r->item;
                    temp->right = r->right;
                    free(r);
                    break;
                }
                else{
                    struct treeNode *t;
                    while(r!=0){
                        t = r;
                        r = r->left;
                    }
                    temp->item = t->item;
                    deleteItem( temp->right, t->item);
                    break;
                }

            }

    }

//    printf("%d\n",temp->item);

}

return 1;

}

int getMinItem() //returns the minimum item in the tree
{
    struct treeNode *node = root;
    if(node == 0) return 0;
    while(node->left !=0){
        node = node->left;
    }
    return node->item;
    //write your codes here
}

int getMaxItem() //returns the maximum item in the tree
{
    struct treeNode *node = root;
    if(node == 0) return 0;
    while(node->right !=0){
        node = node->right;
    }
    return node->item;
    //write your codes here
}

int counter =0;
int rangeSearch(struct treeNode * node, int leftBound, int rightBound) //returns number of items in the
{
    if(leftBound == rightBound) return 1;
    if(node == 0) return 1;
    rangeSearch(node->left, leftBound ,rightBound);

    if(node->item >= leftBound && node->item <= rightBound){
        counter++;
    }
    else if(node->item >= rightBound){
        return counter;
    }
    //print item
//    printf("%03d %d\n",node->item , counter);


    //print right sub-tree
    rangeSearch(node->right, leftBound ,rightBound);

}

void printInOrder(struct treeNode * node, int height)
{
    if(node==0) return ;

    //print left sub-tree
    printInOrder(node->left, height-1);

    //print item
    for(int i=0;i<height;i++)printf("   "); ///Height needed for printing with space
    if(node->Color == RED)
        printf("(%01d,R)\n",node->item);
    else
        printf("(%01d,B)\n",node->item);

    //print right sub-tree
    printInOrder(node->right, height-1);
}
void printLevelOrder(struct treeNode *node , int height , int depth){

    if(node==0) return ;

    //print left sub-tree
    printLevelOrder(node->left, height-1 , depth);

    //print item
    for(int i=0;i<height;i++)printf("   "); ///Height needed for printing with space

    if(node->Color == RED)
        printf("(%01d,-R- %d)\n",node->item, calcDepth(node->item));
    else
        printf("(%01d,-B- %d)\n",node->item , calcDepth(node->item));

    //print right sub-tree
    printLevelOrder(node->right, height-1, depth);

}



int sum =0;
int calcsum(struct treeNode *node){

    if(node==0) return 1;

    //print left sub-tree
    calcsum(node->left);
    sum+= node->item;
//    printf("%03d  %d\n",node->item , sum);

    //print right sub-tree
    calcsum(node->right);

    return sum;

}

int subtreesum(int item){
    struct treeNode * res = 0;
    res = searchItem(root, item);
    if(res==0){
        return -1;
    }

    return calcsum(res);

}

int main(void)
{
    initializeTree();

//    insertItem(root, 10);
//    insertItem(root, 20);
//    insertItem(root, 5);
//    insertItem(root, 3);
//    insertItem(root, 9);
//    insertItem(root, 15);
//    insertItem(root, 20);
//    insertItem(root, 12);

    while(1)
    {
        printf("1. Insert item. 2. Delete item. 3. Search item. \n");
        printf("4. Print height of tree. 5. Print height of an item. \n");
        printf("6. PrintInOrder. 7. exit. 8. getSize. 9. Depth of item.\n");
        printf("10.Minterm. 11. Maxterm. 12. Range Search. 13. Subtreesum 14.LevelOrder\n");


        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            insertItem(root, item);
        }
        else if(ch==2)
        {
            int item;
            scanf("%d", &item);
            if(RBdeleteItem(root, item)){
                printf("Deleted successfully\n");
            }
            else{
                printf("Not found\n");
            }
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            struct treeNode * res = searchItem(root, item);
            if(res!=0) printf("Found.\n");
            else printf("Not found.\n");
        }
        else if(ch==4)
        {
            int height = calcNodeHeight(root);
            printf("Height of tree = %d\n", height);
        }
        else if(ch==5)
        {
            int item;
            scanf("%d", &item);
            int height = calcHeight(item);
            printf("Height of %d = %d\n", item, height);
        }
        else if(ch==6)
        {
            int h = calcNodeHeight(root);
            printf("\n--------------------------------\n",h);
            printInOrder(root, h);
            printf("--------------------------------\n");
        }
        else if(ch==7)
        {
            break;
        }
        else if(ch==8)
        {
            int a = getSize(root);
            printf("Number of nodes : %d \n" ,a-1 );

        }
        else if(ch==9)
        {
            int item;
            scanf("%d",&item);
            int a = calcDepth(item);
            if(a == -1){
                printf("No item\n");
                continue;
            }
            printf("Depth of %d = %d\n",item , a);

        }
        else if(ch==10)
        {
            int a = getMinItem();
            printf("Minimum element = %d\n",a);
        }
        else if(ch==11)
        {
            int a = getMaxItem();
            printf("Maximum element = %d\n",a);
        }
        else if(ch==12)
        {
            counter =0;
            int up , low;
            scanf("%d%d",&up,&low);
            int a = rangeSearch(root , up , low);
            printf("Number of nodes = %d\n",a);

        }
        else if(ch==13)
        {
            sum = 0;
            int a;
            scanf("%d",&a);
            int sum = subtreesum(a);
            if(sum == -1){
                printf("Not found\n");
                continue;
            }
            printf("Sum of subtree = %d\n",sum);

        }
        else if(ch == 14){
            int d = calcNodeDepth(root);
            int h = calcNodeHeight(root);
            printf("\n--------------------------------\n",h);
            printLevelOrder(root, h , d);
            printf("--------------------------------\n");

        }



    }

}

