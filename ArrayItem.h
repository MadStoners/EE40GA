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

// Deriving own first name class
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
            cout << "Item value is " << getStringVal() << " . " << endl;
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

class arrayElement: public basic_item{
protected:
    firstNameItem first_name;
    
public:
    // default constructor and destructor: do nothing
    arrayElement(){;}
    ~arrayElement(){;}
    
    string getArrayElement(){string bob=first_name.getStringVal();return bob;}
    
    // This function is used to print the array on screen
    virtual void printItemOnScreen()
    {
        first_name.printItemOnScreen();
    }
    
    // This function is used to enter the array from the keyboard
    virtual void enterItemFromKeyboard()
    {
        first_name.enterItemFromKeyboard();
    }
    
    // This function is used to generate the array from random values
    virtual void generateRandomItem()
    {
        first_name.generateRandomItem();
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
        
        // now verify if the other item is larger than the curren
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
