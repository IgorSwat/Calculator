#ifndef OPERATOR_H
#define OPERATOR_H


class Operator
{
public:
    enum mode {NUM, PLUS, MINUS, MULTIPLY, DIVIDE, POWER, OPEN_BRACKET, CLOSE_BRACKET, PERCENT,
                SIN, COS, TAN, ARCSIN, ARCCOS, ARCTAN, LN, LOG, SQRT, STRONG, E, PI, COMMA, NONE, ERROR};
private:
    long double val;
    unsigned int zeros;
    mode operator_mode;
public:
    unsigned int lvl;
    explicit Operator(mode omode = NUM, long double pval = 0.0, unsigned int zcount = 0);
    mode getMode(void) const {return operator_mode;}
    long double getVal(void) const {return val;}
    unsigned int getZeros(void) const {return zeros;}
    void setVal(long double v) {this->val = v;}
    Operator operator&(const Operator& op) const;
};

#endif // OPERATOR_H
