#include "poliz.h"
#include "polizlex.cpp"
#include <stack>
#include <vector>

using namespace std;

void Poliz::process_string(vector <Var>& vtable, vector <Label>& ltable, int ind) {
    int is_number; // 0 - '+' 1 - 46 2 - "abc" 3 - "L:"
    stack <Oper*> oper_stack;

    for (int i = 0; i < input.size(); i++) {
        PolizLex* ptr = get_next_lexem(is_number, vtable, ltable, index, ind, input);
        if (ptr) {
            ptr->print();
            cout << " \n"[i == input.size() - 1];
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
    for (int i = 0; i < lexem.size(); i++) {
        if (lexem[i])
            lexem[i]->print();
        cout << " \n"[i == lexem.size() - 1];
    }
}

int Poliz::execute(vector <Var> &vtable, int ind) const {
    stack <PolizLex*> tmp;
    vector <Num> nums(lexem.size());
    int j = 0;
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
                nums[j].set_val(a + b);
                tmp.push(&nums[j++]);
                break;
            } case PolizLex::MINUS : {
                int b = tmp.top()->get_val();
                tmp.pop();
                int a = tmp.top()->get_val();
                tmp.pop();
                nums[j].set_val(a - b);
                tmp.push(&nums[j++]);
                break;
            } case PolizLex::MULT : {
                int b = tmp.top()->get_val();
                tmp.pop();
                int a = tmp.top()->get_val();
                tmp.pop();
                nums[j].set_val(a * b);
                tmp.push(&nums[j++]);
                break;
            } case PolizLex::DIV : {
                int b = tmp.top()->get_val();
                tmp.pop();
                int a = tmp.top()->get_val();
                tmp.pop();
                nums[j].set_val(a / b);
                tmp.push(&nums[j++]);
                break;
            } case PolizLex::UMINUS : {
                int b = tmp.top()->get_val();
                tmp.pop();
                nums[j].set_val(-b);
                tmp.push(&nums[j++]);
                break;
            } case PolizLex::ASSIGN : {
                int b = tmp.top()->get_val();
                tmp.pop();
                PolizLex* p = tmp.top();
                int a = tmp.top()->get_val();
                tmp.pop();
                nums[j].set_val(a);
                p->set_val(b);
                update_var(vtable, p);
                tmp.push(&nums[j++]);
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
