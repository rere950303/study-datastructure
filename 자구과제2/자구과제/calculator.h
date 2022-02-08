#ifndef CALCULATOR_H
#define CALCULATOR_H

//
// Assignment 2 : Simple calculator using Stack
//
// COSE213 Fall 2021
//
// Won-Ki Jeong (wkjeong@korea.ac.kr)
//

#include <iostream>
#include <cassert>
#include <math.h>
#include <string.h>
#include "stack.h"

Stack<double> opr; // stack for operands
Stack<char> opt;   // stack for operators

//
// Modify Eval() below to evaluate the given expression
//

bool isDigit(char c) {
    if (c >= 48 && c <= 57) {
        return true;
    } else {
        return false;
    }
}

int getPriority(char c) {
    if (c == '-' || c == '+') {
        return 1;
    } else if (c == '*' || c == '/') {
        return 2;
    } else if (c == '(') {
        return 0;
    }
    
    return 0;
}

double calculate(double a, double b, double c) {
    double num = 0;
    
    if (c == '+') {
        num = a + b;
    } else if (c == '-') {
        num = b - a;
    } else if (c == '*') {
        num = a * b;
    } else {
        num = b / a;
    }
    
    return num;
}


double Eval(char* in)
{
    size_t len = strlen(in);
    int *check = new int[len + 10]{};
    double out = 0;
    bool minus = false;
    char buf[1000];
    char *trim = new char[len + 10];
    int i = 0;
    int pc = 0;
    int count = 0;
    
    while (in[i] != '\0') {
        if (in[i] != ' ') {
            trim[pc++] = in[i];
        }
        i++;
    }
    
    trim[pc] = '\0';
    double *postfix = new double[len + 10];
    i = pc = 0;

    while (trim[i] != '\0') {
        if (isDigit(trim[i]) || trim[i] == '.') {
            buf[pc++] = trim[i];
            i++;
        } else {
            if (pc > 0) {
                buf[pc++] = '\0';
                double tmp = atof(buf);
                if (minus) {
                    tmp *= -1;
                }
                postfix[count] = tmp;
                check[count++] = 1;
                minus = false;
                pc = 0;
            }
            
            
            if (trim[i] == '-') {
                if (i == 0 || !(trim[i - 1] == ')' || isDigit(trim[i - 1]))) {
                    minus = true;
                    i++;
                    continue;
                } else {
                    while (!opt.IsEmpty() && getPriority(opt.Top()) >= getPriority(trim[i])) {
                        postfix[count++] = opt.Top();
                        opt.Pop();
                    }
                    opt.Push(trim[i]);
                    i++;
                }
            } else if (trim[i] == ')') {
                while (!opt.IsEmpty() && opt.Top() != '(') {
                    postfix[count++] = opt.Top();
                    opt.Pop();
                }
                opt.Pop();
                i++;
            } else if (trim[i] == '(') {
                opt.Push(trim[i]);
                i++;
            } else {
                while (!opt.IsEmpty() && getPriority(opt.Top()) >= getPriority(trim[i])) {
                    postfix[count++] = opt.Top();
                    opt.Pop();
                }
                opt.Push(trim[i]);
                i++;
            }
        }
    }
    
    if (pc > 0) {
        buf[pc++] = '\0';
        double tmp = atof(buf);
        if (minus) {
            tmp *= -1;
        }
        postfix[count] = tmp;
        check[count++] = 1;
        minus = false;
        pc = 0;
    }
    
    while (!opt.IsEmpty()) {
        postfix[count++] = opt.Top();
        opt.Pop();
    }
    
    
    for (i = 0; i < count; i++) {
        if (check[i] == 0) {
            double a = opr.Top();
            opr.Pop();
            double b = opr.Top();
            opr.Pop();
            
            opr.Push(calculate(a, b, postfix[i]));
        } else {
            opr.Push(postfix[i]);
        }
    }
	
    out = opr.Top();
    opr.Pop();
    
    delete [] check;
    delete [] trim;
    delete [] postfix;

    return out;
}

#endif
