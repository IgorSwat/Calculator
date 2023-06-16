#include <cmath>
#include "operator.h"

Operator::Operator(mode omode, long double pval, unsigned int zcount)
{
    this->val = pval;
    this->operator_mode = omode;
    this->zeros = zcount;
    switch (omode)
    {
    case NUM:
    case E:
    case PI:
        this->lvl = 0;
        break;
    case COMMA:
        this->lvl = 1;
        break;
    case OPEN_BRACKET:
    case CLOSE_BRACKET:
        this->lvl = 2;
        break;
    case POWER:
    case PERCENT:
    case LN:
    case LOG:
    case SIN:
    case COS:
    case TAN:
    case ARCSIN:
    case ARCCOS:
    case ARCTAN:
    case SQRT:
    case STRONG:
        this->lvl = 3;
        break;
    case MULTIPLY:
    case DIVIDE:
        this->lvl = 4;
        break;
    case PLUS:
    case MINUS:
        this->lvl = 5;
        break;
    default:
        this->lvl = 6;
        break;
    }
}

double strong(int n)
{
    long double sum = 1.0;
    for (int i = 1; i <= n; i++)
        sum *= i;
    return sum;
}

Operator Operator::operator&(const Operator& op) const
{
    long double nval = 0.0;
    unsigned int zcount = zeros;
    mode nmode = NUM;
    long long p1, p2, dig_num;
    switch (operator_mode)
    {
    case NUM:
        if (op.lvl == 0)
        {
            if (op.getVal() < 10.0 && op.getMode() != PI && op.getMode() != E)
            {
                if (val == 0.0 && op.getVal() == 0.0)
                    zcount += 1;
                nval = val*10 + op.getVal();
            }
            else
                nval = val*op.getVal();
        }
        else if (op.getMode() == STRONG)
            nval = strong(static_cast<int>(val));
        else
        {
            nval = val;
            zcount = 0;
            nmode = op.getMode();
        }
        break;
    case PI:
    case E:
        if (op.lvl == 0)
            nval = val*op.getVal();
        else
        {
            nval = val;
            nmode = op.getMode();
        }
        break;
    case PLUS:
        nval = val + op.getVal();
        break;
    case MINUS:
        nval = val - op.getVal();
        break;
    case MULTIPLY:
        nval = val*op.getVal();
        break;
    case DIVIDE:
        if (op.getVal() == 0.0)
            nmode = ERROR;
        else
            nval = val / op.getVal();
        break;
    case POWER:
        nval = std::pow(val, op.getVal());
        break;
    case PERCENT:
        nval = val * op.getVal() / 100.0;
        break;
    case SQRT:
        nval = val*std::pow(op.getVal(), 0.5);
        break;
    case OPEN_BRACKET:
        nval = op.getVal();
        break;
    case CLOSE_BRACKET:
        nval = val;
        break;
    case SIN:
        nval = val*std::sin(op.getVal());
        break;
    case COS:
        nval = val*std::cos(op.getVal());
        break;
    case TAN:
        nval = val*std::tan(op.getVal());
        break;
    case ARCSIN:
        if (op.getVal() < -1.0 || op.getVal() > 1.0)
            nmode = ERROR;
        nval = val*std::asin(op.getVal());
        break;
    case ARCCOS:
        if (op.getVal() < -1.0 || op.getVal() > 1.0)
            nmode = ERROR;
        nval = val*std::acos(op.getVal());
        break;
    case ARCTAN:
        nval = val*std::atan(op.getVal());
        break;
    case LN:
        if (op.getVal() <= 0.0)
            nmode = ERROR;
        nval = val*std::log(op.getVal());
        break;
    case LOG:
        if (op.getVal() <= 0.0)
            nmode = ERROR;
        nval = val*std::log10(op.getVal());
        break;
    case COMMA:
        p1 = static_cast<long long>(val);
        p2 = static_cast<long long>(op.getVal());
        dig_num = (op.getVal() != 0 ? static_cast<long long>(std::log10(p2)) + 1 : 1) + op.getZeros();
        nval = p1 * pow(10, dig_num) + p2;
        nval = static_cast<long double>(nval) / pow(10, dig_num);
        break;
    default:
        break;
    }
    return Operator(nmode, nval, zcount);
}
