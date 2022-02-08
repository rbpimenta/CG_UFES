#include "Helicoptero.h"

Helicoptero::Helicoptero()
{
	// Inicializando velocidades
	this->velocidadeHelicoptero = 0.0;
	
	// Movimenta��o
	this->posX = 0.0;
	this->posY = 0.0;
	this->anguloGiro = 0.0;
	this->escalaHelicoptero = 1.0;
	this->enableMovimento = false;
	
	// Transformacao
	this->fatorEscala = 0.0;
	float cx = 0.0;
	float cy = 0.0;
	float raio = 0.0;
	
	// Helices
	this->velocidadeHelices = 0.5;
	this->anguloHelices = 0.0;
	this->aceleracaoHelices = 0.5;
	
	// Tiros
	this->tiros = new vector<Tiro>();
	
	// mira
	this->anguloMira = 0.0;
	this->posMiraAnteriorX = 0.0;
	this->posMiraAnteriorY = 0.0;
	
	// Inicializando vari�veis do corpo
	this->mira = new Rectangle();
	this->corpo = new Rectangle();
	this->cauda = new Rectangle();
	this->caudaEsquerda = new Rectangle();
	this->caudaDireita = new Rectangle();
	this->centroHelice = new Circle();
	this->helices = new vector<Polyline>();
}

Helicoptero::~Helicoptero()
{
}

void Helicoptero::carregarInformacoes() {	
	XMLDocument* doc = new XMLDocument();

	doc->LoadFile("helicoptero.svg");

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

	XMLElement* rectElem = svg->FirstChildElement("rect");

	if (rectElem == NULL) {
		cout
				<< "Erro na hora de encontrar Element 'rect'! Finalizando programa...\n";
		exit(1);
	}
	
		// atributos do tipo rect
	string id = ""; // Identificador
	const char* aux = "";

	while (rectElem != NULL) {
		// set Id
		aux = (rectElem->Attribute("id"));
		id = aux;

		// Carregar Mira
		if (id == "Mira") {
			this->mira->setValues(rectElem);
		} else

		// Carregar Corpo
		if (id == "Corpo") {
			this->corpo->setValues(rectElem);
		} else

		// Carregar Cauda
		if (id == "Cauda") {
			this->cauda->setValues(rectElem);
		}

		// Carregar CaudaEsquerda
		if (id == "CaudaEsq") {
			this->caudaEsquerda->setValues(rectElem);
		}

		// Carregar CaudaDireita
		if (id == "CaudaDir") {
			this->caudaDireita->setValues(rectElem);
		}

		rectElem = rectElem->NextSiblingElement("rect");
	}
	
	// Carregando informa��es do centro da h�lice
	XMLElement* circleElem = svg->FirstChildElement("circle");

	if (circleElem == NULL) {
		cout
				<< "Erro na hora de encontrar Element 'circle'! Finalizando programa...\n";
		exit(1);
	}
	
	this->centroHelice->setValues(circleElem);
	
	// Carregando informa��es da h�lice
	XMLElement* polylineElem = svg->FirstChildElement("polyline");

	if (polylineElem == NULL) {
		cout
				<< "Erro na hora de encontrar Element 'polyline'! Finalizando programa...\n";
		exit(1);
	}
	
	while (polylineElem != NULL) {
		Polyline* p = new Polyline();
		p->setValues(polylineElem);
		this->helices->push_back(*p);
		
		polylineElem = polylineElem->NextSiblingElement("polyline");
	}
}

void Helicoptero::desenharMira() {
	float xTranslated = 0.0;
	float yTranslated = this->mira->getHeight();
	glPushMatrix();
		// mover-se para a base do corpo
		glTranslatef(xTranslated, yTranslated, 0.0);
		glRotatef(this->anguloMira, 0.0, 0.0, 1.0);
		glPushMatrix();
			xTranslated = 0.0;
			yTranslated = -this->mira->getHeight();
			glTranslatef(xTranslated, yTranslated,0.0);

			this->mira->desenharRectangle(this->mira->getHeight(), this->mira->getWidth(), 0.0, 0.0, 0.0);
		glPopMatrix();
		/*
	Add to work on linux
	glPopMatrix();
	*/
}

void Helicoptero::desenharCorpo() {
	float xTranslated = 0.0;
	float yTranslated = this->mira->getHeight();
	glPushMatrix();
		glTranslatef(xTranslated, yTranslated, 0.0);
		this->corpo->desenharRectangle(this->corpo->getHeight(), this->corpo->getWidth(), 0.0, 1.0, 0.0);
	glPopMatrix();
}

void Helicoptero::desenharCaudaDireita() {
	float xTranslated = (this->cauda->getWidth()/2 + this->caudaDireita->getWidth()/2);
	float yTranslated = this->mira->getHeight() + this->corpo->getHeight() + 20;
	glPushMatrix();
		glTranslatef(xTranslated, yTranslated, 0.0);
		this->caudaDireita->desenharRectangle(this->caudaDireita->getHeight(), this->caudaDireita->getWidth(), 0.0, 1.0, 0.0);
	glPopMatrix();
}

void Helicoptero::desenharCaudaEsquerda() {
	float xTranslated = -(this->cauda->getWidth()/2 + this->caudaEsquerda->getWidth()/2);
	float yTranslated = this->mira->getHeight() + this->corpo->getHeight() + 20;
	glPushMatrix();
		glTranslatef(xTranslated, yTranslated, 0.0);
		this->caudaEsquerda->desenharRectangle(this->caudaEsquerda->getHeight(), this->caudaEsquerda->getWidth(), 0.0, 1.0, 0.0);
	glPopMatrix();
}

void Helicoptero::desenharCaudaPrincipal() {
	float xTranslated = 0.0;
	float yTranslated = this->mira->getHeight() + this->corpo->getHeight();
	glPushMatrix();
		// Se movimentar para jun��o entre corpo e cauda
		glTranslatef(xTranslated, yTranslated, 0.0);
		
		// desenhar cauda principal
		this->cauda->desenharRectangle(this->cauda->getHeight(), this->cauda->getWidth(), 0.0, 1.0, 0.0);		
	glPopMatrix();
	
}

void Helicoptero::aumentarGiroHelices() {
	this->velocidadeHelices += this->aceleracaoHelices;
}

void Helicoptero::diminuirGiroHelices() {
	if (this->velocidadeHelices - this->aceleracaoHelices < 0) {
		this->velocidadeHelices = 0.0;
	} else {	
		this->velocidadeHelices -= this->aceleracaoHelices;
	}

}

void Helicoptero::moverHelice() {
	if (this->anguloHelices + this->velocidadeHelices > 360) {
		this->anguloHelices = 0.0;
	} else if (this->anguloHelices + this->velocidadeHelices < 0) {
		this->anguloHelices = 0.0;
	} else {
		this->anguloHelices += this->velocidadeHelices;
	}
}

void Helicoptero::desenharHelices(Circle* c) {
	glPushMatrix();
		// Desconsiderando o giro do corpo, fazendo com que a helice gire independente
		glRotatef(this->anguloHelices - this->anguloGiro, 0.0, 0.0, 1.0);	
		int i = 0;
		Polyline aux;
		for (i = 0; i < 4; i ++) {
			aux = this->helices->at(i);
			aux.desenharPolyline(c, 0.0, 0.0, 1.0);
		}
	glPopMatrix();
}

void Helicoptero::desenharCentroHelice() {
	float xTranslated = 0.0;
	float yTranslated = this->mira->getHeight() + 20;
	glPushMatrix();
		glTranslatef(xTranslated, yTranslated, 0.0);
		this->centroHelice->desenharCircle(this->centroHelice->getR(), 1.0, 1.0, 0.0);
		this->desenharHelices(this->centroHelice);
	glPopMatrix();
}

void Helicoptero::desenharHelicoptero(Circle* c) {
	float fatorEscala = 10/c->getR()*this->escalaHelicoptero;
	
	this->fatorEscala = fatorEscala;
	this->cx = c->getCx();
	this->cy = c->getCy();
	this->raio = c->getR();
	
	float fatorEscalaInverso = 1/fatorEscala;
	float xScale = 0.0;
	float yScale = 0.0;
	float xTranslated = 0.0, yTranslated = 0.0;
		
	glPushMatrix(); // Escala
		// diminuir tamanho do helicoptero de acordo com tamanho do c�rculo
		glScalef(fatorEscala, fatorEscala, 0.0);
	
		xTranslated = this->posX*fatorEscalaInverso;
		yTranslated = this->posY*fatorEscalaInverso;
		
		glTranslatef(xTranslated, yTranslated, 0.0);
		
		glPushMatrix(); 
			xTranslated = (c->getCx() + c->getR())*fatorEscalaInverso;
			yTranslated = (c->getCy())*fatorEscalaInverso;

			// Ir para direita do c�rculo
			glTranslatef(xTranslated, yTranslated, 0.0);
			
			// rotacionar o helicoptero em 90�
			glRotatef(90.0 + this->anguloGiro, 0.0, 0.0, 1.0);
			
			this->desenharMira();
			this->desenharCorpo();
			this->desenharCaudaPrincipal();
			this->desenharCaudaDireita();
			this->desenharCaudaEsquerda();
			this->desenharCentroHelice();
		glPopMatrix(); // fim direita do c�rculo
	glPopMatrix();	// Fim escala
}

void Helicoptero::moverParaFrente() {
	if (this->enableMovimento) {
		this->posX += this->velocidadeHelicoptero*cos(this->anguloGiro*M_PI/180);
		this->posY += this->velocidadeHelicoptero*sin(this->anguloGiro*M_PI/180);
	}
}

void Helicoptero::moverParaTras() {
	if( this->enableMovimento) {
		this->posX -= this->velocidadeHelicoptero*cos(this->anguloGiro*M_PI/180);
		this->posY -= this->velocidadeHelicoptero*sin(this->anguloGiro*M_PI/180);
	}	
}

void Helicoptero::rotacionarEsquerda() {
	if (this->enableMovimento) {
		this->anguloGiro -= velocidadeHelicoptero;
	}
}

void Helicoptero::rotacionarDireita() {
	if (this->enableMovimento) {
		this->anguloGiro += velocidadeHelicoptero;
	}
}

void Helicoptero::mudarEscalaMovimento() {
	if (this->escalaHelicoptero == 1.0) {
		this->escalaHelicoptero = 1.5;
		this->enableMovimento = true;
	} else {
		this->escalaHelicoptero = 1.0;
		this->enableMovimento = false;
	}
}

void Helicoptero::rotacionarMira(float x, float y) {
	if (posMiraAnteriorX > x) {
		rotacionarMiraEsquerda();
	} else {
		rotacionarMiraDireita();
	}
	
	posMiraAnteriorX = x;
	posMiraAnteriorY = y;
}

void Helicoptero::rotacionarMiraDireita() { 
	if (this->enableMovimento) {
		if (this->anguloMira > 44) {
			this->anguloMira = 45;
		} else {
	
			this->anguloMira += (5*this->velocidadeHelicoptero);
		}
	}
}


void Helicoptero::rotacionarMiraEsquerda() { 
	if (this->enableMovimento) {
		if (this->anguloMira < -44) {
			this->anguloMira = -45;
		} else {
	
			this->anguloMira -= (5*this->velocidadeHelicoptero);
		}
	}
	
}

void Helicoptero::realizarTiro(Tiro* t) {
	if (enableMovimento) {
		Tiro* novoTiro = new Tiro(this->fatorEscala, (1/this->fatorEscala), this->cx, this->cy, this->raio, this->anguloGiro, this->anguloMira, this->mira->getHeight(),this->posX, this->posY);
		novoTiro->setTiro(t);
		this->tiros->push_back(*novoTiro);
	}
}

void Helicoptero::mostrarTiros() {
	int i = 0;
	Tiro t;
	if (!this->tiros->empty()) {
		for (i = 0; i < (int)this->tiros->size(); i++) {
			t = tiros->at(i);
			t.desenharTiro();
		}
	}
}

void Helicoptero::movimentarTiros() {
	int i = 0;
	Tiro* t;
	if (!this->tiros->empty()) {
		for (i = 0; i < (int) this->tiros->size(); i++) {
			t = &(this->tiros->at(i));
			t->movimentarParaFrente();
		}
	}
}
