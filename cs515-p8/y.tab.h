/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     T_FALSE = 258,
     T_TRUE = 259,
     T_INT_CONSTANT = 260,
     T_DOUBLE_CONSTANT = 261,
     T_STRING_CONSTANT = 262,
     T_ID = 263,
     T_PRINT = 264,
     T_EXIT = 265,
     T_INT = 266,
     T_DOUBLE = 267,
     T_STRING = 268,
     T_MINUS = 269,
     T_PLUS = 270,
     T_DIVIDE = 271,
     T_ASTERISK = 272,
     T_MOD = 273,
     T_AND = 274,
     T_OR = 275,
     T_NOT = 276,
     T_EQUAL = 277,
     T_GREATER = 278,
     T_LESS = 279,
     T_RANDOM = 280,
     T_FLOOR = 281,
     T_ABS = 282,
     T_SQRT = 283,
     T_ATAN = 284,
     T_ACOS = 285,
     T_ASIN = 286,
     T_TAN = 287,
     T_COS = 288,
     T_SIN = 289,
     T_NEAR = 290,
     T_TOUCHES = 291,
     T_CONSTANT = 292,
     T_ELSE = 293,
     T_IF = 294,
     T_LKEY = 295,
     T_KKEY = 296,
     T_JKEY = 297,
     T_HKEY = 298,
     T_FKEY = 299,
     T_DKEY = 300,
     T_SKEY = 301,
     T_AKEY = 302,
     T_WKEY = 303,
     T_SPACE = 304,
     T_MOUSE = 305,
     T_RIGHTMOUSE = 306,
     T_MIDDLEMOUSE = 307,
     T_LEFTMOUSE = 308,
     T_DOWNARROW = 309,
     T_UPARROW = 310,
     T_RIGHTARROW = 311,
     T_LEFTARROW = 312,
     T_COMMA = 313,
     T_SEMIC = 314,
     T_FORWARD = 315,
     T_INITIALIZATION = 316,
     T_TRIANGLE = 317,
     T_PIXMAP = 318,
     T_CIRCLE = 319,
     T_RECTANGLE = 320,
     T_TEXTBOX = 321,
     T_ANIMATION = 322,
     T_F1 = 323,
     T_FOR = 324,
     T_ON = 325,
     T_LEFTMOUSE_DOWN = 326,
     T_LEFTMOUSE_UP = 327,
     T_MIDDLEMOUSE_DOWN = 328,
     T_MIDDLEMOUSE_UP = 329,
     T_MOUSE_DRAG = 330,
     T_MOUSE_MOVE = 331,
     T_PERIOD = 332,
     T_RIGHTMOUSE_DOWN = 333,
     T_RIGHTMOUSE_UP = 334,
     T_LESS_EQUAL = 335,
     T_GREATER_EQUAL = 336,
     T_NOT_EQUAL = 337,
     T_PLUS_ASSIGN = 338,
     T_MINUS_ASSIGN = 339,
     T_ASSIGN = 340,
     T_RBRACKET = 341,
     T_LBRACKET = 342,
     T_RBRACE = 343,
     T_LBRACE = 344,
     T_RPAREN = 345,
     T_LPAREN = 346,
     UNARY_OP = 347,
     T_IF_NO_ELSE = 348
   };
#endif
/* Tokens.  */
#define T_FALSE 258
#define T_TRUE 259
#define T_INT_CONSTANT 260
#define T_DOUBLE_CONSTANT 261
#define T_STRING_CONSTANT 262
#define T_ID 263
#define T_PRINT 264
#define T_EXIT 265
#define T_INT 266
#define T_DOUBLE 267
#define T_STRING 268
#define T_MINUS 269
#define T_PLUS 270
#define T_DIVIDE 271
#define T_ASTERISK 272
#define T_MOD 273
#define T_AND 274
#define T_OR 275
#define T_NOT 276
#define T_EQUAL 277
#define T_GREATER 278
#define T_LESS 279
#define T_RANDOM 280
#define T_FLOOR 281
#define T_ABS 282
#define T_SQRT 283
#define T_ATAN 284
#define T_ACOS 285
#define T_ASIN 286
#define T_TAN 287
#define T_COS 288
#define T_SIN 289
#define T_NEAR 290
#define T_TOUCHES 291
#define T_CONSTANT 292
#define T_ELSE 293
#define T_IF 294
#define T_LKEY 295
#define T_KKEY 296
#define T_JKEY 297
#define T_HKEY 298
#define T_FKEY 299
#define T_DKEY 300
#define T_SKEY 301
#define T_AKEY 302
#define T_WKEY 303
#define T_SPACE 304
#define T_MOUSE 305
#define T_RIGHTMOUSE 306
#define T_MIDDLEMOUSE 307
#define T_LEFTMOUSE 308
#define T_DOWNARROW 309
#define T_UPARROW 310
#define T_RIGHTARROW 311
#define T_LEFTARROW 312
#define T_COMMA 313
#define T_SEMIC 314
#define T_FORWARD 315
#define T_INITIALIZATION 316
#define T_TRIANGLE 317
#define T_PIXMAP 318
#define T_CIRCLE 319
#define T_RECTANGLE 320
#define T_TEXTBOX 321
#define T_ANIMATION 322
#define T_F1 323
#define T_FOR 324
#define T_ON 325
#define T_LEFTMOUSE_DOWN 326
#define T_LEFTMOUSE_UP 327
#define T_MIDDLEMOUSE_DOWN 328
#define T_MIDDLEMOUSE_UP 329
#define T_MOUSE_DRAG 330
#define T_MOUSE_MOVE 331
#define T_PERIOD 332
#define T_RIGHTMOUSE_DOWN 333
#define T_RIGHTMOUSE_UP 334
#define T_LESS_EQUAL 335
#define T_GREATER_EQUAL 336
#define T_NOT_EQUAL 337
#define T_PLUS_ASSIGN 338
#define T_MINUS_ASSIGN 339
#define T_ASSIGN 340
#define T_RBRACKET 341
#define T_LBRACKET 342
#define T_RBRACE 343
#define T_LBRACE 344
#define T_RPAREN 345
#define T_LPAREN 346
#define UNARY_OP 347
#define T_IF_NO_ELSE 348




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 100 "gpl.y"

 int            union_int;
 double         union_double;                // makes this known as a double as well
 std::string*   union_string;               // MUST be a pointer to a string (this sucks!)
 Expression*    union_expression;
 Variable*      union_variable;

 Gpl_type		union_gpltype;
 Operator_type  union_gploperator;           // any Operator_type.. geometric or math

 Game_object*   union_gameobject;
 Statement*     union_statement;
 Statement_block* union_statementblock;
 Window::Keystroke union_keystroke;



/* Line 2068 of yacc.c  */
#line 254 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


