#include <iostream>
#include <cstring>
using namespace std;

#define MAX_ELEMENTS 100
#define MAX_NAME_SIZE 20
#define DIRECTION_FORWARD 1
#define DIRECTION_BACKWARD 0

//Arraylist struct
typedef struct
{
    unsigned size = 0;
    char data[MAX_ELEMENTS][MAX_NAME_SIZE];
} ArrayList;

//Arraylist prototypes
void list_insert(ArrayList &list, char item[], unsigned position);
void list_remove(ArrayList &list, unsigned position);
int list_search(const ArrayList &list, const char *item);
void list_traverse(const ArrayList &list, unsigned direction);

int main()
{
    char user_option = '\0';
    char temp_str[MAX_NAME_SIZE];
    unsigned temp_position = 0;
    ArrayList l;

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
void list_insert(ArrayList &list, char item[], unsigned position)
{
    if (position >= MAX_ELEMENTS)
        cout << "Index out of bound ! position must be less than " << MAX_ELEMENTS << "\n";
    else if (list.size == MAX_ELEMENTS)
        cout << "List is full !\n";
    else
    {
        for (int i = list.size; i > position; i--)
        {
            strcpy(list.data[i], list.data[i - 1]);
        }
        strcpy(list.data[position], item);
        list.size++; //incerement size
    }
}

void list_remove(ArrayList &list, unsigned position)
{
    if (position >= list.size)
        cout << "element in position " << position << " doesn't exist!\n";
    else
    {
        for (int i = position; i < list.size - 1; i++)
        {
            strcpy(list.data[i], list.data[i + 1]);
        }
        list.size--; //decerement size
    }
}

void list_traverse(const ArrayList &list, unsigned direction)
{
    if (list.size == 0)
        cout << "List is empty\n";
    else if (direction == DIRECTION_FORWARD)
    {
        for (int i = 0; i < list.size; i++)
        {
            cout << "name[" << i << "]= " << list.data[i] << "\n";
        }
    }
    else
    {
        for (int i = list.size - 1; i >= 0; i--)
        {
            cout << "name[" << i << "]= " << list.data[i] << "\n";
        }
    }
}

int list_search(const ArrayList &list, const char *item)
{
    for (int i = 0; i < list.size; i++)
    {
        if (strcmp(item, list.data[i]) == 0)
            return i;
    }
    return -1;
}