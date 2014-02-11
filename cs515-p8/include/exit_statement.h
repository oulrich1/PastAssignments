/****************************************************/
/*
x
*/
/*****************************************************/ 

#include "../include/statement.h"

#ifndef EXIT_STATEMENT_H
#define EXIT_STATEMENT_H


class Exit_statement  : public Statement
{
  public:
    Exit_statement(int line_number, Expression *expr);
    ~Exit_statement();
    void execute();
	protected:
  private:
    int m_line_number;

};

#endif
