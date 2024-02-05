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
	int HEIGHT=40,WIDTH=40;

	scoreLabel=new QLabel;
	scoreLabel->setFixedWidth(120);

	QString Fldr=QDir::currentPath();
	string sFldr=Fldr.toStdString(); sFldr+="/";
	//sFldr=checkFinalBackSlash(sFldr);
	// Score File
	scoreFile=sFldr+".SCORE.txt";
	ifstream fIn;
	ofstream fOut;
	fIn.open(scoreFile.c_str());
	if(!fIn.fail())
		{// Define Score Label
		fIn.close();
		defineScore();
		}
	else
		{// Write New Score File
		fOut.open(scoreFile.c_str(),ofstream::out|ofstream::trunc);fOut<<"0\n";fOut.close();
		}
	
	QFont font;
	font.setBold(true);

	// Define Tab
	scTab = new QTabWidget;
	QWidget *tab1 = new QWidget;
	QGridLayout *tab1hbox = new QGridLayout;
	tab1hbox->setSizeConstraint(QLayout::SetFixedSize);
	tab1hbox->addWidget(create_sudokuBox(0),0,0,4,4);
	tab1->setLayout(tab1hbox);
	scTab->addTab(tab1, tr("&0"));

	// Score Label
	//QLabel *aLabel=new QLabel(tr("<b><span style=\"color:red;\">Score:</span></b>:"));jobNameLabel->setAlignment(Qt::AlignCenter|Qt::AlignRight);
	QLabel *aLabel=new QLabel(tr("Score:"));aLabel->setAlignment(Qt::AlignRight);

	QPushButton* puzzleButton=new QPushButton(tr("New Puzzle"));
	puzzleButton->setFixedWidth(120);
	connect(puzzleButton,SIGNAL(clicked()),this,SLOT(newSudoku()));

	QPushButton* solveButton=new QPushButton(tr("Submit Solution"));
	solveButton->setFixedWidth(120);
	connect(solveButton,SIGNAL(clicked()),this,SLOT(checkSudoku()));	

	QGridLayout *mainLayout = new QGridLayout;
	mainLayout->setSizeConstraint(QLayout::SetFixedSize);
	mainLayout->addWidget(aLabel,0,0,1,1); mainLayout->addWidget(scoreLabel,0,1,1,2);
	mainLayout->addWidget(scTab,1,0,4,4);
	mainLayout->addWidget(puzzleButton,5,2,1,1); mainLayout->addWidget(solveButton,5,3,1,1);
	setLayout(mainLayout);

	tmp=sU.difficulty+" Sudoku";
	setWindowTitle(tr(tmp.c_str()));
	//resize(QDesktopWidget().availableGeometry(this).size());

}

QGroupBox* UI::create_sudokuBox(int tabIndex)
	{int HEIGHT=40,WIDTH=40;
	for(int i=0;i<sU.N;i++){for(int j=0;j<sU.N;j++){sU.grid[i][j]=0; sU.problem[i][j]=0;}}

	int range=9,Counter=0,numPanels,rowVal,colVal;
	srand(time(0));
	int res=rand()%range; res++;

	sU.grid[0][0]=res; res=rand()%range; res++;
	sU.grid[3][1]=res; res=rand()%range; res++;
	sU.grid[6][2]=res; res=rand()%range; res++;
	sU.grid[8][3]=res; res=rand()%range; res++;
	sU.grid[4][4]=res; res=rand()%range; res++;
	sU.grid[1][5]=res; res=rand()%range; res++;
	sU.grid[5][6]=res; res=rand()%range; res++;
	sU.grid[2][7]=res; res=rand()%range; res++;
	sU.grid[7][8]=res;

	bool RUNNING=true;
	string i_delimiter=",",delimiter=";",lst="",tmp,*tmpStrArr,*tmpStrArr2;
	if(sU.solveSudoku() == true)
		{//cout<<"Solution:\n"; sU.sudokuGrid();
		// Select Difficulty
		res=rand()%5;
		if(res==0){numPanels=sU.numVeryEasyPanels; sU.difficulty="Very Easy"; sU.numPoints=100;}			// Very Easy
		else if(res==1){numPanels=sU.numEasyPanels; sU.difficulty="Easy"; sU.numPoints=250;}				// Easy
		else if(res==2){numPanels=sU.numMediumPanels; sU.difficulty="Medium"; sU.numPoints=500;}			// Medium
		else if(res==3){numPanels=sU.numHardPanels; sU.difficulty="Hard"; sU.numPoints=1000;}			// Hard
		else if(res==4){numPanels=sU.numVeryHardPanels; sU.difficulty="Very Hard"; sU.numPoints=2000;}		// Very Hard
		
		while(RUNNING)
			{for(int i=0;i<sU.N;i++)
				{for(int j=0;j<sU.N;j++)
					{// Select Row Value
					res=rand()%range;
					tmp=cnvrtNumToStrng(res,0)+i_delimiter;
					// Select Col Value
					res=rand()%range;
					tmp+=cnvrtNumToStrng(res,0)+i_delimiter;
					if(!IN_LIST(tmp,lst,count_delimiter(lst,delimiter),delimiter)){lst+=tmp+delimiter; Counter++;}
					}
				}
			// Exit Criterion
			if(Counter>=numPanels){RUNNING=false; break;}
			}
		tmpStrArr=fill_string_array(lst,numPanels,delimiter);
		for(int i=0;i<numPanels;i++)
			{tmpStrArr2=fill_string_array(tmpStrArr[i],2,i_delimiter);
			rowVal=atoi(tmpStrArr2[0].c_str());
			colVal=atoi(tmpStrArr2[1].c_str());
			delete [] tmpStrArr2;
			sU.problem[rowVal][colVal]=sU.grid[rowVal][colVal];
			}
		//cout<<"\n\nProblem:\n"; sU.problemGrid();
		}
	else{cout << "No solution exists";}

	for(int row = 0; row < sU.N; row++)
		{for(int col = 0; col < sU.N; col++)
			{if(sU.problem[row][col]!=0)
				{tmp=cnvrtNumToStrng(sU.problem[row][col],0);
				tmp="<b>"+tmp+"</b>";
				panelLabel[tabIndex][row][col]=new QLabel(this);
				panelLabel[tabIndex][row][col]->setText(tr(tmp.c_str()));
				panelLabel[tabIndex][row][col]->setAlignment(Qt::AlignCenter);
				panelLabel[tabIndex][row][col]->setFixedWidth(WIDTH);
				panelLabel[tabIndex][row][col]->setFixedHeight(HEIGHT);
				}
			else
				{panelLine[tabIndex][row][col]=new QLineEdit(this);
				panelLine[tabIndex][row][col]->setText(tr(NO_VALUE));
				panelLine[tabIndex][row][col]->setAlignment(Qt::AlignCenter);
				panelLine[tabIndex][row][col]->setFixedWidth(WIDTH);
				panelLine[tabIndex][row][col]->setFixedHeight(HEIGHT);
				panelLine[tabIndex][row][col]->setStyleSheet("font-weight:bold;");
				connect(panelLine[tabIndex][row][col],SIGNAL(returnPressed()),this,SLOT(checkSudoku()));
				}
			}
		}
	
	QGroupBox* box1=new QGroupBox; QGroupBox* box2=new QGroupBox; QGroupBox* box3=new QGroupBox;
	QGroupBox* box4=new QGroupBox; QGroupBox* box5=new QGroupBox; QGroupBox* box6=new QGroupBox;
	QGroupBox* box7=new QGroupBox; QGroupBox* box8=new QGroupBox; QGroupBox* box9=new QGroupBox;
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
				{if(sU.problem[row][col]!=0){layout1->addWidget(panelLabel[tabIndex][row][col],row+1,col+1,1,1);}
				else{layout1->addWidget(panelLine[tabIndex][row][col],row+1,col+1,1,1);}
				}
			else if(row>=0 && row<3 && col>=3 && col<6)
				{if(sU.problem[row][col]!=0){layout2->addWidget(panelLabel[tabIndex][row][col],row+1,col+1,1,1);}
				else{layout2->addWidget(panelLine[tabIndex][row][col],row+1,col+1,1,1);}
				}
			else if(row>=0 && row<3 && col>=6 && col<9)
				{if(sU.problem[row][col]!=0){layout3->addWidget(panelLabel[tabIndex][row][col],row+1,col+1,1,1);}
				else{layout3->addWidget(panelLine[tabIndex][row][col],row+1,col+1,1,1);}
				}
			else if(row>=3 && row<6 && col>=0 && col<3)
				{if(sU.problem[row][col]!=0){layout4->addWidget(panelLabel[tabIndex][row][col],row+1,col+1,1,1);}
				else{layout4->addWidget(panelLine[tabIndex][row][col],row+1,col+1,1,1);}
				}
			else if(row>=3 && row<6 && col>=3 && col<6)
				{if(sU.problem[row][col]!=0){layout5->addWidget(panelLabel[tabIndex][row][col],row+1,col+1,1,1);}
				else{layout5->addWidget(panelLine[tabIndex][row][col],row+1,col+1,1,1);}
				}
			else if(row>=3 && row<6 && col>=6 && col<9)
				{if(sU.problem[row][col]!=0){layout6->addWidget(panelLabel[tabIndex][row][col],row+1,col+1,1,1);}
				else{layout6->addWidget(panelLine[tabIndex][row][col],row+1,col+1,1,1);}
				}
			else if(row>=6 && row<9 && col>=0 && col<3)
				{if(sU.problem[row][col]!=0){layout7->addWidget(panelLabel[tabIndex][row][col],row+1,col+1,1,1);}
				else{layout7->addWidget(panelLine[tabIndex][row][col],row+1,col+1,1,1);}
				}
			else if(row>=6 && row<9 && col>=3 && col<6)
				{if(sU.problem[row][col]!=0){layout8->addWidget(panelLabel[tabIndex][row][col],row+1,col+1,1,1);}
				else{layout8->addWidget(panelLine[tabIndex][row][col],row+1,col+1,1,1);}
				}
			else if(row>=6 && row<9 && col>=6 && col<9)
				{if(sU.problem[row][col]!=0){layout9->addWidget(panelLabel[tabIndex][row][col],row+1,col+1,1,1);}
				else{layout9->addWidget(panelLine[tabIndex][row][col],row+1,col+1,1,1);}
				}
			}
		}
	box1->setLayout(layout1); box2->setLayout(layout2); box3->setLayout(layout3);
	box4->setLayout(layout4); box5->setLayout(layout5); box6->setLayout(layout6);
	box7->setLayout(layout7); box8->setLayout(layout8); box9->setLayout(layout9);
	
	QGroupBox* Output=new QGroupBox;

	QGridLayout *sudokuLayout = new QGridLayout;
	sudokuLayout->setSizeConstraint(QLayout::SetFixedSize);
	sudokuLayout->addWidget(box1,0,0,1,1); sudokuLayout->addWidget(box2,0,1,1,1); sudokuLayout->addWidget(box3,0,2,1,1);
	sudokuLayout->addWidget(box4,1,0,1,1); sudokuLayout->addWidget(box5,1,1,1,1); sudokuLayout->addWidget(box6,1,2,1,1);
	sudokuLayout->addWidget(box7,2,0,1,1); sudokuLayout->addWidget(box8,2,1,1,1); sudokuLayout->addWidget(box9,2,2,1,1);
	Output->setLayout(sudokuLayout);
	return Output;}

void UI::checkSudoku()
	{int tabIndex=scTab->currentIndex();
	int N=scTab->count(); N--;
	string tmp;
	int value;
	bool CHECKING=true;
	if(tabIndex==N)
		{for(int row = 0; row < sU.N; row++)
			{for(int col = 0; col < sU.N; col++)
				{if(sU.problem[row][col]==0)
					{// get Panel value
					tmp=panelLine[tabIndex][row][col]->text().toStdString();
					value=atoi(tmp.c_str());
					if(sU.grid[row][col]!=value){CHECKING=false; break;}
					}
				}
			if(!CHECKING){break;}
			}
		if(CHECKING)
			{// Sudoku solved
			cout<<"Sudoku Solved!\n";
			// Update SCORE file
			value=getScore();
			value+=sU.numPoints;
			updateScore(value);
			newSudoku();
			}
		else
			{cout<<"Not Solved!\n";
			// Provide Hint
			for(int row = 0; row < sU.N; row++)
				{for(int col = 0; col < sU.N; col++)
					{if(sU.problem[row][col]==0)
						{// get Panel value
						tmp=panelLine[tabIndex][row][col]->text().toStdString();
						value=atoi(tmp.c_str());
						if(sU.grid[row][col]!=value)
							{// Wrong Value
							panelLine[tabIndex][row][col]->setStyleSheet("font-weight:bold; color:red;");
							}
						else
							{// Correct Value
							panelLine[tabIndex][row][col]->setStyleSheet("font-weight:bold; color:green;");
							}
						}
					else
						{tmp=panelLabel[tabIndex][row][col]->text().toStdString();
						tmp="<b><span style=\"color:green;\">"+tmp+"</span></b>";
						panelLabel[tabIndex][row][col]->setText(tr(tmp.c_str()));
						}
					}
				}
			}
		}
	}

void UI::newSudoku()
	{// Define New Tab Index
	int N=scTab->count();
	// Define Tab
	QWidget *tab1 = new QWidget;
	QGridLayout *tab1hbox = new QGridLayout;
	tab1hbox->setSizeConstraint(QLayout::SetFixedSize);
	tab1hbox->addWidget(create_sudokuBox(N),1,0,4,4);
	tab1->setLayout(tab1hbox);

	string tmp="&"+cnvrtNumToStrng(N,0);
	scTab->addTab(tab1, tr(tmp.c_str()));

	tmp=sU.difficulty+" Sudoku";
	setWindowTitle(tr(tmp.c_str()));
	}

void UI::defineScore()
	{ifstream fIn;
	fIn.open(scoreFile.c_str());
	if(fIn.fail()){cerr<<"ERROR in defineScore!\nInput file could not be opened.\n";exit(EXIT_FAILURE);}
	uint Sz=15000;
	char Val[Sz];
	string tmp;
	fIn.getline(Val,Sz);
	tmp=Val;
	tmp="<b>"+tmp+"</b>";
	scoreLabel->setText(tr(tmp.c_str()));
	fIn.close();
	}

int UI::getScore()
	{ifstream fIn;
	fIn.open(scoreFile.c_str());
	if(fIn.fail()){cerr<<"ERROR in getScore!\nInput file could not be opened.\n";exit(EXIT_FAILURE);}
	uint Sz=15000;
	char Val[Sz];
	string tmp;
	fIn.getline(Val,Sz);
	tmp=Val;
	int Output=atoi(tmp.c_str());
	fIn.close();
	return Output;}

void UI::updateScore(int value)
	{ofstream fOut;
	fOut.open(scoreFile.c_str(),ofstream::out|ofstream::trunc);
	if(fOut.fail()){cerr<<"ERROR in updateScore!\nInput file could not be opened.\n";exit(EXIT_FAILURE);}
	string tmp=cnvrtNumToStrng(value,0);
	fOut<<tmp;
	tmp="<b>"+tmp+"</b>";
	scoreLabel->setText(tr(tmp.c_str()));
	fOut.close();
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

