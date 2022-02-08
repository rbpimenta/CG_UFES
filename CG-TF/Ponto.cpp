#include "Ponto.h"

Ponto::Ponto()
{
	this->x = 0.0;
	this->y = 0.0;
	this->z = 0.0;
}

Ponto::Ponto(float x, float y)
{
	this->x = x;
	this->y = y;
	this->z = 0;
}

Ponto::Ponto(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Ponto::~Ponto()
{
}
