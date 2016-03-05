/*
 * PrimRec.cpp
 *
 *  Created on: Nov 27, 2015
 *      Author: np183
 *      Module: CO7104
 *      Department of Computer Science
 *      University of Leicester
 */


/*
 * Can I declare my own PrimRec::PrimRec(uint arity, std::string name) ?
 * Project - what is its evaluation output? the i-th coordinate -ith input
 *
 *
 * look at recursive definitions of add and multiply
 */


#include <iostream>
#include <stdexcept>
#include "PrimRec.h"

using std::string;
using std::ostream;
using std::vector;
using std::exception;

using namespace std;

typedef unsigned int uint;

PrimRec::PrimRec(uint arity)
{
	arity_=arity;
}


PrimRec::PrimRec(uint arity, std::string name)
{

arity_=arity;
name_=name;
}

PrimRec:: ~PrimRec()
{
arity_=0;
}

uint PrimRec::arity() const
{
return arity_;
}

// 		VIRTUAL MEMBERS

unsigned int PrimRec::evaluate(vector<uint> param) const
{
//Virtual
  return 0;
}

string PrimRec::toString() const {
	//Virtual
  return "";
}

std::string PrimRec::name() const {
  //Virtual
	return name_;
}
// 		END VIRTUAL MEMBERS


void PrimRec::printOut(std::ostream & o) const{
	o<< this->toString();
}

std::ostream& operator<< (std::ostream& o, const PrimRec& p)
{
	p.printOut(o);

return o;}



// **** CONST **** //
//*****************//
// **** CONST **** //
//*****************//
// **** CONST **** //


Const::Const(unsigned int arity, unsigned int value)
  : PrimRec(arity,"Const"),value_(value)
{
}

std::string Const::toString() const {
return std::to_string(value_);

}

std::string Const::name() const {

  return std::to_string(value_);
}

unsigned int Const::evaluate(std::vector<unsigned int> param) const
{
if(param.size()!=this->arity()){throw std::domain_error("Input arity does not match!");}

	return value_;
}

Const::~Const()
{
}

// **** PROJECT **** //

// **** PROJECT **** //

// **** PROJECT **** //

Project::Project(unsigned int arity, unsigned int coord)
  : PrimRec(arity,"Project"), coord_(coord)
{
}

Project::~Project()
{
}

std::string Project::toString() const
{
	// A Project whose projecting on the i'th coordinate and whose arity
	// is 3 will print: P_i(x_0,x_1,x_2)

string str=name()+"(";
	for(uint i=0; i<arity(); i++)
	{
	str.append("x_");
	str.append(std::to_string(i));
	if(i<arity()-1){str.append(",");}
	}
	str.append(")");
return str;
}

std::string Project::name() const {
string str="P_"+std::to_string(coord_);
	return str;
}

unsigned int Project::evaluate(std::vector<unsigned int> param) const
{

	uint arCheck=this->arity();

	if(arCheck==param.size())
		{throw std::domain_error("Input arity does not match!");}

	if(coord_>=param.size()){throw std::out_of_range("The coordinate is out of range");}

	return param[coord_];


}

// **** UNARY **** //
// **** UNARY **** //
// **** UNARY **** //


Unary::Unary(PrimRec* op)
:PrimRec( op!=nullptr ? op->arity() : throw std::invalid_argument("Cannot have a Unary with no operands."),"Unary")
{

operand_=std::move(op);

}

Unary::~Unary()
{
delete operand_;
operand_=nullptr;

}

std::string Unary::toString() const {
	string mid=operand_->toString();
	return "("+mid+")";
}

// **** BINARY **** //

// **** BINARY **** //

// **** BINARY **** //


Binary::Binary(uint arity, PrimRec* op1, PrimRec* op2)
  : PrimRec(op1!=nullptr && op2!=nullptr ? arity : throw std::invalid_argument("Cannot have a Binary without at least 2 operands."),"Binary")
{
	op1_=std::move(op1);
	op2_=std::move(op2);

}

Binary::~Binary()
{

delete op1_;
delete op2_;
op1_=op2_=nullptr;
}

std::string Binary::toString() const {
	string temp;
	temp="("+op1_->toString()+","+op2_->toString()+")";

	return temp;
}

PrimRec* Binary::op1() const {
  return op1_;
}

PrimRec* Binary::op2() const {
  return op2_;
}

// **** NARY **** //
// **** NARY **** //
// **** NARY **** //


bool Nary::letNary(vector<PrimRec*> ops){
	if(ops.size()<3){return false;} // check size is ok

	for(auto iter=ops.begin(); iter!=ops.end(); ++iter){
		 if(*iter==nullptr){return false;} //check if any pointer is null
	}

			return true; //gives true if neither before is met
}

Nary::Nary(uint arity, vector<PrimRec*> ops)
  : PrimRec( Nary::letNary(ops) ? arity : throw std::invalid_argument("Cannot build this Nary"),"Nary")
{
ops_=std::move(ops);

}

Nary::~Nary()
{

	for(auto iter=ops_.begin(); iter!=ops_.end(); ++iter){
		delete *iter;
		}
	ops_.clear();
}

PrimRec* Nary::operator[](uint i) const {
  return ops_[i];
}

unsigned int Nary::size() const {
  return ops_.size();;
}

std::string Nary::toString() const{
string temp;
	temp=this->name()+"(";
	for(auto iter=ops_.begin(); iter!=ops_.end()-1; ++iter){
		temp+=(*iter)->toString()+",";
	}
	temp+=ops_.back()->toString()+")";
return temp;
}

// **** SUCC **** //
// **** SUCC **** //

// **** SUCC **** //


Succ::Succ(PrimRec* op)
  : Unary(op)
{
//Succ inhereted from Unary
}

Succ::~Succ()
{
}


std::string Succ::toString() const{
	string temp=this->name()+Unary::toString();//here
	return temp;
}


std::string Succ::name() const{

return "Succ";

}

unsigned int Succ::evaluate(std::vector<uint> input) const {
uint opArity=operand_->arity();
	if(opArity!=input.size())
		{
		throw std::domain_error("Arity does not match the input size"); //check if arity matches
		}
	else{
		return operand_->evaluate(input)+1;
	}
}

// **** PRED **** //
// **** PRED **** //

// **** PRED **** //



Pred::Pred(PrimRec* op)
  : Unary(op)
{
// Unary inheritence
	}

Pred::~Pred()
{
//Unray inheritence
}

std::string Pred::toString() const{
	string temp=this->name()+Unary::toString();//here
	return temp;
}

std::string Pred::name() const {
	return "Pred";
}

unsigned int Pred::evaluate(std::vector<uint> input) const {
uint opArity=operand_->arity();
	if(opArity!=input.size())
		{
		throw std::domain_error("Arity does not match the input size"); //check if arity matches

		}
	else{
		return operand_->evaluate(input)-1;
	}
}

// **** COMPOSE **** //

// **** COMPOSE **** //
// **** COMPOSE **** //

bool Compose::letCompose(vector<PrimRec*> input){

unsigned int k=input[0]->arity();
if(input.size()-1!=k){return false;} // see if there's k gs -> g_1...g_k

unsigned int m=input[1]->arity(); //whats m?

	for(auto iter=input.begin()+1; iter!=input.end(); ++iter){
			if(m!=(*iter)->arity()){
				return false;	// if some g is not or arity m, return false
			}
	}
	return true;

}

Compose::Compose(vector<PrimRec*> ops)
  : Nary(letCompose(ops) ? ops[2]->arity() : throw::invalid_argument("Arities dont match"),ops)
{
//child of Nary
}

Compose::~Compose()
{
//inherited from Nary
}



unsigned int Compose::evaluate(std::vector<unsigned int> input)const {

	vector<uint> g1gk;

	for(int i=1; i<ops_.size(); i++){
		g1gk.push_back(ops_[i]->evaluate(input));
	}

	return ops_[0]->evaluate(g1gk);
}

std::string Compose::toString() const{
	string temp=Nary::toString();
	return temp;
}

std::string Compose::name() const {
	return "Compose";
}


// **** RECURSE **** //
// **** RECURSE **** //
// **** RECURSE **** //
// **** RECURSE **** //



Recurse::Recurse(PrimRec* op1, PrimRec* op2)
  : Binary(op1->arity()+1,op1,op2)
{
	if(op1->arity()+1!=op2->arity()-1)
	{throw std::invalid_argument("The arities in Recurse dont match");} //dont build if condition is not met

}

Recurse::~Recurse()
{
//sorted in ~Binary
}


//operands: x_0,...,x_{n-1} and they go into h, that calls f or g (its got h inside)
unsigned int Recurse::evaluate(std::vector<unsigned int> operands) const{
if(operands.size()!=this->arity()){throw std::domain_error("Arity of operands doesnt match the arity of Recurse");}

	if(operands.back()==0){
		operands.pop_back(); // if the last operand is zero, delete it

		return this->op1()->evaluate(operands);

	}else{
		operands[operands.size()-1]-=1;
		operands.push_back(this->evaluate(operands)); //use this function to add another element

		return this->op2()->evaluate(operands);
	}

}

std::string Recurse::toString() const {
	string temp=this->name()+Binary::toString();
	return temp;
}

std::string Recurse::name() const { return "Recurse";}


