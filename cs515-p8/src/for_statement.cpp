/****************************************************/
/*
x
*/
/*****************************************************/ 

#include "../include/for_statement.h"
#include "../expression.h"

For_statement::For_statement( Statement_block* initializer, 
                              Expression* condition, 
                              Statement_block* assignment_statement, 
                              Statement_block* execution_block )
{
  m_initializer           =   initializer;
  m_condition             =   condition;
  m_execution_block       =   execution_block;
  m_assignment_statement  =   assignment_statement;
  
}

For_statement::~For_statement()
{

}

/* loops until m_condition is false */
void For_statement::execute(){
  if(!m_condition)
   return; 
 
  m_initializer->execute();


  for(;m_condition->evaluateDouble();){
    m_execution_block->execute();
    m_assignment_statement->execute();
  }

}