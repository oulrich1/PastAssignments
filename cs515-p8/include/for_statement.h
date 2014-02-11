/****************************************************/
/*

*/
/*****************************************************/ 

#include "../statement_block.h"
#include "../include/statement.h"

#ifndef FOR_STATEMENT_H
#define FOR_STATEMENT_H

class Expression;
class For_statement  : public Statement
{
  public:
    // four arguemnts: left block, expression, right block, for_statement_block
    For_statement(Statement_block* initializer, 
                  Expression* condition, 
                  Statement_block* assignment_statement, 
                  Statement_block* execution_block);

    ~For_statement();
    void execute();
	protected:
  private:
    Statement_block* m_initializer;
    Expression*      m_condition;
    Statement_block* m_execution_block;
    Statement_block* m_assignment_statement;

};

#endif
