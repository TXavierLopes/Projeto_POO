#ifndef SISTEMAFICHEIROS_H
#define SISTEMAFICHEIROS_H

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <sstream>
using namespace std;

#include "Entidade.h"
#include "Directoria.h"
#include "Ficheiro.h"

class SistemaFicheiros

{	
	list<Entidade *> LISTA;


    private:
        // Aqui podem colocar todos os metodos que acharem necessarios para implementar os metodos pedidos!
        // Declarar os Objectos ou conjuntos de objectos necess�rios a resolu��o do problema
    public:
			SistemaFicheiros();                                        // OK
			virtual ~SistemaFicheiros();                               // OK
            //Questao 1: Correr o programa numa dada diretoria e esta (e seus conte�dos)
            // serem carregados para mem�ria (SistemaFicheiros);
            // O m�todo deve devolver true se a opera��o foi bem sucedida.
			bool Load(const string &path);
            //Questao 2: Contar o n�mero de ficheiros que o Sistema de Ficheiros tem guardado em mem�ria;
			int ContarFicheiros();
            //Questao 3: Contar o n�mero de directorias que o Sistema de Ficheiros tem guardado em mem�ria;
			int ContarDirectorias();
            //Questao 4: Determinar toda a mem�ria ocupada;
			int Memoria();
            //Questao 5: Determinar qual a diretoria que tem mais informa��o (maior n�mero de pastas e ficheiros);
            // Se existir mais do que uma, deve devolver uma delas!
            // (N�o deve ser considerado o conte�do das sub-directorias);
			string *DirectoriaMaisElementos();
            //Questao 6: Determinar qual a diretoria que tem menos informa��o (menor n�mero de pastas e ficheiros);
            // Se existir mais do que uma, deve devolver uma delas!
			string *DirectoriaMenosElementos();
            //Questao 7: Determinar o ficheiro que ocupa mais espa�o, bem como o respetivo caminho;
			string *FicheiroMaior();
            //Questao 8: Determinar qual diretoria que est� a ocupar mais espa�o;
			string *DirectoriaMaisEspaco();
            //Questao 9: Pesquisar se existe um dado ficheiro ou diretoria, devolvendo o �caminho� completo at� ele(a);
            // Considere que se Tipo = 0 se pretende pesquisar um ficheiro e se Tipo = 1
            // se pretende uma directoria.
			string *Search(const string &s, int &Tipo);
            //Questao 10: Remover todas as diretorias ou ficheiros; Se tipo = "DIR" remove directorias, sen�o remove ficheiros;
            // Deve devolver true se a opera��o foi bem sucedida.
			bool RemoverAll(const string &s, const string &tipo);
            //Questao 11: Gravar para ficheiro em formato XML todo o Sistema de Ficheiros;
			void Escrever_XML(const string &s);
            //Questao 12: Ler de um ficheiro em formato XML todo o Sistema de Ficheiros (antes de ler deve ser apagado tudo o que estiver no Sistema de Ficheiros);
            // Se leu corretamente devolve true, sen�o devolve false.
			bool Ler_XML(const string &s);
            //Questao 13: 13.	Mover um Ficheiro para outra diretoria; se existir mais do que um ficheiro,
            //move o primeiro encontrado; Se o ficheiro j� estiver em DirNova, n�o deve fazer nada.
            // Se conseguir mover deve devolver true (false caso contr�rio);
			bool MoverFicheiro(const string &Fich, const string &DirNova);
            //Questao 14: Mover uma diretoria (e tudo o que lhe est� associado!) para outra diretoria; se existir mais do que uma directoria, move a primeira encontrada.
            //Assume-se que DirNew n�o � sub-directoria de DirOld. No caso de DirNew ser sub-directoria de DirOld,
            //deve devolver false e n�o efetuar qualquer opera��o.
			bool MoverDirectoria(const string &DirOld, const string &DirNew);
            //Questao 15: Determinar a data de um dado ficheiro; se o ficheiro n�o existir deve devolver NULL; se existirem v�rios, deve devolver a data do primeiro ficheiro;
            // (Exemplo de devolu��o de uma data �2017|10|5�);
			string *DataFicheiro(const string &ficheiro);
            //Questao 16: � semelhan�a do comando do MS-DOS, implemente o m�todo Tree;
            // Deve considerar que a listagem deve sair na consola e num ficheiro.
            // Se o m�todo for chamado com um ficheiro o resultado deve ir para esse ficheiro.
            //Se o m�todo for chamado sem par�metros, o resultado � apresentado na consola.
			void Tree(const string *fich = NULL);                    // OK
            //Questao 17: Pesquisa todas as directorias com nome <dir> e coloca em <lres>
			void PesquisarAllDirectoria(list<string> &lres, const string &dir);  // OK
            //Questao 18: Pesquisa todos os ficheiros com nome <file> e coloca em <lres>
			void PesquisarAllFicheiros(list<string> &lres, const string &file);// OK
            //Questao 19: Renomear Todos os ficheiros com um dado fich_old, para outro nome fich_new
			void RenomearFicheiros(const string &fich_old, const string &fich_new);  // OK
            //Questao 20: Verificar se Existem Ficheiros duplicados, mesmo nome;
			bool FicheiroDuplicados();
            //Questao 21: Copiar todos os ficheiros de uma directoria (e da respetiva estrutura de sub-directorias)
            // cujo nome contenha uma determinada string para (a raiz de) outra diretoria;
            // No caso de existirem ficheiros com o mesmo nome (obviamente em directorias diferentes)
            // deve diferenci�-los acrescentando ao nome (antes da extens�o) um n�mero sequencial com 3 d�gitos.
            // Por exemplo: xptopadraoABC001.ext, xptopadraoABC002.ext.
			bool CopyBatch(const string &padrao, const string &DirOrigem, const string &DirDestino);
};

#endif// SISTEMAFICHEIROS_H
