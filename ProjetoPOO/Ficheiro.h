#pragma once
#ifndef FICHEIRO_H
#define FICHEIRO_H
#include <iostream>
#include <string>
#include <list>
using namespace std;

#include "Entidade.h"

class Ficheiro : public Entidade
{
	list<Entidade *> LFICH;
	string data;
public:
	Ficheiro(string nome);
	virtual ~Ficheiro();
	int GetTipo();
	int Memoria();
	string GetData() { return data; }
	virtual void GetDataFich(string &data, string ficheiro);
	void Tree(int d);
};

#endif