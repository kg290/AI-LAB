#include <bits/stdc++.h>
using namespace std;

bool used[10];

// Convert word to number
int getNum(string s, map<char,int> &mp) {
    int num = 0;
    for(char c : s)
        num = num * 10 + mp[c];
    return num;
}

// Backtracking solver
bool solve(vector<char> &letters, map<char,int> &mp, int idx) {
    if(idx == letters.size()) {
        int send  = getNum("SEND", mp);
        int more  = getNum("MORE", mp);
        int money = getNum("MONEY", mp);

        if(send + more == money) {
            cout << "Solution:\n";
            for(auto &p : mp)
                cout << p.first << " = " << p.second << "\n";
            cout << "SEND = " << send << "\n";
            cout << "MORE = " << more << "\n";
            cout << "MONEY = " << money << "\n";
            return true;
        }
        return false;
    }

    char ch = letters[idx];

    for(int d = 0; d <= 9; d++) {
        if(!used[d]) {
            // Leading digit constraint
            if((ch == 'S' || ch == 'M') && d == 0) continue;

            used[d] = true;
            mp[ch] = d;

            if(solve(letters, mp, idx + 1))
                return true;

            used[d] = false;
        }
    }
    return false;
}

int main() {
    vector<char> letters = {'S','E','N','D','M','O','R','Y'};
    map<char,int> mp;

    memset(used, false, sizeof(used));

    if(!solve(letters, mp, 0))
        cout << "No solution found\n";

    return 0;
}