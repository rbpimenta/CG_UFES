#include "Tiro.h"

Tiro::Tiro() {
	transformacao = new Transformacao();

	this->velocidadeTiro = 0.0;
	this->tiro = new Circle();

	this->fatorEscala = 0.0;
	this->fatorEscalaInverso = 0.0;
	this->cx = 0.0;
	this->cy = 0.0;
	this->cz = 0.0;
	this->raio = 0.0;
	this->anguloGiro = 0.0;
	this->anguloMira = 0.0;
	this->posX = 0.0;
	this->posY = 0.0;
	this->anguloGiro = 0.0;

}

Tiro::Tiro(float fatorEscala, float fatorEscalaInverso, float cx, float cy,float cz,
		float raio, float anguloGiro, float anguloMira, float miraHeight,
		float posX, float posY) {
	transformacao = new Transformacao(fatorEscala, cx, cy, raio, anguloGiro,
			anguloMira, miraHeight, posX, posY);

	this->velocidadeTiro = 0.0;
	this->tiro = new Circle();

	this->fatorEscala = fatorEscala;
	this->fatorEscalaInverso = fatorEscalaInverso;
	this->cx = cx;
	this->cy = cy;
	this->cz = cz;
	this->raio = raio;
	this->anguloGiro = anguloGiro;
	this->anguloMira = anguloMira;
	this->posX = posX;
	this->posY = posY;
	this->miraHeight = miraHeight;

}

Tiro::~Tiro() {
}

void Tiro::carregarInformacoes() {
	XMLDocument* doc = new XMLDocument();

	doc->LoadFile("tiro.svg");

	if (doc == NULL) {
		cout << "Problema ao abrir arquivo .svg\n";
		exit(1);
	}

	XMLElement* svg = doc->FirstChildElement("svg");
	if (svg == NULL) {
		cout
				<< "Erro na hora de encontrar Element 'svg'! Finalizando programa...\n";
		exit(1);
	}

	XMLElement* circleElem = svg->FirstChildElement("circle");
	if (circleElem == NULL) {
		cout
				<< "Erro na hora de encontrar Element 'circle'! Finalizando programa...\n";
		exit(1);
	}

	this->tiro->setValues(circleElem);
}

void Tiro::desenharTiro(bool vision3d, float altura) {

	if (this->transformacao != NULL) {
		this->transformacao->definirTransformacao(fatorEscala, this->cx,
				this->cy, this->cz, this->raio, this->anguloGiro, this->anguloMira,
				this->miraHeight, this->posX, this->posY);
		this->transformacao->iniciarTransformacao(true, false);
	}

	float zTranslated = 1000;
	glTranslatef(0, 0, zTranslated);

	if (vision3d) {
		glPushMatrix();
			glutSolidSphere(this->tiro->getR(), 50, 50);
		glPopMatrix();
	} else {
		this->tiro->desenharCircle(0.0, 0.0, 0.0);
	}

	this->transformacao->fecharTransformacao();
}

bool Tiro::verificarLimites(float limiteSuperior, float limiteInferior,
		float limiteEsquerdo, float limiteDireito) {
	if (this->posX > limiteDireito || this->posX < limiteEsquerdo
			|| this->posY < limiteSuperior || this->posY > limiteInferior) {
		return false;
	} else
		return true;
}

void Tiro::movimentarParaFrente() {
	this->posX = this->posX
			+ this->velocidadeTiro
					* cos(
							(270 + this->anguloGiro) * M_PI / 180
									+ (this->anguloMira) * M_PI / 180);
	this->posY += this->velocidadeTiro
			* sin(
					(270 + this->anguloGiro) * M_PI / 180
							+ (this->anguloMira) * M_PI / 180);
}

void Tiro::movimentarParaTras() {
	this->posX -= this->velocidadeTiro
			* cos(
					(270 + this->anguloGiro) * M_PI / 180
							+ (this->anguloMira) * M_PI / 180);
	this->posY -= this->velocidadeTiro
			* sin(
					(270 + this->anguloGiro) * M_PI / 180
							+ (this->anguloMira) * M_PI / 180);
}

void Tiro::showValues() {
	cout << "Tiro\n";
	this->tiro->showValues();
	cout << "Velocidade Tiro: " << this->velocidadeTiro << "\n";
}
