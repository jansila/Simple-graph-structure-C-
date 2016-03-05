/*
 * TwoDMain.cpp
 *
 *  Created on: 2 Nov 2015
 *      Author: np183
 */

#include <iostream>
#include <vector>
#include "Drink.h"
#include "PrimRec.h"

typedef unsigned int uint;

using std::cin;
using std::cout;
using std::endl;
using std::vector;

typedef unsigned int uint;

void testDrink();
void testConst(vector<uint> inputArg);
void testProject(vector<uint> inputArg, unsigned int coord);
void testUnary(PrimRec*);
void testBinary(PrimRec*, PrimRec*);
void testNary(vector<PrimRec*> input);
void testSucc(PrimRec*,vector<uint> eval);
void testPred(PrimRec*,vector<uint> eval);
void testCompose(vector<PrimRec*> input, vector<uint> eval);
void testNir();

int main() {
uint t1,t2,t3;
vector<uint> input(3,1);

vector<uint> v={5,55,555};
//vector<uint> eval={0,0,0};
// cin >>t1>>t2>>t3;
// vector<uint> eval={t1,t2,t3};

vector<PrimRec*>inputVec;
PrimRec* passy = new Project(uint(2), uint(1)); //f for compose
PrimRec* passy2 = new Const(uint(3), uint(t2)); //g1 for compose
PrimRec* passy3 = new Const(uint(3), uint(t3));	//g2 for compose
inputVec.push_back(passy);
inputVec.push_back(passy2);
inputVec.push_back(passy3);


PrimRec* constant = new Const(uint(3), uint(2));



//testDrink();

//testConst(v);

cout<<"*******"<<endl;

//testProject(v, uint (2)); // v.size()=3, arity ma tedy 3

cout<<"*******"<<endl;
//testUnary(passy);
cout<<"*******"<<endl;
//testBinary(passy, passy2);
cout<<"*******"<<endl;
//testNary(inputVec);
cout<<"*******"<<endl;
//testSucc(constant, eval);
cout<<"*******"<<endl;
//testPred(constant, eval);
cout<<"*******"<<endl;
//testCompose(inputVec, eval);
cout<<"*******"<<endl;
testNir();
cout<<"*******"<<endl;


return 0;}

void testConst(vector<uint> inputArg){
Const testConst(3,555);
cout<<"testConst.toString: "<<testConst.toString()<<endl;
cout<<"arity (not important): "<<testConst.arity()<<endl;
cout<<"operator <<: "<<testConst<<endl;
cout<<"evaluate: "<<testConst.evaluate(inputArg)<<endl;
cout<<"name: "<<testConst.name()<<endl;

}

void testProject(vector<uint> inputArg, uint coord){
Project testProject(inputArg.size(),coord);
cout<<"testProject\n.toString: "<<testProject.toString()<<endl;
cout<<"arity: "<<testProject.arity()<<endl;
cout<<"operator <<: "<<testProject<<endl;
cout<<"evaluate: "<<testProject.evaluate(inputArg)<<endl;
cout<<"name: "<<testProject.name()<<endl;

}

void testUnary(PrimRec * input){
Unary testUnary(input);
cout<<"arity: "<<testUnary.arity()<<endl;
cout<<"name: "<<testUnary.name()<<endl;}


void testBinary(PrimRec* input1, PrimRec * input2){
Binary testBinary(uint(5), input1,input2);
cout<<"arity: "<<testBinary.arity()<<endl;
cout<<"name: "<<testBinary.name()<<endl;
cout<<"test op1: "<<testBinary.op1()<<endl;
cout<<"test op2: "<<testBinary.op2()<<endl;

}

void testNary(vector<PrimRec*> input){
	Nary testNary(uint(5), input);
	cout<<"test []: "<<testNary[0]<<endl;
	cout<<"test size(): "<<testNary.size()<<endl;
}

void testSucc(PrimRec* input, vector<uint> eval){
	Succ testSucc(input);
	cout<<"test name: "<<testSucc.name()<<endl;
	cout<<"test toString: "<<testSucc.toString()<<endl;
	cout<<"test <<: "<<testSucc<<endl;
	cout<<"test evaluate: "<<testSucc.evaluate(eval)<<endl;
}



void testPred(PrimRec* input, vector<uint> eval){
	cout<<"*** test Predecessor ***"<<endl;
	Pred testSucc(input);
	cout<<"test name: "<<testSucc.name()<<endl;
	cout<<"test toString: "<<testSucc.toString()<<endl;
	cout<<"test <<: "<<testSucc<<endl;
	cout<<"test evaluate: "<<testSucc.evaluate(eval)<<endl;
}

void testCompose(vector<PrimRec*> input, vector<uint> eval){
Compose testCompose(input);

cout<<testCompose.evaluate(eval)<<endl;
cout<<testCompose;
}

void testNir(){
	uint t1,t2;
		//	cin >> t1;
	//		PrimRec* one = new Succ(new Const(0,t1));
	//		cout << *one << " = " << one->evaluate(vector<uint>{}) << endl;

			cin >> t1 >> t2;
			PrimRec* add = new Recurse(new Project(1,0), new Succ(new Project(3,2)));
			cout << *add << " = " << add->evaluate(vector<uint>{t1,t2}) << endl;

			PrimRec* add02 = new Recurse(new Project(2,0), new Succ(new Project(4,3)));

			// cout << *add02 << "  = " << add02->evaluate(vector<uint>{3,4,5}) << endl;

			PrimRec* mult = new Recurse(new Const(1,0), add02);
			cout << *mult << " = " << mult->evaluate(vector<uint>{t1,t2}) << endl;

			PrimRec* add03_ = new Recurse(new Project(3,0), new Succ(new Project(5,4)));
			PrimRec* mult02 = new Recurse(new Const(2,0), add03_);
			PrimRec* pow = new Recurse(new Const(1,1), mult02);

			cout << *pow << " = " << pow->evaluate(vector<uint>{t1,t2}) << endl;

			PrimRec* comp = new Compose(vector<PrimRec*>{add,
														new Succ(new Project(2,0)),
														new Succ(new Project(2,1))});
			cout<<*comp<<" = " <<comp->evaluate(vector<uint>{3,4})<<endl;

		//	delete one;
			delete add;
			delete mult;
			delete pow;

}


/*
 *
 *
 * */
void testDrink(){
			Drink* d[2];
			d[0] = new Coffee(1.0,1.0);
			d[1] = new Tea(1.0,"Herbal");

cout<<d[0]->name()<<" volume: "<<d[0]->volume()<<endl;
d[0]->addWater(1);
cout<<"Volume after adding 1 unit of water: "<<d[0]->volume()<<endl;

Tea testTea(-41,"Pu-erh");
Coffee test(-5,-1);

cout<<test.name()<<" volume: "<<test.volume()<< " the concentration is: "<<test.concentration()<<endl;
test.addWater(1);
cout<<"Concentration after adding 0 unit of water: "<<test.concentration()<<endl;
cout<<d[0]->toString()<<endl;
cout<<d[1]->toString()<<endl;
cout<<"****************"<<endl;
cout<<test<<endl;;
cout<<"****************"<<endl;
cout<<testTea<<endl;;
cout<<"*****Original main*****"<<endl;
cout << *(d[0]) << endl;
cout << *(d[1]) << endl;
	}

