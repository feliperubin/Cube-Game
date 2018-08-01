/*
 CG 2018/1
 Autores:
 Felipe Pfeifer Rubin: Email: felipe.rubin@acad.pucrs.br
 Ian Aragon Escobar: Mat , Email: ian.escobar@acad.pucrs.br
 */

/*
 Arquivo: video.cpp
 - Codigo da biblioteca de manipulacao de dados do video
 - Manipulacoes de baixo nivel de estruturas de dados
 - Algoritmos de comparacao
 */


//#include <stdlib.h>
//#include <stdio.h>

#include "video.h"

//Diferenca maxima de distancia
#ifndef DIFF_DIST
#define DIFF_DIST 1.01f
#endif

//Diferenca maxima de velocidade (Speed)
#ifndef DIFF_SPD
#define DIFF_SPD 0.03f
#endif

//Diferenca maxima de angulo 90 == tao no mesmo quadrante
#ifndef DIFF_ANGL
#define DIFF_ANGL 90.0f
#endif

#ifndef ACCEPT_RATIO
#define ACCEPT_RATIO 0.3f
#endif



void printGroups(GList *list)
{
	Group *aux = list->head;
	int i = 0;
	int j = 0;
    int ponctuation = 0; //Precisa usar ',' p/ deixar print correto
	while(aux != NULL){
		printf("Group %d[size:%d][Born:%d,Death:%d]{",i,aux->size,aux->bornAt,aux->deathAt);
        ponctuation = 0;
		for(j = 0; j < aux->length; j++){
            if(aux->presence[j] > 0){
                if(ponctuation)
                    printf(",");
                else
                    ponctuation = 1;
				printf("%d[%d,%d]",j,aux->enteredAt[j],aux->exitedAt[j]);
            }
		}
		printf("}\n");
		aux = aux->next;
		i++;
	}
}

void freeGroup(Group *group)
{
	free(group->presence);
    free(group->enteredAt);
    free(group->exitedAt);
	free(group);
}


void freeGList(GList *list)
{
	Group *aux = list->head;
	while(aux != NULL){
		Group *curr = aux;
		aux = aux->next;
		freeGroup(curr);
	}
    list->head = NULL;
    list->tail = NULL;
	free(list);
}


//////////////////////////////////////////////////////////////////////////////////////////
////										Check if Both Form a Group 			   //
//////////////////////////////////////////////////////////////////////////////////////////
/*
	Verificar p/ todos:
	1 - Distancia
	2 - Velocidade
	3 - Angulo
*/

/*
 A Pessoa P e Q formam um Grupo ?
 0 = nao
 1 = sim
 
 O que pesa mais eh a distancia.
 2x heuristicas.
 1 - A padrao
 2 - Adiciona um pouco mais de variacao de distancia e velocidade ao custo de reforcar
 o angulo do vetor de deslocamento entre as duas pessoas.
 */
int ispp(int p, int q, VideoInfo *vi)
{
    int heuristic1 = 0;
    int heuristic2 = 0;
    int bothpresent = 0;
    for(int i = 0; i < vi->length; i++){
        if(vi->frames[i].person[p].valid && vi->frames[i].person[q].valid){
            float dist = distance(vi->frames[i].person[p].point,vi->frames[i].person[q].point);
            float speed = fabsf(vi->frames[i].person[p].speed - vi->frames[i].person[q].speed);
            float angl = angle(vi->frames[i].person[p].displacement,vi->frames[i].person[q].displacement);
            if(dist <= DIFF_DIST && speed <= DIFF_SPD && angl <= DIFF_ANGL){
                heuristic1++;
            }
            if(dist <= DIFF_DIST + 0.1f && speed <= DIFF_SPD + 0.1f && angl <= DIFF_ANGL - 25.0f){
                heuristic2++;
            }
            bothpresent++;
        }
    }
    
    if(bothpresent == 0){ //Seguranca de n dar NaN
        return 0;
    }
    float possible1 = (float)heuristic1/(float)bothpresent;
    float possible2 = (float)heuristic2/(float)bothpresent;
    
    return possible1 >= ACCEPT_RATIO || possible2 >= ACCEPT_RATIO;
}


//Verifica quando a pessoa entra e quando sai do grupo
void inoutGroup(int p, Group *g,VideoInfo *vi, int *firstin, int *lastin){
    *firstin = -1;
    *lastin = -1;
    int i = 0;
    for(i = vi->personBegin[p]; i < vi->length; i++){
        if(vi->frames[i].person[p].valid){
            for(int j = 0; j < vi->people; j++){
                if(j != p && g->presence[j] > 0 && vi->frames[i].person[j].valid){
                    float dist = distance(vi->frames[i].person[p].point,vi->frames[i].person[j].point);
                    float speed = fabsf(vi->frames[i].person[p].speed - vi->frames[i].person[j].speed);
                    float angl = angle(vi->frames[i].person[p].displacement,vi->frames[i].person[j].displacement);
                    if(dist <= DIFF_DIST && speed <= DIFF_SPD && angl <= DIFF_ANGL){
                        *lastin = i;
                        if(*firstin == -1) *firstin = i;
                    }
                }
            }
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////
//  										Get Group               				  //
//////////////////////////////////////////////////////////////////////////////////////////////


Group* getGroup(GList *list, int pos){
	if(list->size <= pos){
		printf("getGroup() Tentou pegar uma pessoa %d que nao existe no Video com maximo %d\n",pos,list->size);
		exit(EXIT_FAILURE);
	}
	Group *aux = list->head;
	while(pos > 0){
		aux = aux->next;
		pos--;
	}
	return aux;
}


//////////////////////////////////////////////////////////////////////////////////////////////
//   							     Subset and Update Groups               		  //
//////////////////////////////////////////////////////////////////////////////////////////////


/*
	SMALL EH UM SUBSET DE BIG ? 
	0 = NAO
	1 = SIM

	Se Small tem ao menos 1 pessoa que esta em big,
	eh subset.
 */

int subsetof(Group *big, Group *small)
{
	int i = 0;
	for(i = 0; i < big->length; i++){
        if(big->presence[i] != 0 && small->presence[i] != 0){
			return 1;
		}
	}
	return 0;
}
/*
	Limpa os subsets
	ex:
	GList = { {1,2,3}, {1,6}, {1,3}, {4,5} }
	GLIST = { {1,2,3,6}, {4,5} }

	OBS:
	O Group *aux, eh p/ poder dar free no grupo small
	e ainda reter o prev.
	Da p/ fazer sem esse aux e sem a bkflag.
	Mesmo depois de liberar o small,freeGroup(small),
	nao tem problema em fazer small->prev. Por seguranca,
	coloquei esse aux e setei o small p/ null

 */
void subsetGroups(GList *list)
{
	int bkflag = 0; //Se teve break no while interno
	if(list->head == NULL) return;
	Group *small = list->tail;
	Group *big;
	while(small != list->head){
		big = list->head;
		while(big != small && big != NULL){
			if(subsetof(big,small)){
				addGroups(big,small);
				if(small->next != NULL){
					small->next->prev = small->prev;
					small->prev->next = small->next;
					bkflag = 1;					
					Group* aux = small->prev;
					freeGroup(small);
					small = aux; //Olhar comentarios
				}else{ //small == tail
					Group* aux = small->prev;
					small->prev->next = NULL;
					small->prev = NULL;
					freeGroup(small);
					list->tail = aux;
					small = aux;
					bkflag = 1;
				}
				list->size--;
				break;
			}else{
				big = big->next;
			}
		}
		if(bkflag == 1)
			bkflag = 0;
		else
			small = small->prev;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////
//                                        Remove Empty Groups                             //
////////////////////////////////////////////////////////////////////////////////////////////


/*
	Remove todos os grupos vazios da lista
*/
void removeEmptyGroups(GList *list)
{
	Group *aux = list->head;
	while(aux != NULL){
		if(aux->size == 0){
			if(aux->next != NULL){
				if(aux->prev != NULL){
					aux->next->prev = aux->prev;
					aux->prev->next = aux->next;
					Group *aux2 = aux->next;
					free(aux);
					aux = aux2;
				}else{//head
					aux->next->prev = NULL;
					Group *aux2 = aux->next;
					freeGroup(aux);
					list->head = aux2;
					aux = aux2;
				}
			}else{
				if(aux->prev != NULL){ //tail
					aux->prev->next = NULL;
					Group *aux2 = aux->prev;
					freeGroup(aux);
					list->tail = aux2;
					aux = aux2;
				}else{ // head == tail
					freeGroup(aux);
					list->head = NULL;
					list->tail = NULL;
					aux = NULL;
                    //Dou break aqui p/ n bugar aux = aux->next
                    //Se dou break aqui, n vai cair em list->size--
                    list->size--;
					break;
				}
			}
			list->size--;
		}
		aux = aux->next;
	}
}

/*
	Atualiza as informacoes do grupo
	- Size: Assegurar que esta correto
 */
void updateGroup(Group *group)
{
	int i;
	int countSize = 0;
	for(i = 0; i < group->length; i++){
		//Nao pertence ao grupo
		if(group->presence[i] == 0) continue;
		countSize++;
	}
	group->size = countSize;
}

/*
	Chama updateGroup p/ todos os grupos da lista
*/
void updateGroups(GList *list)
{
	Group *aux = list->head;
	int cont = 0;

	while(aux != NULL){
		cont++;
		updateGroup(aux);
		aux = aux->next;
	}

}
////////////////////////////////////////////////////////////////////////////////////////////
//										Add Groups   						     //
////////////////////////////////////////////////////////////////////////////////////////////


/*
	Insere um Grupo no fim da lista de Grupos
*/
void insertGroup(GList *list,Group *newgroup)
{
	if(list->size == 0){
		list->size+=1;
		list->head = newgroup;
		list->head->prev = NULL;
		list->head->next = NULL;
		list->tail = newgroup;
		list->tail->prev = NULL;
		list->tail->next = NULL;
		return;
	}
    
	list->tail->next = newgroup;
	newgroup->prev = list->tail;
	list->tail = newgroup;
	list->tail->next = NULL;
	list->size+= 1;

}

/*
	Cria um grupo e adiciona
	Lista p/ adicionar, Pessoa P, index da Pessoa P,
	Pessoa Q, index da Pessoa Q,
	Tamanho de pessoas no video
*/

void addGroup(GList *list,int p,int q,int length)
{
	Group *newgroup = (Group*)malloc(sizeof(Group));
	newgroup->presence = (int*)calloc(length,sizeof(int));
	newgroup->presence[p] = 1;
	newgroup->presence[q] = 1;
    newgroup->bornAt = -1; //Depois calculo isso
    newgroup->deathAt = -1; // Depois calculo isso
	newgroup->size = 2;
	newgroup->length = length;
	newgroup->prev = NULL;
	newgroup->next = NULL;
    newgroup->color[0] = get_random(0, 1);
    newgroup->color[1] = get_random(0, 1);
    newgroup->color[2] = get_random(0, 1);
    newgroup->enteredAt = (int*)calloc(length, sizeof(int));
    newgroup->exitedAt = (int*)calloc(length, sizeof(int));
	insertGroup(list,newgroup);
}

/*
	Adiciona uma pessoa a um grupo ja existente	
*/
void addToGroup(Group *group, int p)
{
	if(group->presence[p] == 0){
		group->size++;
	}
	group->presence[p]++;
	
}

void removeFromGroup(Group *group, int p)
{
	if(group->presence[p] > 0){
		group->size--;
	}
	group->presence[p] = 0;
}
/*
	Adiciona um grupo ja existente a outro tambem ja existente
	Adiciona o Grupo small no Big
*/
void addGroups(Group *big, Group *small)
{
	int i;
	for(i = 0; i < big->length; i++){
		//Presence of small.person[i]
		//Ha qt tempo essa pessoa ta em small
		int pofi = small->presence[i];
		if(pofi > 0){ //Se essa pessoa realmente esta em small
			//Se esta a mais tempo em small do que em big
			if(pofi > big->presence[i]){
				//Se big nao tem essa pessoa
				if(big->presence[i] == 0){
					big->size++;
				}
				big->presence[i] = small->presence[i];
			}
		}
	}

}
////////////////////////////////////////////////////////////////////////////////////////////
//										READING FILE                               //
////////////////////////////////////////////////////////////////////////////////////////////
/*
	Step 1: Ler arquivo pegando
	- quantidade total de frames
	- quantidade total de pessoas
	- frame inicial
	- frame final
*/
void readFileInfo(VideoInfo *vi,const char *filename)
{
	printf("ReadInfo: Opening File %s\n",filename);
	FILE *file = fopen(filename,"r");
	
	if(!file){
		printf("ReadInfo: Error oppening file! \n");
		return;
	}
	//Pega Pixel x Metro
	fscanf(file,"[%d]",&vi->pxm);
	vi->people = 0;
	int duration; //duracao de frames da pessoa atual
	int firstFrame; //primeiro frame da pessoa atual
	int lastFrame; //ultimo frame da pessoa atual
	int minFrame; //Menor numero de frame total
	int maxFrame; //Maior numero de frame total	
	int i;


	//Lendo a primeira vez p/ poder comparar nas proximas
	if(fscanf(file,"\n%d ",&duration) == 1){
		fscanf(file,"(%*d,%*d,%d)",&minFrame);
		maxFrame = minFrame + duration - 1;
		for(i = 1; i < duration; i++)
			fscanf(file,"(%*d,%*d,%*d)");
		vi->people++;
	}else{
		printf("ReadInfo: Error file doesn't have any frame! \n");
		return;
	}

	//Lendo mesmo agora
	while(fscanf(file,"\n%d ",&duration) == 1){
		fscanf(file,"(%*d,%*d,%d)",&firstFrame);
		lastFrame = duration + firstFrame-1;
		if(minFrame > firstFrame)
			minFrame = firstFrame;
		
		if(maxFrame < lastFrame)
			maxFrame = lastFrame;
		
		for(i = 1; i < duration; i++)
			fscanf(file,"(%*d,%*d,%*d)");

		vi->people++;
	}

	vi->begin = minFrame;
	vi->length = maxFrame - minFrame+1;
	printf("ReadInfo: Closing File %s\n",filename);
	fclose(file);
}

/*
	Step 2: Ler arquivo pegando 
	- todos os dados restantes
*/
void readFileData(VideoInfo *vi,const char *filename)
{
	printf("ReadData: Opening File %s\n",filename);
	FILE *file = fopen(filename,"r");
	
	if(!file){
		printf("ReadData: Error oppening file! \n");
		return;
	}
	int i,j;
	fscanf(file,"[%*d]\n");
	int duration = 0; //duracao de frames da pessoa atual
	int frame = 0; //ultimo frame da pessoa atual
	int x = 0;
	int y = 0;
	for(i = 0; i < vi->people; i++){

		fscanf(file,"%d ",&duration);
		for(j = 0; j < duration; j++){
			fscanf(file,"(%d,%d,%d)",&x,&y,&frame);
			if(j == 0){
				vi->personBegin[i] = frame - vi->begin;
				vi->personEnd[i] = frame + duration - 1 - vi->begin;
			}
			if(i == 0 && j == 0){
				vi->minpoint.x = x;
				vi->minpoint.y = y;
				vi->maxpoint.x = x;
				vi->maxpoint.y = y;
			}else{
				if(vi->minpoint.x > x)
					vi->minpoint.x = x;
				if(vi->minpoint.y > y)
					vi->minpoint.y = y;
				if(vi->maxpoint.x < x)
					vi->maxpoint.x = x;
				if(vi->maxpoint.y < y)
					vi->maxpoint.y = y;
			}
			vi->frames[frame-vi->begin].person[i].valid = 1;
			vi->frames[frame-vi->begin].person[i].point.x = (float)x/(float)vi->pxm;
			vi->frames[frame-vi->begin].person[i].point.y = (float)y/(float)vi->pxm;
            //Provavelmente vi->begin vai ser sempre 1
			if(j == 0){
				vi->frames[frame-vi->begin].person[i].speed = 0.0;
				vi->frames[frame-vi->begin].person[i].displacement.x = 0.0;
				vi->frames[frame-vi->begin].person[i].displacement.y = 0.0;
			}else{
				Person *before = &vi->frames[frame-vi->begin-1].person[i];
				Person *now = &vi->frames[frame-vi->begin].person[i];
				now->speed = distance(before->point,now->point);
				now->displacement = displacement(before->point,now->point);
			}			
		}
		fscanf(file,"\n");
	}
	vi->minpoint.x = vi->minpoint.x/(float)vi->pxm;
	vi->minpoint.y = vi->minpoint.y/(float)vi->pxm;
	vi->maxpoint.x = vi->maxpoint.x/(float)vi->pxm;
	vi->maxpoint.y = vi->maxpoint.y/(float)vi->pxm;
	printf("ReadData: Closing File %s\n",filename);
	fclose(file);
}

/*
    Da free em videoinfo e seus componentes
 */
void freeVideoInfo(VideoInfo *vi)
{
	int i;
	for(i = 0; i < vi->length; i++){
		Frame *f = &vi->frames[i];
		free(f->person);
	}
	free(vi->frames);
	//
	free(vi->personBegin);
	free(vi->personEnd);
}

/*
	Aloca o q for preciso p/ 
*/
void allocateVideoInfo(VideoInfo *vi)
{
	int i;
	vi->frames = (Frame*)malloc(sizeof(Frame) * vi->length);
	vi->minpoint.x = 0;
	vi->minpoint.y = 0;
	vi->maxpoint.x = 0;
	vi->maxpoint.y = 0;
	Frame *f;
	for(i = 0; i < vi->length; i++){
		f = &vi->frames[i];
		f->person = (Person*)calloc(vi->people,sizeof(Person));
        f->person->valid = 0;
	}
	vi->personBegin =(int*) malloc(sizeof(int) * vi->people);
	vi->personEnd = (int*)malloc(sizeof(int) * vi->people);
}
