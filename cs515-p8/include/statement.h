



#ifndef STATEMENT_H
#define STATEMENT_H

#include "../error.h"

#include  "../gpl_assert.h"
#include  "../gpl_type.h"

class Expression;

class Statement{
	public:
    Statement();
		~Statement();
    int get_line_number(){return m_line_number;}
		virtual void execute() = 0;

  protected:
    Expression *m_expr;
    int m_line_number;

	private:
};


#endif 
