/*
 * Arena.cpp
 *
 *  Created on: Nov 20, 2015
 *      Author: rbpimenta
 */

#include "Arena.h"

Arena::Arena() {
	// TODO Auto-generated constructor stub

}

Arena::~Arena() {
	// TODO Auto-generated destructor stub
}

void Arena::desenhar(bool vision3d, float alturaHelicoptero) {
	double xTranslated = this->dadosArena->getWidth() / 2
			+ this->dadosArena->getX();
	double yTranslated = 0.0;

	if (vision3d) {
		glColor3f(1.0, 1.0, 1.0);
		this->desenharChao();

		this->desenharTeto();
		glColor3f(1.0, 0.0, 1.0);
		this->desenharParedes(alturaHelicoptero);
	} else {
		glPushMatrix();
		glTranslated(xTranslated, yTranslated, 0);
		this->dadosArena->desenharRectangle2d(1.0, 1.0, 1.0, false);
		glPopMatrix();
	}

}

void Arena::desenharChao() {

	glBegin(GL_QUADS);
	//lNormal3f(0,1,0);
	//glTexCoord2f (0, 0);
	glVertex3f(0, 0, 0);
	//glNormal3f(0,1,0);
	//glTexCoord2f (0, textureS);
	glVertex3f(0, this->dadosArena->getHeight(), 0);
	//glNormal3f(0,1,0);
	//glTexCoord2f (textureS, textureS);
	glVertex3f(this->dadosArena->getWidth(), this->dadosArena->getHeight(), 0);
	//glNormal3f(0,1,0);
	//glTexCoord2f (textureS, 0);
	glVertex3f(this->dadosArena->getWidth(), 0, 0);
	glEnd();

}

void Arena::desenharTeto() {
}

void Arena::desenharParedes(float alturaHelicoptero) {
	// glBindTexture (GL_TEXTURE_2D, texture);

	desenharParedeEsquerda(alturaHelicoptero);
	desenharParedeDireita(alturaHelicoptero);
	//desenharParedeFundo(alturaHelicoptero);
	desenharParedeFrente(alturaHelicoptero);
}

void Arena::desenharParedeEsquerda(float alturaHelicoptero) {
	double textureS = 1;
	// glBindTexture (GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, 0);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0, textureS);
	glVertex3f(0, this->dadosArena->getHeight(), 0);
	glNormal3f(0, 1, 0);
	glTexCoord2f(textureS, textureS);
	glVertex3f(0, this->dadosArena->getHeight(), 15 * alturaHelicoptero);
	glNormal3f(0, 1, 0);
	glTexCoord2f(textureS, 0);
	glVertex3f(0, 0, 15 * alturaHelicoptero);
	glEnd();
}

void Arena::desenharParedeDireita(float alturaHelicoptero) {
	double textureS = 1;
	//glBindTexture (GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0, 0);
	glVertex3f(this->dadosArena->getWidth(), 0, 0);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0, textureS);
	glVertex3f(this->dadosArena->getWidth(), this->dadosArena->getHeight(), 0);
	glNormal3f(0, 1, 0);
	glTexCoord2f(textureS, textureS);
	glVertex3f(this->dadosArena->getWidth(), this->dadosArena->getHeight(),
			15 * alturaHelicoptero);
	glNormal3f(0, 1, 0);
	glTexCoord2f(textureS, 0);
	glVertex3f(this->dadosArena->getWidth(), 0, 15 * alturaHelicoptero);
	glEnd();
}

void Arena::desenharParedeFundo(float alturaHelicoptero) {
	double textureS = 1;
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, 0);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0, textureS);
	glVertex3f(this->dadosArena->getWidth(), 0, 0);
	glNormal3f(0, 1, 0);
	glTexCoord2f(textureS, textureS);
	glVertex3f(this->dadosArena->getWidth(), 0, 15 * alturaHelicoptero);
	glNormal3f(0, 1, 0);
	glTexCoord2f(textureS, 0);
	glVertex3f(0, 0, 15 * alturaHelicoptero);
	glEnd();
}

void Arena::desenharParedeFrente(float alturaHelicoptero) {
	double textureS = 1;
	// glBindTexture (GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0, 0);
	glVertex3f(0, this->dadosArena->getHeight(), 0);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0, textureS);
	glVertex3f(this->dadosArena->getWidth(), this->dadosArena->getHeight(), 0);
	glNormal3f(0, 1, 0);
	glTexCoord2f(textureS, textureS);
	glVertex3f(this->dadosArena->getWidth(), this->dadosArena->getHeight(),
			15 * alturaHelicoptero);
	glNormal3f(0, 1, 0);
	glTexCoord2f(textureS, 0);
	glVertex3f(0, this->dadosArena->getHeight(), 15 * alturaHelicoptero);
	glEnd();
}
