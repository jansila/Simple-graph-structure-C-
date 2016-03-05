/*
 * PrimRec.h
 *
 *  Created on: Nov 27, 2015
 *      Author: np183
 *      Module: CO7104
 *      Department of Computer Science
 *      University of Leicester
 */

#ifndef PRIMREC_H_
#define PRIMREC_H_

#include <string>
#include <iosfwd>
#include <vector>


// The idea of this exercise it to do a more complex inheritance hierarchy
// and at the same time learn some important computing principles.
// The exercise is based around the concept of primitive recursive funcitons.
// Please have a look at this Wikipedia page:
// https://en.wikipedia.org/wiki/Primitive_recursive_function
// and the first few pages of this summary:
// http://www.cs.umd.edu/~gasarch/COURSES/452/S14/dec.pdf
//
// Primitive recursive functions are functions that take Natural numbers as
// inputs and compute functions over Natural numbers.
// They formed an important part of the study into what is computable and
// what are the limits of the power of computation.
//
// For the purpose of this exercise you don't have to understand the
// theoretical background and most of the exercise can be completed
// without thinking about (math) functions at all.
// The bit that has to do with application of these functions does require
// understanding of what they are.
//
//
// You are asked to implement the following class hierarchy:
//
//                    PrimRec
//                       |
//           --------------------------------------------------
//           |           |              |           |           |
//        Binary       Project        Nary         Const      Unary
//           |                          |                       |
//           |                          |               -----------------
//           |                          |               |               |
//        Recurse                     Compose          Succ            Pred
//
// Even though Nary and Binary have only one object inheriting from them
// you should try to think about them as the base class of many
// possible derived classes and try to push as much of the implementation
// of common features for all Binary and Nary functions into them.
//
// All types of primitive recursive functions support:
// name - a pretty print into a string to the name of the function (details below)
// toString - print the entire function
// evaluate - compute the value of the function for some given input
//
// Some points will be awarded for NOT implementing all functions at the leaf
// level. In particular, this holds for toString.
// You might have to add additional functions and think carefully about what
// private variables are needed and where to put them.
//
// All the following are your role:
// 1. Decide which functions should be virtual.
// 2. Decide which functions should be pure virtual.
// 3. Decide which classes should be abstract classes.
// 4. Decide where to implement the required functions.
//
// Notice that all pointers that are passed on to you (for operands of
// functions that you are building) are dynamic memory and become your
// responsibility once they are sent to the constructor.
//
// This is the base class of the entire hierarchy
class PrimRec {
public:
	PrimRec() = delete;
	PrimRec(const PrimRec&) = delete;
	PrimRec(PrimRec&&) = delete;
	// Every primitive recursive functions has an arity.
	// This means the kind of input that it accepts.
	// For example:
	// A function of arity 1 is a function of 1 natural number: f(x)
	// A function of arity 3 is a function of 3 natural numbers: f(x,y,z)
	PrimRec(unsigned int arity);
	PrimRec(unsigned int arity, std::string name);

	virtual ~PrimRec();

	// Evaluate the function on the given input.
	// The given input should match the arity of the function.
	// Otherwise, you should throw a domain_error exception.
	//
	// Individual explanations to what evaluate should do are given
	// before each class for which this is defined.
	//
	// If the arity of the PrimRec does not match the input
	// then a domain_error exception should be thrown
	virtual unsigned int evaluate(std::vector<unsigned int>) const;

	// Return a string representing the function.
	// This should start with the name of the function and be followed
	// by it's operands.
	// For example:
	// A Const whose value if 5 will be printed as 5
	// A Project whose projecting on the i'th coordinate and whose arity
	// is 3 will print: P_i(x_0,x_1,x_2)
	// A Succ will print: Succ(subexpression)
	// A Pred will print: Pred(subexpression)
	// A Compose will print: Compose(sub1,...,subn)
	// A Recurse will print: Recurse(sub1,sub2)
	virtual std::string toString() const;

	// Return the body of the name of the function
	// A Const whose value if 5 will return 5
	// A Project whose projecting on the i'th coordinate will print: P_i
	// A Succ will print: Succ
	// A Pred will print: Pred
	// A Compose will print: Compose
	// A Recurse will print: Recurse
	virtual std::string name() const;

	// Return the arity of the operator
	unsigned int arity() const;

	// Use toString to allow redirection of all types of PrimRec-s.
	friend std::ostream& operator<< (std::ostream&, const PrimRec&);
	void printOut(std::ostream & o) const;

protected:

private:
	unsigned int arity_;
	std::string name_;

};

// A Const as it's name suggests is a constant.
// It is initailized with its value and can have any arity.
// When evaluated it returns its value.

class Const : public PrimRec {
public:
	Const() = delete;
	Const(const Const&) = delete;
	Const(Const&&) = delete;

	Const(unsigned int arity, unsigned int value=0);

	std::string toString() const override;
	std::string name() const override;
	unsigned int evaluate(std::vector<unsigned int>) const override;

	~Const();

private:
unsigned int value_;
};

// A Project projects a sequence of parameters on a given
// coordinate.
// It is initialized with it's arity and the coordinate
// on which it is projecting.
//
// It can have any arity but if projecting on a coordinate that
// does not match the arity the evaluate should throw out_of_range exception.
//
// Notice that the first coordinate is numbered 0 as usual.

class Project : public PrimRec {
public:
	Project() = delete;
	Project(const Project&) = delete;
	Project(Project&&) = delete;

	Project(unsigned int arity, unsigned int coord);
	std::string toString() const override;
	std::string name() const override;

	unsigned int evaluate(std::vector<unsigned int>) const override;

	~Project();
private:
unsigned int coord_;
};

// A base class for all the unary primitive recursive functions.
// It is a mistake to build a unary function with no operands.
// If this is attempted an invalid_argument exception should be thrown
class Unary : public PrimRec {
public:
	Unary() = delete;
	Unary(const Unary&) = delete;
	Unary(Unary&&) = delete;

	Unary(PrimRec*);
	~Unary();

	std::string toString() const override;

protected:
PrimRec* operand_;
};

// A base class for all the binary primitive recursive functions
// It is a mistake to build a binary function with less than two
// operands.
// If this is attempted an invalid_argument exception should be thrown
class Binary : public PrimRec {
public:
	Binary(unsigned int arity, PrimRec* op1,PrimRec* op2);
	~Binary();

	// All binary operators support the functions op1 and op2
	// that return pointers to their respective operands.
	PrimRec* op1() const;
	PrimRec* op2() const;

	std::string toString() const override;

private:
PrimRec* op1_;
PrimRec* op2_;
};

// A base class for all the n-ary primitive recursive functions
// Nary functions have more than two operands.
// It is a mistake to build an Nary function with two or less parameters.
// It is a mistake to build an n-ary function with operands that
// do not exist.
// If these are attempted an invalid_argument exception should be thrown.
class Nary : public PrimRec {
public:
	bool letNary(std::vector<PrimRec*> ops);

	Nary(unsigned int arity, std::vector<PrimRec*> ops);
	~Nary();


	// All n-ary operators support access to their
	// operators with array and size notation
	PrimRec* operator[](unsigned int) const;
	unsigned int size() const;

	std::string toString() const override;

protected:
std::vector<PrimRec*> ops_;

};

// The successor primitive recursive function
// The arity of the entire function is that of the operand.
// When evaluated Succ should increase the first parameter by 1.
// So Succ(x_0) should be x_0+1.
class Succ : public Unary {
public:
	Succ(PrimRec*);
	~Succ();

	std::string toString() const override;

	std::string name() const override;

	unsigned int evaluate(std::vector<unsigned int>) const override;

};

// The predecessor primitive recursive function
// The arity of the entire function is that of the operand.
// When evaluated Pred should reduce the first parameter by 1 if possible.
// So Succ(x_0) should be x_0-1 for positive x_0 and x_0 otherwise.

class Pred : public Unary {
public:
	Pred(PrimRec*);
	~Pred();

	std::string toString() const override;

	std::string name() const override;
	unsigned int evaluate(std::vector<unsigned int>) const override;

};

// The Compose primitive functions accept k+1 operands
// The first operand has arity k, the rest of the operands
// agree on their arity (say m).
// The arity of the entire function is then m.
// So given f(x_0,...,x_k)
// g_1(x_0,...,x_m)
// g_2(x_0,...,x_m)
// ...
// g_k(x_0,...,x_m)
//
// The function h=Compose(f,g_1,...,g_k) should be:
// h(x_0,...,x_m) = f(g_1(x_0,...,x_m);g_2(x_0,..,x_m); ..., g_k(x_0,...,x_m))
//
// It is a mistake to try and build a compose out of operands
// that cannot be applied (either f has arity different from k
// or one of the g-s has a different arity.
// If this occurs the build should fail and throw an
// invalid_argument exception.

class Compose : public Nary {
public:
	Compose(std::vector<PrimRec*> ops);
	~Compose();

	bool letCompose(std::vector<PrimRec*> input);
	std::string toString()const override;
	std::string name() const override;

	unsigned int evaluate(std::vector<unsigned int>) const override;


};

// The recurse primitive functions accept two operands
// The first parameter has arity n-1 and the second has arity n+1.
// The arity of the entire function is then n.
// So given f(x_0,...,x_{n-2}) and g(x_0,...,x_{n})
//clear (start from 0)
//
// the function h=Recurse(f,g) should be:
// h(x_0,...,x_{n-1}) =
//            if x_{n-1}=0: f(x_0,...,x_{n-2})
//            if x_{n-1}>0: g(x_0,...,x_{n-2},x_{n-1}-1,h(x_0,...,x_{n-2},x_{n-1}-1))
// Notice that the second calls the function h itself again as the last
// parameter sent to g.
//
// It is a mistake to try and build a recurse out of operands that
// cannot be applied (their arities cannot be built as explained above).
// If this occurs the build should fail and throw an invalid_argument
// exception.
class Recurse : public Binary {
public:
	Recurse(PrimRec* op1, PrimRec* op2);
	~Recurse();

	std::string toString() const override;
	std::string name() const override;
	unsigned int evaluate(std::vector<unsigned int>) const override;

};

#endif /* PRIMREC_H_ */


/*
 * PrimRec.h
 *
 *  Created on: Nov 27, 2015
 *      Author: np183
 *      Module: CO7104
 *      Department of Computer Science
 *      University of Leicester
 */

