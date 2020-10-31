//
//  main.cpp
//  begumaltunbas_altunbas_begum_hw1
//
//  Created by Begum Altunbas on 10.07.2020.
//  Copyright © 2020 Begum Altunbas. All rights reserved.
//

#include <iostream>
#include <vector>
#include "Stack.h"
#include <fstream>
#include <sstream>
#include <random>
#include <string>

using namespace std;


struct cells 
{
	int x; //row
	int y; //column
	int l,r,u,d; //wall directions
	bool visited ; //if visited or not
	bool visited_path ;
};


int wall(cells &cell,vector<vector<cells>> &matrix,int row,int col  )
{
	int x= cell.x ;
	int y=cell.y;
	vector <int > walls; 
	if (cell.x>0 && matrix[cell.y][cell.x-1].visited ==false && cell.l==1  ) // left check
	{
		walls.push_back(0) ;
	}
	if (cell.x <col-1 && matrix[cell.y][cell.x+1].visited ==false && cell.r==1 ) // right check
	{
		walls.push_back(1) ;
	}
	if (cell.y<matrix.size()-1 && matrix[cell.y+1][cell.x].visited ==false && cell.u==1  ) // up check
	{
		walls.push_back(2) ;
	}

	if (cell.y>0 &&matrix[cell.y-1][cell.x].visited ==false  &&cell.d==1 ) // down check
	{
		walls.push_back(3) ;
	}

	int choice_count=walls.size();
	if (choice_count==0)
		return 10;

	int index = rand() % choice_count;
	return walls[index] ;

}


void txt_file(vector<vector<cells>> matrix,string name)
{

	fstream myfile;

	myfile.open(name,ios::out) ;

	myfile <<matrix.size()<<" "<< matrix[0].size()<<endl;

	for (int i=0 ; i< matrix.size();i++)
	{
		for (int j=0; j<matrix[0].size() ; j++)
		{
			myfile << "x="<< matrix[i][j].x<< " "; // x coordinate- columnlar
			myfile << "y="<< matrix[i][j].y<< " "; // y coordinate- rowlar
			myfile << "l="<< matrix[i][j].l<< " ";
			myfile << "r="<< matrix [i][j].r<< " ";
			myfile << "u="<< matrix[i][j].u <<" ";
			myfile <<"d="<< matrix[i][j].d<<" " ;
			myfile << endl ;
		}
	}
	myfile.close();
}




void iterator_(int wall_choosen,cells &current_cell,vector<vector<cells>> &matrix,Stack<cells> &mystack,int &visited_counter)
{
	if (wall_choosen==0 ) //left wall
	{

		matrix[current_cell.y][current_cell.x].l=0 ;

		matrix[current_cell.y][current_cell.x-1].visited=true;
		visited_counter++;
		matrix[current_cell.y][current_cell.x-1].r=0 ;
		mystack.push(matrix[current_cell.y][current_cell.x-1]) ;

	}
	else if(wall_choosen==1 ) //right wall
	{

		matrix[current_cell.y][current_cell.x].r=0 ;

		matrix[current_cell.y][current_cell.x+1].visited=true;
		visited_counter++;
		matrix[current_cell.y][current_cell.x+1].l=0 ;
		mystack.push(matrix[current_cell.y][current_cell.x+1]) ;


	}
	else if(wall_choosen==2 ) //up wall
	{

		matrix[current_cell.y][current_cell.x].u=0 ;
		matrix[current_cell.y+1][current_cell.x].visited=true;
		visited_counter++;
		matrix[current_cell.y+1][current_cell.x].d=0 ;
		mystack.push(matrix[current_cell.y+1][current_cell.x]) ;


	}
	else if(wall_choosen==3 ) //down wall
	{

		matrix[current_cell.y][current_cell.x].d=0 ;
		matrix[current_cell.y-1][current_cell.x].visited=true;
		visited_counter++;

		matrix[current_cell.y-1][current_cell.x].u=0 ;
		mystack.push(matrix[current_cell.y-1][current_cell.x]) ;


	}
	else 
	{
		mystack.pop(); 
	}
}



vector<vector<cells>> maze_generator( int row,int col,string name,int i) 
{

	Stack<cells> mystack ;
	vector<vector<cells>> matrix(row, vector<cells>(col));


	for (int j=0 ; j<row ;j++)
	{
		for (int k=0; k<col ;k++)
		{
			matrix[j][k].l=1;
			matrix[j][k].r=1;
			matrix[j][k].u=1;
			matrix[j][k].d=1;
			matrix[j][k].y=j; // yler row
			matrix[j][k].x=k ; //xler col coordinat sistemi gibi
		}
	}

	mystack.push( matrix[0][0]);
	matrix[0][0].visited=true;
	cells current_cell = mystack.top() ;
	int visited_counter=1 ;
	while (visited_counter<=(row*col)-1)
	{
		int wall_todelete = wall(current_cell,matrix,row,col) ;
		iterator_ (wall_todelete,current_cell,matrix,mystack,visited_counter) ;
		current_cell = mystack.top() ;
	}
	txt_file(matrix,name);
	//cout<< (row*col)-1;
	//cout<< visited_counter ;

	return matrix ;
}





int wall_for_path( vector<vector<cells>> &matrix,cells &cell)
{

	vector<int > non_walls ;
	if (cell.x>0 && cell.l==0 && matrix[cell.y][cell.x-1].visited_path ==false ) //left wall =0 
	{
		non_walls.push_back(0) ;

	}
	if (cell.x <matrix[0].size()-1 && matrix[cell.y][cell.x+1].visited_path ==false && cell.r==0 ) // right check
	{
		non_walls.push_back(1) ;
	}
	if (cell.y<matrix.size()-1 && matrix[cell.y+1][cell.x].visited_path ==false && cell.u==0  ) // up check
	{
		non_walls.push_back(2) ;
	}


	if (cell.y>0 &&matrix[cell.y-1][cell.x].visited_path ==false  && cell.d==0 ) // down check
	{
		non_walls.push_back(3) ;
	}

	int choice_count=non_walls.size();
	if (choice_count==0)
		return 10;

	int index = rand() % choice_count;
	return non_walls[index] ;
}





void path_iterator(vector<vector<cells>> &matrix,cells &current_cell,Stack<cells> &mystack,int wall_choosen  )
{

	if (wall_choosen==0 ) //left wall
	{

		matrix[current_cell.y][current_cell.x-1].visited_path=true;
		mystack.push(matrix[current_cell.y][current_cell.x-1]) ;

	}
	else if(wall_choosen==1 ) //right wall
	{

		matrix[current_cell.y][current_cell.x+1].visited_path=true;
		mystack.push(matrix[current_cell.y][current_cell.x+1]) ;


	}
	else if(wall_choosen==2 ) //up wall
	{

		matrix[current_cell.y+1][current_cell.x].visited_path=true;

		mystack.push(matrix[current_cell.y+1][current_cell.x]) ;


	}
	else if(wall_choosen==3 ) //down wall
	{

		matrix[current_cell.y-1][current_cell.x].visited_path=true;

		mystack.push(matrix[current_cell.y-1][current_cell.x]) ;

	}
	else 
	{
		mystack.pop(); 

	}

}





Stack<cells> path_finder(int start_col, int start_row,vector<vector<cells>> &matrix,int exit_col,int exit_row)
{
	Stack<cells> path_stack ;

	matrix[start_row][start_col].visited_path=true; //DEGISTI COL ROW
	path_stack.push(matrix[start_row][start_col]) ; //DEGISTI ROW COL
	cells top_cell=path_stack.top() ;

	while (matrix[exit_row][exit_col].visited_path==false)
	{
		int wall_choosen= wall_for_path(matrix ,top_cell) ;
		path_iterator ( matrix,top_cell, path_stack,wall_choosen) ;
		top_cell=path_stack.top();
	}

	return path_stack ;
}




void txt_file_path( string name,Stack <cells>stack)
{

	fstream myfile;

	myfile.open(name,ios::out) ;

	Stack<cells> temp; 


	while (stack.isEmpty() == false) 
	{ 
		temp.push(stack.top()); 
		stack.pop(); 
	}
	while (temp.isEmpty() == false) 
	{ 
		cells whatever = temp.top(); 
		myfile << whatever.x<<" "<<whatever.y << endl; //AYNI
		temp.pop(); 
		stack.push(whatever);   
	} 

	myfile.close();
}






int main() {
	int no_maze,M,N ;
	int maze_id ;

	int entry_col,entry_row ;
	int exit_col ,exit_row ;

	cout<< "Enter the number of mazes: " ;
	cin>>no_maze ;
	cout<< "Enter the number of rows and columns (M and N): ";
	cin>>M>>N ;

	vector<vector<cells>> maze;
	vector <vector<vector<cells>>> maze_list; 
	for (int i=1 ;i<=no_maze;i++)
	{
		string id= to_string(i) ;
		string name ;
		name ="maze_";
		name.append(id);
		name.append(".txt") ;
		//cout<< name ;
		maze = maze_generator(M,N,name,i);
		maze_list.push_back(maze) ;
		//txt_file(matrix,name) ;


	}

	cout<< "All mazes are generated." <<endl ;
	cout<< endl <<endl ;
	cout<< "Enter a maze ID between 1 to " << no_maze <<" inclusive to find a path: ";
	cin>> maze_id ;
	cout<< "Enter x and y coordinates of the entry points (x,y) or (column,row): " ;
	cin>>entry_col>>entry_row ;
	cout<< "Enter x and y coordinates of the exit points (x,y) or (column,row): " ;
	cin>>exit_col>>exit_row ;

	Stack<cells> final_coordinates = path_finder(entry_col, entry_row,maze_list[maze_id-1],exit_col,exit_row);
	string maze_name_path ;
	maze_name_path="maze_" +to_string(maze_id)+"_" +"path_" + to_string(entry_col)+"_"+to_string(entry_row)+ "_"+to_string(exit_col)+ "_"+to_string(exit_row)+".txt" ;
	cout<<maze_name_path ;

	txt_file_path(maze_name_path,final_coordinates);


	cin.get();
	cin.ignore();

	return 0;
}