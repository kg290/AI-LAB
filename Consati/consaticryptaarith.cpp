#include <bits/stdc++.h>
using namespace std;

vector<char> letters = {'S','E','N','D','M','O','R','Y'};
int val[256];          // mapping char -> digit
bool used[10];         // digits used

bool valid() {
    if(val['S'] == 0 || val['M'] == 0) return false;

    int SEND = val['S']*1000 + val['E']*100 + val['N']*10 + val['D'];
    int MORE = val['M']*1000 + val['O']*100 + val['R']*10 + val['E'];
    int MONEY= val['M']*10000 + val['O']*1000 + val['N']*100 + val['E']*10 + val['Y'];

    return SEND + MORE == MONEY;
}

bool solve(int idx) {
    if(idx == letters.size()) {
        if(valid()) return true;
        return false;
    }

    for(int d = 0; d <= 9; d++) {
        if(!used[d]) {
            val[letters[idx]] = d;
            used[d] = true;

            if(solve(idx + 1)) return true;

            used[d] = false;
        }
    }
    return false;
}

int main() {
    memset(used, false, sizeof(used));

    if(solve(0)) {
        for(auto c : letters)
            cout << c << " = " << val[c] << "\n";

        int SEND = val['S']*1000 + val['E']*100 + val['N']*10 + val['D'];
        int MORE = val['M']*1000 + val['O']*100 + val['R']*10 + val['E'];
        int MONEY= val['M']*10000 + val['O']*1000 + val['N']*100 + val['E']*10 + val['Y'];

        cout << "\n" << SEND << " + " << MORE << " = " << MONEY << "\n";
    } else {
        cout << "No solution\n";
    }
}