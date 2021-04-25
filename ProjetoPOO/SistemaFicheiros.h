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
        // Declarar os Objectos ou conjuntos de objectos necessários a resolução do problema
    public:
			SistemaFicheiros();                                        // OK
			virtual ~SistemaFicheiros();                               // OK
            //Questao 1: Correr o programa numa dada diretoria e esta (e seus conteúdos)
            // serem carregados para memória (SistemaFicheiros);
            // O método deve devolver true se a operação foi bem sucedida.
			bool Load(const string &path);
            //Questao 2: Contar o número de ficheiros que o Sistema de Ficheiros tem guardado em memória;
			int ContarFicheiros();
            //Questao 3: Contar o número de directorias que o Sistema de Ficheiros tem guardado em memória;
			int ContarDirectorias();
            //Questao 4: Determinar toda a memória ocupada;
			int Memoria();
            //Questao 5: Determinar qual a diretoria que tem mais informação (maior número de pastas e ficheiros);
            // Se existir mais do que uma, deve devolver uma delas!
            // (Não deve ser considerado o conteúdo das sub-directorias);
			string *DirectoriaMaisElementos();
            //Questao 6: Determinar qual a diretoria que tem menos informação (menor número de pastas e ficheiros);
            // Se existir mais do que uma, deve devolver uma delas!
			string *DirectoriaMenosElementos();
            //Questao 7: Determinar o ficheiro que ocupa mais espaço, bem como o respetivo caminho;
			string *FicheiroMaior();
            //Questao 8: Determinar qual diretoria que está a ocupar mais espaço;
			string *DirectoriaMaisEspaco();
            //Questao 9: Pesquisar se existe um dado ficheiro ou diretoria, devolvendo o “caminho” completo até ele(a);
            // Considere que se Tipo = 0 se pretende pesquisar um ficheiro e se Tipo = 1
            // se pretende uma directoria.
			string *Search(const string &s, int &Tipo);
            //Questao 10: Remover todas as diretorias ou ficheiros; Se tipo = "DIR" remove directorias, senão remove ficheiros;
            // Deve devolver true se a operação foi bem sucedida.
			bool RemoverAll(const string &s, const string &tipo);
            //Questao 11: Gravar para ficheiro em formato XML todo o Sistema de Ficheiros;
			void Escrever_XML(const string &s);
            //Questao 12: Ler de um ficheiro em formato XML todo o Sistema de Ficheiros (antes de ler deve ser apagado tudo o que estiver no Sistema de Ficheiros);
            // Se leu corretamente devolve true, senão devolve false.
			bool Ler_XML(const string &s);
            //Questao 13: 13.	Mover um Ficheiro para outra diretoria; se existir mais do que um ficheiro,
            //move o primeiro encontrado; Se o ficheiro já estiver em DirNova, não deve fazer nada.
            // Se conseguir mover deve devolver true (false caso contrário);
			bool MoverFicheiro(const string &Fich, const string &DirNova);
            //Questao 14: Mover uma diretoria (e tudo o que lhe está associado!) para outra diretoria; se existir mais do que uma directoria, move a primeira encontrada.
            //Assume-se que DirNew não é sub-directoria de DirOld. No caso de DirNew ser sub-directoria de DirOld,
            //deve devolver false e não efetuar qualquer operação.
			bool MoverDirectoria(const string &DirOld, const string &DirNew);
            //Questao 15: Determinar a data de um dado ficheiro; se o ficheiro não existir deve devolver NULL; se existirem vários, deve devolver a data do primeiro ficheiro;
            // (Exemplo de devolução de uma data “2017|10|5”);
			string *DataFicheiro(const string &ficheiro);
            //Questao 16: À semelhança do comando do MS-DOS, implemente o método Tree;
            // Deve considerar que a listagem deve sair na consola e num ficheiro.
            // Se o método for chamado com um ficheiro o resultado deve ir para esse ficheiro.
            //Se o método for chamado sem parâmetros, o resultado é apresentado na consola.
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
            // deve diferenciá-los acrescentando ao nome (antes da extensão) um número sequencial com 3 dígitos.
            // Por exemplo: xptopadraoABC001.ext, xptopadraoABC002.ext.
			bool CopyBatch(const string &padrao, const string &DirOrigem, const string &DirDestino);
};

#endif// SISTEMAFICHEIROS_H
