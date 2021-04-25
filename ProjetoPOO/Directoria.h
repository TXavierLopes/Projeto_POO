#pragma once
#ifndef DIRETORIA_H
#define DIRETORIA_H
#include <iostream>
#include <string>
#include <list>
#include <time.h>
#include <sys/stat.h>
#include <fstream>
#include "Entidade.h"
#include "Ficheiro.h"
using namespace std;


class Directoria : public Entidade 
{
	list<Entidade *> LENTI;
	string data;
public:
	Directoria(string nome);
	virtual~Directoria();
	int GetTipo();
	void Load(const string &path);
	int Memoria();
	list<Entidade *> GetEntidades();
	int Tamanho();
	int ContarFicheiros();
	int ContarDirectorias();
	Directoria* DirectoriaMaisElementos();
	Directoria* DirectoriaMenosElementos();
	Ficheiro* FicheiroMaior();
	Directoria * DirectoriaMaisEspaço();
	Entidade * Search(const string & s, int & Tipo);
	virtual void GetDataFich(string &data, string ficheiro);
	void Tree(int d);
};

#endif