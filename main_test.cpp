
#include "arrayItem.h"
#include "generalArray.h"





void test_array(int array_size, basic_item* ref_item)
{
	basic_sort_criteria srt_crt(true);
	general_array test_array;	
	// attach the "integer item" as referecen item
	test_array.attachRefrenceItem(ref_item);
	// now allocate the array	
	test_array.allocateArray(array_size);
	// print content to screen (empty)
	cout << " Array is empty at this time." << endl << endl;
	test_array.printArrayOnScreen();
	// fill with random items
	cout << endl << " Filling Array with random values." << endl;
	test_array.fillRandomValueArray();
	// print content to screen
	test_array.printArrayOnScreen();
	// sort the array 
	cout << endl << " Sorting Array." << endl;
	test_array.bubblesort(&srt_crt);
	test_array.printArrayOnScreen();
	cout << endl;
}


void main()
{
	int array_size = 10;
	int temp;	
	// Used as "example item" by the general_array to populate the entire array with integer_item 
	integer_item ref_int_item;
	// Used as "example item" by the general_array to populate the entire array with neg_int_item 
	neg_int_item ref_nint_item;
	// First test with the inger item
	cout << " Testing array with integer (positve and negative) items: " << endl << endl;
	test_array(array_size, &ref_int_item);
	cout << " Done. Enter any nymber to progress to the next test." << endl;
	cin>>temp;
	// Next test with the negative ingteger item
	cout << " Testing array with NEGATIVE ONLY integer items: " << endl << endl;
	test_array(array_size, &ref_nint_item);
	cout << " Done. Enter any nymber to finish." << endl;
	cin>>temp;
}
