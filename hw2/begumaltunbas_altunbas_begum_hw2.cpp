#include <iostream>
#include <fstream>
#include <string>
#include "Header1233.h"
#include <sstream>
#include <vector>
#include "header.cpp"
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

AvlTree<string, WordItem > myTree(my_string,ITEM_NOT_FOUND);



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



bool if_exist(string &str,AvlTree<string, WordItem > &myTree)
{
	if(myTree.find(str)=="")
		return false;
	else
		return true;
}

string toLower(string & word){

	for (int i = 0; i < word.length(); i++) {
		if (word[i] >= 65 && word[i] <= 90)
		{
			word[i]+= 32; 
		}
	}
	return word;
}



void file_read(string file_name, AvlTree<string, WordItem > &myTree)
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
			if ( if_number(word)==false ) //if its string
			{
				word=toLower(word) ;
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

				}

			}  
			else 
			{
				;

			}


		}
		
	}

}




int main ()
{


	vector<string> file_name_list;
	int num_files;
	string file_name, query_line;

	cout<< "Enter number of input files: " ;
	cin >>num_files;


	for (int i=1; i<=num_files ; i++)
	{
		cout<< "Enter "<< i <<". file name: " ;
		cin >>file_name;
		file_name_list.push_back(file_name);
		file_read(file_name,myTree) ;
	}

	

	cout<< "Enter queried words in one line: " ;
	//cin>>query_line;


	cin.ignore();
    getline(cin,query_line);



	query_line= toLower(query_line);


	vector <WordItem *> outputs;

	istringstream iss2(query_line) ;
	string myword;
	while (iss2>>myword)
	{
		if (if_exist(myword,myTree)==false)
		{
			cout<< "No document contains the given query" ;
			//cin.get();
			//cin.ignore();
			return 10 ;

		}
		else 
		{
			WordItem * smt= myTree.getNode(myword) ;
			outputs.push_back(smt);
		}

	}


	if (outputs.size()!=0)
	{
		for (int i=0 ; i < file_name_list.size() ;i++)
		{
			cout<<"In Document " <<file_name_list[i] << ",";
			for (int k=0; k<outputs.size();k ++ )
			{
				
				for (int j=0 ;j<outputs[k]->document_list.size(); j++)
				{
					if (outputs[k]->document_list[j].documentName ==file_name_list[i] )
					{
						cout<<  outputs[k]->word << "  found " ;
					   cout <<outputs[k]->document_list[j].count << " times" ;
					   if (k!=outputs.size()-1)
					   {
						   cout<< "," ;
					   }
					   else 
						   cout<< "."<<endl;
					}
					

				}

			}

		}

	}

    //cin.get();
	//cin.ignore();

	return 0 ;
}


