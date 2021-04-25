#include "Directoria.h"
#include <iostream>
#include <dirent.h>
#include "Ficheiro.h"
using namespace std;



Directoria::Directoria(string nome)
{
	this->SetNome(nome);
}


Directoria::~Directoria()
{
	LENTI.clear();
	delete(&LENTI);
}

void Directoria::Load(const string &path) {
	DIR *dir;
	struct dirent *ent;
	dir = opendir(path.c_str());
	if (dir != NULL)
	{
		while ((ent = readdir(dir)) != NULL)
		{
			if ((strcmp(ent->d_name, "..") != 0) && (strcmp(ent->d_name, ".")) != 0)
			{
				if (ent->d_type == DT_DIR)
				{
					Directoria *pasta = new Directoria((*ent).d_name);
					pasta->SetPai(this);
					//cout << "Nome:" << path + "/" + ent->d_name << endl;
					LENTI.push_back(pasta);
					pasta->Load(path + "/" + ent->d_name);
				}

				else
				{
					Ficheiro *ficheiro = new Ficheiro((*ent).d_name);
					ficheiro->SetPai(this);
					//cout << "Nome:" << path + "/" + ent->d_name << endl;
					LENTI.push_back(ficheiro);
				}


			}
		}
		closedir(dir);
	}
}

int Directoria::GetTipo()
{
	return DIRE;
}

int Directoria::Memoria()
{
	int m = sizeof(*this) + this->GetNome().size() * sizeof(char) + sizeof(list<Entidade *>);
	for (list<Entidade *>::iterator it = this->LENTI.begin(); it != this->LENTI.end(); ++it) {
		m += (*it)->Memoria();
	}

	return m;
}

list<Entidade*> Directoria::GetEntidades()
{
	return this->LENTI;
}

int Directoria::Tamanho()
{
	return this->LENTI.size();
}

int Directoria::ContarFicheiros() {
	
	int n = 0;
	for (list<Entidade *>::iterator it = LENTI.begin(); it != LENTI.end(); ++it) {

		if ((*it)->GetTipo() == DIRE)
		{
			Directoria* dir = (Directoria*)(*it);
			n += dir->ContarFicheiros();
		}
		else
		{
			n++;
		}
	}
	return n;
}

int Directoria::ContarDirectorias() {

	int d = 0;
	for (list<Entidade *>::iterator it = LENTI.begin(); it != LENTI.end(); ++it) {

		if ((*it)->GetTipo() == DIRE)
		{
			d++;
			Directoria* dir = (Directoria*)(*it);
			d += dir->ContarDirectorias();
		}
		else
		{
			continue;
		}
	}
	return d;
}

Directoria* Directoria::DirectoriaMaisElementos() {

	Directoria* maior = NULL;

	for (list<Entidade *>::iterator it = LENTI.begin(); it != LENTI.end(); ++it) {
	
		if ((*it)->GetTipo() == DIRE) {
			if (maior == NULL) {
				maior = (Directoria*)(*it);
			}

			Directoria* dir = (Directoria*)(*it);
			Directoria* subdir = dir->DirectoriaMaisElementos();
			if (subdir != NULL)
			{
				maior = maior->Tamanho() >= subdir->Tamanho() ? maior : subdir;
			}
		}
	}
	return maior;
}

Directoria* Directoria::DirectoriaMenosElementos() {

	Directoria* menor = NULL;

	for (list<Entidade *>::iterator it = LENTI.begin(); it != LENTI.end(); ++it) {

		if ((*it)->GetTipo() == DIRE) {
			if (menor == NULL) {
				menor = (Directoria*)(*it);
			}

			Directoria* dir = (Directoria*)(*it);
			Directoria* subdir = dir->DirectoriaMenosElementos();
			if (subdir != NULL)
			{
				menor = menor->Tamanho() <= subdir->Tamanho() ? menor : subdir;
			}
		}
	}
	return menor;
}


Ficheiro* Directoria::FicheiroMaior() {
	
	Ficheiro* maior = NULL;
	Ficheiro* sub = NULL;

	for (list<Entidade *>::iterator it = LENTI.begin(); it != LENTI.end(); ++it) {

		if (maior == NULL) {
			if ((*it)->GetTipo() == FICHE) {
				maior = (Ficheiro*)(*it);
			}
			else
			{
				Directoria* dir = (Directoria*)(*it);
				maior = dir->FicheiroMaior();
			}
			continue;
		}

		if ((*it)->GetTipo() == DIRE) {
			Directoria* dir = (Directoria*)(*it);
			Ficheiro* sub = dir->FicheiroMaior();
			maior = maior->Memoria() >= sub->Memoria() ? maior : sub;
		}
		else
		{
			Ficheiro* fich = (Ficheiro*)(*it);
			maior = maior->Memoria() >= fich->Memoria() ? maior : fich;
		}
	}
	return maior;
}

Directoria* Directoria::DirectoriaMaisEspaço() {

	Directoria* maior = NULL;

	for (list<Entidade *>::iterator it = LENTI.begin(); it != LENTI.end(); ++it) {

			if ((*it)->GetTipo() == DIRE) {
				if (maior == NULL) {
					maior = (Directoria*)(*it);
				}

				Directoria* dir = (Directoria*)(*it);
				Directoria* subdir = dir->DirectoriaMenosElementos();
				if (subdir != NULL)
				{
					maior = maior->Memoria() <= subdir->Memoria() ? maior : subdir;
				}
			}
	}

	return maior;
}

Entidade* Directoria::Search(const string &s, int &Tipo) {
	
	Entidade* found = NULL;

	for (list<Entidade *>::iterator it = LENTI.begin(); it != LENTI.end(); ++it) {
		string nome = (*it)->GetNome();

		if (Tipo == 0) {
			if ((*it)->GetTipo() == FICHE) {
				if (nome.compare(s) == 0) {
					found = (*it);
				}
				else {
					continue;
				}
				if ((nome.compare(s) == 0) && ((*it)->GetTipo() == DIRE)) {
					continue;
				}
			}
			else
			{
				found = ((Directoria*)(*it))->Search(s, Tipo);
			}
		}
		else {
			if ((*it)->GetTipo() == DIRE) {
				if (nome.compare(s) == 0) {
					found = (*it);
				}
				else {
					found = ((Directoria*)(*it))->Search(s, Tipo);
				}
				if ((nome.compare(s) == 0) && ((*it)->GetTipo() == FICHE)) {
					continue;
				}
			}
		}

		if (found != NULL)
		{
			break;
		}
	}
	return found;
}

void Directoria::GetDataFich(string & data, string ficheiro)
{
	for (list<Entidade *>::iterator it = LENTI.begin(); it != LENTI.end(); ++it) {
		(*it)->GetDataFich(data, ficheiro);
	}
}

void Directoria::Tree(int d) {

	for (int i = 0; i <= d; i++)
		cout << "----";
	d++;
	cout << this->GetNome() << endl;
	for (list<Entidade *>::iterator it = LENTI.begin(); it != LENTI.end(); it++)
		(*it)->Tree(d);

}
