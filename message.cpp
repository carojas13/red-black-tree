
#include "message.h"


//constructors
person::person() : name(NULL)
{
}



person::person(char * a_name)
{
    name = new char [strlen(a_name) + 1];
    strcpy(name, a_name);
}



person::person(const person & to_copy)
{
    if(to_copy.name)
    {
        name = new char[strlen(to_copy.name) + 1];
	strcpy(name, to_copy.name);
    }
    else 
        name = NULL;
}



person::~person() //destuctor
{
    if(name)
        delete [] name;
}



int person::display() //displays name
{
    cout <<"person: " << name << endl;
}



int person::compare(char * compare) const //comapres names
{
    if(!name)
        return -2;

    else return strcmp(compare, name);
}



//private message contructors
pm::pm(): private_message(NULL)
{
}



pm::pm(char * a_name, char * a_message) : person(a_name)
{
    if(a_message)
    {
        private_message = new char [strlen(a_message) + 1];
        strcpy(private_message, a_message);
    }
    else
        private_message = NULL;
}



pm::pm(const pm & to_copy) : person(to_copy)
{
    if(to_copy.private_message)
    {
        private_message = new char[strlen(to_copy.private_message) + 1];
	strcpy(private_message, to_copy.private_message);
    }
    else 
        private_message = NULL;
}



pm::~pm() //destructor
{
    if(private_message)
        delete [] private_message;
}



//overloaded operators for pm class
ostream & operator << (ostream & out, const pm & obj)
{
    obj.display();
    return out;
}



pm & pm::operator = (const pm & obj)
{
    copy_pm(obj.private_message);
    return *this;
}


 
bool pm::operator < (const pm & obj) const
{
    if(compare(obj.name) < 0)
	return 1;
    else 
        return 0;
}



bool pm::operator > (const pm & obj) const
{
    if(compare(obj.name) > 1)
        return 1;
    else
        return 0;
}



bool pm::operator >= (const pm & obj) const
{

    if(compare(obj.name) >= 0)
        return 1;

    else 
        return 0;
}



bool pm::operator <= (const pm & obj) const
{

    if(compare(obj.name) <= 0)
        return 1;

    else 
        return 0;
}



void pm::display() const //displays a name and private message
{
    if(name)
        cout << "name: " << name << endl;
    if(private_message)
	cout << "pm: " << private_message << endl;
}



void pm::copy_pm(char * pm) //copies a private message when sending a user a pm
{
    private_message = new char[strlen(pm) + 1];
    strcpy(private_message, pm);
}



void pm::delete_pm() //deletes message
{
    if(private_message)
        delete [] private_message;
    if(name)
        delete [] name;

}



//message contructors
message::message() : im(NULL)
{
}



message::message(char * a_message)
{
    if(a_message)
    {
        im = new char[strlen(a_message) + 1];
	strcpy(im, a_message);
    }
}



message::message(const message & to_copy) 
{
    if(to_copy.im)
    {
        im = new char[strlen(to_copy.im) + 1];
	strcpy(im, to_copy.im);
    }

}



message::~message() //destructors
{
    delete [] im;
}



void message::display() //displays general message
{
    if(im)
        cout << im << endl;
}


        
int message::delete_message() //deletes a general message
{
    if(im)
        delete [] im;
}
