#ifndef SEMANTIC_TYPE_H_INCLUDED
#define SEMANTIC_TYPE_H_INCLUDED

typedef enum {INTEGER_SYMBOL, REAL_SYMBOL, VOID_SYMBOL, ERROR_SYMBOL} SemanticType;

SemanticType getNumericType(SemanticType t1, SemanticType t2);

#endif // SEMANTIC_TYPE_H_INCLUDED
