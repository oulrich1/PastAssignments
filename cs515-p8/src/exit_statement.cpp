/****************************************************/
/*
x
*/
/*****************************************************/ 

#include "../include/exit_statement.h"
#include "../expression.h"

Exit_statement::Exit_statement(int line_number, Expression* expr)
{
  m_line_number = line_number;
  m_expr = expr;
}

Exit_statement::~Exit_statement()
{

}


void Exit_statement::execute(){

  if(!m_expr) 
    return;
  

  double exit_status = 0;
  if(m_expr->getEvaluatedType() & (DOUBLE | INT)){
    exit_status = m_expr->evaluateDouble();
    printf("gpl[%d]: exit(%d)\n", m_line_number, (int)exit_status);
    exit(exit_status);
  } else {
    printf("gpl[%d]: exit(0)\n", m_line_number);
    exit(0);
  }
  
  
}