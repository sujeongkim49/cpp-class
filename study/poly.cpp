istream& operator<< (istream& is, Polynomial& p) {
    int noofterms; float coef; int exp;
    is >> noofterms;
    for (int i = 0; i < noofterms; i++) {
        is >> coef >> exp;
        p.NewTerm(coef, exp);
    }
    return is;
}

ostream& operator<<(ostream& os, Polynomial& p) {
    for (int i = 0; i < p.terms; i++) {
        float coef = p.termArray[i].coef;
        int exp = p.termArray[i].exp;

        if (coef == 0) continue;

        if (i == 0 && coef < 0) os << '-';
        if (i == 0 && coef >= 0) os << " ";

        if (i > 0 && coef < 0) os << '-';
        if (i > 0 && coef >= 0) os << "+";

        float absCoef = (coef >= 0) ? coef : -coef;

        if (exp == 0) os<<absCoef;
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

Polynomial::Polynomial() : capacity(1), terms(0) {
    termArray = new Term[capacity];
}

void Polynomial::NewTerm(const float theCoef, const int theExp) {
    if (terms == capacity) {
        capacity *= 2;
        Term* temp = new Term[capacity];
        copy(termArray, termArray + terms, temp);
        delete[] termArray;
        termArray = temp;
    }
    termArray[terms].coef = theCoef;
    termArray[terms].exp = theExp;
    terms++;
}