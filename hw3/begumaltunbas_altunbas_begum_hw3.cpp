//
//  main.cpp
//  hw3 _cs300
//
//  Created by Begum Altunbas on 29.07.2020.
//  Copyright © 2020 Begum Altunbas. All rights reserved.
//

#include <iostream>
#include "Header_tree.h"
#include "Header_hash.h"
//#include "NEWTABLE.h"
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <chrono>




using namespace std;

struct DocumentItem {
	string documentName;
	int count;
};
struct WordItem  {
	string word;
	vector <DocumentItem> document_list ;
	// List of DocumentItem’s. In order to keep the documents
	//you can again use the BST that you are going to implement.

};




WordItem  ITEM_NOT_FOUND;
string my_string="";


//BST IMPLEMENTATION
BstTree<string, WordItem > myTree(my_string,ITEM_NOT_FOUND);

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
	cout << "\nTime: " << BSTTime.count() / k << "\n";
	start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < k; i++)
	{
		// QueryDocuments (with hashtable);


		findtable(outputs_table) ;

	}
	auto HTTime = std::chrono::duration_cast<std::chrono::nanoseconds>
		(std::chrono::high_resolution_clock::now() - start);
	cout << "\nTime: " << HTTime.count() / k << "\n";


	double bst_time_double =BSTTime.count() / k ;

	double speed= bst_time_double/(HTTime.count()/k);
	cout<< "Speed Up: "<< speed ;


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






	cout<< "Enter queried words in one line: " ;
	//cin>>query_line;


	cin.ignore();
	getline(cin,query_line);



	query_line= toLower(query_line);


	vector <WordItem *> outputs;
	vector <WordItem *> outputs_table;

	query_line=only_alpha(query_line);
	istringstream iss2(query_line) ;
	string myword;
	
	
	

	while (iss2>>myword)
	{
		
		
		if (if_exist(myword,myTree)==false) // && if_exist_table(mystring,myTable)==false)
		{

			cout<< "No document contains the given query"<<endl ;
			cout<< "No document contains the given query" <<endl;
			time_func(outputs,outputs_table);
			
			/*cin.get();
			cin.ignore();*/
			
			return 10 ;

		}
		
		
		else 
		{
			WordItem * smt= myTree.getNode(myword) ;
			outputs.push_back(smt);
			WordItem * smt2=myTable.getNode_Tree(myword);
			outputs_table.push_back(smt2);
			
			
		}
		

	}

	




	for (int b=1; b<=2 ;b++)
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
						int begum=k+1; //EKLENTI BURADAN RETURN 10A KADAR
						if(begum==outputs.size())begum=k;
						if (outputs[k]->document_list[j].documentName!=outputs[begum]->document_list[j].documentName){
							cout<< "No document contains the given query"<<endl<< "No document contains the given query" <<endl;time_func(outputs,outputs_table);
							return 10;}
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


	time_func(outputs,outputs_table);


	//myTree.binarytree_count(myTree) ;

	cin.get();
	cin.ignore();
	return 0;
}
