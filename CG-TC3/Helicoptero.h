#ifndef HELICOPTERO_H
#define HELICOPTERO_H

#include "Rectangle.h"
#include "Circle.h"
#include "Polyline.h"
#include "tinyxml2.h"
#include "Tiro.h"

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <vector>
#include <math.h>

using namespace std;
using namespace tinyxml2;


class Helicoptero
{
protected:
	// Definindo velocidade do helicoptero
	float velocidadeHelicoptero;
	
	// Helice
	float velocidadeHelices;
	float anguloHelices;
	float aceleracaoHelices;
	
	// Transformacao
	float fatorEscala;
	float cx;
	float cy;
	float raio;
	
	// Movimentacao
	float escalaHelicoptero;
	float enableMovimento;
	float posX;
	float posY;
	float anguloGiro;
	
	// Tiro
	vector<Tiro>* tiros;
	
	// Mira
	float anguloMira;
	float posMiraAnteriorX;
	float posMiraAnteriorY;
	
	// Propriedades do corpo do helicoptero
	Rectangle* mira;
	Rectangle* corpo;
	Rectangle* cauda;
	Rectangle* caudaEsquerda;
	Rectangle* caudaDireita;	
	Circle* centroHelice;
	vector<Polyline>* helices;
	
public:
	Helicoptero();
	~Helicoptero();
	void carregarInformacoes();
	void showValues();
	
	// Tiro
	void realizarTiro(Tiro* t);
	void mostrarTiros();
	void movimentarTiros();
	
	// Mira
	void rotacionarMira (float x, float y);
	void rotacionarMiraDireita();
	void rotacionarMiraEsquerda();
	
	// Helices
	void aumentarGiroHelices();
	void diminuirGiroHelices();
	void moverHelice();
	
	// Movimenta��o
	void moverParaFrente();
	void moverParaTras();
	void mudarEscalaMovimento();
	
	// Rota��o
	void rotacionarDireita();
	void rotacionarEsquerda();
	
	// Desenhar Helicoptero
	void desenharMira();
	void desenharCorpo();
	void desenharCaudaPrincipal();
	void desenharCaudaEsquerda();
	void desenharCaudaDireita();
	void desenharCentroHelice();
	void desenharHelices(Circle* c);
	void desenharHelicoptero(Circle* c);
	
	//Getters and Setters
	void setVelocidade (float v) {
		this->velocidadeHelicoptero = v;
	}
	float getVelocidade () {
		return this->velocidadeHelicoptero;
	}
};

#endif
