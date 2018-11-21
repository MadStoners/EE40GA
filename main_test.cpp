#include <iostream>
#include <string>

#include "ArrayItem.h"
#include "generalArray.h"




void test_array(int array_size, basic_item* ref_item)
{
	basic_sort_criteria srt_crt;
	general_array test_array;
    //integer_item test_item;
    firstNameItem testItem;
    int key;
    // attach the "integer item" as reference item
	test_array.attachRefrenceItem(ref_item);
	
    // now allocate the array
	test_array.allocateArray(array_size);
	
    // print content to screen (empty)
	cout << " Array is empty at this time." << endl << endl;
	test_array.printArrayOnScreen();
    
    //fill with random items
	cout << endl << " Filling Array with random values." << endl;
	test_array.fillRandomValueArray();
	test_array.printArrayOnScreen();
    cout<< "Please select an option: " << endl << " 0 - Ascending" << endl << " 1 - Decending" << endl;
    cin >> key;
    cout << "Sort the array in order selected" << endl;
    srt_crt.setAscending(key);
	
    // sort the array
	cout << endl << " Sorting Array." << endl;
	test_array.bubblesort(&srt_crt);
	test_array.printArrayOnScreen();
	cout << endl;
}
    


int main()
{
	int array_size = 10;
	int temp;	
	// Used as "example item" by the general_array to populate the entire array with integer_item 
	//integer_item ref_int_item;
    arrayElement refArrayElement;
	// Used as "example item" by the general_array to populate the entire array with neg_int_item 
    // neg_int_item ref_nint_item;
	// First test with the integer item
	//cout << "Testing array with integer (positve and negative) items: " << endl << endl;
	//test_array(array_size, &ref_int_item);
    //cout << "Done. Enter any number to progress to the next test." << endl;
	//cin>>temp;
    
    cout << "Testing array with string items: " << endl << endl;
    test_array(array_size, &refArrayElement);
    cout << "Done. Enter any number to progress to the next test." << endl;
    cin>>temp;
    
    /*
	// Next test with the negative ingteger item
	cout << "Testing array with NEGATIVE ONLY integer items: " << endl << endl;
	test_array(array_size, &ref_nint_item);
	cout << "Done. Enter any number to finish." << endl;
	cin>>temp;
     */
return 0;
}
