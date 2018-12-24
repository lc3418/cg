// --------------------------------
//
//   Simple Polynomials in R[x,y]
//
//   Christoph M. Hoffmann
//   Winter 2001
//
//   lightly revised Fall 2018
//
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <iostream>
#include "Evpoly.h"

using namespace std;

// constructors
term::term(int op, pExp *L, pExp *R) {
  operation = op;
  arg1 = L;
  if (operation == UNARYMINUS)
    return;
  arg2 = R;
}

opnd::opnd(int kd, double v) {
  kind = kd;
  if (kind == CONSTANT)
    val = v;
}

// evaluation -- operations
double term::eval(double vx, double vy) {
  double v1 = arg1->eval(vx,vy), v2, w;
  int    ex;
  if (operation == UNARYMINUS)
    return -v1;
  v2 = arg2->eval(vx,vy);
  switch (operation) {
  case PLUS:
    return v1 + v2;
  case MINUS:
    return v1 - v2;
  case TIMES:
    return v1 * v2;
  case DIVIDE:
    return v1 / v2;
  case POWER:
    ex = ((int) v2);
    if (ex < 0)
      assert(0);
    if (ex == 0)
      return 1;
    if (ex == 1)
      return v1;
    w = v1;
    while (--ex > 0)
      w *= v1;
    return w;
  }
  assert(0);
  return 0;
}

// evaluation -- operations
double term::evalDx(double vx, double vy) {
  double d1 = arg1->evalDx(vx,vy), d2, v1, v2, w;
  int    ex;
  if (operation == UNARYMINUS)
    return -d1;
  d2 = arg2->evalDx(vx,vy);
  v1 = arg1->eval(vx,vy);
  v2 = arg2->eval(vx,vy);
  switch (operation) {
  case PLUS:
    return d1 + d2;
  case MINUS:
    return d1 - d2;
  case TIMES:
    return v1 * d2 + d1 * v2;
  case DIVIDE:
    return (d1 * v2 - v1 * d2) / (v2 * v2);
  case POWER:
    ex = ((int) v2);
    if (ex < 0)
      assert(0);
    if (ex == 0)
      return 0;
    if (ex == 1)
      return d1;
    w = d1*ex;
    while (--ex > 0)
      w *= v1;
    return w;
  }
  assert(0);
  return 0;
}

// evaluation -- operations
double term::evalDy(double vx, double vy) {
  double d1, d2, v1, v2, w;
  int    ex;
  d1 = arg1->evalDy(vx,vy);
  if (operation == UNARYMINUS)
    return -d1;
  d2 = arg2->evalDy(vx,vy);
  v1 = arg1->eval(vx,vy);
  v2 = arg2->eval(vx,vy);
  switch (operation) {
  case PLUS:
    return d1 + d2;
  case MINUS:
    return d1 - d2;
  case TIMES:
    return v1 * d2 + d1 * v2;
  case DIVIDE:
    return (d1 * v2 - v1 * d2) / (v2 * v2);
  case POWER:
    ex = ((int) v2);
    if (ex < 0)
      assert(0);
    if (ex == 0)
      return 0;
    if (ex == 1)
      return d1;
    w = d1*ex;
    while (--ex > 0)
      w *= v1;
    return w;
  }
  assert(0);
  return 0;
}

// evaluation -- operands
double opnd::eval(double vx, double vy) {
  switch (kind) {
  case CONSTANT:
    return val;
  case X:
    return vx;
  case Y:
    return vy;
  }
  assert(0);
  return 0;
}

// evaluation -- operands
double opnd::evalDx(double vx, double vy) {
  switch (kind) {
  case CONSTANT:
    return 0;
  case X:
    return 1;
  case Y:
    return 0;
  }
  assert(0);
  return 0;
}

// evaluation -- operands
double opnd::evalDy(double vx, double vy) {
  switch (kind) {
  case CONSTANT:
    return 0;
  case X:
    return 0;
  case Y:
    return 1;
  }
  assert(0);
  return 0;
}

// symbolic output in readable form
std::ostream& operator<<(std::ostream& os, pExp& E) {
  if (E.type() == pExp::OPERATION)
    os << ((term&) E);
  else 
    os << ((opnd&) E);
  return os;
}

std::ostream& operator<<(std::ostream& os, opnd& E) {
  if (E.subtype() == pExp::CONSTANT) {  
    if (E.val < 0)
      os << "(" << E.val << ")";
    else
      os << E.val;
  } else if (E.subtype() == pExp::X)
    os << "x";
  else
    os << "y";
  return os;
}

std::ostream& operator<<(std::ostream& os, term& E) {
  int ex;
  switch(E.subtype()) {
  case pExp::PLUS:
    os << *E.arg1 << "+" << *E.arg2;
    break;
  case pExp::MINUS:
    os << *E.arg1 << "-" << *E.arg2;
    break;
  case pExp::UNARYMINUS:
    os << "(-";
    if (E.arg1->type() == pExp::OPERATION)
      os << "(" << *E.arg1 << ")";
    else
      os << *E.arg1;
    os << ")";
    break;
  case pExp::TIMES:
  case pExp::DIVIDE:
    if (E.arg1->type() == pExp::OPERATION &&
       (E.arg1->subtype() == pExp::PLUS ||
        E.arg1->subtype() == pExp::MINUS)) 
      os << "(" << *E.arg1 << ")";
    else
      os << *E.arg1;
    if (E.subtype() == pExp::TIMES)
      os << "*";
    else
      os << "/";
    if (E.arg2->type() == pExp::OPERATION &&
       (E.arg2->subtype() == pExp::PLUS ||
        E.arg2->subtype() == pExp::MINUS)) 
      os << "(" << *E.arg2 << ")";
    else
      os << *E.arg2;
    break;
  case pExp::POWER:
    ex = ((int) (E.arg2->eval(0,0)));
    assert(ex >= 0);
    if (E.arg1->type() == pExp::OPERAND ||
       (E.arg1->type() == pExp::OPERATION &&
        E.arg1->subtype() == pExp::UNARYMINUS)) {
      os << *E.arg1 << "^" << ex;
    } else {
      os << "(" << *E.arg1 << ")^" << ex;
    }
    break;
  }
  return os;
}

// sign evaluation; eps adjusted by degree
int pExp::signEval(double vx, double vy) {
  double eps, s = eval(vx,vy);
  int d = degree();
  if (d == 0)
    eps = 0;
  else if (d <= 1)
    eps = 1e-9;
  else if (d <= 2)
    eps = 1e-7;
  else if (d <= 3)
    eps = 1e-6;
  else if (d <= 5)
    eps = 1e-5;
  else
    eps = 1e-4;
  if (s > eps)
    return 1;
  if (s < -eps)
    return -1;
  return 0;
}

// degree
int term::degree() {
  int d1, d2, t = subtype();
  d1 = arg1->degree();
  if (t == UNARYMINUS)
    return d1;
  if (t == POWER) {
    t = ((int) arg2->eval(0,0));
    assert(t >= 0);
    return t*d1;
  }
  d2 = arg2->degree();
  switch (t) {
  case PLUS:
  case MINUS:
    return (d1>d2 ? d1 : d2);
  case TIMES:
    return d1+d2;
  }
  return -1;
}

int opnd::degree() {
  if (subtype() == CONSTANT)
    return 0;
  return 1;
}


// -----------------------------
//
//  expression input parse utilities
//
//  recursive descent parsing
//  power exponent must be numerical
//

enum{
  TK_EOF = 1, 
  TK_CONST, TK_VARX,  TK_VARY,
  TK_LPAR,  TK_RPAR,
  TK_PLUS,  TK_MINUS,
  TK_TIMES, TK_DIVIDE,
  TK_POWER
};

// globals for expression input
static int    token;              // scanner token
static double tkValue;            // value of numeric constants
static char   lineString[1024];   // parse string
static char  *lineP;              // scan position

static void skipWhite() {         // skip blank and tab
  while (*lineP == ' ' || *lineP == '\t')
    lineP++;
}

static void getToken() {          // get token and
  double frac, divs;              // stop on next character
  skipWhite();                    // except for EOS which does not advance
  if (*lineP == '\0') {
    token = TK_EOF;
    return;
  }
  if ('0' <= *lineP && *lineP <= '9') {
    // put number together
    token = TK_CONST;
    tkValue = *lineP - '0';
    while (*++lineP >= '0' && *lineP <= '9')
      tkValue = tkValue*10 + *lineP - '0';
    if (*lineP == '.') {
      frac = 0;
      divs = 10;
      while (*++lineP >= '0' && *lineP <= '9') {
        frac += (*lineP - '0') / divs;
        divs *= 10;
      }
      tkValue += frac;
    }
    return;
  }
  switch (*lineP) {
  case 'x':
  case 'X':
    token = TK_VARX;
    break;
  case 'y':
  case 'Y':
    token = TK_VARY;
    break;
  case '(':
    token = TK_LPAR;
    break;
  case ')':
    token = TK_RPAR;
    break;
  case '+':
    token = TK_PLUS;
    break;
  case '-':
    token = TK_MINUS;
    break;
  case '*':
    token = TK_TIMES;
    break;
  case '/':
    token = TK_DIVIDE;
    break;
  case '^':
    token = TK_POWER;
    break;
  default:
    assert(0);
  }
  lineP++;
  return;
}

static pExp* getTerm();
static pExp* getPowr();
static pExp* getPrim();

static pExp* getSum() {
  pExp *E1, *E2;
  int tk;
  E1 = getTerm();
  if (E1 == 0)
    return 0;
  while (token == TK_PLUS || token == TK_MINUS) {
    tk = (token==TK_PLUS ? pExp::PLUS : pExp::MINUS);
    getToken();
    E2 = getTerm();
    if (E2 == 0)
      return 0;
    E1 = new term(tk, E1, E2);
  }
  return E1;
}

static pExp* getTerm() {
  pExp *E1, *E2;
  int  tk;
  E1 = getPowr();
  if (E1 == 0)
    return 0;
  while (token == TK_TIMES || token == TK_DIVIDE) {
    tk = (token==TK_TIMES ? pExp::TIMES : pExp::DIVIDE);
    getToken();
    E2 = getPowr();
    if (E2 == 0)
      return 0;
    E1 = new term(tk, E1, E2);
  }
  return E1;
}

static pExp* getPowr() {
  pExp *E1, *E2;
  E1 = getPrim();
  if (E1 == 0)
    return 0;
  if (token == TK_POWER) {
    getToken();
    E2 = getPrim();
    if (E2 == 0)
      return 0;
    if (E2->subtype() != pExp::CONSTANT) {
      cerr << "exponent must be a positive number\n";
      return 0;
    }
    E1 = new term(pExp::POWER, E1, E2);
  } 
  return E1;
}

static pExp* getPrim() {
  pExp *E1;
  if (token == TK_LPAR) {
    getToken();
    E1 = getSum();
  } else if (token == TK_CONST) {
    E1 = new opnd(pExp::CONSTANT, tkValue);
  } else if (token == TK_VARX) {
    E1 = new opnd(pExp::X, 0);
  } else if (token == TK_VARY) {
    E1 = new opnd(pExp::Y, 0);
  } else if (token == TK_MINUS) {
    getToken();
    E1 = getTerm();
    if (E1 == 0)
      return 0;
    E1 = new term(pExp::UNARYMINUS, E1, 0);
    return E1;
  } else {
    cerr << "ill-formed expression\n";
    return 0;
  }
  if (E1 == 0)
    return 0;
  getToken();
  return E1;
}

pExp* readExp(char* is) {
  pExp *Q;
  strcpy_s(lineString, is);
  lineP = lineString;
  getToken();
  if (token == TK_EOF)
    return 0;
  Q = getSum();
  return Q;
}

