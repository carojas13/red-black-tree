
#include "node.h"

using namespace std;

bool again(); //do while control function

int main() 
{
    manager obj; //manager object for interacting with program

    cout << "***** MESSAGING APPLICATION *****" << endl << endl;
    
    do
    {
        int option = 0;
	cout << "1: add a person" << endl;
	cout << "2: send a PM" << endl;
	cout << "3: send a general message" << endl;;
	cout << "4: display all people in the tree" << endl;
	cout << "5. display all of a persons messages" << endl;
	cin >> option; cin.ignore(100, '\n');
	if(option == 1)
            obj.create();
	if(option == 2)
	    obj.send_pm();
	if(option == 3)
	    obj.as_who();
	if(option == 4)
            obj.display_all();
	if(option == 5)
	    obj.display_messages();

    }
    while(again());
    return 0;
}



bool again() // dowhile control loop
{
    char answer;
    cout << "continue the program? y/n: " << endl;
    cin >> answer; cin.ignore(100, '\n');
    if(answer == 'y' || answer == 'Y')
        return true;
    else return false;
}

