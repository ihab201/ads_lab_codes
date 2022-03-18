#include<iostream>
#define MAX_NODES 27

using namespace std; 

typedef struct{
    int val;
    int left;
    int right;
    int parent;
} node;

typedef struct{
    int size;
    node nodes[MAX_NODES];
} tree;


//prototypes
void    BST_init(tree &t);
void    BST_insert(tree &t , int val);
void    BST_traverse_inOrder(tree &t);
void    BST_traverse_preOrder(tree &t);
void    BST_traverse_postOrder(tree &t);
void    printTabs(int tabs);
void    printTree(tree &t,int root, int depth);
// void    BST_delete(tree &t); //destructore

int main(){
    tree t; 
    BST_init(t);

    BST_insert(t, 8 );
    BST_insert(t, 3 );
    BST_insert(t, 1 );
    BST_insert(t, 6 );
    BST_insert(t, 7 );
    BST_insert(t, 9);
    // BST_insert(t, 14);
    BST_insert(t, 4 );


    int choice = -1 , tempVal;
    while(choice != 0){
        cout    <<  "Choose an option:\n"
                <<  "1 + intVAL to insert a new integer\n"
                <<  "2: print tree in graphical way\n"
                <<  "3: Traverse BST using inorder traversal\n"
                <<  "4: Traverse BST using perorder traversal\n"
                <<  "5: Traverse BST using postorder traversal\n" 
                <<  "6: Show tree + all traversals\n" 
                <<  "0: to EXIT" 
                << endl;

        cin >> choice;
        switch (choice)
        {
        case 1:
            cin >> tempVal;
            cout << "inserting  " << tempVal << endl;
            BST_insert(t,tempVal);
            break;
        case 2:
            cout <<"\n==================================\n";
            printTree(t,0,0);
            cout <<"\n==================================\n";
            break;
        case 3:
            BST_traverse_inOrder(t);
            break;
        case 4:
            BST_traverse_preOrder(t);
            break;
        case 5:
            BST_traverse_postOrder(t);
            break;
        case 6:
            cout << "\n==================================\n";
            printTree(t,0,0);
            cout << endl;
            BST_traverse_inOrder(t);
            BST_traverse_preOrder(t);
            BST_traverse_postOrder(t);
            cout <<"\n==================================\n";
            break;
        }   
    }

    return 0;
}



void printTabs(int tabs){
    for (int i = 0; i < tabs; i++)cout << "\t";
}
void printTree(tree &t,int root, int depth){
    if(t.size == 0){
        cout << "tree is empty !" << endl;
        return;
    }
        
    if(t.nodes[root].right != -1) printTree(t, t.nodes[root].right, depth + 1);
    printTabs(depth); cout << "[" <<t.nodes[root].val << "]\n" ;
    if(t.nodes[root].left != -1) printTree(t, t.nodes[root].left, depth + 1);
    
}

//================================ implementations ==================================

void BST_init(tree &t){
    t.size = 0;
    for (int i = 0; i < MAX_NODES; i++)
    {
        t.nodes[i].parent = t.nodes[i].left = t.nodes[i].right = -1;
    }
    
}

//-----------------------------------------------------------------------------------

void BST_insert_rec(tree &t, int root , int val){
    /*The main loop MUST always call this with root = 0 */

    if(t.size == MAX_NODES-1){
        cout << "Can't insert, tree is full !" << endl;  
    }     
    //case1: tree is empty 
    else if(t.size == 0){ 
        t.nodes[0].val = val;
        t.size++;
    }
    //case2: insert left
    else if(val <= t.nodes[root].val){   
        if(t.nodes[root].left == -1){
           int index = t.size;
           t.nodes[index].val = val;     //insert value
           t.nodes[index].parent = root; //set parent
           t.nodes[root].left = index;   //update parent's left node value
           t.size++;                     
        }else{
            BST_insert_rec(t, t.nodes[root].left , val);
        }
    //case3: insert right
    }else{ 
        if(t.nodes[root].right == -1){
           int index = t.size;
           t.nodes[index].val = val;     //insert value
           t.nodes[index].parent = root; //set parent
           t.nodes[root].right = index;  //update parent's right node value
           t.size++;                     
        }else{
            BST_insert_rec(t, t.nodes[root].right , val);
        }
    }

}

void BST_insert(tree &t , int val){
    BST_insert_rec(t, 0 , val);
}

//-----------------------------------------------------------------------------------
void BST_traverse_inOrder_rec(tree &t, int root){
    if(t.size == 0){
        cout << "tree is empty !" << endl;
        return;
    }

    if(t.nodes[root].left != -1)  BST_traverse_inOrder_rec(t, t.nodes[root].left);
    cout << "[" <<t.nodes[root].val << "] -> " ;
    if(t.nodes[root].right != -1) BST_traverse_inOrder_rec(t, t.nodes[root].right);
}

void BST_traverse_inOrder(tree &t){
    cout << "inOrder:   ";
    BST_traverse_inOrder_rec(t, 0);
    cout << "END" << endl;
}

//-----------------------------------------------------------------------------------
void BST_traverse_preOrder_rec(tree &t, int root){
    if(t.size == 0){
        cout << "tree is empty !" << endl;
        return;
    }
    cout << "[" <<t.nodes[root].val << "] -> " ;
    if(t.nodes[root].left != -1)  BST_traverse_preOrder_rec(t, t.nodes[root].left);
    if(t.nodes[root].right != -1) BST_traverse_preOrder_rec(t, t.nodes[root].right);
}

void BST_traverse_preOrder(tree &t){
    cout << "preOrder:  ";
    BST_traverse_preOrder_rec(t, 0);
    cout << "END" << endl;   
}

//-----------------------------------------------------------------------------------
void BST_traverse_postOrder_rec(tree &t, int root){
    if(t.size == 0){
        cout << "tree is empty !" << endl;
        return;
    }
    if(t.nodes[root].left != -1)  BST_traverse_postOrder_rec(t, t.nodes[root].left);
    if(t.nodes[root].right != -1) BST_traverse_postOrder_rec(t, t.nodes[root].right);
    cout << "[" <<t.nodes[root].val << "] -> " ;
}

void BST_traverse_postOrder(tree &t){
    cout << "postOrder: ";
    BST_traverse_postOrder_rec(t, 0);
    cout << "END" << endl;
}
//-----------------------------------------------------------------------------------


void BST_delete(tree &t) {//destructore

}