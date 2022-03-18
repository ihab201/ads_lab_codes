#include <iostream>
#include <cstring>
using namespace std;

#define MAX_ELEMENTS 100
#define MAX_NAME_SIZE 20
#define DIRECTION_FORWARD 1
#define DIRECTION_BACKWARD 0


struct node{
    char data[MAX_NAME_SIZE];
    struct node* next = nullptr;
    struct node* prev = nullptr;
};

typedef struct node node;

//LinkedList wrapper struct
typedef struct
{
    unsigned size = 0;
    node* first = nullptr;
    node* last  = nullptr;
} LinkedList;

//Arraylist prototypes
void list_insert(LinkedList &list, char item[], unsigned position);
void list_remove(LinkedList &list, unsigned position);
int  list_search(const LinkedList &list, const char *item);
void list_traverse(const LinkedList &list, unsigned direction);

int main()
{
    char user_option = '\0';
    char temp_str[MAX_NAME_SIZE];
    unsigned temp_position = 0;
    LinkedList l;

    list_insert(l, "aaa", 0);
    list_insert(l, "bbb", 1);
    list_insert(l, "ccc", 2);
    list_insert(l, "123", 1);
    list_insert(l, "321", 4);

    while (user_option != 'q')
    {
        cout << "> Please select an option to proceed: \n"
             << "    i: insert new element\n"
             << "    d: delete an element \n"
             << "    s: search for index of an element \n"
             << "    f: traverse list forward \n"
             << "    b: traverse list backward \n"
             << "    q: to quit the program \n";
        cin >> user_option;

        switch (user_option)
        {
        case 'i': /*insert*/
            cout << "> type the position & name to insert: ";
            cin >> temp_position >> temp_str;
            list_insert(l, temp_str, temp_position);
            break;

        case 'd': /*delete*/
            cout << "> type item position to delete: ";
            cin >> temp_position;
            list_remove(l, temp_position);
            break;

        case 's': /*serach and get index*/
            cout << "> type the name to search for: ";
            cin >> temp_str;
            cout << temp_str << " index is : " << list_search(l, temp_str) << "\n";
            break;

        case 'f': /*traverse forward*/
            list_traverse(l, DIRECTION_FORWARD);
            break;

        case 'b': /*traverse backward*/
            list_traverse(l, DIRECTION_BACKWARD);
            break;

        case 'q': /*quit*/
            cout << "Quitting program ... ";
            break;

        default:
            cout << "Wrong input ! try again !\n";
            break;
        }
        cout << "\n------------------------------------------\n\n";
    }
    return 0;
}

//prototypes implementation
void list_insert(LinkedList &list, char item[], unsigned position)
{

    node *temp_1 = list.first;
    
    if( position > list.size || position < 0){ /*Wrong input*/
        cout << "no such position \n";
        return; //do not increment, retuern directly
    } 
    else if (list.first == nullptr && position == 0){ /*inserting for first time*/
            list.first = new node;              // create new node
            strcpy(list.first->data, item);    // put data in new node
            list.first->next = list.first->prev = nullptr;
    } 
    else if(position == 0){ /*inserting at index 0*/
        node *temp_2 = new node;     // create new node
        strcpy(temp_2->data, item);  // put data in new node
        temp_2->prev = nullptr;
        temp_2->next = temp_1;
        temp_1->prev = temp_2;
        list.first   = temp_2;        //keep track of first element
    }
    else{ /*inserting at index greater than 0 */
        for (int i = 1; i < position ; i++) /*get node[position-1]*/
        {
            temp_1 = temp_1->next;
        }
        node *temp_2 = new node;     // create new node
        strcpy(temp_2->data, item);  // put data in new node
        temp_2->next = temp_1->next; 
        temp_2->prev = temp_1;
        temp_1->next = temp_2;
        
        if (position == list.size) list.last = temp_2; //track last element aswell
        else temp_2->next->prev = temp_2;              // if next element is not null correct it's backward link
    }
    
    list.size++; //incerement size
}

void list_remove(LinkedList &list, unsigned position)
{
    node *temp_1 = list.first;
    
    if( position >= list.size || position < 0){ /*Wrong input*/
        cout << "no such position \n";
        return; //do not decrement, retuern directly
    } 
    else if(position == 0){ /* removing element at index 0*/
        node *temp_2 = temp_1->next;   
        list.first = temp_2; //keep track of first element when deleting
        delete temp_1;

        if(list.size != 1) temp_2->prev = nullptr; //correct back link if first element is not the last
    }
    else{ /*deleting element at index greater than 0 */
        for (int i = 0; i < position ; i++) /*get node[position]*/
        {
            temp_1 = temp_1->next;
        }
        node *temp_0 = temp_1->prev;     // get prev node pointer
        node *temp_2 = temp_1->next;     // get next node pointer
        temp_0->next = temp_2;
        delete temp_1;

        if (position == (list.size-1)) list.last = temp_0; //keep track of last when deleting
        else temp_2->prev = temp_0;     //if next element isn't null correct it's back link
    }
    
    list.size--; //decerement size
}

void list_traverse(const LinkedList &list, unsigned direction)
{
    int index;
    if(list.size == 0) cout << "List is empty\n";
    else if (direction == DIRECTION_FORWARD)
    {
        node* temp = list.first;
        index = 0;
        while (temp != nullptr)
        {
            cout << "element[" << index++ << "]= " << temp->data << "\n";
            temp = temp->next;
        }
        
    }
    else
    {
        node* temp = list.last;
        index = list.size;
        while (temp != nullptr)
        {
            cout << "element[" << --index << "]= " << temp->data << "\n";
            temp = temp->prev;
        }
    }
}

int list_search(const LinkedList &list, const char *item)
{
    node* temp = list.first;
    int index  = 0;
    while (temp != nullptr)
    {
        if(strcmp(temp->data, item) == 0) return index;
        temp = temp->next; //traverse forward
        index++;
    }
    
    return -1;
}