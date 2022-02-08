#ifndef PONTO_H
#define PONTO_H

class Ponto {
protected:
	float x;
	float y;
	float z;
public:
	Ponto();
	Ponto(float x, float y);
	Ponto(float x, float y, float z);
	~Ponto();

	// Getters and Setters
	float getX() {
		return this->x;
	}
	void setX(float x) {
		this->x = x;
	}
	float getY() {
		return this->y;
	}
	void setY(float y) {
		this->y = y;
	}
	Ponto* getPonto() {
		return this;
	}

	float getZ() {
		return z;
	}

	void setZ(float z) {
		this->z = z;
	}
};

#endif

