#include "Transformacao.h"

Transformacao::Transformacao()
{
	this->fatorEscala = 0;
	
	if (this->fatorEscala != 0) {
		this->fatorEscalaInverso = 1/this->fatorEscala;
	} else {
		this->fatorEscala = 0;
	}
	
	this->cx = 0;
	this->cy = 0;
	this->cz = 0;
	this->raio = 0;
	this->anguloGiro = 0;
	this->anguloMira = 0;
	this->height = 0;
	this->posX = 0;
	this->posY = 0;
}

Transformacao::Transformacao (float fatorEscala, float cx, float cy, float raio, float anguloGiro, float anguloMira, float height, float posX, float posY) {
	this->fatorEscala = fatorEscala;
	
	if (this->fatorEscala != 0) {
		this->fatorEscalaInverso = 1/this->fatorEscala;
	} else {
		this->fatorEscala = 0;
	}
	
	this->cx = cx;
	this->cy = cy;
	this->raio = raio;
	this->anguloGiro = anguloGiro;
	this->anguloMira = anguloMira;
	this->height = height;
	this->posX = posX;
	this->posY = posY;
}

Transformacao::~Transformacao()
{
}

void Transformacao::definirTransformacao (float fatorEscala, float cx, float cy, float cz, float raio, float anguloGiro, float anguloMira, float height, float posX, float posY) {
	this->fatorEscala = fatorEscala;

	if (this->fatorEscala != 0) {
		this->fatorEscalaInverso = 1/this->fatorEscala;
	} else {
		this->fatorEscala = 0;
	}

	this->cx = cx;
	this->cy = cy;
	this->cz = cz;
	this->raio = raio;
	this->anguloGiro = anguloGiro;
	this->anguloMira = anguloMira;
	this->height = height;
	this->posX = posX;
	this->posY = posY;
}

void Transformacao::iniciarTransformacao(bool ehTiro, bool vision3d) {
	
	if (vision3d) {
		glPushMatrix(); // Escala
			// diminuir tamanho do helicoptero de acordo com tamanho do c�rculo
			glScalef(this->fatorEscala, this->fatorEscala, this->fatorEscala);

			float xTranslated = this->posX*this->fatorEscalaInverso;
			float yTranslated = this->posY*this->fatorEscalaInverso;

			// come�a do centro do c�rculo
			glTranslatef(xTranslated, yTranslated, this->cz);

			glPushMatrix();
				// rotacionar o helicoptero de acordo com o usu�rio
				glRotatef(this->anguloGiro, 0.0, 0.0, 1.0);

				if (ehTiro) {
					// devemos ir para a parte superior, de acordo com o angulo da mira
					xTranslated = (this->height)*sin(this->anguloMira*M_PI/180);
					yTranslated = -(this->raio)*fatorEscalaInverso*cos(this->anguloMira*M_PI/180);
				} else {
					xTranslated = 0.0;
					yTranslated = -(this->raio) * fatorEscalaInverso;
				}

				// Ir para a parte superior do c�rculo
				glTranslatef(xTranslated, yTranslated, 30 + 20);

	} else {

	glPushMatrix(); // Escala
		// diminuir tamanho do helicoptero de acordo com tamanho do c�rculo
		glScalef(this->fatorEscala, this->fatorEscala, 0.0);
	
		float xTranslated = this->posX*this->fatorEscalaInverso;
		float yTranslated = this->posY*this->fatorEscalaInverso;
		
		// come�a do centro do c�rculo
		glTranslatef(xTranslated, yTranslated, 0);
		
		glPushMatrix();
			// rotacionar o helicoptero de acordo com o usu�rio
			glRotatef(this->anguloGiro, 0.0, 0.0, 1.0);

			if (ehTiro) {
				// devemos ir para a parte superior, de acordo com o angulo da mira
				xTranslated = (this->height)*sin(this->anguloMira*M_PI/180);
				yTranslated = -(this->raio)*fatorEscalaInverso*cos(this->anguloMira*M_PI/180);
			} else {
				xTranslated = 0.0;
				yTranslated = -(this->raio) * fatorEscalaInverso;
			}

			// Ir para a parte superior do c�rculo
			glTranslatef(xTranslated, yTranslated, 30 + 20);
	}
	
}

void Transformacao::fecharTransformacao() {
		glPopMatrix();
	glPopMatrix(); // Escala
}
