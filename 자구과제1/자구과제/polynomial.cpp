#include "polynomial.h"
#include <iostream>
#include <math.h>


//
// Implementation
//

Polynomial::Polynomial(const Polynomial& source)
{
    this->capacity = source.capacity;
    this->terms = source.terms;
    this->termArray = new Term[this->capacity];
    for(int i = 0; i < source.terms; i++){
        this->termArray[i].coef = source.termArray[i].coef;
        this->termArray[i].exp = source.termArray[i].exp;
    }
}

Polynomial::~Polynomial()
{
    delete [] termArray;
}


Polynomial& Polynomial::operator = (const Polynomial& source)
{
    if (this != &source) {
        delete [] termArray;
        this->capacity = source.capacity;
        this->terms = source.terms;
        this->termArray = new Term[this->capacity];
        for(int i = 0; i < source.terms; i++){
            this->termArray[i].coef = source.termArray[i].coef;
            this->termArray[i].exp = source.termArray[i].exp;
        }
    }
    
    return *this;
}

Polynomial Polynomial::operator +(const Polynomial& source)
{
	Polynomial c;
    
    int pt = 0;
    int ps = 0;
    
    while (pt < this->terms && ps < source.terms) {
        if (this->termArray[pt].exp == source.termArray[ps].exp) {
            if (source.termArray[ps].coef + this->termArray[pt].coef == 0) {
                pt++;
                ps++;
                continue;
            }
            c.CreateTerm(source.termArray[ps].coef + this->termArray[pt].coef, source.termArray[ps].exp);
            pt++;
            ps++;
        } else if (this->termArray[pt].exp > source.termArray[ps].exp){
            c.CreateTerm(this->termArray[pt].coef, this->termArray[pt].exp);
            pt++;
        } else{
            c.CreateTerm(source.termArray[ps].coef, source.termArray[ps].exp);
            ps++;
        }
    }
    
    if (pt != this->terms) {
        for (int i = pt; i < this->terms; i++) {
            c.CreateTerm(this->termArray[i].coef, this->termArray[i].exp);
        }
    }
    
    if (ps != source.terms) {
        for (int i = ps; i < source.terms; i++) {
            c.CreateTerm(source.termArray[i].coef, source.termArray[i].exp);
        }
    }
    
	return c;
}

Polynomial Polynomial::operator - (const Polynomial& source)
{
    Polynomial c;
    
    int pt = 0;
    int ps = 0;
    
    while (pt < this->terms && ps < source.terms) {
        if (this->termArray[pt].exp == source.termArray[ps].exp) {
            if (source.termArray[ps].coef == this->termArray[pt].coef) {
                pt++;
                ps++;
                continue;
            }
            c.CreateTerm(this->termArray[pt].coef - source.termArray[ps].coef, source.termArray[ps].exp);
            pt++;
            ps++;
        } else if (this->termArray[pt].exp > source.termArray[ps].exp){
            c.CreateTerm(this->termArray[pt].coef, this->termArray[pt].exp);
            pt++;
        } else{
            c.CreateTerm(source.termArray[ps].coef * -1, source.termArray[ps].exp);
            ps++;
        }
    }
    
    if (pt != this->terms) {
        for (int i = pt; i < this->terms; i++) {
            c.CreateTerm(this->termArray[i].coef, this->termArray[i].exp);
        }
    }
    
    if (ps != source.terms) {
        for (int i = ps; i < source.terms; i++) {
            c.CreateTerm(source.termArray[i].coef, source.termArray[i].exp);
        }
    }
        
    return c;
	
}

Polynomial Polynomial::operator * (const Polynomial& source)
{
	Polynomial c;
        
    for (int i = 0; i < this->terms; i++){
        for (int j = 0; j < source.terms; j++){
            Polynomial *temp = new Polynomial;
            temp->CreateTerm(this->termArray[i].coef * source.termArray[j].coef, this->termArray[i].exp + source.termArray[j].exp);
            c = c + (*temp);
            delete temp;
        }
    }
    
	return c;	
}

bool Polynomial::operator == (const Polynomial& right)
{
    bool ret = false;
    
    if (this->terms != right.terms) {
        return ret;
    }
    
    for (int i = 0; i < terms; i++){
        if (!(this->termArray[i].coef == right.termArray[i].coef && this->termArray[i].exp == right.termArray[i].exp)) {
            return ret;
        }
    }
		
    return true;
}

float Polynomial::Eval(float x)
{
	float ret = 0;
    
    for (int i = 0; i < terms; i++) {
        ret += pow(x, termArray[i].exp) * termArray[i].coef;
    }
		
	return ret;
}

Polynomial Polynomial::Derivative()
{
	Polynomial c;
    
    for (int i = 0; i < terms - 1; i++) {
        float tempCoef = termArray[i].coef;
        int tempExp = termArray[i].exp;
        
        c.CreateTerm(tempCoef * tempExp, tempExp - 1);
    }
    
    if (termArray[terms - 1].exp != 0) {
        float tempCoef = termArray[terms - 1].coef;
        int tempExp = termArray[terms - 1].exp;
        
        c.CreateTerm(tempCoef * tempExp, tempExp - 1);
    }
    
	return c;
}

void Polynomial::CreateTerm(const float coef, const int exp)
{
    for (int i = 0; i < terms; i++) {
        if (termArray[i].exp == exp) {
            termArray[i].coef = coef;
            return;
        }
    }
    
    if (this->capacity == this->terms) {
        this->capacity += 10;
        Term *temp = new Term[capacity];
        for (int i = 0; i < this->terms; i++){
            temp[i].coef = this->termArray[i].coef;
            temp[i].exp = this->termArray[i].exp;
        }
        delete [] termArray;
        this->termArray = temp;
    }
    
    int insertIndex = terms;
    
    for (int i = 0; i < terms; i++) {
        if (termArray[i].exp < exp) {
            insertIndex = i;
            break;
        }
    }
    
    for (int i = terms; i > insertIndex; i--) {
        termArray[i] = termArray[i - 1];
    }
    
    termArray[insertIndex].coef = coef;
    termArray[insertIndex].exp = exp;
    terms++;
}
