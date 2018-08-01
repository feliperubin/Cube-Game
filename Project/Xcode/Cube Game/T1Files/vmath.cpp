/*
 CG 2018/1
 Autores:
 Felipe Pfeifer Rubin: Email: felipe.rubin@acad.pucrs.br
 Ian Aragon Escobar: Mat , Email: ian.escobar@acad.pucrs.br
 */

/*
 Arquivo: vmath.cpp
 - Codigo da bilioteca de Funcoes Matematicas
 */


#include "vmath.h"

//De: https://stackoverflow.com/questions/9912151/math-constant-pi-value-in-c
//User: Martin ...
 #ifndef V_PI
 #define V_PI acos(-1.0)
 #endif

#ifndef V_RADANGLE
#define V_RADANGLE 180.0/acos(-1.0)
#endif


/*
	Distancia entre Pontos P(x,y) e Q(x0,y0)
 */

float distance(Point p, Point q)
{
	float dx = fabsf(p.x - q.x);
	float dy = fabsf(p.y - q.y);
	return sqrtf(dx*dx + dy*dy);	
}

/*
	Modulo do Vetor |a| 
*/
float magnitude(Point p)
{
	return sqrtf(p.x*p.x + p.y*p.y);
}

/*			
	Vetor Unitario
*/
Point unitvector(Point p)
{
	float mag = magnitude(p);
	if(mag == 0){
		Point unit = {.x = 0.0, .y = 0.0};
		return unit;
	}
	Point unit = {.x = p.x/mag, .y = p.y/mag};
	return unit;
}


/*
	A diferenca entre dois Pontos eh um vetor
	Deslocamento (Displacement)
	P ---> Q
*/
Point displacement(Point p, Point q)
{
	Point v = {.x = q.x - p.x, .y = q.y - p.y};

	return v;
}

/*
	Cosseno do Angulo entre 2 Vetores
	Cos O = unitario(p) * unitario(q)
	Cos O = [-1;1]
 */
float cosvector(Point p, Point q)
{

	Point unitp = unitvector(p);

	Point unitq = unitvector(q);

	float a = unitp.x*unitq.x + unitp.y*unitq.y;
	 if (a > 1.0 && a < 1.1)
	 	a = 1.0f;
	 if (a < -1.0 && a > -1.1)
	 	a = -1.0f;
	 
	if (a > 1 || a < -1){
	 printf("cosvector() Isso n deveria ocorrer\n");
	 printf("Exit_FAILURE cosvector() \n");
	 exit(EXIT_FAILURE);
	}

	return a;
}

/*
	Angulo entre 2 dois vetores
*/
float angle(Point p, Point q)
{
    float res = acos(cosvector(p,q)) * V_RADANGLE;
    return res;
}

/*
    Retorna um float pseudo-random entre [a,b]
    Como nao eh chamada srand(), ele ira devolver sempre a mesma sequencia de valores pseudo-random
*/
float get_random(float a, float b)
{
    return ((b - a) * ((float)rand() / RAND_MAX)) + a;
}








