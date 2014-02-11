/****************************************************/
/*
*/
/*****************************************************/ 

#include "../include/statement.h"



#ifndef PRINT_STATEMENT_H
#define PRINT_STATEMENT_H

class Expression;

class Print_statement : public Statement
{
  public:
    Print_statement(int line_number, Expression* expr);  // need the line at which the print is executed, and the string (expr)
    ~Print_statement();
    
    void execute();
	protected:

  private:
   // expression *m_expr                 // inherited from statement.h 
    int m_line_number;

};

#endif
