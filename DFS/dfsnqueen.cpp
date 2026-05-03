#include <bits/stdc++.h>
using namespace std;

int n=8;
vector<int> board(n,-1);

bool safe(int row,int col){
    for(int i=0;i<row;i++){
        if(board[i]==col || abs(board[i]-col)==abs(i-row))
            return false;
    }
    return true;
}

bool dfs(int row){
    if(row==n) return true;

    for(int col=0;col<n;col++){
        if(safe(row,col)){
            board[row]=col;
            if(dfs(row+1)) return true;
        }
    }
    return false;
}

int main(){
    if(dfs(0)){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(board[i]==j) cout<<"Q ";
                else cout<<". ";
            }
            cout<<"\n";
        }
    }
}