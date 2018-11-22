#ifndef __ARRAYITEM_H_
#define __ARRAYITEM_H_

#include <iostream>
using namespace std;
#include <string>
#include "stdlib.h" 
#include "time.h" 

////// this is needed to check compatibility between items (and to use a derived-class pointer that is passes as "base class")
template <class Base, class Derived> Derived* typecastItem(Base* basic_ptr, Derived* derivedItem_ptr)
{
	Derived* typecasted_ptr=dynamic_cast <Derived *>(basic_ptr);

	if(typecasted_ptr==NULL)				
		printf("\n Error typecasting item: type does not match the expected derived item\n");

	return typecasted_ptr;
}
//////


/* this is the base version of an object that holds the information about sorting ctiteria.

    for simple array items: the options "ascending/descending" affred here suffice.
 
    For more complex/composite array items: an appropriate sort criteria should be deirved from
 
    this base class and used in "IsLargerThan" */
class basic_sort_criteria{
protected:
	bool ascending;
	void basic_initialization(){setAscending(true);} //This initialises to ascending automatically
public:
	basic_sort_criteria(){basic_initialization();} // Class constructor
	basic_sort_criteria(bool value){setAscending(value);} // Constructor with value
	void setAscending(bool value){ascending=value;} // 
	bool getAscending(){return ascending;}	
};





class basic_item{
protected:
	bool empty;

public:
	basic_item(){empty=true;}
	~basic_item(){;}
	
	bool isEmpty(){return empty;} // Function called to check if the array is empty
	
	//The following must be implemented by any derived item:
	virtual void printItemOnScreen()=0; 
	virtual void enterItemFromKeyboard()=0;
	virtual void generateRandomItem()=0;
    // virtual void loadItemFromFile(FILE* fin)=0;
	
    
    
	/* Needed for sorting; the second parameter holds the information about soritng ctireria;
     If you do not supply a second parameter, a default option (simple ascending sorting) is assumed */
	virtual bool IsLargerThan(basic_item* other_item, basic_sort_criteria* sort_criteria=NULL)=0;
	virtual basic_item* allocateItem()=0;
	virtual void deallocateItem(basic_item* item_ptr)=0;
    // virtual basic_item* makeCopyofItem()=0;

};
// Example of derived class implementing an integer item
class integer_item: public basic_item{
protected:
	int item_value;
	
public:
	// default constructor and destructor: do nothing
	integer_item(){;}
	~integer_item(){;}

	int getItemVal(){return item_value;}
    
    // This function is used to print the array on screen
	virtual void printItemOnScreen()
	{
		if(isEmpty())
			cout << "Item is empty." << endl;
		else
			cout << "Item value is " << getItemVal() << " . " << endl;
	}
    
    // This function is used to enter the array from the keyboard
	virtual void enterItemFromKeyboard()
	{
		cout << "Insert element then hit enter." << endl;
		cin >> item_value;
		cout << endl;
		
		// item filled
		empty=false;
	}

    // This function is used to generate the array from random values
	virtual void generateRandomItem()
	{
		int item;
		int max_rand_val = 1000;

		item=rand();
		item = item % (max_rand_val+1);

		// turn to negative 50% of the time
		if( (rand()%10) >=5 )
			item=(-1)*item;

		item_value=item;
		// item filled
		empty=false;
		
	}

    // Function is used to check the items for sorting the array
	virtual bool IsLargerThan(basic_item* other_item, basic_sort_criteria* sort_criteria=NULL)
	{
		bool result=false;
		// if the other item is "empty" (non allocated) don't do any comparison
		if(other_item==NULL)
			return false;

		// first typecast the other item to confimr it is the same as this;
		integer_item* typecasted_other_item = typecastItem(other_item, this);
		
		// check that it worked
		if(typecasted_other_item==NULL)
		{
			cout << "Other item is not of type integer_item." << endl;
			return false;
			// items of the wrong type (or null pointers) will be pushed to the end of the list
		}

		// now verify if the other item is larger than the curren
		if( getItemVal() > (typecasted_other_item->getItemVal()) )
			result=true;


		// chek if there are sorting options to apply 
		if(sort_criteria!=NULL)
		{
			// if sorting is in descending order the result is reversed 
			if( !( sort_criteria->getAscending() ) )
				result=!result;
		}

		return result;
	}

    // Function is used to release the memory
	virtual void deallocateItem(basic_item* item_ptr)
	{
		// first typecast the other item to confimr it is the same as this;
		integer_item* typecasted_item_ptr = typecastItem(item_ptr, this);
		
		// check that it worked
		if(typecasted_item_ptr==NULL)
		{
			// items of the wrong type (or null pointers)
			cout << "Error in deallocateItem (for integer_item): "<< endl << "Other item is not of type integer_item." << endl;
			return;
		}
		delete typecasted_item_ptr;
	}
	virtual basic_item* allocateItem()
	{
		integer_item* result = new integer_item;
		if(result==NULL)
			cout << " Error in integer_item::allocateItem(): out of memory"<< endl;
		return result;
	}
};

////////////////////////////////////
// Deriving own first name class //
///////////////////////////////////
class firstNameItem: public basic_item{
protected:
    string firstName;
    
public:
    // default constructor and destructor: do nothing
    firstNameItem(){;}
    ~firstNameItem(){;}
    
    string getStringVal(){return firstName;}
    
    // This function is used to print the array on screen
    virtual void printItemOnScreen()
    {
        if(isEmpty())
            cout << "Item is empty." << endl;
        else
            cout << "First name:    " << getStringVal() << endl;
    }
    
    // This function is used to enter the array from the keyboard
    virtual void enterItemFromKeyboard()
    {
        cout << "Insert element then hit enter." << endl;
        cin >> firstName;
        cout << endl;
        
        // item filled
        empty=false;
    }
    
    // This function is used to generate the array from random values
    virtual void generateRandomItem()
    {
        int index;
        string first_name[10]={"Dylan","Calum","Matthew","Callum","Niko","Francis","Jack","Jan","Trev","Jaseh"};
        index = rand() % 10;
        firstName = first_name[index];
        empty=false;
        
    }
    
    // Function is used to check the items for sorting the array
    virtual bool IsLargerThan(basic_item* other_item, basic_sort_criteria* sort_criteria=NULL)
    {
        bool result=false;
        // if the other item is "empty" (non allocated) don't do any comparison
        if(other_item==NULL)
            return false;
        
        // first typecast the other item to confimr it is the same as this;
        firstNameItem* typecasted_other_item = typecastItem(other_item, this);
        
        // check that it worked
        if(typecasted_other_item==NULL)
        {
            cout << "Other item is not of type integer_item." << endl;
            return false;
            // items of the wrong type (or null pointers) will be pushed to the end of the list
        }
        
        // now verify if the other item is larger than the curren
        if( getStringVal() > (typecasted_other_item->getStringVal()) )
            result=true;
        
        
        // chek if there are sorting options to apply
        if(sort_criteria!=NULL)
        {
            // if sorting is in descending order the result is reversed
            if( !( sort_criteria->getAscending() ) )
                result=!result;
        }
        
        return result;
    }
    
    // Function is used to release the memory
    virtual void deallocateItem(basic_item* item_ptr)
    {
        // first typecast the other item to confimr it is the same as this;
        firstNameItem* typecasted_item_ptr = typecastItem(item_ptr, this);
        
        // check that it worked
        if(typecasted_item_ptr==NULL)
        {
            // items of the wrong type (or null pointers)
            cout << "Error in deallocateItem (for firstNameItem): "<< endl << "Other item is not of type firstNameItem." << endl;
            return;
        }
        delete typecasted_item_ptr;
    }
    virtual basic_item* allocateItem()
    {
        firstNameItem* result = new firstNameItem;
        if(result==NULL)
            cout << " Error in firstNameItem::allocateItem(): out of memory"<< endl;
        return result;
    }
};

////////////////////////////////////
// Deriving own last name class //
////////////////////////////////////

class lastNameItem: public basic_item{
protected:
    string lastName;
    
public:
    // default constructor and destructor: do nothing
    lastNameItem(){;}
    ~lastNameItem(){;}
    
    string getStringVal(){return lastName;}
    
    // This function is used to print the array on screen
    virtual void printItemOnScreen()
    {
        if(isEmpty())
            cout << "Item is empty." << endl;
        else
            cout << "Family Name:   " << getStringVal() << endl;
    }
    
    // This function is used to enter the array from the keyboard
    virtual void enterItemFromKeyboard()
    {
        cout << "Insert element then hit enter." << endl;
        cin >> lastName;
        cout << endl;
        
        // item filled
        empty=false;
    }
    
    // This function is used to generate the array from random values
    virtual void generateRandomItem()
    {
        int index;
        string last_name[10]={"Quirie","Muir","Flappybird","Knight","Lachazar","Clark","Mclean","Povaka","Ted","Onfry"};
        index = rand() % 10;
        lastName = last_name[index];
        empty=false;
        
    }
    
    // Function is used to check the items for sorting the array
    virtual bool IsLargerThan(basic_item* other_item, basic_sort_criteria* sort_criteria=NULL)
    {
        bool result=false;
        // if the other item is "empty" (non allocated) don't do any comparison
        if(other_item==NULL)
            return false;
        
        // first typecast the other item to confimr it is the same as this;
        lastNameItem* typecasted_other_item = typecastItem(other_item, this);
        
        // check that it worked
        if(typecasted_other_item==NULL)
        {
            cout << "Other item is not of type integer_item." << endl;
            return false;
            // items of the wrong type (or null pointers) will be pushed to the end of the list
        }
        
        // now verify if the other item is larger than the curren
        if( getStringVal() > (typecasted_other_item->getStringVal()) )
            result=true;
        
        
        // chek if there are sorting options to apply
        if(sort_criteria!=NULL)
        {
            // if sorting is in descending order the result is reversed
            if( !( sort_criteria->getAscending() ) )
                result=!result;
        }
        
        return result;
    }
    
    // Function is used to release the memory
    virtual void deallocateItem(basic_item* item_ptr)
    {
        // first typecast the other item to confimr it is the same as this;
        lastNameItem* typecasted_item_ptr = typecastItem(item_ptr, this);
        
        // check that it worked
        if(typecasted_item_ptr==NULL)
        {
            // items of the wrong type (or null pointers)
            cout << "Error in deallocateItem (for firstNameItem): "<< endl << "Other item is not of type firstNameItem." << endl;
            return;
        }
        delete typecasted_item_ptr;
    }
    virtual basic_item* allocateItem()
    {
        lastNameItem* result = new lastNameItem;
        if(result==NULL)
            cout << " Error in firstNameItem::allocateItem(): out of memory"<< endl;
        return result;
    }
};

// Deriving own first name class
class studentNumberItem: public basic_item{
protected:
    string studentNumber;
    
public:
    // default constructor and destructor: do nothing
    studentNumberItem(){;}
    ~studentNumberItem(){;}
    
    string getStringVal(){return studentNumber;}
    
    // This function is used to print the array on screen
    virtual void printItemOnScreen()
    {
        if(isEmpty())
            cout << "Item is empty." << endl;
        else
            cout << "Student ID:    " << getStringVal() << " . " << endl;
    }
    
    // This function is used to enter the array from the keyboard
    virtual void enterItemFromKeyboard()
    {
        cout << "Insert element then hit enter." << endl;
        cin >> studentNumber;
        cout << endl;
        
        // item filled
        empty=false;
    }
    
    // This function is used to generate the array from random values
    virtual void generateRandomItem()
    {
        int index;
        string student_ID[10]={"51658154","51658232","12345678","87654321","10293847","364572910","37482918","46573829","56482911","56379294"};
        index = rand() % 10;
        studentNumber = student_ID[index];
        empty=false;
        
    }
    
    // Function is used to check the items for sorting the array
    virtual bool IsLargerThan(basic_item* other_item, basic_sort_criteria* sort_criteria=NULL)
    {
        bool result=false;
        // if the other item is "empty" (non allocated) don't do any comparison
        if(other_item==NULL)
            return false;
        
        // first typecast the other item to confimr it is the same as this;
        studentNumberItem* typecasted_other_item = typecastItem(other_item, this);
        
        // check that it worked
        if(typecasted_other_item==NULL)
        {
            cout << "Other item is not of type studentNumberItem." << endl;
            return false;
            // items of the wrong type (or null pointers) will be pushed to the end of the list
        }
        
        // now verify if the other item is larger than the curren
        if( getStringVal() > (typecasted_other_item->getStringVal()) )
            result=true;
        
        
        // chek if there are sorting options to apply
        if(sort_criteria!=NULL)
        {
            // if sorting is in descending order the result is reversed
            if( !( sort_criteria->getAscending() ) )
                result=!result;
        }
        
        return result;
    }
    
    // Function is used to release the memory
    virtual void deallocateItem(basic_item* item_ptr)
    {
        // first typecast the other item to confimr it is the same as this;
        studentNumberItem* typecasted_item_ptr = typecastItem(item_ptr, this);
        
        // check that it worked
        if(typecasted_item_ptr==NULL)
        {
            // items of the wrong type (or null pointers)
            cout << "Error in deallocateItem (for firstNameItem): "<< endl << "Other item is not of type firstNameItem." << endl;
            return;
        }
        delete typecasted_item_ptr;
    }
    virtual basic_item* allocateItem()
    {
        studentNumberItem* result = new studentNumberItem;
        if(result==NULL)
            cout << " Error in firstNameItem::allocateItem(): out of memory"<< endl;
        return result;
    }
};

// Deriving own first name class
class nationalityItem: public basic_item{
protected:
    string nationality;
    
public:
    // default constructor and destructor: do nothing
    nationalityItem(){;}
    ~nationalityItem(){;}
    
    string getStringVal(){return nationality;}
    
    // This function is used to print the array on screen
    virtual void printItemOnScreen()
    {
        if(isEmpty())
            cout << "Item is empty." << endl;
        else
            cout << "Nationality:   " << getStringVal()<< endl;
    }
    
    // This function is used to enter the array from the keyboard
    virtual void enterItemFromKeyboard()
    {
        cout << "Insert element then hit enter." << endl;
        cin >> nationality;
        cout << endl;
        
        // item filled
        empty=false;
    }
    
    // This function is used to generate the array from random values
    virtual void generateRandomItem()
    {
        int index;
        string nationalities[10]={"Scottish","Welsh","English CUNT","Italian","Irish","Bulgarian","Czech","Brazilian","Persian","Chinese"};
        index = rand() % 10;
        nationality = nationalities[index];
        empty=false;
        
    }
    
    // Function is used to check the items for sorting the array
    virtual bool IsLargerThan(basic_item* other_item, basic_sort_criteria* sort_criteria=NULL)
    {
        bool result=false;
        // if the other item is "empty" (non allocated) don't do any comparison
        if(other_item==NULL)
            return false;
        
        // first typecast the other item to confimr it is the same as this;
        nationalityItem* typecasted_other_item = typecastItem(other_item, this);
        
        // check that it worked
        if(typecasted_other_item==NULL)
        {
            cout << "Other item is not of type integer_item." << endl;
            return false;
            // items of the wrong type (or null pointers) will be pushed to the end of the list
        }
        
        // now verify if the other item is larger than the curren
        if( getStringVal() > (typecasted_other_item->getStringVal()) )
            result=true;
        
        
        // chek if there are sorting options to apply
        if(sort_criteria!=NULL)
        {
            // if sorting is in descending order the result is reversed
            if( !( sort_criteria->getAscending() ) )
                result=!result;
        }
        
        return result;
    }
    
    // Function is used to release the memory
    virtual void deallocateItem(basic_item* item_ptr)
    {
        // first typecast the other item to confimr it is the same as this;
        nationalityItem* typecasted_item_ptr = typecastItem(item_ptr, this);
        
        // check that it worked
        if(typecasted_item_ptr==NULL)
        {
            // items of the wrong type (or null pointers)
            cout << "Error in deallocateItem (for firstNameItem): "<< endl << "Other item is not of type firstNameItem." << endl;
            return;
        }
        delete typecasted_item_ptr;
    }
    virtual basic_item* allocateItem()
    {
        nationalityItem* result = new nationalityItem;
        if(result==NULL)
            cout << " Error in firstNameItem::allocateItem(): out of memory"<< endl;
        return result;
    }
};

// Deriving own first name class
class studentEmail: public basic_item{
protected:
    string sEmail;
    
public:
    // default constructor and destructor: do nothing
    studentEmail(){;}
    ~studentEmail(){;}
    
    string getStringVal(){return sEmail;}
    
    // This function is used to print the array on screen
    virtual void printItemOnScreen()
    {
        if(isEmpty())
            cout << "Item is empty." << endl;
        else
            cout << "Email:         " << getStringVal()<< endl;
    }
    
    // This function is used to enter the array from the keyboard
    virtual void enterItemFromKeyboard()
    {
        cout << "Insert element then hit enter." << endl;
        cin >> sEmail;
        cout << endl;
        
        // item filled
        empty=false;
    }
    
    // This function is used to generate the array from random values
    virtual void generateRandomItem()
    {
        int index;
        string startYear[10]={"14","15","16","17","18","19","20","21","22","23"};
        index = rand() % 10;
        sEmail = "Student."+startYear[index]+"@aberdeen.ac.uk";
        empty=false;
        
    }
    
    // Function is used to check the items for sorting the array
    virtual bool IsLargerThan(basic_item* other_item, basic_sort_criteria* sort_criteria=NULL)
    {
        bool result=false;
        // if the other item is "empty" (non allocated) don't do any comparison
        if(other_item==NULL)
            return false;
        
        // first typecast the other item to confimr it is the same as this;
        studentEmail* typecasted_other_item = typecastItem(other_item, this);
        
        // check that it worked
        if(typecasted_other_item==NULL)
        {
            cout << "Other item is not of type integer_item." << endl;
            return false;
            // items of the wrong type (or null pointers) will be pushed to the end of the list
        }
        
        // now verify if the other item is larger than the curren
        if( getStringVal() > (typecasted_other_item->getStringVal()) )
            result=true;
        
        
        // chek if there are sorting options to apply
        if(sort_criteria!=NULL)
        {
            // if sorting is in descending order the result is reversed
            if( !( sort_criteria->getAscending() ) )
                result=!result;
        }
        
        return result;
    }
    
    // Function is used to release the memory
    virtual void deallocateItem(basic_item* item_ptr)
    {
        // first typecast the other item to confimr it is the same as this;
        studentEmail* typecasted_item_ptr = typecastItem(item_ptr, this);
        
        // check that it worked
        if(typecasted_item_ptr==NULL)
        {
            // items of the wrong type (or null pointers)
            cout << "Error in deallocateItem (for firstNameItem): "<< endl << "Other item is not of type firstNameItem." << endl;
            return;
        }
        delete typecasted_item_ptr;
    }
    virtual basic_item* allocateItem()
    {
        studentEmail* result = new studentEmail;
        if(result==NULL)
            cout << " Error in firstNameItem::allocateItem(): out of memory"<< endl;
        return result;
    }
};

// Deriving own first name class
class degreeProgramme: public basic_item{
protected:
    string degree;
    
public:
    // default constructor and destructor: do nothing
    degreeProgramme(){;}
    ~degreeProgramme(){;}
    
    string getStringVal(){return degree;}
    
    // This function is used to print the array on screen
    virtual void printItemOnScreen()
    {
        if(isEmpty())
            cout << "Item is empty." << endl;
        else
            cout << "Programme:     " << getStringVal()<< endl;
    }
    
    // This function is used to enter the array from the keyboard
    virtual void enterItemFromKeyboard()
    {
        cout << "Insert element then hit enter." << endl;
        cin >> degree;
        cout << endl;
        
        // item filled
        empty=false;
    }
    
    // This function is used to generate the array from random values
    virtual void generateRandomItem()
    {
        int index;
        int index2;
        string degree_type[2]={"MEng ","BEng "};
        string degree_programme[8]={"Electrical", "Electrical and Electronic","Chemical","Mechanical","Petroleum","Electronic and Software","Electrical and Mechanical"};
        index = rand() % 2;
        index2 = rand() % 8;
        degree = degree_type[index] + degree_programme[index2];
        empty=false;
        
    }
    
    // Function is used to check the items for sorting the array
    virtual bool IsLargerThan(basic_item* other_item, basic_sort_criteria* sort_criteria=NULL)
    {
        bool result=false;
        // if the other item is "empty" (non allocated) don't do any comparison
        if(other_item==NULL)
            return false;
        
        // first typecast the other item to confimr it is the same as this;
        degreeProgramme* typecasted_other_item = typecastItem(other_item, this);
        
        // check that it worked
        if(typecasted_other_item==NULL)
        {
            cout << "Other item is not of type integer_item." << endl;
            return false;
            // items of the wrong type (or null pointers) will be pushed to the end of the list
        }
        
        // now verify if the other item is larger than the curren
        if( getStringVal() > (typecasted_other_item->getStringVal()) )
            result=true;
        
        
        // chek if there are sorting options to apply
        if(sort_criteria!=NULL)
        {
            // if sorting is in descending order the result is reversed
            if( !( sort_criteria->getAscending() ) )
                result=!result;
        }
        
        return result;
    }
    
    // Function is used to release the memory
    virtual void deallocateItem(basic_item* item_ptr)
    {
        // first typecast the other item to confimr it is the same as this;
        degreeProgramme* typecasted_item_ptr = typecastItem(item_ptr, this);
        
        // check that it worked
        if(typecasted_item_ptr==NULL)
        {
            // items of the wrong type (or null pointers)
            cout << "Error in deallocateItem (for firstNameItem): "<< endl << "Other item is not of type firstNameItem." << endl;
            return;
        }
        delete typecasted_item_ptr;
    }
    virtual basic_item* allocateItem()
    {
        degreeProgramme* result = new degreeProgramme;
        if(result==NULL)
            cout << " Error in firstNameItem::allocateItem(): out of memory"<< endl;
        return result;
    }
};

// Deriving own first name class
class markCGS: public basic_item{
protected:
    double CGS;
    
public:
    // default constructor and destructor: do nothing
    markCGS(){;}
    ~markCGS(){;}
    
    float getDoubleVal(){return CGS;}
    
    // This function is used to print the array on screen
    virtual void printItemOnScreen()
    {
        if(isEmpty())
            cout << "Item is empty." << endl;
        else
            cout << "Avg CGS:       "<< getDoubleVal() << endl;
    }
    
    // This function is used to enter the array from the keyboard
    virtual void enterItemFromKeyboard()
    {
        cout << "Insert element then hit enter." << endl;
        cin >> CGS;
        cout << endl;
        
        // item filled
        empty=false;
    }
    
    // This function is used to generate the array from random values
    virtual void generateRandomItem()
    {
        float avgCGS = rand() % 22 +1;
        CGS=avgCGS;
        empty=false;
        
    }
    
    // Function is used to check the items for sorting the array
    virtual bool IsLargerThan(basic_item* other_item, basic_sort_criteria* sort_criteria=NULL)
    {
        bool result=false;
        // if the other item is "empty" (non allocated) don't do any comparison
        if(other_item==NULL)
            return false;
        
        // first typecast the other item to confimr it is the same as this;
        markCGS* typecasted_other_item = typecastItem(other_item, this);
        
        // check that it worked
        if(typecasted_other_item==NULL)
        {
            cout << "Other item is not of type integer_item." << endl;
            return false;
            // items of the wrong type (or null pointers) will be pushed to the end of the list
        }
        
        // now verify if the other item is larger than the curren
        if( getDoubleVal() > (typecasted_other_item->getDoubleVal()) )
            result=true;
        
        
        // chek if there are sorting options to apply
        if(sort_criteria!=NULL)
        {
            // if sorting is in descending order the result is reversed
            if( !( sort_criteria->getAscending() ) )
                result=!result;
        }
        
        return result;
    }
    
    // Function is used to release the memory
    virtual void deallocateItem(basic_item* item_ptr)
    {
        // first typecast the other item to confimr it is the same as this;
        markCGS* typecasted_item_ptr = typecastItem(item_ptr, this);
        
        // check that it worked
        if(typecasted_item_ptr==NULL)
        {
            // items of the wrong type (or null pointers)
            cout << "Error in deallocateItem (for firstNameItem): "<< endl << "Other item is not of type firstNameItem." << endl;
            return;
        }
        delete typecasted_item_ptr;
    }
    virtual basic_item* allocateItem()
    {
        markCGS* result = new markCGS;
        if(result==NULL)
            cout << " Error in firstNameItem::allocateItem(): out of memory"<< endl;
        return result;
    }
};

// Deriving own first name class
class dateOfBirth: public basic_item{
protected:
    int day;
    int month;
    int year;
  
public:
    // default constructor and destructor: do nothing
   dateOfBirth(){;}
    ~dateOfBirth(){;}
    
    //int getDOBVal
    int getDayVal(){return day ;}
    int getMonthVal(){return month;}
    int getYearVal(){return year;}
   
    // This function is used to print the array on screen
    virtual void printItemOnScreen()
    {
        if(isEmpty())
            cout << "Item is empty." << endl;
        else
            cout << "DOB:           " << getDayVal() << "/" << getMonthVal() << "/19" << getYearVal() << endl;
    }
    
    // This function is used to enter the array from the keyboard
    virtual void enterItemFromKeyboard()
    {
        
        cout << "Insert element then hit enter." << endl;
        cin >> day;
        cin >> month;
        cin >> year;
        cout << endl;
        
        // item filled
        empty=false;
    }
    
    // This function is used to generate the array from random values
    virtual void generateRandomItem()
    {
        int random;
        int random2;
        random = rand() % 12+1;
        random2 = rand() % 99;
        switch(random)
        {
            case 1:
                day = rand() % 31+1;
                month = 1;
                break;
            case 2:
                day = rand() % 28+1;
                month = 2;
                break;
            case 3:
                day = rand() % 31+1;
                month = 3;
                break;
            case 4:
                day = rand() % 30+1;
                month = 4;
                break;
            case 5:
                day = rand() % 31+1;
                month = 5;
                break;
            case 6:
                day = rand() % 30+1;
                month = 6;
                break;
            case 7:
                day = rand() % 31+1;
                month = 7;
                break;
            case 8:
                day = rand() % 31+1;
                month = 8;
                break;
            case 9:
                day = rand() % 30+1;
                month = 9;
                break;
            case 10:
                day = rand() % 31+1;
                month = 10;
                break;
            case 11:
                day = rand() % 30+1;
                month = 11;
                break;
            case 12:
                day = rand() % 31+1;
                month = 12;
                break;
            default:
                cout << " YOUR CODE IS BROKEN - AGAIN" << endl;
        }
        if (random2 <= 9)
            year =random2 +10;
        else
            year = random2;
        empty=false;
    }
    
    // Function is used to check the items for sorting the array
    virtual bool IsLargerThan(basic_item* other_item, basic_sort_criteria* sort_criteria=NULL)
    {
        bool result=false;
        // if the other item is "empty" (non allocated) don't do any comparison
        if(other_item==NULL)
            return false;
        
        // first typecast the other item to confimr it is the same as this;
        dateOfBirth* typecasted_other_item = typecastItem(other_item, this);
        
        // check that it worked
        if(typecasted_other_item==NULL)
        {
            cout << "Other item is not of type integer_item." << endl;
            return false;
            // items of the wrong type (or null pointers) will be pushed to the end of the list
        }
        
        // now verify if the other item is larger than the current
        if( getYearVal() > (typecasted_other_item->getYearVal()) )
            result=true;
        
        
        // chek if there are sorting options to apply
        if(sort_criteria!=NULL)
        {
            // if sorting is in descending order the result is reversed
            if( !( sort_criteria->getAscending() ) )
                result=!result;
        }
        
        return result;
    }
    
    // Function is used to release the memory
    virtual void deallocateItem(basic_item* item_ptr)
    {
        // first typecast the other item to confimr it is the same as this;
        dateOfBirth* typecasted_item_ptr = typecastItem(item_ptr, this);
        
        // check that it worked
        if(typecasted_item_ptr==NULL)
        {
            // items of the wrong type (or null pointers)
            cout << "Error in deallocateItem (for firstNameItem): "<< endl << "Other item is not of type firstNameItem." << endl;
            return;
        }
        delete typecasted_item_ptr;
    }
    virtual basic_item* allocateItem()
    {
        dateOfBirth* result = new dateOfBirth;
        if(result==NULL)
            cout << " Error in firstNameItem::allocateItem(): out of memory"<< endl;
        return result;
    }
};

class arrayElement: public basic_item{
protected:
    firstNameItem firstName;
    lastNameItem lastName;
    studentNumberItem studentNumber;
    studentEmail studentEmail;
    degreeProgramme degree;
    markCGS CGS;
    dateOfBirth DOB;
    nationalityItem nationality;
    
    int row;
    string first;
    string last;
    string bob;
    
public:
    // default constructor and destructor: do nothing
    arrayElement(){;}
    ~arrayElement(){;}
    string ln=last;
    string fn=first;
    
    string getArrayElement(){
        first=firstName.getStringVal();
        last=lastName.getStringVal();
        bob=studentNumber.getStringVal();
        bob=nationality.getStringVal();
        bob=studentEmail.getStringVal();
        bob=degree.getStringVal();
        bob=CGS.getDoubleVal();
        bob=DOB.getDayVal();
        bob=DOB.getMonthVal();
        bob=DOB.getYearVal();
        return bob;
    }
    
    // This function is used to print the array on screen
    virtual void printItemOnScreen()
    {
        firstName.printItemOnScreen();
        lastName.printItemOnScreen();
        studentNumber.printItemOnScreen();
        nationality.printItemOnScreen();
        studentEmail.printItemOnScreen();
        degree.printItemOnScreen();
        CGS.printItemOnScreen();
        DOB.printItemOnScreen();
    }
    
    // This function is used to enter the array from the keyboard
    virtual void enterItemFromKeyboard()
    {
        firstName.enterItemFromKeyboard();
        lastName.enterItemFromKeyboard();
        studentNumber.enterItemFromKeyboard();
        nationality.enterItemFromKeyboard();
        studentEmail.enterItemFromKeyboard();
        degree.enterItemFromKeyboard();
        CGS.enterItemFromKeyboard();
        DOB.enterItemFromKeyboard();
    }
    
    // This function is used to generate the array from random values
    virtual void generateRandomItem()
    {
        firstName.generateRandomItem();
        lastName.generateRandomItem();
        studentNumber.generateRandomItem();
        nationality.generateRandomItem();
        studentEmail.generateRandomItem();
        degree.generateRandomItem();
        CGS.generateRandomItem();
        DOB.generateRandomItem();
    }
    
    // Function is used to check the items for sorting the array
    virtual bool IsLargerThan(basic_item* other_item, basic_sort_criteria* sort_criteria=NULL)
    {
        bool result=false;
        // if the other item is "empty" (non allocated) don't do any comparison
        if(other_item==NULL)
            return false;
        
        // first typecast the other item to confimr it is the same as this;
        arrayElement* typecasted_other_item = typecastItem(other_item, this);
        
        // check that it worked
        if(typecasted_other_item==NULL)
        {
            cout << "Other item is not of type integer_item." << endl;
            return false;
            // items of the wrong type (or null pointers) will be pushed to the end of the list
        }
        
        // now verify if the other item is larger than the current
        if( getArrayElement() > (typecasted_other_item->getArrayElement()) )
            result=true;
        
        
        // chek if there are sorting options to apply
        if(sort_criteria!=NULL)
        {
            // if sorting is in descending order the result is reversed
            if( !( sort_criteria->getAscending() ) )
                result=!result;
        }
        
        return result;
    }
    
    // Function is used to release the memory
    virtual void deallocateItem(basic_item* item_ptr)
    {
        // first typecast the other item to confimr it is the same as this;
        arrayElement* typecasted_item_ptr = typecastItem(item_ptr, this);
        
        // check that it worked
        if(typecasted_item_ptr==NULL)
        {
            // items of the wrong type (or null pointers)
            cout << "Error in deallocateItem (for firstNameItem): "<< endl << "Other item is not of type firstNameItem." << endl;
            return;
        }
        delete typecasted_item_ptr;
    }
    virtual basic_item* allocateItem()
    {
        arrayElement* result = new arrayElement;
        if(result==NULL)
            cout << " Error in firstNameItem::allocateItem(): out of memory"<< endl;
        return result;
    }
};



#endif
