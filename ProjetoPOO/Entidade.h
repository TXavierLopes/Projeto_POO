#pragma once
#ifndef ENTIDADE_H
#define ENTIDADE_H
#include <iostream>
#include <string>
#include <list>
#include <string>
#include <vector>
#include <list>
#include <sstream>
using namespace std;

const int DIRE = 1;
const int FICHE = 0;

class SistemaFicheiros;

class Entidade
{
	string nome;
	Entidade* pai;
protected:
	int tipo;

public:
	Entidade();
	virtual ~Entidade();
	void SetNome(string elemento);
	string GetNome();
	void SetPai(Entidade * parent);
	Entidade * GetPai();
	string GetPath();
	virtual int Memoria() = 0;
	virtual int GetTipo() = 0;
	virtual void GetDataFich(string &data, string ficheiro) = 0;
	virtual void Tree(int d) = 0;
};

#endif 