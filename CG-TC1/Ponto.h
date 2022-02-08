/*
 * Ponto.h
 *
 *  Created on: 20/08/2015
 *      Author: rodrigo
 */

#ifndef PONTO_H_
#define PONTO_H_

using namespace std;

class Ponto {
protected:
	float x;
	float y;
	int identificador;

public:
	Ponto(int x, int y, int id);
	virtual ~Ponto();
	float getX();
	void setX(float x);
	float getY();
	void setY(float y);
	int getIdentificador();
	void setIdentificador(int id);

	/*bool operator < (const Ponto p) {
		return (this->identificador < p.identificador);
	}*/

	static bool compara (const Ponto& p1, const Ponto& p2) {
		return (p1.identificador < p2.identificador);
	}
};


#endif /* PONTO_H_ */
