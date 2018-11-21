
#include "ArrayItem.h"
#include "generalArray.h"





void test_array(int array_size, basic_item* ref_item)
{
	basic_sort_criteria srt_crt;
	general_array test_array;
    integer_item test_item;
    bool key;
    // attach the "integer item" as reference item
	test_array.attachRefrenceItem(ref_item);
	// now allocate the array	
	test_array.allocateArray(array_size);
	// print content to screen (empty)
	cout << " Array is empty at this time." << endl << endl;
	test_array.printArrayOnScreen();
    // Fill array with values from the keyboard
    /*cout << "Please manually fill the array" << endl << endl;
    test_array.enterArrayFromKeyboard();*/
	
    // fill with random items
	cout << endl << " Filling Array with random values." << endl;
	test_array.fillRandomValueArray();
    
	// print content to screen
    test_array.printArrayOnScreen();
    cout << "Sort the order of the array to: 0 - Ascending or 1 - Descending" << endl;
    cin >> key;
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
	studentNumberItem refSNItem;

	// First test with the integer item
	cout << "Testing array with integer (positve and negative) items: " << endl << endl;
	test_array(array_size, &refSNItem);
    cout << "Compiled" << endl;
    cout << "Done. Enter any number to progress to the next test." << endl;
	cin>>temp;
return 0;
}
