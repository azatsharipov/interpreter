#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <vector>
#include "poliz.h"

using namespace std;

void vtable_print(vector <Var> vtable) {
    for (int i = 0; i < vtable.size(); i++)
        cout << vtable[i].get_name() << ' ' << vtable[i].get_val() << endl;
}

int main() {
    string input;
    cout << "select a mode" << endl;
    cout << "offline or online" << endl;
    cin >> input;
    for (int j = 0; j < input.size(); j++)
        if (input[j] >= 'A' && input[j] <= 'Z')
            input[j] += 'a' - 'A';
    while (input != "offline" && input != "off" && input != "on" && input != "online" && input != "exit") {
        cout << "wrong mode" << endl;
        cin >> input;
        for (int j = 0; j < input.size(); j++)
            if (input[j] >= 'A' && input[j] <= 'Z')
                input[j] += 'a' - 'A';
    }
    if (input == "offline" || input == "off") {
//      OFFLINE
	    vector <string> str;
	    vector <Var> vtable;
        vector <Poliz> plz;
        int size = 0;
        cin >> input;
        while (input != "exit") {
            size++;
            str.push_back(input);
            cin >> input;
        }
        int i = 0;
        while (i < size) {
            if (str[i] == "var") {
                i++;
                for (int j = 0; j < str[i].size(); j++) {
                    string var;
                    while (j < str[i].size() && str[i][j] != ',')
                        var.push_back(str[i][j++]);
                    vtable.push_back(Var(var, 0));
                }
            }
            else if (str[i] == "print") {
                i++;
                for (int j = 0; j < vtable.size(); j++)
                    if (str[i] == vtable[j].get_name()) {
                        cout << vtable[j].get_val() << endl;
                        break;
                    }
            } else {
                plz.push_back(Poliz(str[i]));
                plz[plz.size() - 1].process_string(vtable);
                cout << plz[plz.size() - 1].execute(vtable) << endl;
            }
            i++;
        }
    } else if (input == "online" || input == "on") {
//      ONLINE
	    vector <Var> vtable;
        cin >> input;
	    while (input != "exit") {
            if (input == "var") {
                cin >> input;
                for (int i = 0; i < input.size(); i++) {
                    string var;
                    while (i < input.size() && input[i] != ',')
                        var.push_back(input[i++]);
                    vtable.push_back(Var(var, 0));
                }
            } else if (input == "print") {
                cin >> input;
                for (int i = 0; i < vtable.size(); i++) {
                    if (input == vtable[i].get_name()) {
                        cout << vtable[i].get_val() << endl;
                        break;
                    }
                }
            } else {
                Poliz plz(input);
                plz.process_string(vtable);
                cout << plz.execute(vtable) << endl;
            }
            cin >> input;
	    }
    }
	return 0;
}
