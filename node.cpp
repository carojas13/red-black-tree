
#include "node.h"
using namespace std;



//node contructors 
node::node(): color(1), left(NULL), right(NULL), head(NULL) //each node is always inserted as red
{

}



node::node(const pm & to_add) : a_pm(to_add)
{
    right = left = NULL;
}



node * & node::goright()
{
    return right;
}



node * & node::goleft()
{
    return left;
}



//setters and getters for node class
void node::set_left(node * current)
{
    this->left = current;
}



void node::set_right(node * current)
{
    this->right = current;
}



void node::setflag(bool flag)
{
    this->color = flag;
}



void node::display() //displays pm
{
    cout << a_pm;
}



int node::compare(char * to_compare) //comapares name
{
    this->a_pm.compare(to_compare);
}



int node::delete_pm() //deletes a pm
{
    a_pm.delete_pm();
}



//LLL node constructors
l_node::l_node() : next(NULL)
{
}



l_node::l_node(const message & to_add) : a_message(to_add)
{
    next = NULL;
}



l_node * & l_node::gonext()
{
    return next;
}



//LLL node setters and getters
void l_node::set_next(l_node * current)
{
    this->next = current;
}



//manager construcor and destructor
manager::manager() : root(NULL)
{
}



manager::~manager() //destructor that deletes tree
{
    delete_all();
}



void manager::create() //creates an instance a pm(name and null priavate_message)
{

    char * a_name;
    char answer = 'y';
    do
    {
        a_name = new char[50];
	cout << "enter name of person: " << endl;
	cin.get(a_name, 100, '\n'); cin.ignore(100, '\n');
	pm obj(a_name, NULL);
	insert(obj, a_name);
	if(a_name)
	    delete [] a_name;
	cout << "again? y/n: " << endl;
	cin >> answer; cin.ignore(100, '\n');
    }
    while (answer == 'y' || answer == 'Y');

}



void node::send_message() //sends general message
{
    char * a_message;
    char answer = 'y';
    do
    {
        a_message = new char[141];
	cout << "enter your message: " << endl;
	cin.get(a_message, 100, '\n'); cin.ignore(100, '\n');
	message obj(a_message);
	insert(obj, head);
	if(a_message)
	    delete [] a_message;
	cout << "again? y/n: " << endl;
	cin >> answer; cin.ignore(100, '\n');
    }
    while(answer == 'y' || answer == 'Y');
    // cout << add persons name of message they're sending
    display_all(head);
}



void node::display_messages() //displays a message
{
    display_all(head);
}



int manager::as_who() //wrapper for sending a message as someone
{
    char * sender;
    sender = new char[50];
    cout << "send message as who?" << endl;
    cin.get(sender, 100, '\n'); cin.ignore(100, '\n');
    as_who(sender, root);
    if(sender)
        delete [] sender;
}



int manager::as_who(char * sender, node * root)//sends message 
{
    if(!root)
        return 1;
    as_who(sender, root->goleft()) + as_who(sender, root->goright());
    if(root->compare(sender) == 0)
    {
        root->send_message();
	return 1;
    }
}



int manager::send_pm() //sends 1 pm to a persons node in tree
{
    char * recipient;
    recipient = new char[50];
    cout << "send pm to who: " << endl;
    cin.get(recipient, 100, '\n'); cin.ignore(100, '\n');
    send_pm(root, recipient);
    if(recipient)
        delete [] recipient;
}



int manager::send_pm(node * root, char * recipient) //recursive function for sending a pm
{
    if(!root)
        return 0;
    send_pm(root->goleft(), recipient) + send_pm(root->goright(), recipient);
    if(root->compare(recipient) == 0)
    {
        char * message = new char [150];
        cout << "enter your 1 pm to this person" << endl;
	cin.get(message, 100, '\n'); cin.ignore(100, '\n');
	root->copy_pm(message);
	return 1;
    } 
}



int node::copy_pm(char * message) //copies a private_message to pm object in node
{
     a_pm.copy_pm(message);
    return 1;
}


int manager::display_all() //displays all
{
    if(!root)
         return 0;
    return display_all(root);
}



int manager::display_all(node * root) //display all recursive call
{
    if(!root)
        return 1;
    display_all(root->goleft());
    root->display();
    display_all(root->goright());
    
}



void manager::insert(const pm & obj, char * key) //insert wrapper for red-black tree
{
    if(!root) //base case. empty tree, root is always black
    {
        root = new node(obj);
	root->setflag(0);
	return;
    }
    insert(root, obj, key);
}



bool node::getflag() //getter for nodes color flag
{
    return color;
}



int manager::insert(node * & root, const pm & obj, char * key) //insert algorithm for red-black tree
{
    int count = 0; //count for on teh way back we know where out grandfather of the last node we inserted is
    if(!root)
    {
        root = new node(obj);
	++count;
	return count;
    }
    node * parent = root; 
    node * uncle; 
    int direction; //for knowing what side of tree its on. 1 = left, 2 = right

    if(root->compare(key) < 0)
    {
        count += 1 + insert(root->goleft(), obj, key);
	parent = root->goleft();
	uncle = root->goright();
	direction = 1;
    }
    else 
    {
        count += 1 + insert(root->goright(), obj, key);
	parent = root->goright();
	uncle = root->goleft();
	direction = 2;
    }
    if(count == 2)
    {
        node * grandparent = root;
	if(parent->getflag() == 1 && uncle && uncle->getflag() == 1)//first case where we just recolor
	{
	    parent->setflag(0);
	    uncle->setflag(0);
	    grandparent->setflag(1);
	    return 1;
	}
	if(parent->getflag() == 1 && (!uncle || uncle->getflag() == 0)) //second case were we must rotate and recolor
	{
	    int c_direction; //for knowing which direction our child is in and the four rotate cases
	    if(parent->compare(key) < 0)
	        c_direction = 1; //left
	    else c_direction = 2; //right

	    if(direction == 1 && c_direction == 1) //left side of tree with our child on the left
	    {
	        left_left_rotate(root);
		return 1;
	    }
	    if(direction == 1 && c_direction == 2) //left side of tree with child on right
	    {
	        left_right_rotate(root);
		return 1;

	    }
	    if(direction == 2 && c_direction == 2) //right side of tree with child on the right
	    {
	        right_right_rotate(root);
		return 1;

	    }
	    if(direction == 2 && c_direction == 1) //right side of tree with child on the left
	    {
	        right_left_rotate(root);
		return 1;
	    }


	}

    }

}


//rotation functions for each of our four cases
int manager::left_left_rotate(node * & grandparent)
{
    node * uncle = grandparent->goright();
    node * parent = grandparent->goleft();
//    if(parent->goright()) should cover every case..(?)
 //   {
        node * temp = parent->goright();
        grandparent->set_left(temp);
	parent->set_right(grandparent);
	parent->setflag(0);
	grandparent->setflag(1);

  //  }

}


int manager::left_right_rotate(node * & grandparent)
{
//    node * uncle = grandparent->goright();
    node * parent = grandparent->goleft();
    node * child = parent->goright();

    node * temp = child->goleft();
    grandparent->set_left(child);
    child->set_left(parent);
    parent->set_right(temp);

    node * hold = child->goright();
    child->set_right(grandparent);
    grandparent->set_left(hold);
    grandparent->setflag(1);
    child->setflag(0);
    
}



int manager::right_right_rotate(node * & grandparent)
{
    node * parent = grandparent->goright();
    node * uncle = grandparent->goleft();

    node * temp = parent->goleft();
    parent->set_left(grandparent);
    grandparent->set_right(temp);
    grandparent->setflag(1);
    parent->setflag(0);
}



int manager::right_left_rotate(node * & grandparent)
{
    node * parent = grandparent->goright();
    node * child = parent->goleft();

    node * temp = child->goright();
    child->set_right(parent);
    parent->set_left(temp);

    grandparent->set_right(child->goleft());
    child->set_left(grandparent);

    grandparent->setflag(1);
    child->setflag(0);
}



void manager::display_messages() //wrapper for persons messages theuve sent
{
    char * to_display;
    to_display = new char[50];
    cout << "display who's messages" << endl;
    cin.get(to_display, 100, '\n'); cin.ignore(100, '\n');
    display_messages(root, to_display);
}



int manager::display_messages(node * root, char * to_display) //recursive call display
{
    if(!root)
        return 0;
    display_messages(root->goleft(), to_display) + display_messages(root->goright(), to_display);
    if(root->compare(to_display) == 0)
    {
        root->display_messages();
	return 1;
    }
}



int manager::delete_all() //deletes all wrapper. desutrctor calls this
{
    if(!root)
        return 0;
    return delete_all(root);
}



int manager::delete_all(node * & root) //recursive call delete all
{
    if(!root)
        return 1;
    delete_all(root->goleft()) + delete_all(root->goright());
    root->delete_pm();
    //root->delete_message();
}



int manager::delete_messages()  //for deleting list...couldnt get working
{
    //delete_a_message(head);
}



int l_manager::delete_a_message(class l_node * & head)//delets a message
{
    if(!head)
        return 1;
     l_node * temp = head->gonext();
     head->delete_message();

     delete head;
     return delete_a_message(head->gonext());
}
    

void l_manager::insert(const message & obj, class l_node * & head)//for inserting a message in teh list
{
    if(!head)
    {
        head = new l_node(obj);
	return;
    }
    else
    {
        l_node * hold = head;
        l_node * temp = new l_node(obj);
	head = temp;
	temp->set_next(hold);
    }
}



void l_manager::display_all(class l_node * head) //displays all in list
{
    if(!head)
        return;
    head->display();
    return display_all(head->gonext());
}



void l_node::display()//display function for message object
{
    this->a_message.display();
}


int l_node::delete_message()//deletes message content
{
    a_message.delete_message();
}

