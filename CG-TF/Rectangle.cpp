/*
 * Arena.cpp
 *
 *  Created on: 14/09/2015
 *      Author: rodrigo
 */

#include "Rectangle.h"
#include "tinyxml2.h"

#include <iostream>

using namespace std;
using namespace tinyxml2;

Rectangle::Rectangle() {
	// TODO Auto-generated constructor stub
	this->fill = "";
	this->height = 0.0;
	this->id = "";
	this->stroke = "";
	this->stroke_width = 0;
	this->width = 0.0;
	this->x = 0.0;
	this->y = 0.0;
}

Rectangle::~Rectangle() {
	// TODO Auto-generated destructor stub
}

void Rectangle::showValues() {
	cout << "Dados Rectangle:\n";
	cout << "Id = " << this->getId() << "\n";
	cout << "X = " << this->getX() << "\n";
	cout << "Y = " << this->getY() << "\n";
	cout << "Width = " << this->getWidth() << "\n";
	cout << "Hight = " << this->getHeight() << "\n";
	cout << "Fill = " << this->getFill() << "\n";
	cout << "Stroke-Widht = " << this->getStrokeWidth() << "\n";
	cout << "Stroke = " << this->getStroke() << "\n\n";
}

void Rectangle::setValues(XMLElement* elem) {
	// atributos do tipo rect
	float x = 0.0; // posição em X
	float y = 0.0; // posição em Y
	float width = 0.0; // comprimento
	float height = 0.0; // altura
	string fill = "";
	int stroke_width = 0; // Comprimento da linha
	string stroke = "";
	string id = ""; // Identificador

	// set Id
	const char* aux = "";
	aux = (elem->Attribute("id"));
	id = aux;
	this->id = id;

	// set X
	elem->QueryFloatAttribute("x", &x);
	this->setX(x);

	// set Y
	elem->QueryFloatAttribute("y", &y);
	this->setY(y);

	// set Widht
	elem->QueryFloatAttribute("width", &width);
	this->setWidth(width);

	// set Height
	elem->QueryFloatAttribute("height", &height);
	this->setHeight(height);

	// set Fill
	aux = elem->Attribute("fill");
	fill = aux;
	this->setFill(fill);

	// set stroke_width
	elem->QueryIntAttribute("stroke-width", &stroke_width);
	this->setStrokeWidth(stroke_width);

	// set stroke
	aux = elem->Attribute("stroke");
	stroke = aux;
	this->setStroke(stroke);
}

void Rectangle::desenharContorno2d(float R, float G, float B) {
	// Contorno
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-this->width / 2.0, 0.0);                        // Top Left
	glVertex2f(-this->width / 2.0, this->height);               // Bottom Left
	glVertex2f(this->width / 2.0, this->height);               // Bottom Right
	glVertex2f(this->width / 2.0, 0.0);                // Top Right
	glEnd();
}

void Rectangle::desenharRectangle2d(float R, float G, float B,
		bool desenharContorno) {
	glColor3f(R, G, B);
	glBegin(GL_QUADS);
	glVertex2f(-this->width / 2.0, 0.0);                        // Top Left
	glVertex2f(-this->width / 2.0, this->height);               // Bottom Left
	glVertex2f(this->width / 2.0, this->height);               // Bottom Right
	glVertex2f(this->width / 2.0, 0.0);                // Top Right
	glEnd();

	if (desenharContorno == true) {
		this->desenharContorno2d(0.0, 0.0, 0.0);
	}
}

void Rectangle::desenharRectangle2d(float height, float width, float R, float G,
		float B, bool desenharContorno) {
	glColor3f(R, G, B);
	glBegin(GL_QUADS);
	glVertex2f(-width / 2.0, 0.0);                        // Top Left
	glVertex2f(-width / 2.0, height);               // Bottom Left
	glVertex2f(width / 2.0, height);               // Bottom Right
	glVertex2f(width / 2.0, 0.0);                // Top Right
	glEnd();

	if (desenharContorno == true) {
		this->desenharContorno2d(0.0, 0.0, 0.0);
	}
}

void Rectangle::desenharContorno3d(Ponto* p1, Ponto* p2, Ponto* p3, Ponto* p4) {
	// Contorno
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(p1->getX(), p1->getZ(), p1->getY());
	glVertex3f(p2->getX(), p2->getZ(), p2->getY());
	glVertex3f(p3->getX(), p3->getZ(), p3->getY());
	glVertex3f(p4->getX(), p4->getZ(), p4->getY());
	glEnd();

}

void Rectangle::desenharBaixo3d(float altura, bool desenharContorno) {
	Ponto* p1 = new Ponto(-this->width / 2.0, 0, 0);
	Ponto* p2 = new Ponto(this->width / 2.0, 0, 0);
	Ponto* p3 = new Ponto(this->width / 2.0, altura, 0);
	Ponto* p4 = new Ponto(-this->width / 2.0, altura, 0);

	glBegin(GL_QUADS);
	glVertex3f(p1->getX(), p1->getZ(), p1->getY());
	glVertex3f(p2->getX(), p2->getZ(), p2->getY());
	glVertex3f(p3->getX(), p3->getZ(), p3->getY());
	glVertex3f(p4->getX(), p4->getZ(), p4->getY());
	glEnd();

	if (desenharContorno) {
		desenharContorno3d(p1, p2, p3, p4);
	}
}

void Rectangle::desenharAlto3d(float altura, bool desenharContorno) {
	Ponto* p1 = new Ponto(-this->width / 2.0, 0, this->height);
	Ponto* p2 = new Ponto(this->width / 2.0, 0, this->height);
	Ponto* p3 = new Ponto(this->width / 2.0, altura, this->height);
	Ponto* p4 = new Ponto(-this->width / 2.0, altura, this->height);

	glBegin(GL_QUADS);
	glVertex3f(p1->getX(), p1->getZ(), p1->getY());
	glVertex3f(p2->getX(), p2->getZ(), p2->getY());
	glVertex3f(p3->getX(), p3->getZ(), p3->getY());
	glVertex3f(p4->getX(), p4->getZ(), p4->getY());
	glEnd();

	if (desenharContorno) {
		desenharContorno3d(p1, p2, p3, p4);
	}
}

void Rectangle::desenharFrente3d(float altura, bool desenharContorno) {
	Ponto* p1 = new Ponto(-this->width / 2.0, altura, 0);
	Ponto* p2 = new Ponto(this->width / 2.0, altura, 0);
	Ponto* p3 = new Ponto(this->width / 2.0, altura, this->height);
	Ponto* p4 = new Ponto(-this->width / 2.0, altura, this->height);

	glBegin(GL_QUADS);
	glVertex3f(p1->getX(), p1->getZ(), p1->getY());
	glVertex3f(p2->getX(), p2->getZ(), p2->getY());
	glVertex3f(p3->getX(), p3->getZ(), p3->getY());
	glVertex3f(p4->getX(), p4->getZ(), p4->getY());
	glEnd();

	if (desenharContorno) {
		desenharContorno3d(p1, p2, p3, p4);
	}
}

void Rectangle::desenharCostas3d(float altura, bool desenharContorno) {
	Ponto* p1 = new Ponto(-this->width / 2.0, altura, 0);
	Ponto* p2 = new Ponto(this->width / 2.0, altura, 0);
	Ponto* p3 = new Ponto(this->width / 2.0, altura, this->height);
	Ponto* p4 = new Ponto(-this->width / 2.0, altura, this->height);

	glBegin(GL_QUADS);
	glVertex3f(p1->getX(), p1->getZ(), p1->getY());
	glVertex3f(p2->getX(), p2->getZ(), p2->getY());
	glVertex3f(p3->getX(), p3->getZ(), p3->getY());
	glVertex3f(p4->getX(), p4->getZ(), p4->getY());
	glEnd();

	if (desenharContorno) {
		desenharContorno3d(p1, p2, p3, p4);
	}

}

void Rectangle::desenharLateralDireita3d(float altura, bool desenharContorno) {

	Ponto* p1 = new Ponto(this->width / 2.0, 0, 0);
	Ponto* p2 = new Ponto(this->width / 2.0, 0, this->height);
	Ponto* p3 = new Ponto(this->width / 2.0, altura, this->height);
	Ponto* p4 = new Ponto(this->width / 2.0, altura, 0);

	glBegin(GL_QUADS);
	glVertex3f(p1->getX(), p1->getZ(), p1->getY());
	glVertex3f(p2->getX(), p2->getZ(), p2->getY());
	glVertex3f(p3->getX(), p3->getZ(), p3->getY());
	glVertex3f(p4->getX(), p4->getZ(), p4->getY());
	glEnd();

	if (desenharContorno) {
		desenharContorno3d(p1, p2, p3, p4);
	}
}

void Rectangle::desenharLateralEsquerda3d(float altura, bool desenharContorno) {
	Ponto* p1 = new Ponto(-this->width / 2.0, 0, 0);
	Ponto* p2 = new Ponto(-this->width / 2.0, 0, this->height);
	Ponto* p3 = new Ponto(-this->width / 2.0, altura, this->height);
	Ponto* p4 = new Ponto(-this->width / 2.0, altura, 0);

	glBegin(GL_QUADS);
	glVertex3f(p1->getX(), p1->getZ(), p1->getY());
	glVertex3f(p2->getX(), p2->getZ(), p2->getY());
	glVertex3f(p3->getX(), p3->getZ(), p3->getY());
	glVertex3f(p4->getX(), p4->getZ(), p4->getY());
	glEnd();

	if (desenharContorno) {
		desenharContorno3d(p1, p2, p3, p4);
	}
}

void Rectangle::desenharRectangle3d(float R, float G, float B, float altura,
		bool desenharContorno) {
	glColor3f(R, G, B);
	desenharBaixo3d(altura, desenharContorno);
	glColor3f(R, G, B);
	desenharAlto3d(altura, desenharContorno);

	glColor3f(R, G, B);
	desenharCostas3d(altura, desenharContorno);
	glColor3f(R, G, B);
	desenharFrente3d(0, desenharContorno);

	glColor3f(R, G, B);
	desenharLateralEsquerda3d(altura, desenharContorno);
	glColor3f(R, G, B);
	desenharLateralDireita3d(altura, desenharContorno);

	glColor3f(R, G, B);
}

void Rectangle::desenharRectangle3d(float height, float width, float R, float G,
		float B, bool desenharContorno) {
	glColor3f(R, G, B);
	glBegin(GL_QUADS);
	glVertex2f(-width / 2.0, 0.0);                        // Top Left
	glVertex2f(-width / 2.0, height);               // Bottom Left
	glVertex2f(width / 2.0, height);               // Bottom Right
	glVertex2f(width / 2.0, 0.0);                // Top Right
	glEnd();

	if (desenharContorno == true) {
		this->desenharContorno2d(0.0, 0.0, 0.0);
	}
}

bool Rectangle::detectarRectangle(float x, float y) {
	if (x > this->getX() && x < (this->getX() + this->getWidth())) {

		if (y > this->getY() && y < (this->getY() + this->getHeight())) {

			return true;
		}
	}
	return false;
}

// Getters and Setters
float Rectangle::getX() {
	return this->x;
}

void Rectangle::setX(float x) {
	this->x = x;
}

float Rectangle::getY() {
	return this->y;
}

void Rectangle::setY(float y) {
	this->y = y;
}

float Rectangle::getWidth() {
	return this->width;
}

void Rectangle::setWidth(float width) {
	this->width = width;
}

float Rectangle::getHeight() {
	return this->height;
}

void Rectangle::setHeight(float height) {
	this->height = height;
}

string Rectangle::getFill() {
	return this->fill;
}

void Rectangle::setFill(string fill) {
	this->fill = fill;
}

int Rectangle::getStrokeWidth() {
	return this->stroke_width;
}

void Rectangle::setStrokeWidth(int stroke_width) {
	this->stroke_width = stroke_width;
}

string Rectangle::getStroke() {
	return this->stroke;
}

void Rectangle::setStroke(string stroke) {
	this->stroke = stroke;
}

string Rectangle::getId() {
	return this->id;
}

void Rectangle::setId(string id) {
	this->id = id;
}
