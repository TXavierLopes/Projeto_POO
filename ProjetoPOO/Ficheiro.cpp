#include "Ficheiro.h"
#include <iostream>
#include <string>
using namespace std;



Ficheiro::Ficheiro(string nome)
{
	//cout << "Contruindo Ficheiro..." << endl;
	this->SetNome(nome);
}


Ficheiro::~Ficheiro()
{
	//cout << "Destruindo Ficheiro..." << endl;

}

int Ficheiro::GetTipo()
{
	return FICHE;
}

int Ficheiro::Memoria()
{
	int m = sizeof(*this) + this->GetNome().size() * sizeof(char);
	return m;
}

void Ficheiro::GetDataFich(string &data, string ficheiro) {


	if (this->GetNome() == ficheiro) {
		data = this->GetData();
	}
}

void Ficheiro::Tree(int d)
{
	d++;
	for (int i = 0; i <= d; i++)
		cout << "-";
	cout << this->GetNome() << endl;
}