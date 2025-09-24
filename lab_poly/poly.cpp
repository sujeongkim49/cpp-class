//C435071 김수정
#include <iostream>
#include "poly.h"
using namespace std;
istream& operator>> (istream& is, Polynomial& p) {
    // #terms and (coefficoent, exponent)의 pair들을 읽어들인다. // 높은 차수의 항부터 입력되어 저장된다고 가정한다.
    int noofterms; float coef; int exp;
    is >> noofterms;
    for (int i = 0; i < noofterms; i++) {
        is >> coef >> exp; // 계수와 지수 pair를 읽어들인다.
        p.NewTerm(coef, exp);
    }
    return is;
}
ostream& operator<< (ostream& os, Polynomial& p) {
    for (int i = 0; i < p.terms; i++) {
        float coef = p.termArray[i].coef;
        int exp = p.termArray[i].exp;

        if (coef == 0) continue; // 계수가 0인 항은 출력하지 않는다.

        if (i == 0 && coef < 0) os << "-";
        if (i == 0 && coef >= 0) os << "";

        if (i > 0 && coef >= 0) os << " +";
        if (i > 0 && coef < 0) os << " -";

        float absCoef = (coef >= 0) ? coef : -coef;

        if (exp == 0) os << absCoef;
        else if (exp == 1) {
            if (absCoef == 1) os << "x";
            else os << absCoef << "x";
        }
        else {
            if (absCoef == 1) os << "x^" << exp;
            else os << absCoef << "x^" << exp;
        }
    }
    os << endl;
    return os;
}
Polynomial::Polynomial() :capacity(1), terms(0)
{
    termArray = new Term[capacity];
}

void Polynomial::NewTerm(const float theCoeff, const int theExp)
{
    if (terms == capacity) {
        capacity *= 2;
        Term* temp = new Term[capacity];
        copy(termArray, termArray + terms, temp);
        delete[] termArray;
        termArray = temp;
    }
    termArray[terms].coef = theCoeff;
    termArray[terms].exp = theExp;
    terms++;
}

Polynomial Polynomial::operator+(Polynomial& b)
{
    Polynomial result;
    int aPos = 0, bPos = 0;
    while (aPos < terms && bPos < b.terms) {
        if (termArray[aPos].exp == b.termArray[bPos].exp) {
            float t = termArray[aPos].coef + b.termArray[bPos].coef;
            if (t) result.NewTerm(t, termArray[aPos].exp);
            aPos++; bPos++;
        }
        else if (termArray[aPos].exp > b.termArray[bPos].exp) {
            result.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
            aPos++;
        }
        else {
            result.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
            bPos++;
        }
    }
    for(;aPos<terms;aPos++)
        result.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
    for (; bPos < b.terms; bPos++)
        result.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
    return result;
}