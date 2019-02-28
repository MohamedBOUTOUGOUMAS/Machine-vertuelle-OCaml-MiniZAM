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

using namespace std;
using namespace minizam;




int main() {

	ifstream fichier("tests/n-ary_funs/grab2.txt", ios::in);  // on ouvre en lecture
	if(fichier)  // si l'ouverture a fonctionné
	{
		vector<Instruction> instructions = vector<Instruction>();

		string ligne;
		while(getline(fichier, ligne))  // tant que l'on peut mettre la ligne dans "contenu"
		{
			regex e("\\t");
			regex_token_iterator<string::iterator> it(ligne.begin(), ligne.end(), e, -1);
			regex_token_iterator<string::iterator> end;
			string l = *it++;
			string instr = *it++;
			Instruction ins = Instruction(l, instr);
			instructions.push_back(ins);
		}
		fichier.close();
	}
	else
		cerr << "Impossible d'ouvrir le fichier !" << endl;

	return 0;
}
