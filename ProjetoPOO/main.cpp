#include "SistemaFicheiros.h"

#include <iostream>
#include <string>

using namespace std;

int main()
{
	SistemaFicheiros SF;

	SF.Load("directoria a escolha"); //inserir nome da diretoria entre as aspas.
	SF.ContarFicheiros();
	SF.ContarDirectorias();
	SF.Memoria();
	SF.DirectoriaMaisElementos();
	SF.DirectoriaMenosElementos();
	SF.FicheiroMaior();
	SF.DirectoriaMaisEspaco();
	int d = 1; // constante para Search(), se quiser pesquisar directoria.
	int f = 0; // constante para Search(), se quiser pesquisar ficheiro.
	SF.Search("directoria/ficheiro à escolha", d /*escolher tipo d ou f.*/);
	//SF.Escrever_XML();
	//SF.Ler_XML();
	cout << "	A data do ficheiro e: " << *SF.DataFicheiro("bla.txt");
	cout << "\n------------------------------------------------------------------------------------------------------------------------";
	string file = "ficheiro a escolher"; // variavel para Tree(), inserir nome do ficheiro entre as aspas.
	string* tree = &file; // variavel para Tree().
	SF.Tree();
	system("pause");

	return 0;
	

	
}
