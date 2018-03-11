#include "polizlex.h"
const int PolizLex::PolizOperatorPriority[8] =  {1, 1, 2, 2, 3, -1, -2, 0};
const char PolizLex::PolizOperatorChar[8] = {'+', '-', '*', '/', '-', '(', ')', '='};
const string PolizLex::PolizOperatorString[8] = {"+", "-", "*", "/", "-", "(", ")", "="};
