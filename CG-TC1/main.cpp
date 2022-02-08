/*
 * main.cpp
 *
 *  Created on: 19/08/2015
 *      Author: rodrigo
 */

#include "tinyxml2.h"

#include "Ponto.h"
#include "AppSettings.h"

#include <cstdlib>
#include <stdlib.h>
#include <cstring>
#include <ctime>
#include <math.h>

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

// Definindo as cores
#define GREEN 0.0, 1.0, 0.0
#define RED 1.0, 0.0, 0.0
#define BLUE 0.0, 0.0, 1.0
#define BLACK 0.0, 0.0, 0.0

// Variáveis referentes ao tamanho da tela
#define DISPLAY_WIDTH 500
#define DISPLAY_HEIGHT 500

// Tamanho do ponto
#define POINT_SIZE 3

// Distância mínima para modificar um vértice
#define POINT_DISTANCE 10.0

using namespace std;
using namespace tinyxml2;

AppSettings* appSettings = new AppSettings();

// Variável que representa quais os pontos do polígono
vector<Ponto> poligono;

// Vértices
float globalX, globalY;

// Variáveis de apoio
bool firstMouseClicked = false, insercaoVertices = false;
bool alteracaoVertices = false, movement = false;


// Seleciona o vértice
int idVerticeEscolhido = 0;

void init(void) {
	// Selecionar cor de fundo (preto)
	glClearColor(0.0, 0.0, 0.0, 0.0);

	// Inicializar sistema de viz
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, DISPLAY_WIDTH, DISPLAY_HEIGHT, 0.0, 0.0, 1.0);
}

void desenharPoligono(bool primeiraVez) {

	// seta a cor do poligono como verde
	glColor3f(GREEN);

	glBegin(GL_POLYGON);

	vector<Ponto>::iterator it;

	float auxX, auxY;

	if (primeiraVez) {
		for (it = appSettings->vertices.begin();
				it != appSettings->vertices.end(); it++) {


			auxX = globalX + it->getX();
			auxY = globalY + it->getY();

			// Insere os pontos do polígono na variável global Polígonos
			Ponto* p = new Ponto(auxX, auxY, it->getIdentificador());
			poligono.push_back(*p);

			glVertex3f(auxX, auxY, 0.0);
		}
	} else {
		for (it = poligono.begin(); it != poligono.end(); it++) {
			glVertex3f(it->getX(), it->getY(), 0.0);
		}
	}

	glEnd();
}

void desenharLinhas() {
	glColor3f(RED);
	vector<Ponto>::iterator it;

	glBegin(GL_LINE_LOOP);
	for (it = poligono.begin(); it != poligono.end(); it++) {
		glVertex3f(it->getX(), it->getY(), 0.0);
	}
	glEnd();
}

void desenharPontos() {
	glColor3f(BLUE);

	vector<Ponto>::iterator it;
	glPointSize(POINT_SIZE);
	glBegin(GL_POINTS);

	for (it = poligono.begin(); it != poligono.end(); it++) {
		glVertex3f(it->getX(), it->getY(), 0.0);
	}

	glEnd();
}

void display(void) {

	glClear(GL_COLOR_BUFFER_BIT);
	vector<Ponto>::iterator it;

	if (insercaoVertices) {
		desenharPoligono(true);
		desenharLinhas();
		desenharPontos();
		insercaoVertices = false;
		alteracaoVertices = true;

	} else if (alteracaoVertices) {

		desenharPoligono(false);
		desenharLinhas();
		desenharPontos();
	}

	glutSwapBuffers();
}

void idle(void) {
	glutPostRedisplay();
}

/*
 * Método responsável por retornar a distância de um
 * vértice até o ponto x e y
 */
float calcularDistancia(int xSelecionado, int ySelecionado, float xPoligono,
		float yPoligono, int idPoligono) {

	float distX = powf((double) xSelecionado - xPoligono, (double) 2);
	float distY = powf((double) ySelecionado - yPoligono, (double) 2);

	if (distX < 0) {
		distX = distX * (-1);
	}

	if (distY < 0) {
		distY = distY * (-1);
	}

	float distancia = sqrt(distX + distY);
	return distancia;
}

void mouse(int button, int state, int x, int y) {

	if (state == GLUT_DOWN) {
		// Entrando no modo de inserção de vértices
		if (firstMouseClicked == false) {
			globalX = (float) x;
			globalY = (float) y;

			firstMouseClicked = true;
			insercaoVertices = true;
			alteracaoVertices = false;
		} else {
			movement = false;
			// Modo de edição de vértices
			vector<Ponto>::iterator it;

			float menorDistancia = 0.0f, distanciaCalculada = 0.0f;

			for (it = poligono.begin(); it != poligono.end(); it++) {
				distanciaCalculada = calcularDistancia(x, y, it->getX(),
						it->getY(), it->getIdentificador());

				if (menorDistancia == 0.0) {
					menorDistancia = distanciaCalculada;
					idVerticeEscolhido = it->getIdentificador();
				} else if (distanciaCalculada < menorDistancia) {

					idVerticeEscolhido = it->getIdentificador();
					menorDistancia = distanciaCalculada;
				}
			}

			// Modificar valor do vector poligono se a
			// menor distância for menor que POINT_DISTANCE
			if (menorDistancia <= POINT_DISTANCE && idVerticeEscolhido != 0) {
				poligono.at(idVerticeEscolhido - 1).setX((float) x);
				poligono.at(idVerticeEscolhido - 1).setY((float) y);
				movement = true;
			}
		}
	}
}

void mouseMove(int x, int y) {
	if (movement == true) {

		poligono.at(idVerticeEscolhido - 1).setX((float) x);
		poligono.at(idVerticeEscolhido - 1).setY((float) y);
	}
}

int main(int argc, char** argv) {

// Abrindo arquivo de configuração
	appSettings->load(argv);

// Iniciando tela e demais variáveis
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowSize(DISPLAY_WIDTH, DISPLAY_HEIGHT);
	glutInitWindowPosition(100, 100);

	glutCreateWindow("Trabalho 1");

// Inicializa a janela
	init();

	glutDisplayFunc(display);
	glutIdleFunc(idle);

	glutMouseFunc(mouse);
	glutMotionFunc(mouseMove);

	glutMainLoop();

	return 0;
}
