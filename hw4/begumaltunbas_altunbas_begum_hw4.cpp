#include <iostream>
#include "Hash_header.h"
#include "Bst_header.h"
//#include "NEWTABLE.h"
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <chrono>
#include "Header_sort.h"



using namespace std;

struct DocumentItem {
	string documentName;
	int count;
};
struct WordItem  {
	string word;
	vector <DocumentItem> document_list ;
	// List of DocumentItemís. In order to keep the documents
	//you can again use the BST that you are going to implement.

};




WordItem  ITEM_NOT_FOUND;
string my_string="";


//BST IMPLEMENTATION
BstTree<string, WordItem > myTree(my_string,ITEM_NOT_FOUND);

//vector created for sorting later
vector <WordItem> myvector ;


bool  if_number (string s ) //this function checks if the user input coordinates contain  alphabetical letters
{
	for (int i=0 ; i<s.length(); i++)
	{
		char c = s.at(i) ;
		if ((c>= 48 && c<= 57) ) //0-9 kdr
		{
			return true ;

		}
	}
	return false;
}


bool if_exist(string &str,BstTree<string, WordItem > &myTree)
{
	if(myTree.find(str)=="")
		return false;
	else
		return true;
}


string toLower(string  word){

	for (int i = 0; i < word.length(); i++) {
		if (word[i] >= 65 && word[i] <= 90)
		{
			word[i]+= 32;
		}
	}
	return word;
}


string only_alpha(string & word)
{

	for (int i = 0; i < word.length(); i++)
	{
		if (word.at(i) < 97 || word.at(i) > 122) // if not a letter replace to space
			word.at(i) =  ' ';


	}
	return word;
}

int counter1=0 ;

void file_read_tree(string file_name, BstTree<string, WordItem > &myTree)
{
	ifstream inputfile ;
	string line ;
	
	inputfile.open(file_name) ;

	while(getline(inputfile,line))
	{

		istringstream iss (line) ;
		string word ;

		while (iss>>word)
		{
			word=toLower(word);
			word=only_alpha(word);
			istringstream iss4(word);
			while (iss4>>word)
			{

				if ( if_number(word)==false ) //if its string
				{
					// word=toLower(word) ;
					if (if_exist(word,myTree)==true) //if word occured before
					{
						bool flag = false ;
						WordItem * current_node = myTree.getNode(word) ;
						for (int i = 0; i <current_node->document_list.size() ; i++)
						{
							// check the list filename
							if (current_node->document_list[i].documentName == file_name )
							{
								flag = true; // occured before, just need to update  count
								current_node->document_list[i].count++ ;

							}
						}

						if (flag == false) //  we are on a different txt
						{
							DocumentItem newdoc;
							newdoc.count = 1;
							newdoc.documentName = file_name;
							current_node->document_list.push_back(newdoc);
						}

					}

					else { //if word didnt occur before

						WordItem item;
						item.word=toLower(word) ;
						DocumentItem details;
						details.documentName=file_name;
						details.count=1;

						item.document_list.push_back(details) ;

						myTree.insert(word,item);
						counter1 ++;
					}
				}
				else
				{
					;

				}

			}

		}

	}
	//cout<< counter1<< "unique"<<endl; 
}




// Hash Table create


bool if_exist_table(string &str,HashTable<string, WordItem > &myTable)
{
	if(myTable.find(str).word== "")
		return false;
	else
		return true;
}





HashTable<string, WordItem> myTable(my_string, ITEM_NOT_FOUND);
int counter2=0 ;

void create_table(string file_name, HashTable<string,  WordItem > &myTable)
{
	ifstream file;
	file.open(file_name.c_str()); // File is opened


	string line;
	while(getline(file, line)) // read each line , then process it
	{
		istringstream iss(line);
		string word;

		
		while (iss>>word)
		{
			word= toLower(word);
			// seperator
			string templine =  only_alpha(word);

			istringstream iss2(templine);
			string tempword;
			//vector <DocumentItem>empty ;
			//WordItem temp1( tempword,empty);

			while(iss2 >> tempword)
			{

				if ( if_number(tempword)==false ) //if its string
				{
					// if the word exists , update the corresponding hashnode
					//else , insert it to the hashtable
					bool existence = if_exist_table(tempword,myTable);
					if (existence == true) // means the word exists
					{
						//updateNode(tempint, filename);

						bool flag = false ;
						//int i= findPos (tempword) ;
						//WordItem current_node = myTable.find (tempword);

						WordItem * current_node = myTable.getNode_Tree(tempword) ;

						for (int i = 0; i <current_node->document_list.size() ; i++)
						{
							// check the list filename
							if (current_node->document_list[i].documentName == file_name )
							{
								flag = true; // occured before, just need to update  count
								current_node->document_list[i].count++ ;

							}
						}

						if (flag == false) //  we are on a different txt
						{
							DocumentItem newdoc;
							newdoc.count = 1;
							newdoc.documentName = file_name;
							current_node->document_list.push_back(newdoc);
						}


					}
					else // means the word doenst  exist
					{
						WordItem item;
						//item.word = tempword;
						item.word=toLower(tempword) ;
						DocumentItem docitem;
						docitem.count = 1;
						docitem.documentName = file_name;
						item.document_list.push_back(docitem);
						myTable.insert(tempword,item);
						counter2++;
					}

				}
				else 
					;


			}
		}

	}

	//cout<< counter2 <<"unique table" <<endl ;
}







void findtable(vector <WordItem*>outputs)
{
	int counter=0 ;
	for (int i=0 ; i< outputs.size() ;i++)
	{
		if (if_exist_table(outputs[i]->word,myTable)==true) //if (myTable.find(outputs[i]->word).word !="")
			counter++ ;

	}

}

void findtree(vector <WordItem*>outputs)
{
	int counter=0 ;
	for (int i=0 ; i< outputs.size() ;i++)
	{
		if (if_exist(outputs[i]->word,myTree)==true) //if (myTree.find(outputs[i]->word) !="")
			counter++ ;

	}

}

//VECTOR FUNCTS


bool vector_exist (string word,vector<WordItem> &vec)
{
	for (int i=0 ; i< vec.size(); i++ )
    {
        if ((vec[i].word == word) ){
            return true ;
        }
    }
    
    return false ;


}

WordItem* return_index (string word ,vector<WordItem> &vec)
{
	for (int i=0 ; i< vec.size(); i++ )
    {
        if ((vec[i].word == word) ){
            return &(vec[i]) ;
        }
    }
    
    return NULL ;



}







void file_read_vector (string file_name,vector<WordItem> &vec )
{
	
	ifstream file;
	file.open(file_name.c_str()); // File is opened


	string line;
	while(getline(file, line)) // read each line , then process it
	{
		istringstream iss(line);
		string word;

		
		while (iss>>word)
		{
			word= toLower(word);
			// seperator
			string templine =  only_alpha(word);

			istringstream iss2(templine);
			string tempword;
			//vector <DocumentItem>empty ;
			//WordItem temp1( tempword,empty);

			while(iss2 >> tempword)
			{

				if ( if_number(tempword)==false ) //if its string
				{
					// if the word exists , update the corresponding hashnode
					//else , insert it to the hashtable
					bool existence = vector_exist(tempword,vec);
					if (existence == true) // means the word exists
					{

						bool flag = false ;
					//WordItem * current_node = myTable.getNode_Tree(tempword) ;
						WordItem *current_node=return_index(tempword,vec);

						for (int i = 0; i <current_node->document_list.size() ; i++)
						{
							// check the list filename
							if (current_node->document_list[i].documentName == file_name )
							{
								flag = true; // occured before, just need to update  count
								current_node->document_list[i].count++ ;

							}
						}

						if (flag == false) //  we are on a different txt
						{
							DocumentItem newdoc;
							newdoc.count = 1;
							newdoc.documentName = file_name;
							current_node->document_list.push_back(newdoc);
						}


					}
					else // means the word doenst  exist
					{
						WordItem item;
						//item.word = tempword;
						item.word=toLower(tempword) ;
						DocumentItem docitem;
						docitem.count = 1;
						docitem.documentName = file_name;
						item.document_list.push_back(docitem);
						//myTable.insert(tempword,item);
						vec.push_back(item) ;
						counter2++;
					}

				}
				else 
					;


			}
		}

	}



}






double speed_func(double a, double b)
{
	

	double speed= a/b ;
	return  speed ;
	

}





void time_func(vector <WordItem*> outputs,vector <WordItem*>outputs_table)
{

	int k = 10000;
	auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < k; i++)
	{


		findtree(outputs) ;

		// QueryDocuments(with BST);
	}
	auto BSTTime = std::chrono::duration_cast<std::chrono::nanoseconds>
		(std::chrono::high_resolution_clock::now() - start);
	cout << "Binary Search Tree Time:: " << BSTTime.count() / k << "\n";
	start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < k; i++)
	{
		// QueryDocuments (with hashtable);


		findtable(outputs_table) ;

	}
	auto HTTime = std::chrono::duration_cast<std::chrono::nanoseconds>
		(std::chrono::high_resolution_clock::now() - start);
	cout << "Hash Table Time: " << HTTime.count() / k << "\n";


	double bst_time_double =BSTTime.count() / k ;

	/*double speed= bst_time_double/(HTTime.count()/k);
	cout<< "Speed Up: "<< speed ;*/
	
}

int binarySearch(vector<WordItem> &myvec, int l, int r, string &some_word) 
{ 
    while (l <= r) { 
        int m = l + (r - l) / 2; 
  
        // Check if x is present at mid 
		if (myvec[m].word == some_word) 
            return m; 
  
        // If x greater, ignore left half 
		if (myvec[m].word < some_word) 
            l = m + 1; 
  
        // If x is smaller, ignore right half 
        else
            r = m - 1; 
    } 
  
    // if we reach here, then element was 
    // not present 
    return -1; 
}

void binary_2(vector<WordItem> &smt,vector<string> &query_lines,int n )
{
	int count=0 ;

	for (int i = 0; i< query_lines.size() ; i++)
	{
		int a=binarySearch(smt,0,n-1,query_lines[i]);
		if (a!=-1)
			count++;
	}


}
vector<double> time_2 (vector <WordItem*> outputs,vector <WordItem*>outputs_table) //int n,vector<WordItem> &heapvec,vector<string> &query_words)
{
	vector <double> numbers; 
	int k = 10000;
    clock_t begin_time = clock();
    for (int i = 0; i < k; i++)
		findtree(outputs) ;
        // QueryDocuments with Binary Search Tree
    double endBST = float(clock() - begin_time);

    cout << "\nBinary Search Tree Time: " << endBST / k << "\n";
	numbers.push_back(endBST/k) ;


	begin_time = clock();
    for (int i = 0; i < k; i++)
		findtable(outputs_table) ;
        // QueryDocuments with Hash Table
    double endHT = float(clock() - begin_time);

    cout << "\nHash Table Time: " << endHT / k << "\n";
   numbers.push_back(endHT/k) ;


   return numbers;

}



 
  



int main() {

	int nu_files;
	string file_name,query_line;
	vector<string> file_name_list;


	cout<< "Enter number of input files:";
	cin>>nu_files;
	for (int i=1; i<=nu_files;i++){
		cout<<"Enter "<<i <<". file name:";
		cin>>file_name;
		file_name_list.push_back(file_name);
		file_read_tree(file_name,myTree);
		//create_table(file_name, myTable);

	}


	for (int j=0; j<nu_files; j++)
	{
		create_table(file_name_list[j],myTable);

	}

	myTable.resulting(); 



	for (int j=0; j<nu_files; j++)
	{
		file_read_vector(file_name_list[j],myvector);

	}

	vector <WordItem>insertionvec (myvector);
	vector <WordItem>quickvec1 (myvector);
	vector <WordItem>quickvec2 (myvector);
	vector <WordItem>quickvec3 (myvector);
	vector <WordItem>mergevec (myvector);
	vector <WordItem>heapvec (myvector);

	cout<< "Enter queried words in one line: " ;
	//cin>>query_line;


	cin.ignore();
	getline(cin,query_line);

	query_line= toLower(query_line);


	vector <WordItem *> outputs; //tree
	vector <WordItem *> outputs_table;

	query_line=only_alpha(query_line);
	istringstream iss2(query_line) ;
	string myword;




    
	vector<string > query_words ;
	while (iss2>>myword)
	{


		if (if_exist(myword,myTree)==false) // && if_exist_table(mystring,myTable)==false)
		{
			cout<< "No document contains the given query"<<endl ;
			cout<< "No document contains the given query" <<endl;
			cout<< "No document contains the given query" <<endl;
			//time_func(outputs,outputs_table);
			time_2(outputs,outputs_table);

			//cin.get();
			//cin.ignore();
			return 10 ;

		}
		else 
		{
			WordItem * smt= myTree.getNode(myword) ;
			outputs.push_back(smt);
			WordItem * smt2=myTable.getNode_Tree(myword);
			outputs_table.push_back(smt2);
		}

		

		query_words.push_back(myword) ;
	}
	


	for (int b=1; b<=3 ;b++)
	{

		bool flag=true;
		//bool flag2=true;
		if (outputs.size()!=0)
		{
			for (int i=0 ; i < file_name_list.size() ;i++)
			{
				//cout<<"In Document " <<file_name_list[i] << ",";
				for (int k=0; k<outputs.size();k ++ )
				{

					for (int j=0 ;j<outputs[k]->document_list.size(); j++)
					{
						//cout<<"In Document " <<file_name_list[i] << ",";
						if (outputs[k]->document_list[j].documentName == file_name_list[i] )
						{

							while (flag==true)
							{
								cout<<"In Document " <<outputs[k]->document_list[j].documentName << ",";
								flag=false;
							}

							//cout<<"In Document " <<outputs[k]->document_list[j+1].documentName << ",";

							cout<<  outputs[k]->word << "  found " ;
							cout <<outputs[k]->document_list[j].count << " times" ;

							if (k!=outputs.size()-1)
							{
								cout<< "," ;
								flag=false;
							}
							else {

								cout<< "."<<endl;
								flag=true;
							}
						}
					}

				}

			}

		}
	}
	
	//time_func(outputs,outputs_table);
	/*int n = sizeof(myvector) / sizeof(myvector[0]); */
	//int t = 10000;
	//auto start1 = std::chrono::high_resolution_clock::now();
	//start1 = std::chrono::high_resolution_clock::now();
	//for (int i = 0; i < t; i++)
	//{
	//	// QueryDocuments (with hashtable);

	//	binarySearch(myvector,0, n - 1,myword);
	//	//findtable(outputs_table) ;

	//}
	//auto BinaryTime = std::chrono::duration_cast<std::chrono::nanoseconds>
	//	(std::chrono::high_resolution_clock::now() - start1);
	//cout << "Binary Search Time: " << BinaryTime.count() / t << "\n";



	
	
	vector<double>timesof= time_2(outputs,outputs_table) ;
	

	int t=10000;
	
	int k = 100;
	//int k = 10;
    clock_t begin_time = clock();

	begin_time = clock();
	for (int i = 0; i < k; i++)
	{
		heapvec=myvector;
		heapsort(heapvec) ;
		//heapvec= heapsort(myvector) ;
	}
		//heapvec= heapsort(myvector) ;
    double endHT = float(clock() - begin_time);


	
	int n=heapvec.size() ;


	begin_time = clock();
	for (int i = 0; i < t; i++)
		 binary_2(heapvec,query_words,n); 
        // QueryDocuments with Binary Search
    double endBS1 = float(clock() - begin_time);
    cout << "\nBinary Search Time: " << endBS1 / t << "\n";



	cout<< endl ;


   
	begin_time = clock();
	for (int i = 0; i < k; i++){
		quickvec1=myvector ; 
		quicksort(quickvec1, 0, myvector.size( ) - 1); //,"median");
		
	}
	
	double endBS = float(clock() - begin_time);
    cout << "Quick Sort(median) Time: " << endBS / k << "\n";
	

	begin_time = clock();
	for (int i = 0; i < k; i++){
		quickvec2=myvector ; 
		quicksortR(quickvec2, 0, myvector.size( ) - 1 ) ;
		//quickSortrandom(quickvec2, 0, myvector.size( ) - 1);
		
	
	}
	double endBS2 = float(clock() - begin_time);
    cout << "Quick Sort(random) Time: " << endBS2 / k << "\n";

	
	
	begin_time = clock();
    for (int i = 0; i < k; i++){
		 
		quickvec3=myvector ;
		quicksortF(quickvec3, 0, myvector.size( ) - 1) ;//,"first");
		
		//quickvec1=quickSortG(myvector, 0, myvector.size( ) - 1,"median") ;
	}
		
      
    double endBS3 = float(clock() - begin_time);
    cout << "Quick Sort(first) Time: " << endBS3 / k << "\n";





	begin_time = clock();
	for (int i = 0; i < k; i++) 
	{
		mergevec=myvector;
		mergeSort(mergevec) ;
		
	
	}

    double endBS4 = float(clock() - begin_time);
    cout << "Merge Sort Time: " << endBS4 / k << "\n";
	


	/*begin_time = clock();
    for (int i = 0; i < k; i++)
			heapsort(heapvec) ;
    double endHT = float(clock() - begin_time);*/

    cout << "Heap Sort Time: " << endHT / k << "\n";




	begin_time = clock();
	for (int i = 0; i < k; i++){
		insertionvec=myvector;
		insertionSort(insertionvec) ;
		
	}
			//insertionvec=insertionSort(myvector) ;
    double endBST = float(clock() - begin_time);

    cout << "Insertion Sort Time: " << endBST / k << "\n";









	//int k = 100;
	//auto start = std::chrono::high_resolution_clock::now();
	////QUICK SORTSS
	//for (int i = 0; i < k; i++)
	//{
	//	quicksort(quickvec1,"median") ;

	//	
	//	// QueryDocuments(with BST);
	//}
	//auto MedianTime = std::chrono::duration_cast<std::chrono::nanoseconds>
	//	(std::chrono::high_resolution_clock::now() - start);
	//cout << "Quick Sort(median) Time: " << MedianTime.count() / k << "\n";
	//
	//start = std::chrono::high_resolution_clock::now();
	//for (int i = 0; i < k; i++)
	//{
	//	// QueryDocuments (with hashtable);

	//	quicksort(quickvec2,"random") ;
	//	

	//}
	//auto RandomTime = std::chrono::duration_cast<std::chrono::nanoseconds>
	//	(std::chrono::high_resolution_clock::now() - start);
	//cout << "Quick Sort(random) Time: " << RandomTime.count() / k << "\n";


	//start = std::chrono::high_resolution_clock::now();
	//for (int i = 0; i < k; i++)
	//{
	//	// QueryDocuments (with hashtable);

	//	quicksort(quickvec3,"first") ;
	//	

	//}
	//auto FirstTime = std::chrono::duration_cast<std::chrono::nanoseconds>
	//	(std::chrono::high_resolution_clock::now() - start);
	//cout << "Quick Sort(first) Time: " << FirstTime.count() / k << "\n";



	////MERGE
	//start = std::chrono::high_resolution_clock::now();
	//for (int i = 0; i < k; i++)
	//{
	//	// QueryDocuments (with hashtable);

	//	mergeSort(mergevec) ;
	//	

	//}
	//auto MergeTime = std::chrono::duration_cast<std::chrono::nanoseconds>
	//	(std::chrono::high_resolution_clock::now() - start);
	//cout << "Merge Sort Time: " << MergeTime.count() / k << "\n";


	////HEAP SORT

	//start = std::chrono::high_resolution_clock::now();
	//for (int i = 0; i < k; i++)
	//{
	//	// QueryDocuments (with hashtable);

	//	heapsort(heapvec) ;
	//	

	//}
	//auto HeapTime = std::chrono::duration_cast<std::chrono::nanoseconds>
	//	(std::chrono::high_resolution_clock::now() - start);
	//cout << "Heap Sort Time: " << HeapTime.count() / k << "\n";






	////INSERTION SORT
	//start = std::chrono::high_resolution_clock::now();
	//for (int i = 0; i < k; i++)
	//{
	//	// QueryDocuments (with hashtable);

	//	insertionSort(insertionvec) ;
	//	

	//}
	//auto insertTime = std::chrono::duration_cast<std::chrono::nanoseconds>
	//	(std::chrono::high_resolution_clock::now() - start);
	//cout << "Insertion Sort Time: " << insertTime.count() / k << "\n";


cout<<endl ;
cout<< "Speed Up BST/HST:"<<speed_func(timesof[0],timesof[1])<<endl;
cout<< "Speed Up Merge Sort/Quick Sort(Median):"<< speed_func(endBS4 / k,endBS / k)<<endl;
cout<< "Speed Up Heap Sort/Quick Sort(Median):"<< speed_func(endHT/ k,endBS / k)<<endl;
cout<< "Speed Up Insertion Sort/Quick Sort(Median):"<< speed_func(endBST / k,endBS / k)<<endl;

cout<< endl ;
cout << "Speed Up Binary Search / Binary Search Tree Time: " << (endBS1/t)/timesof[0]<<endl;
cout << "Speed Up Binary Search / Hash Table Time: "<< (endBS1/t)/timesof[1] <<endl;



	//cin.get();
	//cin.ignore();
	return 0;
}
