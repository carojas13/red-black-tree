
#include <iostream>
#include <cctype>
#include <cstring>
#include <cstdlib>
using namespace std;



class person //class for managing a name
{
    public:
        //constructors and destructor
        person();
        person(char * a_name);
        person(const person &);
	~person();
	int display();//displays name
	int compare(char * compare) const; //compares name

    
    protected:
	char * name;
};


class pm : public person //class for managing a private message
{
    public:
        //constructors and destructor
	pm();
	pm(char * a_name, char * a_message);
	pm(const pm &);
	~pm();
	void copy_pm(char * pm); //for copying a private message into the tree nodes pm object
	void display() const; //displays a private message
	void delete_pm(); //deletes private mesasge

	//overloaded operators for the private message type
	friend ostream & operator << (ostream &, const pm &);
	pm operator + (const pm &) const;
	pm & operator = (const pm &);
	bool operator < (const pm &) const;
	bool operator > (const pm &) const;
	bool operator >= (const pm &) const;
	bool operator <= (const pm & obj) const;



    protected:
	char * private_message;//private message each person gets in the tree

};



class message : public person //class for managing a general message
{
    public:
        //constructors and destructor
        message();
	message(char * a_message);
	message(const message &);
	~message();
	void display();//displays a message
	int delete_message(); //deletes a message


    protected:
	char * im; //general message
};


