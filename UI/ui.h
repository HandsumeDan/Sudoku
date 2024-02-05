# include <iostream>
# include <string>

// Computational Constants
# define MAX_GRIDS 100
# define NO_VALUE " "

using namespace std;

# ifndef UI_H
# define UI_H

# include <QWidget>
//# include <QTextToSpeech>

QT_BEGIN_NAMESPACE
class QLineEdit;
QT_END_NAMESPACE
class Button;
# include <QDialog>

QT_BEGIN_NAMESPACE
class QCheckBox;
class QComboBox;
class QDateTimeEdit;
class QDial;
class QGroupBox;
class QLabel;
class QLineEdit;
class QProgressBar;
class QPushButton;
class QRadioButton;
class QScrollBar;
class QSlider;
class QSpinBox;
class QTabWidget;
class QTableWidget;
class QTextEdit;
QT_END_NAMESPACE

string cnvrtNumToStrng(float Num,int numberAfterDecimalpoint);
string cnvrtNumToStrng(double Num,int numberAfterDecimalpoint);
string cnvrtNumToStrng(long double Num,int numberAfterDecimalpoint);
string cnvrtNumToStrng(int Num,int numberAfterDecimalpoint);
string cnvrtNumToStrng(unsigned int Num,int numberAfterDecimalpoint);
string* fill_string_array(string Data,int numPnts,string delimiter);
int* fill_int_array(string Data,int numPnts,string delimiter);
double* fill_double_array(string Data,int numPnts,string delimiter);
bool IN_LIST(string X,string list,int N,string delimiter);
int count_delimiter(string Data,string delimiter);

# endif

class Sudoku
	{public:
		Sudoku()
			{grid=new int*[N];
			problem=new int*[N];
			for(int i=0;i<N;i++){grid[i]=new int[N]; problem[i]=new int[N];}
			for(int i=0;i<N;i++){for(int j=0;j<N;j++){grid[i][j]=0; problem[i][j]=0;}}

			int range=9,Counter=0,numPanels,rowVal,colVal;
			srand(time(0));
			int res=rand()%range; res++;

			grid[0][0]=res; res=rand()%range; res++;
			grid[3][1]=res; res=rand()%range; res++;
			grid[6][2]=res; res=rand()%range; res++;
			grid[8][3]=res; res=rand()%range; res++;
			grid[4][4]=res; res=rand()%range; res++;
			grid[1][5]=res; res=rand()%range; res++;
			grid[5][6]=res; res=rand()%range; res++;
			grid[2][7]=res; res=rand()%range; res++;
			grid[7][8]=res;

			bool RUNNING=true;
			string i_delimiter=",",delimiter=";",lst="",tmp,*tmpStrArr,*tmpStrArr2;
			if(solveSudoku() == true)
				{//cout<<"Solution:\n"; sudokuGrid();
				// Select Difficulty
				res=rand()%5;
				if(res==0)
					{// Very Easy
					numPanels=numVeryEasyPanels;
					difficulty="Very Easy";
					numPoints=100;
					}
				else if(res==1)
					{// Easy
					numPanels=numEasyPanels;
					difficulty="Easy";
					numPoints=250;
					}
				else if(res==2)
					{// Medium
					numPanels=numMediumPanels;
					difficulty="Medium";
					numPoints=500;
					}
				else if(res==3)
					{// hard
					numPanels=numHardPanels;
					difficulty="Hard";
					numPoints=1000;
					}
				else if(res==4)
					{// Very Hard
					numPanels=numVeryHardPanels;
					difficulty="Very Hard";
					numPoints=2000;
					}
				
				while(RUNNING)
					{for(int i=0;i<N;i++)
						{for(int j=0;j<N;j++)
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
					problem[rowVal][colVal]=grid[rowVal][colVal];
					}
				//cout<<"\n\nProblem:\n"; problemGrid();
				}
			else{cout << "No solution exists";}
			}
	int N=9;
	int **grid;
	int **problem;
	string difficulty;
	int numVeryEasyPanels=55;
	int numEasyPanels=45;
	int numMediumPanels=35;
	int numHardPanels=25;
	int numVeryHardPanels=20;
	int numPoints;

	bool solveSudoku();
	bool isValidPlace(int row, int col, int num);
	bool findEmptyPlace(int &row, int &col);
	void problemGrid();
	void sudokuGrid();
	bool isPresentInBox(int boxStartRow, int boxStartCol, int num);
	bool isPresentInRow(int row, int num);
	bool isPresentInCol(int col, int num);
	};


// ZPRED UI
class UI : public QWidget
{
    Q_OBJECT

public:
   UI(QWidget *parent = 0);
	Sudoku sU;
	QLineEdit* panelLine[MAX_GRIDS][9][9];
	QLabel* panelLabel[MAX_GRIDS][9][9];
	QLabel* scoreLabel;
	string scoreFile;
	QTabWidget* scTab;
public slots:
	QGroupBox* create_sudokuBox(int tabIndex);
	void checkSudoku();
	void defineScore();
	int getScore();
	void updateScore(int value);
	void newSudoku();
};

//⁰ ¹ ² ³ ⁴ ⁵ ⁶ ⁷ ⁸ ⁹ ⁺ ⁻ ⁼ ⁽ ⁾
//ᵃ ᵇ ᶜ ᵈ ᵉ ᶠ ᵍ ʰ ⁱ ʲ ᵏ ˡ ᵐ ⁿ ᵒ ᵖ ʳ ˢ ᵗ ᵘ ᵛ ʷ ˣ ʸ ᶻ 
//ᴬ ᴮ ᴰ ᴱ ᴳ ᴴ ᴵ ᴶ ᴷ ᴸ ᴹ ᴺ ᴼ ᴾ ᴿ ᵀ ᵁ ⱽ ᵂ 
//ₐ ₑ ₕ ᵢ ⱼ ₖ ₗ ₘ ₙ ₒ ₚ ᵣ ₛ ₜ ᵤ ᵥ ₓ
//ᵅ ᵝ ᵞ ᵟ ᵋ ᶿ ᶥ ᶲ ᵠ ᵡ 
//ᵦ ᵧ ᵨ ᵩ ᵪ  
//1₀ ₁ ₂ ₃ ₄ ₅ ₆ ₇ ₈ ₉ ₊ ₋ ₌ ₍ ₎
