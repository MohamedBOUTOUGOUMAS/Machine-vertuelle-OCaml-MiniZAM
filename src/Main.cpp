//============================================================================
// Name        : ProjetCA.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <string>
#include <fstream>
#include <iostream>
#include <regex>
#include <vector>
#include "Instruction.h"
#include "Programme.h"
#include "Interpreter.h"
using namespace std;
using namespace minizam;




int main() {


	ifstream fichier("tests/unary_funs/fun2.txt", ios::in);

	//ifstream fichier("tests/rec_funs/fibo.txt", ios::in);
	//ifstream fichier("tests/rec_funs/facto.txt", ios::in);

	//ifstream fichier("tests/n-ary_funs/mytest.txt", ios::in);
	//ifstream fichier("tests/n-ary_funs/grab2.txt", ios::in);
	//ifstream fichier("tests/n-ary_funs/grab3.txt", ios::in);
	//ifstream fichier("tests/n-ary_funs/grab4.txt", ios::in);
	if(fichier)
	{
		vector<Instruction> instructions = vector<Instruction>();

		string ligne;
		while(getline(fichier, ligne))
		{
			regex e("\\t");
			regex_token_iterator<string::iterator> it(ligne.begin(), ligne.end(), e, -1);
			regex_token_iterator<string::iterator> end;
			string l = *it++;
			string instr = *it++;
			Instruction ins = Instruction(l, instr);
			instructions.push_back(ins);
		}

		Programme prog = Programme(instructions);

		Interpreter inter = Interpreter(prog);

		IValue * accumulateur = inter.evaluer();

		cout<<"Le resultat de l'evaluation est : "<<accumulateur->getValue()<<endl;

		//inter.~Interpreter();
		fichier.close();
	}
	else
		cerr << "Impossible d'ouvrir le fichier !" << endl;

	return 0;
}
