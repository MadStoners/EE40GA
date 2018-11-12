#ifndef __GENERALARRAY_H_
#define __GENERALARRAY_H_


#include "arrayItem.h"




// version with inheritance

class general_array{
protected:
	
	// "reference item" has to be initialized with the address  
	// of a (non-base class) valid object, allocated on the heap
	basic_item *reference_item;

	// this is an array of pointers.
	// each pints to a generic element
	basic_item **thearray;
	
	// number of array entries allocated
	int max_arraysize;
	bool memallocated;

	// number of array entries used
	int tot_items;
	
	// index of current item (may be useful)
	int current_index;

	// functions that are needed by each derived class to do sorting (this is useful for bublbesort
	bool swapElements(int elem1_index, int elem2_index)
	{
		// check that the memory is allocated and that the element indexes are within array boundary
		if(memIsAllocated() && checkIndexIsAllowed(elem1_index) && checkIndexIsAllowed(elem2_index) )
		{
			basic_item* temp_swap;
			temp_swap=thearray[elem1_index];
			thearray[elem1_index]=thearray[elem2_index];
			thearray[elem2_index]=temp_swap;
			return true;
		}
		return false;
	}
	
	// allocate item on heap for the specific type (calling the porper constructor)
	basic_item* allocateSpecificItem()
	{
		basic_item* result = NULL;
		if(reference_item!=NULL)
			result=reference_item->allocateItem();
		return result;
	}

	// remove item from heap for the specific type  (calling the porper distructor)
	void deallocateSpecificItem(basic_item* item_ptr)
	{
		if(reference_item!=NULL && item_ptr!=NULL)
			reference_item->deallocateItem(item_ptr);
	}

	void deallocateArrayContent()
	{
		if( (memIsAllocated()) && (getMaxSize()>0) )
		{
			basic_item* curr_elem_ptr;
			// delete all items that have been allocated
			for(int index=0; index<getMaxSize();index++)
			{
				curr_elem_ptr=getNremoveElementPtr(index);
				
				// call a function for the specific item
				if(curr_elem_ptr!=NULL)
					deallocateSpecificItem(curr_elem_ptr);
			}
			resetCurrIndexDefault();
		}
	}

	void deallocateArray()
	{
		deallocateArrayContent();
		if( (memIsAllocated()) && (getMaxSize()>0) )
		{
			// now deallocate the memory for the array itself
			// if calloc is used to allocate
			free(thearray);
			// if new is used to allocate
			//delete thearray;
			thearray=NULL;
			memallocated=false;	
			max_arraysize=0;
		}
		// option to deallocate the referece item (that was allocated externally)
		//if(reference_item!=NULL)
		//	delete reference_item;
	}

	//  ---- following functions give direct acees to elemt pointers: use for advanced stuff only ---- 
	// gives direct access an element: only to be used by memeber functions;
	// It leaves the element in the array.
	// [ this is useful for the bubblesort (and mergesort) ]
	basic_item *getElementPtr(int index)
	{
		// check that the memory is allocated and that the element indexes are within array boundary
		if( checkIndexIsAllowed(index) )
			return thearray[index];
		else
			return NULL;
	}
	// It removes the element from the array:
	// [ this is useful for the mergesort ]
	basic_item *getNremoveElementPtr(int index)
	{
		// copy the pointer
		basic_item *elem_ptr=getElementPtr(index);
		if(elem_ptr!=NULL)
		{
			// clear the pointer in the array, but the moemory it points to is still valid (and the pointer is returned)
			thearray[index]=NULL;
			tot_items--;
			if(tot_items<0)
				tot_items=0;
		}
		return elem_ptr;
	}
	// insert an element to the array (if requred position is available)
	bool insertElementPtr(int index, basic_item* item_ptr)
	{
		// check that the memory is allocated and that the element index is within array boundary
		if(memIsAllocated() && checkIndexIsAllowed(index) )
		{
			// add the item if array element is not occupied already
			if( (thearray[index]==NULL) )
			{
				if( (item_ptr!=NULL) )
				{
					thearray[index]=item_ptr;
					tot_items++;
					return true;
				}
				else
				{
					cout << endl << " Attempting to insert a NULL element." << endl; 
					return false;
				}
			}
			else
			{
				cout << endl << " Attempting to overwrite element at position " << index <<  " : not allowed." << endl; 
				return false;
			}
		}
		else
			return false;
	}
	//  -------------------------------------------------------------------------------------------------

	//reset the current index to the default value (-1)
	void resetCurrIndexDefault(){current_index=-1;}
	//
	void basic_initialization()
	{
		max_arraysize=0; memallocated=false; reference_item=NULL;
		tot_items=0; thearray=NULL; resetCurrIndexDefault();
	}
public: 
	general_array(){basic_initialization();}	
	// the derived object destructor should call deallocateArrayAndContent()
	~general_array(){deallocateArray();}
	//
	bool attachRefrenceItem( basic_item* ref_item_ptr)
	{
		// only performed once
		if(reference_item==NULL && ref_item_ptr!=NULL)
		{
			reference_item=ref_item_ptr;
			return true;
		}
		return false;
	}
	//
	bool memIsAllocated() {return memallocated;}
	int getMaxSize() {return max_arraysize;}
	int getTotItems() {return tot_items;}
	int getCurrIndex() {return current_index;}
	bool allocateArray(int in_arraysize)
	{
		if( (!memIsAllocated()) && (in_arraysize>0) )
		{
			if(reference_item==NULL)
			{
				cout << "Error in allocateArray(): reference item must be allocated first."<< endl;
				return false;
			}
			// calloc guarantees the pointer are set to NULL
			thearray=(basic_item **)calloc(in_arraysize, sizeof(basic_item *) );
			if(thearray!=NULL)
			{
				max_arraysize=in_arraysize;
				memallocated=true;
				// now fill with "empty" integer_items: each needs to be allocated
				for(int index=0;index<getMaxSize(); index++)
				{
					basic_item* emptyitem=allocateSpecificItem();
					if(emptyitem==NULL)
					{
						cout << "Error in allocateArray(): out of memory for item "<< index << endl;
						return false;
					}
					appendElementPtr(emptyitem);
				}
				resetCurrIndexToZero();
				return true;
			}
			else
				return false;
		}
		return false;
	}
	//
	bool checkIndexIsAllowed(int index)
	{
		if(memIsAllocated() && index>=0 && index<getMaxSize())
			return true;
		else
			return false;
	}
	bool resetCurrIndexToZero()
	{
		if(checkIndexIsAllowed(0))
		{
			current_index=0;
			return true;
		}
		return false;
	}
	// to insert or remove elemnts (useful with mergesort)
	bool appendElementPtr(basic_item* item_ptr)
	{
		bool success = insertElementPtr((current_index+1), item_ptr);
		if(success)
		{
			current_index++;
			//tot_items++;// not needed: this is done by insertElementPtr
		}
		return success;
	}
	basic_item * getNremoveCurrElementPtr()
	{
		basic_item* result=getNremoveElementPtr(current_index);
		current_index++;
		tot_items--;
		return result;
	}
	basic_item * getCurrElementPtr()
	{
		basic_item* result=getElementPtr(current_index);		
		return result;
	}	
	// to print content to screen with the right format
	bool printItemOnScreen(int position)
	{
		basic_item* elem_ptr=getElementPtr(position);
		if(elem_ptr!=NULL)
		{
			elem_ptr->printItemOnScreen();
			return true;
		}
		return false;
	}
	void printArrayOnScreen()
	{
		if( memIsAllocated() && (getTotItems()>0) )
		{
			// parse all positions
			for(int position=0; position<getMaxSize(); position++)
			{
				
				cout << "Element at position "<< position << " :" << endl;
				// print the item, if any
				if( printItemOnScreen(position) )
					cout << endl;
				else
					cout << "No Element in this position."<< endl;
			}
		}		
	}
	// input functions
	void enterArrayFromKeyboard()
	{
		if( memIsAllocated() && (getTotItems()>0) )
		{
			basic_item *curr_item;
			// parse all positions
			for(int position=0; position<getMaxSize(); position++)
			{
				curr_item=getElementPtr(position);
				if(curr_item==NULL)
					cout << "Element at position "<< position << "is not allocated" << endl;
				else
				{
					if(!curr_item->isEmpty())
						cout << "Enter value for element at position "<< position << endl;
					else
						cout << "Overwrtite value for element at position "<< position << endl;
					curr_item->enterItemFromKeyboard();
					tot_items++;
				}
			}
		}		
	}
	void fillRandomValueArray()
	{
		if( memIsAllocated() && (getTotItems()>0) )
		{
			basic_item *curr_item;
			// the following sets the random number generator differently
			// for evey execution, depending on the date/time.	
			srand((unsigned int)time(NULL));
			// parse all positions
			for(int position=0; position<getMaxSize(); position++)
			{
				curr_item=getElementPtr(position);
				if(curr_item==NULL)
					cout << "Element at position "<< position << "is not allocated" << endl;
				else
				{
					curr_item->generateRandomItem();
					tot_items++;
				}
			}
		}		
	}
	//
	void bubblesort(basic_sort_criteria* sort_criteria_ptr=NULL)
	{
		// Parse the array with a double for loop.
		// Select two successive items using the getElementPtr: items A and B
		// Use  A->IsLargerThan(B); if so, use swapElements(...).

		// note: sort_criteria_ptr is an optional paramteter (default is null)
		// when present, this can be used to determine the sorting type:
		// example 1: "ascending" or "discending" for simple items that hold numbers or strings
		// example 2: "sort by name" or "sort by student ID" for complex items that hold both names and numbers 

		
		// To be completed by students:
		// The version below produces the correct result but performs some unnecessary comparisons.
		// Modify it so that it becomes smore efficient
		
		for(int loop_index=0; loop_index<getMaxSize()-1; loop_index++)
		{
			for(int curr_index=0; curr_index<getMaxSize()-1; curr_index++)
			{
				bool comparison_result=true;
				basic_item* curr_item=getElementPtr(curr_index);
				basic_item* next_item=getElementPtr(curr_index+1);

				// in case there are "empty (non allocated) items"
				if(curr_item!=NULL)
					comparison_result=curr_item->IsLargerThan(next_item, sort_criteria_ptr);
				
				if(comparison_result)
					swapElements(curr_index, curr_index+1);
			}
		}
	}
	void mergesort(basic_sort_criteria* sort_criteria=NULL)
	{
		// To be completed by students;

		// sugestions (see mergesort for integers):
		// Create two "half-size arrays" for the two half/lists.
		// Move the items in the input array to the two "half-size arrays" using the getNremoveElementPtr(...) and appendElementPtr(...) 
		//
		// Sort the two "half-size arrays" recursively;
		//
		// For the two "half-size arrays", write a (privante) subroutine merge_sorted_lists to fill the intial array (now empty but allocated)
		// with the two "half-size arrays" that are now sorted; Use  A->IsLargerThan(B); .
		//
		// close recursion for a list of one element


		// note: sort_criteria_ptr is an optional paramteter (default is null): see bublerot for examples
		
	}
};






#endif