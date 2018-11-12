
#include <iostream>
#include <string>

// to use ostringstream:
#include <sstream>


// to use ofstream
#include <fstream>

using namespace std;


// INSTRUCTIONS: THE FOLLOWING ARE SOME EXAMPLES USING STRING; 
// L4 students are expected to go through this content applying critical thinking
// i.e. do not expect to just do copy/paste have the assignment be done for you.


string stringtestfunc()
{
	string slocal = "String returned by a function";
	return slocal;  
}


// any of the following can be called from main 
void stringtestmain()
{
	/////
	string s1;
    s1 = "Test string";
	
    cout << "s1  is: " << s1 << endl;

    // copy constructor
    //string s2 (s1);
	
	string s2;
    s2=s1;
	
	cout << "s2  is: " << s2 << endl;
	
	// concatenate strings
	s1+= " is now longer";
	s2+= " is different";
	
	cout << "s1  is: " << s1 << endl;
	cout << "s2  is: " << s2 << endl;
	
	
	// example of comparing strings
	int comp = s1.compare(s2);
    cout << "String s1 is ";
	if(comp == 0)
		cout << "equal";
	else
		cout << "not equal";
    cout << " to string s2" << endl;
	
	comp = s2.compare(s1);

	/////

	string s3;
	cout << "Enter string : "<< endl;
	getline(cin,s3);
	cout << "s3  is: " << s3 << endl;
	
	// only for a single-word entry, you can use this
	//cout << "Enter string again : "<< endl;	
	//cin >> s3;
	//cout << "s3  is: " << s3 << endl;


	
	// example of a string created inside a function and returned
	//string anotherstring=stringtestfunc();
	//cout << anotherstring << endl;


	//// IO to/form file
	
	// with the "empty" basedirectory the file should be where the source files are 
	string basedir="";

	// otherwise put a full path here (use \\ instead of \ )
	//string basedir="H:\\fverdiccABDN\\UniABDN\\MyCourses\\EG40GA\\LectureNoteRepository\\EE40GA_Sort\\IOfiles\\";
	
	
	string filename, fullpathfilename; 

	cout << "The base directory is: " << endl << basedir << endl;
	
	cout << "enter output filename (.txt)" << endl;
	cin >> filename;
	fullpathfilename = basedir + filename;
	
	//output file	
	ofstream outfile;
	cout << "Writing to file "<< endl << fullpathfilename << endl;
	
	// by dafult this opens the file in text mode
	outfile.open (fullpathfilename);
	
	if(outfile.is_open())
	{
		int localint=100;
		outfile << "Writing this to a file.\n";
		outfile << s3 << endl;
		outfile << "Also Writing a number as text to this file: " << localint;
		
		outfile.close();
	}
	else
		cout << "File" << endl <<fullpathfilename << endl <<"did not open correctly.";

	
	// now read from the same file
	ifstream infile;
	cout << "Reading from file "<< endl << fullpathfilename << endl;
	
	// by dafult this opens the file in text mode
	infile.open (fullpathfilename);
	
	if(infile.is_open())
	{
		string currentlinecontent;

		// read line after line
		while ( getline(infile,currentlinecontent) )
		{
			cout << currentlinecontent << endl;
		}
		
		infile.close();
	}
	else
		cout << "File" << endl <<fullpathfilename << endl <<"did not open correctly.";

	
	/////////


	// this can convert numbers to strings (may not be eeded after all)
	int inpnum; 
	string s4;
	ostringstream theconverter;
	//cout << "Enter number: "<< endl;
	
	//cin >> inpnum;	
	//cout << "number is :" << inpnum << endl;
	// stored and manipulated as a number
	
	// convert to a string to write as text (in txt file for example)
	//theconverter << inpnum;
	//s4=theconverter.str();

	//cout << "s4  is: " << s4 << endl;
	///////////////////////


}