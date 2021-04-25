#include "SistemaFicheiros.h"



SistemaFicheiros::SistemaFicheiros()
{
	//cout << "Construindo Sistema de Ficheiros..." << endl;
}


SistemaFicheiros::~SistemaFicheiros()
{
	//cout << "Destruindo Sistema de Ficheiros..." << endl;
}

bool SistemaFicheiros::Load(const string &path) {

	cout << "------------------------------------------------------------------------------------------------------------------------";
	cout << "	Alinea 1 - Load().\n";
	cout << "------------------------------------------------------------------------------------------------------------------------";
	DIR *dir;
	struct dirent *ent;
	dir = opendir(path.c_str());
	if ( dir !=NULL)
	{
		while ((ent = readdir(dir)) != NULL)
		{
			if ((strcmp(ent->d_name, "..") != 0) && (strcmp(ent->d_name, ".")) != 0)
			{	
				if (ent->d_type == DT_DIR)
				{
					Directoria *pasta = new Directoria((*ent).d_name);
					//cout << "Nome:" << path + "/" + ent->d_name << endl;
					LISTA.push_back(pasta);
					pasta->Load(path + "/" + ent->d_name);
				}
			
				else
				{
					Ficheiro *ficheiro = new Ficheiro((*ent).d_name);
					//cout << "Nome:" << path + "/" + ent->d_name << endl;
					LISTA.push_back(ficheiro);
				}	
			}
		}
	}

	closedir(dir);
	return true;
}

int SistemaFicheiros::ContarFicheiros() { 
	
	int n = 0;
	for (list<Entidade *>::iterator it = LISTA.begin(); it != LISTA.end(); ++it) {

		if ((*it)->GetTipo() == 1)
		{
			Directoria* dir = (Directoria*)(*it);
			n += dir->ContarFicheiros();
		}
		else
		{
			n++;
		}
	}

	cout << "------------------------------------------------------------------------------------------------------------------------";
	cout << "	Alinea 2 - ContarFicheiros().\n" << endl;
	cout << "	Existem " << n << " ficheiros na diretoria analisada.\n";
	cout << "------------------------------------------------------------------------------------------------------------------------";
	return n;
}

int SistemaFicheiros::ContarDirectorias() {

	int d = 0;
	for (list<Entidade *>::iterator it = LISTA.begin(); it != LISTA.end(); ++it) {
		
		if ((*it)->GetTipo() == 1)
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
	
	cout << "------------------------------------------------------------------------------------------------------------------------";
	cout << "	Alinea 3 - ContarDirectorias().\n" << endl;
	cout << "	Existem " << d << " diretorias na diretoria analisada.\n";
	cout << "------------------------------------------------------------------------------------------------------------------------";
	return d; 
}

int SistemaFicheiros::Memoria() {
	int m = sizeof(*this);

	for (list<Entidade *>::iterator it = LISTA.begin(); it != LISTA.end(); ++it) {
		m += (*it)->Memoria();
		Directoria* dir = (Directoria*)(*it);
		list<Entidade *> lista = dir->GetEntidades();

		for (list<Entidade *>::iterator itt = lista.begin(); itt != lista.end(); ++itt) {
			m += (*it)->Memoria();
		}
	}

	cout << "------------------------------------------------------------------------------------------------------------------------";
	cout << "	Alinea 4 - Memoria().\n" << endl;
	cout << "	O projeto ocupa " << m << " bytes.\n";
	cout << "------------------------------------------------------------------------------------------------------------------------";
	return m;
}

string* SistemaFicheiros::DirectoriaMaisElementos() {
	
	Directoria* maior = NULL;

	for (list<Entidade *>::iterator it = LISTA.begin(); it != LISTA.end(); ++it) {
		
		if ((*it)->GetTipo() == DIRE) {
			if (maior == NULL) {
				maior = (Directoria*)(*it);
			}

			Directoria* dir = (Directoria*)(*it);
			Directoria* subdir = dir->DirectoriaMaisElementos();

			if (subdir != NULL) {
				maior = maior->Tamanho() >= subdir->Tamanho() ? maior : subdir;
			}
		}
	}

	cout << "------------------------------------------------------------------------------------------------------------------------";
	cout << "	Alinea 5 - DirectoriaMaisElementos().\n" << endl;
	cout << "	A diretoria com mais elementos e: " << maior->GetPath() << ".\n";
	cout << "------------------------------------------------------------------------------------------------------------------------";
	return &maior->GetNome();
}


string * SistemaFicheiros::DirectoriaMenosElementos() {
	
	Directoria* menor = NULL;

	for (list<Entidade *>::iterator it = LISTA.begin(); it != LISTA.end(); ++it) {

		if ((*it)->GetTipo() == DIRE) {
			if (menor == NULL) {
				menor = (Directoria*)(*it);
			}

			Directoria* dir = (Directoria*)(*it);
			Directoria* subdir = dir->DirectoriaMenosElementos();

			if (subdir != NULL) {
				menor = menor->Tamanho() <= subdir->Tamanho() ? menor : subdir;
			}
		}
	}

	cout << "------------------------------------------------------------------------------------------------------------------------";
	cout << "	Alinea 6 - DirectoriaMenosElementos().\n" << endl;
	cout << "	A diretoria com menos elementos e: " << menor->GetPath() << ".\n";
	cout << "------------------------------------------------------------------------------------------------------------------------";
	return &menor->GetNome();
}

string * SistemaFicheiros::FicheiroMaior() { 
	Ficheiro* maior = NULL;

	for (list<Entidade *>::iterator it = LISTA.begin(); it != LISTA.end(); ++it) {
		
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

	cout << "------------------------------------------------------------------------------------------------------------------------";
	cout << "	Alinea 7 - FicheiroMaior().\n" << endl;
	cout << "	O ficheiro que ocupa mais espaco e: " << maior->GetPath() << ".\n";
	cout << "------------------------------------------------------------------------------------------------------------------------";
	return &maior->GetNome();
}


string * SistemaFicheiros::DirectoriaMaisEspaco() {
	Directoria* maior = NULL;

	for (list<Entidade *>::iterator it = LISTA.begin(); it != LISTA.end(); ++it) {

		if ((*it)->GetTipo() == DIRE) {
			if (maior == NULL) {
				maior = (Directoria*)(*it);
			}
			continue;
		}

		Directoria* dir = (Directoria*)(*it);
		Directoria* subdir = dir->DirectoriaMaisElementos();

		if (subdir != NULL) {
			maior = maior->Tamanho() >= subdir->Tamanho() ? maior : subdir;
		}
	}

	cout << "------------------------------------------------------------------------------------------------------------------------";
	cout << "	Alinea 8 - DirectoriaMaisEspaco().\n" << endl;
	cout << "	A diretoria que ocupa mais espaco e: " << maior->GetPath() << ".\n";
	cout << "------------------------------------------------------------------------------------------------------------------------";
	return &maior->GetNome();
}

string * SistemaFicheiros::Search(const string &s, int &Tipo) { //optimizar

	cout << "------------------------------------------------------------------------------------------------------------------------";
	cout << "	Alinea 9 - Search().\n" << endl;
	Entidade* found = NULL;
	
	for (list<Entidade *>::iterator it = LISTA.begin(); it != LISTA.end(); ++it) {
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
			else { continue; }
		}

		if (found != NULL) {
			cout << "	O caminho para o ficheiro/diretoria e: " << found->GetPath() << ".\n";
			break;
		}
		else {
			cout << "Nao encontrado!" << endl;
		}
	}
	cout << "------------------------------------------------------------------------------------------------------------------------";

	string* str = &found->GetNome();
	return found != NULL ? str: NULL;
}

bool SistemaFicheiros::RemoverAll(const string &s, const string &tipo) {
	
	return true;
}

void SistemaFicheiros::Escrever_XML(const string &s) {

}

bool SistemaFicheiros::Ler_XML(const string &s) {
	return false;
}

bool SistemaFicheiros::MoverFicheiro(const string &Fich, const string &DirNova) {
	return false;
}

bool SistemaFicheiros::MoverDirectoria(const string &DirOld, const string &DirNew) {
	return false;
}

string * SistemaFicheiros::DataFicheiro(const string &ficheiro) {

	cout << "------------------------------------------------------------------------------------------------------------------------";
	cout << "	Alinea 15 - DataFicheiro().\n" << endl;

	Entidade* found = NULL;
	string data = "";

	for (list<Entidade *>::iterator it = LISTA.begin(); it != LISTA.end(); ++it) {
		string nome = (*it)->GetNome();

			if ((*it)->GetTipo() == FICHE) {
				if (nome.compare(ficheiro) == 0) {
					found = (*it);
					found->GetDataFich(data, ficheiro);
				}
				else {
					continue;
				}
				if ((nome.compare(ficheiro) == 0) && ((*it)->GetTipo() == DIRE)) {
					continue;
				}
			}
			else
			{
				((Directoria*)(*it))->GetDataFich(data, ficheiro);
			}
		}
	return new string(data);
}

void SistemaFicheiros::Tree(const string *fich) {
	cout << "------------------------------------------------------------------------------------------------------------------------";
	cout << "	Alinea 16 - Tree().\n" << endl;

	Entidade* found = NULL;
	int d = 0;

		for (list<Entidade *>::iterator it = LISTA.begin(); it != LISTA.end(); ++it) {
			string nome = (*it)->GetNome();

			if (fich == NULL) {
				((Directoria*)(*it))->Tree(d);
			}
			else{
			if ((*it)->GetTipo() == FICHE) {
				if (nome.compare(fich->c_str()) == 0) {
					found = (*it);
				}
				else {
					continue;
				}
			}
			else
			{
				((Directoria*)(*it))->Tree(d);
			}
		}	
	}
	cout << "------------------------------------------------------------------------------------------------------------------------";
}

void SistemaFicheiros::PesquisarAllDirectoria(list<string> &lres, const string &dir) {

}

void SistemaFicheiros::PesquisarAllFicheiros(list<string> &lres, const string &file) {

}

void SistemaFicheiros::RenomearFicheiros(const string &fich_old, const string &fich_new) {

}

bool SistemaFicheiros::FicheiroDuplicados() {
	return false;
}

bool SistemaFicheiros::CopyBatch(const string &padrao, const string &DirOrigem, const string &DirDestino) {
	return false;
}

