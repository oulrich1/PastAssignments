/****************************************************/
/*
x
*/
/*****************************************************/ 

#include "../statement_block.h"
#include "../include/statement.h"

#ifndef ASSIGN_STATEMENT_H
#define ASSIGN_STATEMENT_H

class Variable;
class Expression;
class Assign_statement  : public Statement
{
  public:
    enum Assign_type{
      ASSIGN = 0,
      PLUS_ASSIGN = 1,
      MINUS_ASSIGN = 2
    };

    Assign_statement(Variable* var, int assign_type, Expression* expr);
    ~Assign_statement();
    void execute();
	protected:
  private:
    Variable*   m_variable;       // THIS VARIABLE
    Assign_type m_assign_type;    // IS ASSIGNED (by this operation)
    Expression* m_expression;           // THIS EXPRESSION's evaluated value

};

#endif
