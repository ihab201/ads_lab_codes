#include<iostream>

using namespace std; 

typedef struct node{
    int val;
    struct node* left;
    struct node* right;
    struct node* parent;
} node;


//prototypes
void    BST_init(node* &tree);
void    BST_insert(node* &tree , int val);
void    BST_traverse_inOrder(node* tree);
void    BST_traverse_preOrder(node* tree);
void    BST_traverse_postOrder(node* tree);
void    printTabs(int tabs);
void    printTree(node* root, int depth);


int main(){
    node *tree;

    BST_init(tree);

    BST_insert(tree, 8 );
    BST_insert(tree, 3 );
    BST_insert(tree, 1 );
    BST_insert(tree, 6 );
    BST_insert(tree, 7 );
    BST_insert(tree, 10);
    BST_insert(tree, 14);
    BST_insert(tree, 4 );

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
            cout << "tempVal = " << tempVal << endl;
            BST_insert(tree,tempVal);
            break;
        case 2:
            cout <<"\n==================================\n";
            printTree(tree,0);
            cout <<"\n==================================\n";
            break;
        case 3:
            cout <<"inOrder: ";BST_traverse_inOrder(tree); cout << "END" << endl;
            break;
        case 4:
            cout <<"preOrder: ";BST_traverse_preOrder(tree); cout << "END" << endl;
            break;
        case 5:
            cout <<"postOrder: ";BST_traverse_postOrder(tree); cout << "END" << endl;
            break;
        case 6:
            cout << "\n==========================================================\n";
            printTree(tree,0);
            cout << endl;
            cout <<"inOrder: ";BST_traverse_inOrder(tree); cout << "END" << endl;
            cout <<"preOrder: ";BST_traverse_preOrder(tree); cout << "END" << endl;
            cout <<"postOrder: ";BST_traverse_postOrder(tree); cout << "END" << endl;
            cout <<"\n===========================================================\n";
            break;
        }   
    }

    return 0;
}

void printTabs(int tabs){
    for (int i = 0; i < tabs; i++)cout << "\t";
}
void printTree(node* root, int depth){
    if(root == nullptr){
        cout << "tree is empty !" << endl;
        return;
    }
        
    if(root->right != nullptr) printTree(root->right, depth + 1);
    printTabs(depth); cout << "[" <<root->val << "]\n" ;
    if(root->left != nullptr) printTree(root->left, depth + 1);
    
}


//================================ implementations ==================================


void BST_init(node* &tree){
    tree = nullptr;
}

//-----------------------------------------------------------------------------------

void BST_insert(node* &root , int val){
  
    //case1: root is null  (empty tree)
    if(root == nullptr){ 
        root = new node;
        root->val = val;
        root->left = root->right = root->parent = nullptr;
    }
    //case2: insert left
    else if(val <= root->val){   
        if(root->left == nullptr){
            root->left          = new node;
            root->left->val     = val;
            root->left->parent  = root;
        }else{
            BST_insert(root->left , val);
        }
    //case3: insert right
    }else{ 
        if(root->right == nullptr){
            root->right          = new node;
            root->right->val     = val;
            root->right->parent  = root;
        }else{
            BST_insert(root->right , val);
        }
    }

}

//-----------------------------------------------------------------------------------
void BST_traverse_inOrder(node* root){
    if(root == nullptr){
        cout << "tree is empty !" << endl;
        return;
    }

    if(root->left != nullptr)  BST_traverse_inOrder(root->left);
    cout << "[" <<root->val << "] -> " ;
    if(root->right != nullptr) BST_traverse_inOrder(root->right);
}


//-----------------------------------------------------------------------------------
void BST_traverse_preOrder(node* root){
    if(root == nullptr){
        cout << "tree is empty !" << endl;
        return;
    }

    cout << "[" <<root->val << "] -> " ;
    if(root->left != nullptr)  BST_traverse_preOrder(root->left);
    if(root->right != nullptr) BST_traverse_preOrder(root->right);
}

//-----------------------------------------------------------------------------------
void BST_traverse_postOrder(node* root){
    if(root == nullptr){
        cout << "tree is empty !" << endl;
        return;
    }

    if(root->left != nullptr)  BST_traverse_postOrder(root->left);
    if(root->right != nullptr) BST_traverse_postOrder(root->right);
    cout << "[" <<root->val << "] -> " ;
}
