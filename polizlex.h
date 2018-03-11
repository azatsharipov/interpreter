#ifndef _POLIZLEXH_
#define _POLIZLEXH_
#include <stack>
#include <iostream>
#include <string>

using std::stack;
using std::cout;
using std::string;

class PolizLex {
public:
	enum PolizOperator {PLUS, MINUS, MULT, DIV, UMINUS, OPEN, CLOSE, ASSIGN};
	static const int PolizOperatorPriority[8];
	static const string PolizOperatorString[8];
	static const char PolizOperatorChar[8];
    PolizLex() {
	}
	virtual void process(stack <int> &res) {
	}
	virtual void print() {
	}
	virtual int is_number() {
    }
	virtual int is_var() {
    }
	virtual void set_val(int) {
	}
	virtual int get_val() {
	}
	virtual string get_name() {
	}
};

class Num : public PolizLex {
private:
    int val;
public:
    Num(int a = 0) {
        val = a;
    }

    void process(stack <int>& res) {
    }

    void print() {
        cout << val;
    }

    int is_number() {
        return 1;
    }

    int is_var() {
        return 0;
    }

    void set_val(int value) {
        val = value;
    }

    int get_val() {
        return val;
    }
};

class Oper : public PolizLex {
private:
    PolizOperator val;
public:
    Oper(PolizOperator a) {
        val = a;
    }

    int get_priority() {
        return PolizOperatorPriority[val];
    }

    void process(stack <int>& res) {
    }
 
    void print() {
        cout << PolizOperatorString[val];
    }

    int is_number() {
        return 0;
    }

    int is_var() {
        return 0;
    }

    int get_val() {
        return val;
    }
};

class Var : public PolizLex {
	string name;
	int val;
public:
	Var(string s, int value) {
		Var::name = s;
		Var::val = value;
	}
	string get_name() {
		return name;
	}
	int get_val() {
		return val;
	}
	void set_val(int value) {
		val = value;
	}

    void print() {
        cout << name;
    }

    int is_number() {
        return 0;
    }

    int is_var() {
        return 1;
    }
};

#endif
