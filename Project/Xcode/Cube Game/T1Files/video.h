/*
 CG 2018/1
 Autores:
 Felipe Pfeifer Rubin: Email: felipe.rubin@acad.pucrs.br
 Ian Aragon Escobar: Mat , Email: ian.escobar@acad.pucrs.br
 */

/*
 Arquivo: video.h
 - Header da biblioteca de manipulacao de dados do video
 */

#ifndef VIDEO_H
#define VIDEO_H
#include "globals.h"
#include "vmath.h"

// Estrutura que armazena informacoes de uma pessoa
typedef struct{
    int valid; //Deveria existir neste frame ?
	Point point; // ponto (x,y)
	float speed; // Velocidade da pessoa do frame anterior p/ agora
	Point displacement; // Deslocamento da Pessoa D = P1 - P0
}Person;

//Estrutura que armazena informacoes de um grupo
typedef struct Group{
	int *presence; //Quanto tempo que a Pessoa[x] esta no grupo, 0 = nao esta; malloc length
    int bornAt; //Quando que comeca o Grupo
    int deathAt; // Quando que termina o Grupo
	int size; //Quantas pessoas tem no grupo agora
	int length; //Quantas pessoas tem no video ao todo, ou seja, qts posicoes em presence[]
    float color[3]; //Cor do grupo
    
    int *enteredAt; //Primeira vez q a pessoa entrou no grupo
    int *exitedAt; //Ultima vez q a pessoa estava presente no grupo

	struct Group *next;
	struct Group *prev;
}Group;

//lista duplamente encadeada de grupos
typedef struct{
	int size;
	Group *head;
	Group *tail;
}GList;

// Informacoes da pessoa no frame atual
typedef struct{
	Person *person;
}Frame;

typedef struct{
	int pxm; // Pixel x Metro
	int length; //Numero de frames total
	int begin; //Primeiro frame em que alguem aparece
	Frame *frames; //Lista de frames (vetor alocado dinamicamente)
	Point minpoint; // Armazena os MENORES X e Y
	Point maxpoint; // Armazena os MAIORES X e Y
	int people; //Numero de pessoas
	int *personBegin; //primeira aparicao de cada pessoa
	int *personEnd; // ultima aparicao de cada pessoa
}VideoInfo;

/*
    Imprime os grupos
*/
void printGroups(GList *list);

/*
    Verifica se a Pessoa P e a Pessoa Q sao um grupo
 */
int ispp(int p, int q, VideoInfo *vi);

/*
    Pega o grupo da posicao pos dessa lista
 */
Group* getGroup(GList *list, int pos);

/*
   Verifica se small e big devem se unir
 */
int subsetof(Group *big, Group *small);

/*
    Merge nos grupos com mesmas pessoas
*/
void subsetGroups(GList *list);

/*
    Atualiza as informacoes de um grupo
 */
void updateGroup(Group *group);

/*
    Atualiza as informacoes de todos os grupos
 */
void updateGroups(GList *list);

/*
    Insere um grupo na lista de grupos
 */
void insertGroup(GList *list,Group *newgroup);
/*
    Cria um grupo e depois insere ele na lista de grupos
 */
void addGroup(GList *list, int p, int q, int length);

/*
    Adiciona uma pessoa a um grupo
 */
void addToGroup(Group *group, int p);
/*
    Remove uma pessoa de um grupo
 */
void removeFromGroup(Group *group, int p);

/*
   Adiciona todas as pessoas do grupo small no grupo big
 */
void addGroups(Group *big, Group *small);
/*
    Free na struct de VideoInfo
 */
void freeVideoInfo(VideoInfo *vi);
/*
    Aloca a memoria necessaria p/ struct VideoInfo
 */
void allocateVideoInfo(VideoInfo *vi);

/*
    Free na lista de grupos
 */
void freeGList(GList *list);

/*
    Elimina todos os grupos vazios da lista de grupos
 */
void removeEmptyGroups(GList *list);
/*
    Verifica, para cada pessoa quando entrou e quando saiu do grupo
*/
void inoutGroup(int p, Group *g,VideoInfo *vi, int *firstin, int *lastin);

/*
    Utilizar antes de readFileData(),
    Le as informacoes iniciais do arquivo para alocar espaco suficiente
    para inserir todas as informacoes de cada pessoa
 */
void readFileInfo(VideoInfo *vi,const char *filename);

/*
    Utilizar depois de readFileInfo(),
    Le todo o arquivo e insere todos os dados nas respectivas structs de VideoInfo
 */
void readFileData(VideoInfo *vi,const char *filename);
#endif
