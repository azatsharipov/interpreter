#ifndef _POLIZH_
#define _POLIZH_
#include "polizlex.h"
#include <vector>
#include <string>

using std::vector;
using std::string;

class Poliz {
    int index;
    string input;
    vector <PolizLex*> lexem; 

public:
    Poliz(const string& s) {
        index = 0;
        input = s;
    }
    void process_string(vector <Var>&, vector <Label>&, int);
    int execute(vector <Var>&, int) const;
    void update_var(vector <Var>&, PolizLex*) const;
};
#endif
