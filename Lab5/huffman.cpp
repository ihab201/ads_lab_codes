#include <iostream>
#include "string.h"
using namespace std;

typedef struct node
{
    int left, right, parent;
} node;

typedef struct
{
    int root;
    float weight;
} cell;

class Huffman
{

private:
    int  chars_nbr;
    int  nodes_nbr;
    int  last_tree;
    int  tree_slot; // used for inserting elements to the tree
    node *tree;
    cell *forrest;
    cell *forrest_copy;
    char *alphabet;

public:

    Huffman() = delete; //force other constructor

    Huffman(int chars_nbr)
    {
        this->chars_nbr = last_tree = tree_slot = chars_nbr;
        nodes_nbr = 2 * chars_nbr - 1;
        tree = new node[nodes_nbr];
        forrest = new cell[chars_nbr];
        forrest_copy = new cell[chars_nbr];
        alphabet = new char[chars_nbr];
    }

    ~Huffman()
    {
        delete[] tree;
        delete[] forrest;
        delete[] forrest_copy;
        delete[] alphabet;
    }

    void populate()
    {
        //populate forrest
        for (size_t i = 0; i < chars_nbr; i++)
        {
            cout << "introduce a character and its weight (ex: a 0.5)" << endl;
            cin >> alphabet[i] >> forrest[i].weight;
            forrest[i].root = i;
        }
        //make a backup of forrest
        memcpy(forrest_copy, forrest, chars_nbr*sizeof(cell));
        
        //init tree
        for (size_t i = 0; i < nodes_nbr; i++)
        {
            tree[i].left = tree[i].right = tree[i].parent = -1;
        }
    }

    /*  Huffman algorithm:
        we start with a forrest such that each node is a tree
        while there is more than 1 tree
        1- find the 2 trees with the smallest weights 
        2- create a new node and merge last two trees with the new node
        2- trees--
    */
    void run() 
    {
        int first, second;
        while (last_tree > 1)
        {
            smallest(first, second);
            
            //create a new parent node in the tree
            tree[forrest[first].root].parent  = tree_slot;
            tree[forrest[second].root].parent = tree_slot;
            //merge first and second
            tree[tree_slot].left  = forrest[first].root;
            tree[tree_slot].right = forrest[second].root;
            forrest[first].weight += forrest[second].weight;
            forrest[first].root = tree_slot;

            //bring last tree element in place of second to ignore it
            forrest[second] = forrest[last_tree-1];

            last_tree--;
            tree_slot++;
        }
    }

    void printTreeTable(){
        for (size_t i = 0; i < nodes_nbr; i++)
        {
            printf("%d: [%+d, %+d, %+d]\n", i,
                                        tree[i].parent,
                                        tree[i].left, 
                                        tree[i].right);
        }
    }


    void printTreeGraph(){
        printTree_rec(nodes_nbr-1, 0);
    }

    void code()  //print a table of char vs its code
    {
        for (size_t i = 0; i < chars_nbr; i++)
        {
            //first extract the code in reverse
            char huff_code[chars_nbr];
            int root = i, bit = 0, parent;
            while(tree[root].parent != -1) // start from last leaf node and ascend to first root
            {   
                //go a step beck and check if this node is on left or right
                parent = tree[root].parent; 
                if(tree[parent].left == root)
                    huff_code[bit] = '0';
                else
                    huff_code[bit] = '1';
                root = parent;
                bit++;
            } 
            reverseString(huff_code, bit);
            huff_code[bit] = '\0'; //add string termination character
            printf("[%d | %c | %.2f] = %s\n", i, alphabet[i], 
                                            forrest_copy[i].weight, 
                                            huff_code);
            // cout << "[" << alphabet[i] <<"] = " << huff_code <<endl;
        } 
    }

private:
    void smallest(int &first, int &second)
    {
        if (forrest[0].weight <= forrest[1].weight)
        {
            first = 0;
            second = 1;
        }
        else
        {
            first = 1;
            second = 0;
        }

        for (size_t i = 0; i < last_tree; i++)
        {
            if (forrest[i].weight == forrest[first].weight){
                continue;
            }
            else if(forrest[i].weight < forrest[first].weight)
            {
                second = first;
                first = i;
            }
            else if(forrest[i].weight < forrest[second].weight)
            {
                second = i;
            }
        }
    }

    void printTree_rec(int root, int depth){
        if(tree[root].right != -1) printTree_rec(tree[root].right, depth+1);
        for(int i = 0; i < depth; i++) cout <<"\t"; //generate tabs
        cout <<"["<< root <<"]" << endl;
        if(tree[root].left != -1) printTree_rec(tree[root].left, depth+1);
    }

    void reverseString(char* arr, int size){
        char temp;
        for (int i = 0; i < size/2; i++)
        {
            temp = arr[i];
            arr[i] = arr[size-i-1];
            arr[size-i-1] = temp;
        } 
    }
};

int main()
{
    int n = 0;
    cout << "Enter number of charachters to encode: " << endl; // type: 5 a 0.12 b 0.4 c 0.15 d 0.08 e 0.25
    cin >> n;
    Huffman huff(n);
    huff.populate(); // populate forrest
    huff.run();
    cout << "---------------------------------------------" <<endl;
    huff.printTreeTable();
    cout << "---------------------------------------------" <<endl;
    huff.printTreeGraph();
    cout << "---------------------------------------------" <<endl;
    huff.code();


    return 0;
}

