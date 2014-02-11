/****************************************************/
/*

*/
/*****************************************************/ 

#include "../statement_block.h"
#include "../include/statement.h"


#ifndef IF_STATEMENT_H
#define IF_STATEMENT_H


class If_statement : public Statement
{
  public:
    If_statement(Gpl_type eval_type, Expression *expr, Statement_block* then_block, Statement_block* else_blocki = 0);
    ~If_statement();
    void execute();
	protected:
    Gpl_type        m_expr_eval_type;
  private:

    Statement_block* m_then_block;
    Statement_block* m_else_block;

};

#endif
