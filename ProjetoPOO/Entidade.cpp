#include "Entidade.h"
#include <iostream>
using namespace std;



Entidade::Entidade()
{
	
}

Entidade::~Entidade()
{
}

void Entidade::SetNome(string elemento)
{
	this->nome = elemento;
}

string Entidade::GetNome()
{
	return this->nome;
}


void Entidade::SetPai(Entidade *parent)
{
	pai = parent;
}

Entidade* Entidade::GetPai() {
	return pai;
}

string Entidade::GetPath() {
	string path;
	Entidade* ent = pai;

	while (ent != NULL)
	{
		path = ent->GetNome() + "/" + path;
		ent = ent->GetPai();
	}

	path = "../" + path + nome;

	return path;
}







