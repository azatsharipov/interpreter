#include "polizlex.h"
#include <vector>

using namespace std;
const int PolizLex::PolizOperatorPriority[8] =  {1, 1, 2, 2, 3, -1, -2, 0};
const char PolizLex::PolizOperatorChar[8] = {'+', '-', '*', '/', '-', '(', ')', '='};
const string PolizLex::PolizOperatorString[8] = {"+", "-", "*", "/", "-", "(", ")", "="};

bool is_it_number(string input, int index) {
    return (index < input.size()) && ('0' <= input[index]) && (input[index] <= '9');
}

bool is_it_text(string input, int index) {
    return (index < input.size()) && ('a' <= input[index] && input[index] <= 'z' || 'A' <= input[index] && input[index] <= 'Z');
}

PolizLex* get_next_lexem(int& is_number, vector <Var>& vtable, vector <Label>& ltable, int& index, int ind, string input) {
    while (index < input.size() && (input[index] == ' ' || input[index] == '\t'))
        index++;

    is_number = 0;
    int value = 0;
    string var;
    int var_i = 0;
    if (is_it_number(input, index)) {
        is_number = 1;
        while (is_it_number(input, index)) {
            value = value * 10 + input[index++] - '0';
        }
    } else if (is_it_text(input, index)) {
        is_number = 2;
        while (is_it_text(input, index)) {
            var.push_back(input[index++]);
        }
        if (index < input.size() && input[index] == ':') {
            is_number = 3;
            index++;
            int flag = 0;
            for (int i = 0; i < ltable.size(); i++)
                if (var == ltable[i].get_name())
                    flag = 1;
            if (!flag)
                ltable.push_back(Label(var, ind));
        } else {
            for (int i = 0; i < vtable.size(); i++)
                if (vtable[i].get_name() == var)
                {
                    var_i = i;
                    break;
                }
		    value = vtable[var_i].get_val();
        }
	} else {
        while (index < input.size()) {
            int flag = 0;
            for (int i = 0; i < sizeof(PolizLex::PolizOperatorChar); i++)
                if (input[index] == PolizLex::PolizOperatorChar[i]) {
                    flag = 1;
                    break;
                }
            if (flag)
                var.push_back(input[index++]);
            else
                break;
        }
    }
    if (is_number == 1) {
        return new Num(value);
    } else if (is_number == 2) {
        return new Var(var, value);
    }
    for (int i = 0; i < sizeof(PolizLex::PolizOperatorString); i++)
        if (var == PolizLex::PolizOperatorString[i]) {
//            if (index == 0 && var[0] == '-' && i == 1 || var.size() > 1 && var[0] == '(' && var[1] == '-')
//                continue;
            return new Oper((PolizLex::PolizOperator)i);
        }
        return NULL;
}
