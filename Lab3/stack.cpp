#include<iostream>
#include<string>

using namespace std;

#define DIRECTION_FORWARD  0
#define DIRECTION_BACKWARD 1

typedef struct person person;

struct person {
    public:
    string first_name;
    string last_name;
    unsigned age;
    person* prev;
};




class Stack{
private:
    person *head;
    void person_print(person *p)
    {
        cout << "first name: " << p->first_name << " last name: " << p->last_name << " age: " << p->age << endl;
    }

public:
    Stack(){//initalizaton of the stack
        head = nullptr;
    }

    void push(string fname, string lname, unsigned age ){
        person* temp = new person;
        temp->first_name = fname;
        temp->last_name = lname;
        temp->age = age;

        if(head != nullptr){
            temp->prev = head;
            head = temp;
        }else{
            temp->prev  = nullptr;
            head = temp;
        }
    }


    void pop(){
        if(head == nullptr){
            cout << "not possible ! stack is empty" << endl;
        }else if(head->prev == nullptr){
            delete head;
            head = nullptr;
        }else{
            person* temp = head;
            head = head->prev;
            delete temp;
        }
    }
    
    void traverse(int direction){
        if (head == nullptr){
            cout << "not possible ! stack is empty" << endl;
            return;
        }
        person* temp = head;
        if(direction == DIRECTION_BACKWARD){
            while (temp != nullptr)
            {
                person_print(temp);
                temp = temp->prev;
            }
            
        }else{
            recurr_forward(head);
        }
    }

    void recurr_forward(person* p){
        if(p == nullptr) return;
        else {
            recurr_forward(p->prev);
            person_print(p);
        }
    }

};

int main(){
    Stack s;
    
    s.push("nassim", "maallem", 20);
    s.push("zakaria", "madaoui", 21);
    s.push("vdfsfd", "sdfdsf", 51);


    // s.traverse(DIRECTION_BACKWARD);

    char user_option = '\0';
    string temp_fname;
    string temp_lname;
    int    temp_age;

    while (user_option != 'q')
    {
        cout << "> Please select an option to proceed: \n"
             << "    i: insert new element\n"
             << "    d: delete an element \n"
             << "    f: traverse list forward \n"
             << "    b: traverse list backward \n"
             << "    q: to quit the program \n";
        cin >> user_option;

        switch (user_option)
        {
        case 'i': /*insert*/
            cout << "> person to insert: ";
            cin >> temp_fname >> temp_lname >> temp_age ;
            s.push(temp_fname, temp_lname, temp_age);
            break;

        case 'd': /*delete*/
            s.pop();
            break;


        case 'f': /*traverse forward*/
            s.traverse(DIRECTION_FORWARD);
            break;

        case 'b': /*traverse backward*/
            s.traverse(DIRECTION_BACKWARD);
            // list_traverse(l, DIRECTION_BACKWARD);
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
