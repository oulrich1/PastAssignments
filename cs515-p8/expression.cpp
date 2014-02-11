#include "expression.h"
//-------------------------------------------//
/* Definitions of Expression functions       */
//-------------------------------------------//

//-------------------------------------------//
// EXPRESSION CONSTRUCTORS:
//    Take a variable
//       or
//    Take a value of type: int, double, or string
//-------------------------------------------//
/*  ------------------------------------------------------ */
// VARIABLE VALUE
// TERMINAL NODES
Expression::Expression(Variable *variable){
  m_variable    = variable;
  m_type        = m_variable->getType(); 

  m_left_expr   = NULL;
  m_right_expr  = NULL;
  m_isOperator  = false;

  m_type_set = false;

  m_is_geometric_operator = false;

//  m_exp_level   = m_type;
}

// GEOMETRIC OPERATIONS: Near, touches. Compares the location of the variable on the left to the variable on the right
Expression::Expression(Variable *varLeft, Variable *varRight, Operator_type TYPE){
  m_variable    = NULL; 
  m_type        = INVALID_TYPE;
  m_left_expr   = new Expression(varLeft);
  m_right_expr  = new Expression(varRight);

  m_operator    = TYPE;
  m_isOperator  = true;

  m_type_set = false;

  m_is_geometric_operator = false;

  if((TYPE == TOUCHES) || (TYPE == NEAR)){
    m_is_geometric_operator = true;
  }

 // m_exp_level   = m_type;
}
/*  ------------------------------------------------------ */
/*  ------------------------------------------------------ */
// CONSTANT VALUES
// TERMINAL NODES
Expression::Expression(Gpl_type TYPE, int x){
    m_variable    = NULL; 
  m_type = TYPE;
  m_integer = x; 

  m_left_expr   = NULL;
  m_right_expr  = NULL;

  m_isOperator  = false;
  m_type_set = false;

  m_is_geometric_operator = false;
}
Expression::Expression(Gpl_type TYPE, double x){
    m_variable    = NULL; 
  m_type = TYPE;
  m_double = x; 

  m_left_expr   = NULL;
  m_right_expr  = NULL;

  m_isOperator  = false;
  m_type_set = false;

  m_is_geometric_operator = false;
}
Expression::Expression(Gpl_type TYPE, string* str){
    m_variable    = NULL; 
  m_type = TYPE;
  m_string = new string(str->c_str());

  m_left_expr   = NULL;
  m_right_expr  = NULL; 

  m_isOperator  = false;
  m_type_set = false;

  m_is_geometric_operator = false;
}
/*  ------------------------------------------------------ */
/*  ------------------------------------------------------ */

// OPERATOR NODES (w/ left and right ptrs) // 

//      CREATES A NON TERMINAL NODE
Expression::Expression(Expression* left_exp, Expression* right_exp, Operator_type TYPE){
  m_variable    = NULL;
  m_type        = INVALID_TYPE;

  m_left_expr   = left_exp;
  m_right_expr  = right_exp;

  m_operator    = TYPE;
  m_isOperator  = true;
  m_type_set = false;

 m_is_geometric_operator = false;

//  m_exp_level   =  left_exp->getType() | right_exp->getType();
}

// Operator with no right ptr.. only left ptr expression.. example: UNARY_MINUS and NOT and MATH_OPS
Expression::Expression(Expression* left_exp, Operator_type TYPE){
  m_variable    = NULL;
  m_type        = INVALID_TYPE;  // the data type is invalid.. since this node is an operator

  m_left_expr   = left_exp;     // essentially a unary operator anyways..
  m_right_expr  = NULL;

  // Operator type get //
  m_operator    = TYPE;
  m_isOperator  = true;
  m_type_set = false;

  m_is_geometric_operator = false;

 // m_exp_level   = left_exp->getType();
}
/*  ------------------------------------------------------ */
/*  ------------------------------------------------------ */

//prints the tree LNR
//  (uses COUT to print details to standard out)
void        Expression::printTree(){
  if(m_left_expr){
    cout << " ...entering left... ";
    m_left_expr->printTree();
  }

  cout << " ...EXAMINING NODE... ";
  if(m_variable){
    cout << " " << m_variable->getVarName() << " ";
  } else if(!m_isOperator) {
    switch(m_type){
      case INT:
        cout << " " << m_integer << " ";
      break;
      case DOUBLE:
        cout << " " << m_double << " ";
      break;
      case STRING:
        cout << " \"" << *m_string << "\" ";
      break;
      case INVALID_TYPE:
      case ANIMATION_BLOCK:
      case GAME_OBJECT:
      //cout << "INVALID TYPE DETECTED IN TREE " << endl;
      break;
    }
  } else {
    cout << operator_to_string(m_operator)  << endl;
  }

  if(m_right_expr){
    cout << " ...entering right... ";
    m_right_expr->printTree();
  }

  cout << "\n ...RETURNING... \n" ;
  return;
}


Gpl_type Expression::getEvaluatedType(){
  if(m_type_set == false){
    m_expr_tree_type = getEvaluatedType_recursive();

    if(ANIMATION_BLOCK & m_expr_tree_type)
      m_expr_tree_type = ANIMATION_BLOCK;
    else if(GAME_OBJECT & m_expr_tree_type)
      m_expr_tree_type = GAME_OBJECT;
    else if(STRING & m_expr_tree_type)
      m_expr_tree_type = STRING;
    else if(DOUBLE & m_expr_tree_type)
      m_expr_tree_type = DOUBLE;
    else if(INT & m_expr_tree_type)
      m_expr_tree_type = INT;
    else
      m_expr_tree_type = INVALID_TYPE;

    m_type_set = true;
    return m_expr_tree_type;
  }
  return m_expr_tree_type;
}

// this time REALLY figure out what the tree SHOULD evaluate to
//  else if( what it SHOULD isnt really what it DOES evaluate to ):
//          then the evaluation type is INVALID
//  else the tree EVALUATES like getType() essentially
Gpl_type Expression::getEvaluatedType_recursive(){

  Gpl_type cur_type, left_type, right_type;
  if(m_variable){
    //cout << "at variable: " << m_variable->getVarName() << " is " << m_variable->getType() << endl;
    return m_variable->getType();
  }
  if(m_isOperator){

      if(m_left_expr){                                    // GET THE LEFT AND RIGHT EVALUATED TYPES
            left_type = m_left_expr->getEvaluatedType_recursive();  // IF THEY ARE INVALID then CALL THEM INVALID
            if(m_right_expr){                             //  else they CONTAIN THE PROPER EVALUATED TYPE
                right_type = m_right_expr->getEvaluatedType_recursive();
                if((left_type == INVALID_TYPE) || (right_type == INVALID_TYPE)){
                  cur_type = INVALID_TYPE;
                } else {
                  cur_type = (Gpl_type)(left_type | right_type); 
                }

            } else {
                if(left_type == INVALID_TYPE){
                  cur_type = INVALID_TYPE;
                } else {
                  cur_type = (Gpl_type)(left_type);        // CUR_TYPE is the new name for the TYPE TO RETURN
                }
            }
      }
      //cout << "at non terminal expression: "<< cur_type << endl;

    switch(m_operator){
      //evaluates to integer or double or string (operands: int, double, string)

      case PLUS: 
        return cur_type;
      break;
      //evalutes to integer or double   (operands: int, double)
      case MINUS:
      case MULTIPLY: 
      case DIVIDE:
        if(cur_type & STRING){      // INVALID TYPE ALERT
          cur_type = INVALID_TYPE;
        }
        return cur_type;
      break;

      // should only evaluate to INTEGER  (operands: int, double)
      case UNARY_MINUS: 
        if(!(cur_type & (INT | DOUBLE))){  // INVALID TYPE ALERT
          cur_type = INVALID_TYPE;
        }
        return cur_type; 
      break;
      case NOT:
        if(cur_type & STRING){  // INVALID TYPE ALERT
          cur_type = INVALID_TYPE;
        } else {
          cur_type = INT;
        }
        return cur_type; 
      break;

      case MOD:                 //(operands: int) 
        if(cur_type & (STRING | DOUBLE)){  // INVALID TYPE ALERT( cannot mod a string nor a double )
            cur_type = INVALID_TYPE;
        }
        return cur_type; 
      break;

      case AND:                 //(operands: int, double) 
      case OR:
        if(cur_type & STRING){  // INVALID TYPE ALERT( cannot AND, OR a string
          cur_type = INVALID_TYPE;
        } else {
          cur_type = INT;
        }
        return cur_type; 
      break;

      case EQUAL:                //(operands: int, double, string)  // BEGIN LIST
      case NOT_EQUAL:
      case LESS_THAN:
      case LESS_THAN_EQUAL:
      case GREATER_THAN:
      case GREATER_THAN_EQUAL:   //(operands: int, double, string)  // END LIST
        cur_type = INT;
        return cur_type;
      break;
      case NEAR:
      case TOUCHES:
        if(cur_type & (STRING | ANIMATION_BLOCK | INT | DOUBLE)){
          cur_type = INVALID_TYPE;
        } else {
          cur_type = INT; // if the type of the left and right are GAME_OBJECT then make sure that
          // THIS EXPRESSION EVALUATES TO AN INT!!!!! AHHHHH
        }
        return cur_type;
      break;

      // should only evaluate to DOUBLE  (operands: int, double)
      case SIN:
      case COS:
      case TAN:
      case ASIN:
      case ACOS:
      case ATAN:
      case SQRT:
        cur_type = (Gpl_type)(cur_type | DOUBLE);
      case ABS:
        if(cur_type & STRING){  // INVALID TYPE ALERT
          cur_type = INVALID_TYPE;
        }
        return cur_type;
      break;
      case RANDOM:        // as long as random has an expression that isnt bad, then it always outputs an integer
        if(cur_type & STRING){  // INVALID TYPE ALERT
          cur_type = INVALID_TYPE;
        } else if(cur_type & DOUBLE){
          cur_type = INT;  // because that is what the expression will evaluate to
        }
        return cur_type;
      break;

      case FLOOR:
        if(cur_type & STRING){  // INVALID TYPE ALERT
          cur_type = INVALID_TYPE;
        } else  {
          cur_type = INT;
        }
        return cur_type;
      break;
      default:
        return INVALID_TYPE; // it should have went through te switch statement properly
      break;
    } // end switch  block
  } // end if is_operator
  //cout << "at terminal expression: "<< m_type << endl;
  return m_type;
}


//-------------------------------------------//

// getValue:  returns a void ptr to a value (from a variable, a varible array.. or constant)

//-------------------------------------------//
void *
Expression::getValue(){
	if(m_variable){
    Expression* index_expr = m_variable->getExpression();
    if(index_expr){                                               // then the variable is an array!
      return m_variable->getValue(index_expr->evaluateInteger()); 
    }

   // its a variable, without an expression ( so its not an array variable) and its not a member variable
    return m_variable->getValue(); // so getvalue
	}
	if(INT & m_type){
    return &m_integer;
  } else if(DOUBLE & m_type){
    return &m_double;
  } else if(STRING & m_type){
    return m_string;
  } 

  return NULL;
}

/////////////////////////////////////////////////
// WORK IN PROGRESS
/////////////////////////////////////////////////
// TODO: "cast" callback function instead?
        //    pass cast as a paramater if NULL.. eh
        //    else execute the cast on the retval.. then return   
        //    retval

//-------------------------------------------//
// Evaluates the expression:
//  If teh expression evaluates to a String then evaluate the string
//   else evaluate as double..
//   if i expected the value to be an integer then the returned value will be caststed 
//     in the scope that the evaluate function was called (where it was called)
///  
//-------------------------------------------//
double
Expression::evaluate(Gpl_type &left_expr_type, Gpl_type &right_expr_type){
    assert(m_left_expr);
    left_expr_type  = m_left_expr->getEvaluatedType();
    right_expr_type = INVALID_TYPE;
    if(m_right_expr){
      right_expr_type = m_right_expr->getEvaluatedType();
    }

    double retval;   
   // cout << "operator:  " << operator_to_string(m_operator)  << endl;
    /* if LEFT or RIGHT is a STRING.. THEN: perform the desired string operation...*/
    if(left_expr_type & STRING || (m_right_expr && (right_expr_type & STRING)) ){
        if(string_operate[m_operator]){
        retval = string_operate[m_operator](m_left_expr->evaluateString(),
                                 (m_right_expr) ? m_right_expr->evaluateString() : 0
                                );
        } else {  // else its an invalid string operation 
          assert(false);
        } 
    } else {
    // or its just a regular integer or double expression
      //cout << (int)left_expr_type <<  " " << (int)right_expr_type << endl;
      
      
      if(m_is_geometric_operator){
        switch(m_operator){
          case TOUCHES:
            retval = ((Game_object*)(m_left_expr->getValue()))->touches((Game_object*)(m_right_expr)->getValue());
            break;
          case NEAR:
            retval = ((Game_object*)(m_left_expr->getValue()))->near((Game_object*)(m_right_expr)->getValue());
            break;
          default:
            retval = -1;
          break;
        }
        return retval;
      } else {
        
          retval = operate[m_operator]( ( ((left_expr_type & DOUBLE)) ? 
                                      m_left_expr->evaluateDoubleRecursive() 
                                      : m_left_expr->evaluateIntegerRecursive() )  ,
                                  (m_right_expr) ? 
                                    ((right_expr_type & DOUBLE) ? 
                                      m_right_expr->evaluateDoubleRecursive() 
                                      : m_right_expr->evaluateIntegerRecursive() )
                                   : 0
                                ); 
      }
    }
    return retval;
}

int
Expression::evaluateInteger(){

   m_evaluatedInt =   (int)evaluateIntegerRecursive();
   return m_evaluatedInt;
}

double
Expression::evaluateIntegerRecursive(){
  if(m_isOperator){ // THEN OPERATE

      Gpl_type left_expr_type;
      Gpl_type right_expr_type;

     double retval = evaluate(left_expr_type, right_expr_type);
      // special case for negative values:
      if(retval == 0) {
        retval = 0;
      } else if( !((left_expr_type | right_expr_type) & DOUBLE) ){ 
        //if the left and the right are not doubles
        retval = (int)retval;  // since the operands were evaluated as integers
      }

   // cout << "retval:    " << retval << endl;
   // cout << "---------------" << endl;
        //cout << "operator: " << operator_to_string(m_operator) << endl;
    return retval;
  }   // end if operator
  else {
    switch(m_type){

      case INT:
        //cout << "value:     " << (*(int*)getValue()) << endl;
        return (*(int*)getValue());
      break;
      case DOUBLE:
        return (*(double*)getValue());
      break;
      case STRING:
      case INVALID_TYPE:
      case GAME_OBJECT:
      case ANIMATION_BLOCK:
      default:
      assert(false);
      return 661;

    } // end switch between type
  }   // end else
  assert(false);
  return 661;
}

double      
Expression::evaluateDouble(){

  m_evaluatedDbl = (double)evaluateDoubleRecursive();
  return m_evaluatedDbl;
}

double      
Expression::evaluateDoubleRecursive(){


  if(m_isOperator == true){ // THEN OPERATE

      Gpl_type left_expr_type;
      Gpl_type right_expr_type;

     double retval = evaluate(left_expr_type, right_expr_type);

      // special case for negative values: WHY doesnt it drop the negative?
      if(retval == 0) {
        retval = 0;
      } 
      else if( ( (left_expr_type & INT) && !(left_expr_type & (DOUBLE | STRING))) &&
            ( (right_expr_type & INT) && !(right_expr_type & (DOUBLE | STRING)) ) 
      ){
        //else if (!((left_expr_type | right_expr_type) & DOUBLE)){
        // the case where it SHOULD Have evaluated to an integer 
        //  (also the case where both are not DOUBLES nor STRINGS)
        retval = (int)retval; // instead of callign the integerfunction instead.. im already here
      }
      /*
      if(!(left_expr_type & DOUBLE) && !(right_expr_type & DOUBLE)){
      }
      */

    //cout << retval << " return value " << endl;
    //cout << "operator: " << operator_to_string(m_operator) << endl;
    return retval;
  }   // end if operator
  else { // base case:  contains a terminal type
    switch(m_type){

      case INT:
        return double(*(int*)getValue());
      break;
      case DOUBLE:
        return (*(double*)getValue());
      break;
      case STRING:
     // this is actually an error since we cannot add strings to integers and output an interger
      case INVALID_TYPE:
      case GAME_OBJECT:
      case ANIMATION_BLOCK:
      default:
      assert(false);
      return 3.1444;

    } // end switch between type
  }   // end else
  assert(false);
  return 3.1444;
}

void
Expression::evaluateString(string &str){
  str = (evaluateString()); // set the passed str to the evaluated string..

  // letting go of the evaluated string
    m_evaluatedStr = str;       // set the value of this root node to the currently expressed value
    m_valsUpdated  = true;          // say that this expression node contains an updated value for the expression

  return;
}


string 
Expression::evaluateString(){
  // only valid operattion on strings is addition 
  if(m_isOperator){ // THEN OPERATE
    string retval;

    Gpl_type left_expr_type  = m_left_expr->getEvaluatedType();
    Gpl_type right_expr_type = INVALID_TYPE;
    if(m_right_expr){
      right_expr_type = m_right_expr->getEvaluatedType();
    }

    string left_value;
    string right_value;

   if( !(left_expr_type & STRING) && (!(m_right_expr) || !(right_expr_type & STRING)) ){
        // IF the left and the right (oh and if the right exists that is)
        //      do not contain any experssions that evaluate to a string.. then
        // ... should be doing int/double arithmetic
        retval = toString<double>(this->evaluateDoubleRecursive()); // if there happen to be more nested strings 
                                                                  // this function call should also take care of 
                                                                  // those as well
      return retval;

    } else if( !(left_expr_type & STRING) ){
      // evaluate the left as a double and the right as a string
      left_value = toString<double>(m_left_expr->evaluateDoubleRecursive()); 

        if(m_operator == PLUS){ // else it wants to add strings together
          retval = left_value + (m_right_expr->evaluateString());   
        } else if(((int)m_operator >= 9) && ((int)m_operator <= 14)) {
          retval = toString<double>( string_operate[m_operator](left_value,
                                                        (m_right_expr) ?
                                                             m_right_expr->evaluateString() 
                                                             : 0
                                                      )
                          );
        } 
    return retval;
    } else if(m_right_expr && !(right_expr_type & STRING) ){
      // evaluate the right as a double and the left a string
      right_value = toString<double>(m_right_expr->evaluateDoubleRecursive()); 

        if(m_operator == PLUS){ // else it wants to add strings together
          retval = m_left_expr->evaluateString() + right_value;   
        } else if(((int)m_operator >= 9) && ((int)m_operator <= 14)) {
          retval = toString<double>( string_operate[m_operator](m_left_expr->evaluateString(),
                                                                right_value
                                                               )
                          );
        } 
    return retval;
    } else {  // evaluate each left and right as a string
      if(m_operator == PLUS){ // else it wants to add strings together
        retval = (m_left_expr->evaluateString()) + (m_right_expr->evaluateString());   
      } else if(((int)m_operator >= 9) && ((int)m_operator <= 14)) {
        retval = toString<double>( string_operate[m_operator](m_left_expr->evaluateString(),
                                                      (m_right_expr) ?
                                                           m_right_expr->evaluateString() 
                                                           : 0
                                                    )
                        );
      return retval;
      } 
    }
   
    return retval;
  }   // end if operator
  else {
    switch(m_type){

      case INT:
        return toString<int>(*(int*)getValue());
      break;
      case DOUBLE:
        return toString<double>(*(double*)getValue());
      break;
      case STRING:
        return *(string*)getValue();
      break;
      case INVALID_TYPE:
      case GAME_OBJECT:
      case ANIMATION_BLOCK:
      default:
      assert(false);
      return "herpderp";

    } // end switch between type
  }   // end else

  assert(false);
  return "herpderp";
}


// //////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////
/* static */
int Expression::initialize_operation_functions(){
  operate      =    new operation_function_t[27];
  operate[0]   =    _plus_;
  operate[1]   =    _minus_;
  operate[2]   =    _mult_;
  operate[3]   =    _div_;
  operate[4]   =    _mod_;
  operate[5]   =    _unary_minus_;
  operate[6]   =    _not_;
  operate[7]   =    _and_;
  operate[8]   =    _or_;
  operate[9]   =    _equal_;
  operate[10]  =    _not_equal_;
  operate[11]  =    _less_than_;
  operate[12]  =    _less_than_equal_;
  operate[13]  =    _greater_than_;
  operate[14]  =    _greater_than_equal_;
  operate[15]  =    NULL;  // for touches and near
  operate[16]  =    NULL;
  operate[17]  =    _sin_;
  operate[18]  =    _cos_;
  operate[19]  =    _tan_;
  operate[20]  =    _asin_;
  operate[21]  =    _acos_;
  operate[22]  =    _atan_;
  operate[23]  =    _sqrt_;
  operate[24]  =    _floor_;
  operate[25]  =    _abs_;
  operate[26]  =    _random_;

  string_operate = new string_compare_t[15];
  string_operate[0]   =    NULL;   
  string_operate[1]   =    NULL;
  string_operate[2]   =    NULL;   
  string_operate[3]   =    NULL;   //
  string_operate[4]   =    NULL;   ///  NOT USED (didnt realize this would happen until now, oops)
  string_operate[5]   =    NULL;   //
  string_operate[6]   =    NULL;
  string_operate[7]   =    NULL;
  string_operate[8]   =    NULL;
  string_operate[9]   = str_compare_equal_;
  string_operate[10]  = str_compare_not_equal_;
  string_operate[11]  = str_compare_less_than_;
  string_operate[12]  = str_compare_less_than_equal_;
  string_operate[13]  = str_compare_greater_than_;
  string_operate[14]  = str_compare_greater_than_equal_;

  return 0;
}
int Expression::delete_operation_functions(){
  delete operate;
  return 0;
}

//-------------------------------------------//
  // BELOW ARE DEFINITIONS OF THE OPERATIONS...
  //  
//-------------------------------------------//
//*  OPERATIONS 

double _plus_(double left, double right){
  return left + right;
}
double _minus_(double left, double right){
  return left - right;
}
double _mult_(double left, double right){
  return left * right;
}
double _div_(double left, double right){ 
  return left / right;
}
double _mod_(double left, double right){
       return (int)left % (int)right;   //sum Values
     }

double _unary_minus_(double right, double TRASH){
       return (-1) * right;
     }

double _not_(double right, double TRASH){
    return right ? 0: 1;
}


double _and_(double left, double right){
    return (left && right);
}

double _or_(double left, double right){
    return (left || right);
}


//  also used for string compare....
double _equal_(double left, double right){
    return (left == right);
}

double _not_equal_(double left, double right){
    return (left != right);
}

double _less_than_(double left, double right){
    return (left < right);
  }
double _less_than_equal_(double left, double right){
    return (left <= right);
  }
double _greater_than_(double left, double right){
    return (left > right);
  }
double _greater_than_equal_(double left, double right){
    return (left >= right);
  }


// TO DO: //  NEAR, TOUCHES, //....

// trig funcs
double _sin_(double degrees, double TRASH ){
      return sin(toRadians(degrees)); 
    }
double _cos_(double degrees, double TRASH){
      return cos(toRadians(degrees)); 
    }
double _tan_(double degrees, double TRASH){
      return tan(toRadians(degrees)); 
    }
double _asin_(double ratio, double TRASH ){
      return toDegrees(asin(ratio)); 
    }
double _acos_(double ratio, double TRASH ){
      return toDegrees(acos((ratio))); 
    }
double _atan_(double ratio, double TRASH ){
      return toDegrees(atan((ratio))); 
    }

// end trig funcs
double _sqrt_(double x, double TRASH ){
      return sqrt(x); 
    }
double _floor_(double x, double TRASH ){
      return floor(x);
    }
double _abs_(double x, double TRASH){
      if(x < 0) x *= -1;
      return x;
    }
double _random_(double MAX, double TRASH){
    double seed = 0; (void)seed;
  #ifndef _SEED_
    seed = (double)time(NULL);
  #else 
    seed = _SEED_;
    srand(seed);
  #endif
   // srand(seed);
  return rand() % (int)MAX;
}

// STRING COMPARISONS  

double str_compare_equal_  (string left, string right){
  return (left == right);
}
double str_compare_not_equal_ (string left, string right){
  return (left != right);
}
double str_compare_less_than_ (string left, string right){
  return (left < right);
}
double str_compare_less_than_equal_ (string left, string right){
  return (left <= right);
}
double str_compare_greater_than_ (string left, string right){
  return (left > right);
}
double str_compare_greater_than_equal_ (string left, string right){
  return (left >= right);
}



// END STRING COMPARISONS


//***     end operations     ***
//******************************

// templated functions cannot be used outside
//  of the file it has been defined in.. 
//  at least not to my knowledge
template <typename TYPE>
string toString(TYPE x){
  stringstream ss;
  ss << x;
  return ss.str();
}