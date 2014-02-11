

#ifndef __EXPRESSION_H
#define __EXPERSSION_H


#include "variable.h"
#include "globals.h"


/* */
typedef double (*operation_function_t)(double, double);
static operation_function_t *operate;               // please ignore warnings about these not being used

/* */
typedef double (*string_compare_t)(string, string);
static string_compare_t *string_operate;            

using namespace std;

// ----------------------- //
// An expression can be an operator
//  ; OR  a primative gpl type, INT DOUBLE STRING
//  ; OR  a variable ptr 
// 
//  Expressions can be evaluated:
//    evaluation returns a ptr to the expressed value
//          The expressed value can be:
//              CALCULATED
//              STORED
class Expression{
  public:

    static int initialize_operation_functions();
    static int delete_operation_functions();
    // EMPTY CONSTRUCTOR
    Expression() { operate = 0; string_operate = 0; } //initialize to NULL not necessary, gets rid of warning..
	
    // VARIABLE VALUE
    Expression(Variable *variable);

    // Variable GEOMETRIC_OPERATOR Variable
    Expression(Variable *varLeft, Variable *varRight, Operator_type TYPE); 

    // CONSTANT VALUES
    Expression(Gpl_type TYPE, int x);              
    Expression(Gpl_type TYPE, double x);
    Expression(Gpl_type TYPE, string* str);

    // OPERATOR NODES (w/ left and right ptrs)
    Expression(Expression* left_exp, Expression* right_exp, Operator_type TYPE);        
    Expression(Expression* left_exp, Operator_type TYPE);                          // for math operators

    // DESTRUCTOR
    ~Expression() {delete m_left_expr; delete m_right_expr; 
                    if(m_string)
                        delete m_string;  
                    delete m_variable;
                }

    void        printTree();


    //Gpl_type    getType();
    Gpl_type    getEvaluatedType();
    Gpl_type    getEvaluatedType_recursive();

	void*       getValue();
    string      getNameOfVariable(){return (m_variable ? m_variable->getName() : "");}




    double      evaluate(Gpl_type &left_expr_type, Gpl_type &right_expr_type);
    int         evaluateInteger();
    double      evaluateDouble();
    void        evaluateString(string &str); //sets a pointer to a str that has been provided
    string      evalString() { string str;
                                   evaluateString(str); 
                                   m_evaluatedStr = str;
                                   m_valsUpdated  = true;
                                   return str; }
	
    

    bool        IsOperator() { return m_isOperator; }

  private:

    int         getInteger() { return m_integer; }
    double      getDouble() { return m_double; }
    string      getString() { return *m_string; }

    double      evaluateIntegerRecursive();     // actually finds the integer
    double      evaluateDoubleRecursive();      // actually finds the double
    string      evaluateString();               // actually finds the string

    // *** Expression Data *** //
    // ----------------------- //

    // CONSTANT and VARIABLE information :
	Variable*       m_variable;    // a variable value in the expression

    // POssible gpl_types: int, double, string, game_object, animation_block
    Gpl_type        m_type;        // NOTE NOT DIRECTLY ASSOCIATED WITH VARIABLE.. only a variable has access to type of variable DIRECTLY
    int             m_integer;     // these are the values stored in an expression (this values should be constants)
    double          m_double;
    string*         m_string;	


    // OPERATOR information
    Operator_type   m_operator;     // if and when an expression node is an operator
    bool            m_is_geometric_operator;

    Expression*     m_left_expr;
    Expression*     m_right_expr;

    bool            m_isOperator;

    // EVALUATED VALUES updated.. (else needs to be evaluated again if valsUpdated == false)
    bool            m_valsUpdated;
    int             m_evaluatedInt;
    double          m_evaluatedDbl;
    string          m_evaluatedStr;

    bool            m_type_set;
    Gpl_type        m_expr_tree_type;

    //Gpl_type        m_exp_level;  // int->double->string  (keeps track of evaluation at each stage bottom up)


};

#endif

// operation functions
double _plus_(double left, double right);
double _minus_(double left, double right);
double _mult_(double left, double right);
double _div_(double left, double right);
double _mod_(double left, double right);
double _unary_minus_(double right, double TRASH=0);
double _not_(double right, double TRASH=0);
double _and_(double left, double right);
double _or_(double left, double right);
double _equal_(double left, double right);
double _not_equal_(double left, double right);
double _less_than_(double left, double right);
double _less_than_equal_(double left, double right);
double _greater_than_(double left, double right);
double _greater_than_equal_(double left, double right);
double _sin_(double degrees, double TRASH = 0);
double _cos_(double degrees, double TRASH = 0);
double _tan_(double degrees, double TRASH = 0);
double _asin_(double ratio, double TRASH = 0);
double _acos_(double ratio, double TRASH = 0);
double _atan_(double ratio, double TRASH = 0);
double _sqrt_(double x, double TRASH = 0);
double _floor_(double x, double TRASH = 0);
double _abs_(double x, double TRASH = 0);
double _random_(double x, double TRASH = 0);
double _abs_(double x, double TRASH );
double _random_(double MAX, double TRASH );

double str_compare_equal_  (string left, string right);
double str_compare_not_equal_ (string left, string right);
double str_compare_less_than_ (string left, string right);
double str_compare_less_than_equal_ (string left, string right);
double str_compare_greater_than_ (string left, string right);
double str_compare_greater_than_equal_ (string left, string right);
///  EXTRA HELPING FUNCTIONS

template <typename TYPE>
string              toString(TYPE x);