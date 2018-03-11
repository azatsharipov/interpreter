#include "poliz.h"
#include <stack>
#include <vector>

using std::stack;
using std::endl;
using std::cout;

PolizLex* Poliz::get_next_lexem(int& is_number, vector <Var>& vtable) {
    while (index < input.size() && (input[index] == ' ' || input[index] == '\t'))
        index++;

    is_number = 0;
    int value = 0;
    string var;
    int var_i = 0;
    if ((index < input.size()) && ('0' <= input[index]) && (input[index] <= '9')) {
        is_number = 1;
        while ((index < input.size()) && ('0' <= input[index]) && (input[index] <= '9')) {
            value = value * 10 + input[index++] - '0';
        }
    }
    else if ((index < input.size()) && ('a' <= input[index] && input[index] <= 'z' || 'A' <= input[index] && input[index] <= 'Z')) {
        is_number = 2;
        while ((index < input.size()) && ('a' <= input[index] && input[index] <= 'z' || 'A' <= input[index] && input[index] <= 'Z')) {
            var.push_back(input[index++]);
        }
        for (int i = 0; i < vtable.size(); i++)
            if (vtable[i].get_name() == var)
            {
                var_i = i;
                break;
            }
		value = vtable[var_i].get_val();
	}
    else {
        while (index < input.size())
        {
            int flag = 0;
            for (int i = 0; i < sizeof(PolizLex::PolizOperatorChar); i++)
                if(input[index] == PolizLex::PolizOperatorChar[i])
                {
                    flag = 1;
                    break;
                }
            if(flag)
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

void Poliz::process_string(vector <Var>& vtable) {
    int is_number; // 0 - '+' 1 - 46 2 - "abc"
    stack <Oper*> oper_stack;

    for (int i = 0; i < input.size(); i++) {
        PolizLex* ptr = get_next_lexem(is_number, vtable);
        if (ptr) {
//            ptr->print();
//            cout << " \n"[i == input.size() - 1];
            if (is_number) {
                lexem.push_back(ptr);
            } else {
				if (((Oper*)ptr)->get_priority() == -1) {
					oper_stack.push((Oper*)ptr);
				} else if (((Oper*)ptr)->get_priority() == -2) {
					while ((oper_stack.size() > 0) && (oper_stack.top()->get_priority() != -1)) {
                    	lexem.push_back(oper_stack.top());
                    	oper_stack.pop();
					}
					oper_stack.pop();
				} else {
              		int current_priority = ((Oper*)ptr)->get_priority();
                	while ((oper_stack.size() > 0) && (current_priority <= oper_stack.top()->get_priority())) {
                    	lexem.push_back(oper_stack.top());
                    	oper_stack.pop();
                	}
                	oper_stack.push((Oper*)ptr);
				}
			}
        }
    }
    while (oper_stack.size() > 0) {
        lexem.push_back(oper_stack.top());
        oper_stack.pop();
    }
    /*
    for (int i = 0; i < lexem.size(); i++) {
        if (lexem[i])
            lexem[i]->print();
        cout << " \n"[i == lexem.size() - 1];
    }
    */
}

int Poliz::execute(vector <Var> &vtable) const {
    stack <PolizLex*> tmp;
    for (int i = 0; i < lexem.size(); i++) {
        if (lexem[i]->is_number())
            tmp.push(lexem[i]);
        else if (lexem[i]->is_var())
            tmp.push(lexem[i]);
        else switch (lexem[i]->get_val()) {
            case PolizLex::PLUS : {
                int b = tmp.top()->get_val();
                tmp.pop();
                int a = tmp.top()->get_val();
                tmp.pop();
                Num c(a + b);
                tmp.push(&c);
                break;
            } case PolizLex::MINUS : {
                int b = tmp.top()->get_val();
                tmp.pop();
                int a = tmp.top()->get_val();
                tmp.pop();
                Num c(a - b);
                tmp.push(&c);
                break;
            } case PolizLex::MULT : {
                int b = tmp.top()->get_val();
                tmp.pop();
                int a = tmp.top()->get_val();
                tmp.pop();
                Num c(a * b);
                tmp.push(&c);
                break;
            } case PolizLex::DIV : {
                int b = tmp.top()->get_val();
                tmp.pop();
                int a = tmp.top()->get_val();
                tmp.pop();
                Num c(a / b);
                tmp.push(&c);
                break;
            } case PolizLex::UMINUS : {
                int b = tmp.top()->get_val();
                tmp.pop();
                Num c(-b);
                tmp.push(&c);
                break;
            } case PolizLex::ASSIGN : {
                int b = tmp.top()->get_val();
                tmp.pop();
                PolizLex* p = tmp.top();
                int a = tmp.top()->get_val();
                tmp.pop();
                Num c(b);
                p->set_val(b);
                update_var(vtable, p);
                tmp.push(&c);
                break;
            }
        }
    }
    return tmp.top()->get_val();
}

void Poliz::update_var(vector <Var> &vtable, PolizLex* p) const {
    for (int i = 0; i < vtable.size(); i++) {
        if (vtable[i].get_name() == p->get_name()) {
            vtable[i].set_val(p->get_val());
            break;
        }
    }
}
