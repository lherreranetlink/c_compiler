#include "grammar_attributes.h"

SemanticType getNumericType(SemanticType t1, SemanticType t2)
{
    if (t1 == INTEGER_SYMBOL && t2 == INTEGER_SYMBOL)
        return INTEGER_SYMBOL;
    else if (t1 == INTEGER_SYMBOL && t2 == REAL_SYMBOL)
        return INTEGER_SYMBOL;
    else if (t1 == REAL_SYMBOL && t2 == INTEGER_SYMBOL)
        return INTEGER_SYMBOL;
    else if (t1 == REAL_SYMBOL && t2 == REAL_SYMBOL)
        return REAL_SYMBOL;
    else if (t1 == BOOLEAN_SYMBOL && t2 == BOOLEAN_SYMBOL)
        return BOOLEAN_SYMBOL;
    else if (t1 == BOOLEAN_SYMBOL && t2 == INTEGER_SYMBOL)
        return BOOLEAN_SYMBOL;
    else if (t1 == INTEGER_SYMBOL && t2 == BOOLEAN_SYMBOL)
        return BOOLEAN_SYMBOL;
    else
        return ERROR_SYMBOL;
}
