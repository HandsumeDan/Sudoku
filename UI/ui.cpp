# include <cmath>
# include <cstdio>
# include <cstring>
# include <fstream>
# include <iostream>
# include <sstream>
# include <string>
# include <fcntl.h>					// Defines O_CREAT flag
# include <csignal>
# include <thread>
# include <sys/reg.h>
# include <sys/syscall.h>			// Defines OS System Calls
# include <sys/ptrace.h>
# include <sys/types.h>
# include <sys/user.h>
# include <sys/wait.h>
# include <sys/stat.h>				// Defines chmod function
# include <unistd.h>
# include <boost/filesystem.hpp>		// create_directory

# include <QtWidgets>
# include <QProcess>

# include "ui.h"

using namespace std;

UI::UI(QWidget *parent) : QWidget(parent)
	{string tmp;	
	int HEIGHT=50,WIDTH=50;	

	for(int row = 0; row < sU.N; row++)
		{for(int col = 0; col < sU.N; col++)
			{if(sU.problem[row][col]!=0)
				{tmp=cnvrtNumToStrng(sU.problem[row][col],0);
				panelLabel[row][col]=new QLabel(this);
				panelLabel[row][col]->setText(tr(tmp.c_str()));
				panelLabel[row][col]->setAlignment(Qt::AlignCenter);
				panelLabel[row][col]->setFixedWidth(WIDTH);
				panelLabel[row][col]->setFixedHeight(HEIGHT);
				}
			else
				{panelLine[row][col]=new QLineEdit(this);
				panelLine[row][col]->setText(tr(NO_VALUE));
				panelLine[row][col]->setAlignment(Qt::AlignCenter);
				panelLine[row][col]->setFixedWidth(WIDTH);
				panelLine[row][col]->setFixedHeight(HEIGHT);
				connect(panelLine[row][col],SIGNAL(returnPressed()),this,SLOT(checkSudoku()));
				}
			}
		}
	
	QGroupBox* box1=new QGroupBox;
	QGroupBox* box2=new QGroupBox;
	QGroupBox* box3=new QGroupBox;
	QGroupBox* box4=new QGroupBox;
	QGroupBox* box5=new QGroupBox;
	QGroupBox* box6=new QGroupBox;
	QGroupBox* box7=new QGroupBox;
	QGroupBox* box8=new QGroupBox;
	QGroupBox* box9=new QGroupBox;
	QGridLayout *layout1 = new QGridLayout; layout1->setSizeConstraint(QLayout::SetFixedSize);
	QGridLayout *layout2 = new QGridLayout; layout2->setSizeConstraint(QLayout::SetFixedSize);
	QGridLayout *layout3 = new QGridLayout; layout3->setSizeConstraint(QLayout::SetFixedSize);
	QGridLayout *layout4 = new QGridLayout; layout4->setSizeConstraint(QLayout::SetFixedSize);
	QGridLayout *layout5 = new QGridLayout; layout5->setSizeConstraint(QLayout::SetFixedSize);
	QGridLayout *layout6 = new QGridLayout; layout6->setSizeConstraint(QLayout::SetFixedSize);
	QGridLayout *layout7 = new QGridLayout; layout7->setSizeConstraint(QLayout::SetFixedSize);
	QGridLayout *layout8 = new QGridLayout; layout8->setSizeConstraint(QLayout::SetFixedSize);
	QGridLayout *layout9 = new QGridLayout; layout9->setSizeConstraint(QLayout::SetFixedSize);
	
	for(int row = 0; row < sU.N; row++)
		{for(int col = 0; col < sU.N; col++)
			{if(row>=0 && row<3 && col>=0 && col<3)
				{if(sU.problem[row][col]!=0){layout1->addWidget(panelLabel[row][col],row+1,col+1,1,1);}
				else{layout1->addWidget(panelLine[row][col],row+1,col+1,1,1);}
				}
			else if(row>=0 && row<3 && col>=3 && col<6)
				{if(sU.problem[row][col]!=0){layout2->addWidget(panelLabel[row][col],row+1,col+1,1,1);}
				else{layout2->addWidget(panelLine[row][col],row+1,col+1,1,1);}
				}
			else if(row>=0 && row<3 && col>=6 && col<9)
				{if(sU.problem[row][col]!=0){layout3->addWidget(panelLabel[row][col],row+1,col+1,1,1);}
				else{layout3->addWidget(panelLine[row][col],row+1,col+1,1,1);}
				}
			else if(row>=3 && row<6 && col>=0 && col<3)
				{if(sU.problem[row][col]!=0){layout4->addWidget(panelLabel[row][col],row+1,col+1,1,1);}
				else{layout4->addWidget(panelLine[row][col],row+1,col+1,1,1);}
				}
			else if(row>=3 && row<6 && col>=3 && col<6)
				{if(sU.problem[row][col]!=0){layout5->addWidget(panelLabel[row][col],row+1,col+1,1,1);}
				else{layout5->addWidget(panelLine[row][col],row+1,col+1,1,1);}
				}
			else if(row>=3 && row<6 && col>=6 && col<9)
				{if(sU.problem[row][col]!=0){layout6->addWidget(panelLabel[row][col],row+1,col+1,1,1);}
				else{layout6->addWidget(panelLine[row][col],row+1,col+1,1,1);}
				}
			else if(row>=6 && row<9 && col>=0 && col<3)
				{if(sU.problem[row][col]!=0){layout7->addWidget(panelLabel[row][col],row+1,col+1,1,1);}
				else{layout7->addWidget(panelLine[row][col],row+1,col+1,1,1);}
				}
			else if(row>=6 && row<9 && col>=3 && col<6)
				{if(sU.problem[row][col]!=0){layout8->addWidget(panelLabel[row][col],row+1,col+1,1,1);}
				else{layout8->addWidget(panelLine[row][col],row+1,col+1,1,1);}
				}
			else if(row>=6 && row<9 && col>=6 && col<9)
				{if(sU.problem[row][col]!=0){layout9->addWidget(panelLabel[row][col],row+1,col+1,1,1);}
				else{layout9->addWidget(panelLine[row][col],row+1,col+1,1,1);}
				}
			}
		}
	box1->setLayout(layout1); box2->setLayout(layout2); box3->setLayout(layout3);
	box4->setLayout(layout4); box5->setLayout(layout5); box6->setLayout(layout6);
	box7->setLayout(layout7); box8->setLayout(layout8); box9->setLayout(layout9);
	
	QGridLayout *mainLayout = new QGridLayout;
	mainLayout->setSizeConstraint(QLayout::SetFixedSize);
	mainLayout->addWidget(box1,0,0,1,1); mainLayout->addWidget(box2,0,1,1,1); mainLayout->addWidget(box3,0,2,1,1);
	mainLayout->addWidget(box4,1,0,1,1); mainLayout->addWidget(box5,1,1,1,1); mainLayout->addWidget(box6,1,2,1,1);
	mainLayout->addWidget(box7,2,0,1,1); mainLayout->addWidget(box8,2,1,1,1); mainLayout->addWidget(box9,2,2,1,1);
	setLayout(mainLayout);

	tmp=sU.difficulty+" Sudoku";
	setWindowTitle(tr(tmp.c_str()));
	//resize(QDesktopWidget().availableGeometry(this).size());

}

void UI::checkSudoku()
	{string tmp;
	int value;
	bool CHECKING=true;
	for(int row = 0; row < sU.N; row++)
		{for(int col = 0; col < sU.N; col++)
			{if(sU.problem[row][col]==0)
				{// get Panel value
				tmp=panelLine[row][col]->text().toStdString();
				value=atoi(tmp.c_str());
				if(sU.grid[row][col]!=value){CHECKING=false; break;}
				}
			}
		if(!CHECKING){break;}
		}
	if(CHECKING)
		{// Sudoku solved
		cout<<"Sudoku Solved!\n";}
	else
		{cout<<"Not Solved!\n";}
	}

string cnvrtNumToStrng(int Num,int numberAfterDecimalpoint)
	{stringstream ss;
	ss.setf(ios::fixed);
	if(numberAfterDecimalpoint>0)
		{ss.setf(ios::showpoint);}
	ss.precision(numberAfterDecimalpoint);
	ss<<Num;
	return ss.str();}

string cnvrtNumToStrng(unsigned int Num,int numberAfterDecimalpoint)
	{stringstream ss;
	ss.setf(ios::fixed);
	if(numberAfterDecimalpoint>0)
		{ss.setf(ios::showpoint);}
	ss.precision(numberAfterDecimalpoint);
	ss<<Num;
	return ss.str();}

string cnvrtNumToStrng(double Num,int numberAfterDecimalpoint){stringstream ss;ss.setf(ios::fixed);if(numberAfterDecimalpoint>0){ss.setf(ios::showpoint);}ss.precision(numberAfterDecimalpoint);ss<<Num;return ss.str();}

string cnvrtNumToStrng(long double Num,int numberAfterDecimalpoint){stringstream ss;ss.setf(ios::fixed);if(numberAfterDecimalpoint>0){ss.setf(ios::showpoint);}ss.precision(numberAfterDecimalpoint);ss<<Num;return ss.str();}

string cnvrtNumToStrng(float Num,int numberAfterDecimalpoint){stringstream ss;ss.setf(ios::fixed);if(numberAfterDecimalpoint>0){ss.setf(ios::showpoint);}ss.precision(numberAfterDecimalpoint);ss<<Num;return ss.str();}

double* fill_double_array(string Data,int numPnts,string delimiter){double* Output=new double[numPnts];string bld="",tmp="";int Counter=0;for(uint i=0;i<Data.length();i++){tmp=Data[i];if(tmp.compare(delimiter)==0 && Counter<numPnts){Output[Counter]=strtod(bld.c_str(),NULL);Counter++;bld="";}else{bld+=Data[i];}}return Output;}

int* fill_int_array(string Data,int numPnts,string delimiter){int* Output=new int[numPnts];string bld="",tmp="";int Counter=0;for(uint i=0;i<Data.length();i++){tmp=Data[i];if(tmp.compare(delimiter)==0 && Counter<numPnts){Output[Counter]=atoi(bld.c_str());Counter++;bld="";}else{bld+=Data[i];}}return Output;}

string* fill_string_array(string Data,int numPnts,string delimiter){string* Output=new string[numPnts];string bld="",tmp="";int Counter=0;for(uint i=0;i<Data.length();i++){tmp=Data[i];if(tmp.compare(delimiter)==0 && Counter<numPnts){Output[Counter]=bld;Counter++;bld="";}else{bld+=Data[i];}}return Output;}

bool Sudoku::isPresentInCol(int col, int num){ //check whether num is present in col or not
   for (int row = 0; row < N; row++)
      if (grid[row][col] == num)
         return true;
   return false;
}

bool Sudoku::isPresentInRow(int row, int num){ //check whether num is present in row or not
   for (int col = 0; col < N; col++)
      if (grid[row][col] == num)
         return true;
   return false;
}

bool Sudoku::isPresentInBox(int boxStartRow, int boxStartCol, int num){
//check whether num is present in 3x3 box or not
   for (int row = 0; row < 3; row++)
      for (int col = 0; col < 3; col++)
         if (grid[row+boxStartRow][col+boxStartCol] == num)
            return true;
   return false;
}

void Sudoku::problemGrid(){ //print the problem grid to be solved solve
   for (int row = 0; row < N; row++){
      for (int col = 0; col < N; col++){
         if(col == 3 || col == 6)
            cout << " | ";
			if(problem[row][col]!=0){cout << problem[row][col] <<" ";}
			else{cout<<"  ";}
      }
      if(row == 2 || row == 5){
         cout << endl;
         for(int i = 0; i<N; i++)
            cout << "---";
      }
      cout << endl;
   }
}

void Sudoku::sudokuGrid(){ //print the sudoku grid after solve
   for (int row = 0; row < N; row++){
      for (int col = 0; col < N; col++){
         if(col == 3 || col == 6)
            cout << " | ";
         cout << grid[row][col] <<" ";
      }
      if(row == 2 || row == 5){
         cout << endl;
         for(int i = 0; i<N; i++)
            cout << "---";
      }
      cout << endl;
   }
}

bool Sudoku::findEmptyPlace(int &row, int &col){ //get empty location and update row and column
   for (row = 0; row < N; row++)
      for (col = 0; col < N; col++)
         if (grid[row][col] == 0) //marked with 0 is empty
            return true;
   return false;
}

bool Sudoku::isValidPlace(int row, int col, int num){
   //when item not found in col, row and current 3x3 box
   return !isPresentInRow(row, num) && !isPresentInCol(col, num) && !isPresentInBox(row - row%3 ,
col - col%3, num);
}

bool Sudoku::solveSudoku(){
   int row, col;
   if (!findEmptyPlace(row, col))
      return true; //when all places are filled
   for (int num = 1; num <= 9; num++){ //valid numbers are 1 - 9
      if (isValidPlace(row, col, num)){ //check validation, if yes, put the number in the grid
         grid[row][col] = num;
         if (solveSudoku()) //recursively go for other rooms in the grid
            return true;
         grid[row][col] = 0; //turn to unassigned space when conditions are not satisfied
      }
   }
   return false;
}

bool IN_LIST(string X,string list,int N,string delimiter)
	{// Is X in list?
	bool Output=false;
	string* L,tmp;
	if(N<=0){Output=false;}
	else{L=fill_string_array(list,N,delimiter);
		for(int i=0;i<N;i++)
			{tmp=L[i];
			if(tmp.compare(X)==0){Output=true;break;}}}
	return Output;}

int count_delimiter(string Data,string delimiter)
	{int Counter=0,rng=delimiter.length()-1;
	if(Data.length()==0){return Counter;}
	string tmp="";
	for(int i=0;i<Data.length()-rng;i++)
		{tmp=Data[i];
		for(int j=1;j<rng+1;j++){tmp+=Data[i+j];}
		if(tmp.compare(delimiter.c_str())==0){Counter++;}
		}
	return Counter;}

