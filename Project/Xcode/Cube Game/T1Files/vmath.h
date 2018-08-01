/*
 CG 2018/1
 Autores:
 Felipe Pfeifer Rubin: Email: felipe.rubin@acad.pucrs.br
 Ian Aragon Escobar: Mat , Email: ian.escobar@acad.pucrs.br
 */

/*
 Arquivo: vmath.h
 - Header da bilioteca de Funcoes Matematicas
 */

#ifndef VMATH_H
#define VMATH_H
#include "globals.h"

typedef struct{
	float x;
	float y;
}Point;

/*
 Distancia entre Pontos P(x,y) e Q(x0,y0)
 */
float distance(Point p, Point q);
/*
 Modulo do Vetor |a|
 */
float magnitude(Point p);
/*
 Vetor Unitario
 */
Point unitvector(Point p);
/*
 A diferenca entre dois Pontos eh um vetor
 Deslocamento (Displacement)
 P ---> Q
 */
Point displacement(Point p, Point q);
/*
 Cosseno do Angulo entre 2 Vetores
 Cos O = unitario(p) * unitario(q)
 Cos O = [-1;1]
 */
float cosvector(Point p, Point q);

/*
    Angulo entre 2 dois vetores
    Eh o cosvector transformado em angulos
 */
float angle(Point p, Point q);
/*
 Retorna um float pseudo-random entre [a,b]
 Como nao eh chamada srand(), ele ira devolver normalmente a mesma sequencia de valores pseudo-random
 */
float get_random(float a, float b);


#endif
