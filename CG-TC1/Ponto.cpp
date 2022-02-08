/*
 * Ponto.cpp
 *
 *  Created on: 20/08/2015
 *      Author: rodrigo
 */

#include "Ponto.h"


Ponto::Ponto(int x, int y, int id) {
	// TODO Auto-generated constructor stub
	this->x = x;
	this->y = y;
	this->identificador = id;
}

Ponto::~Ponto() {
	// TODO Auto-generated destructor stub
}

float Ponto::getX(){
	return this->x;
}

void Ponto::setX(float x) {
	this->x = x;
}

float Ponto::getY () {
	return this->y;
}

void Ponto::setY (float y) {
	this->y = y;
}

int Ponto::getIdentificador() {
	return this->identificador;
}

void Ponto::setIdentificador(int id) {
	this->identificador = id;
}
