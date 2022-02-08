/*
 * Arena.h
 *
 *  Created on: Nov 20, 2015
 *      Author: rbpimenta
 */

#ifndef ARENA_H_
#define ARENA_H_

#include "Rectangle.h"

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

class Arena {
protected:
	// Dados principais da arena
	Rectangle* dadosArena;

public:
	Arena();
	virtual ~Arena();

	void desenhar(bool vision3d, float alturaHelicoptero);
	void desenharChao();
	void desenharTeto();
	void desenharParedes(float alturaHelicoptero);
	void desenharParedeEsquerda(float alturaHelicoptero);
	void desenharParedeDireita(float alturaHelicoptero);
	void desenharParedeFundo(float alturaHelicoptero);
	void desenharParedeFrente(float alturaHelicoptero);



	// Getters and Setters
	Rectangle* getDadosArena() const {
		return dadosArena;
	}

	void setDadosArena(Rectangle* dadosArena) {
		this->dadosArena = dadosArena;
	}
};

#endif /* ARENA_H_ */
