//============================================================================
// Name        : Sudoku-puzzle.cpp
// Author      : Bhawana
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
using namespace std;



bool checkpos(vector < vector < char > > &A, int n, int row, int col, int num){
    char currchar=num+'0';
    for(int i=0; i<n; i++){
        if(A[row][i]==currchar)
            return false;
        if(A[i][col]==currchar)
            return false;
    }

    int rootn=sqrt(n);
    int boxrow=row/rootn;
    int boxcol=col/rootn;
    int boxcellstartrow=(boxrow)*rootn;
    int boxcellstartcol=(boxcol)*rootn;
    for(int i=boxcellstartrow;i<boxcellstartrow+rootn;i++){
        for(int j=boxcellstartcol;j<boxcellstartcol+rootn;j++){
            if(A[i][j]==currchar){
                return false;
            }
        }
    }
    return true;
}

bool solve(vector < vector < char > > &A, int n, int row, int col){
    if(row==n)
        return true;
    if(col==n)
        return solve(A,n,row+1,0);
    if(A[row][col]!='.')
        return solve(A,n,row,col+1);

    for(int currnum = 1; currnum<=n; currnum++){
        if(checkpos(A,n,row,col,currnum)==true){
            A[row][col]=currnum+'0';
            bool possible = solve(A,n,row,col+1);
            if(possible==true)
                return true;
            A[row][col]='.';
        }
    }
    return false;
}

int main() {
	int n;
	cout << "Enter size of sudoku" << endl;
	cin >> n ;
	vector < vector < char > > B;
	B.resize(n);
    for(int i=0; i<n; i++){
    	B[i].resize(n);
    }

	cout << "Enter the sudoku input" << endl ;
    for(int i=0; i<n; i++){
    	for(int j=0; j<n; j++){
    		cin >> B[i][j];
    	}
    }
    solve(B,n,0,0);
    for(int i=0; i<n; i++){
    	for(int j=0; j<n; j++){
    		cout << B[i][j] << " ";
    	}
    	cout << endl << endl;
    }

	return 0;
}


