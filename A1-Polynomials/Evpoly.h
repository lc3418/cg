// --------------------------------
//
//   Simple Polynomials in K[x,y]
//
//   Christoph M. Hoffmann
//   Winter 2001
//
//   light edits Fall 2018

//
//   no destructors
//   no simplifications
//
#include <iostream>

#pragma once

class ostream;
class pExp;
class term;
class opnd;

// single string to polynomial; no delimiters at end
pExp* readExp(char* is);

//
// parent class:
//   type()    -- OPERATION or OPERAND
//   subtype() -- what operation or what operand
//
class pExp {
public:
  virtual int  type() = 0;
  virtual int  subtype() = 0;
  virtual double eval(double vx, double vy) = 0;
  virtual double evalDx(double vx, double vy) = 0;
  virtual double evalDy(double vx, double vy) = 0;
  virtual int  degree() = 0;
  int  signEval(double vx, double vy);
  friend std::ostream& operator<< (std::ostream&, pExp&);
  enum {OPERATION, OPERAND};
  enum {PLUS, MINUS, TIMES, DIVIDE, POWER, UNARYMINUS, CONSTANT, X, Y};
};

//
// OPERATION
//    subtypes PLUS, MINUS, TIMES, DIVIDE, POWER, UNARYMINUS
//
class term : public pExp {
protected:
public:
  int   operation;
  pExp *arg1, *arg2;
public:
  term(int op, pExp *L, pExp *R);
  int type() {return OPERATION;}
  int subtype() {return operation;}
  int degree();
  double eval(double vx, double vy);
  double evalDx(double vx, double vy);
  double evalDy(double vx, double vy);
  friend std::ostream& operator<< (std::ostream&, term&);
};

//
// OPERAND
//    subtypes CONSTANT, X, Y
//
class opnd : public pExp {
protected:
public:
  int   kind;
  double val;
public:
  opnd(int kd, double v);
  int type() {return OPERAND;}
  int subtype() {return kind;}
  int degree();
  double eval(double vx, double vy);
  double evalDx(double vx, double vy);
  double evalDy(double vx, double vy);
  friend std::ostream& operator<< (std::ostream&, opnd&);
};
