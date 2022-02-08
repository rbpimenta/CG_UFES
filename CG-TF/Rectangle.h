/*
 * Arena.h
 *
 *  Created on: 14/09/2015
 *      Author: rodrigo
 */

#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include <iostream>
#include "tinyxml2.h"
#include "Ponto.h"

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

using namespace std;
using namespace tinyxml2;

class Rectangle {
protected:
	float x; // posição em X
	float y; // posição em Y

	float width; // comprimento
	float height; // altura

	string fill;
	int stroke_width; // Comprimento da linha
	string stroke;

	string id; // Identificador

public:
	Rectangle();
	virtual ~Rectangle();
	void showValues();
	void setValues(XMLElement* elem);
	
	void desenharRectangle2d (float height, float width, float R, float G, float B, bool desenharContorno);
	void desenharRectangle2d (float R, float G, float B, bool desenharContorno);
	void desenharContorno2d (float R, float G, float B);
	void desenharRectangle3d (float height, float width, float R, float G, float B, bool desenharContorno);


	void desenharBaixo3d (float altura, bool desenharContorno);
	void desenharAlto3d (float altura, bool desenharContorno);
	void desenharFrente3d (float altura, bool desenharContorno);
	void desenharCostas3d (float altura, bool desenharContorno);
	void desenharLateralDireita3d (float altura, bool desenharContorno);
	void desenharLateralEsquerda3d (float altura, bool desenharContorno);
	void desenharRectangle3d (float R, float G, float B, float altura, bool desenharContorno);

	void desenharContorno3d (Ponto* p1, Ponto* p2, Ponto* p3, Ponto* p4);

	bool detectarRectangle (float x, float y);

	// Getters and Setters
	float getX ();
	void setX (float x);
	float getY ();
	void setY (float y);

	float getWidth ();
	void setWidth (float width);
	float getHeight ();
	void setHeight (float height);

	string getFill ();
	void setFill (string fill);
	int getStrokeWidth ();
	void setStrokeWidth (int stroke_width);
	string getStroke ();
	void setStroke (string stroke);
	string getId ();
	void setId (string id);

};

#endif /* RECTANGLE_H_ */
