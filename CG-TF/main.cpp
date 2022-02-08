/*
 * main.cpp
 *
 *  Created on: 13/09/2015
 *      Author: rodrigo
 */

#include "tinyxml2.h"
#include "AppSettings.h"
#include "Rectangle.h"
#include "Circle.h"

#include <cstdlib>
#include <stdlib.h>
#include <cstring>
#include <ctime>
#include <math.h>

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <math.h>

// Variáveis referentes ao tamanho da tela
float DISPLAY_WIDTH = 0;
float DISPLAY_HEIGHT = 0;

AppSettings* appSettings = new AppSettings();

// Vértices
float globalX = 0.0, globalY = 0.0;

int keyStatus[256];

// Atributos da camera
float camPosition[3] = { 0, 0, 0 };
float camLook[3] = { 0, 0, 0 };
float camUp[3] = { 0, 0, 0 };
int camType = 0;

using namespace std;
using namespace tinyxml2;

void keyPress(unsigned char key, int x, int y) {
	switch (key) {
	case '+':
		keyStatus['+'] = 1;
		break;
	case '-':
		keyStatus['-'] = 1;
		break;
	case 'w':
		keyStatus['w'] = 1;
		break;
	case 's':
		keyStatus['s'] = 1;
		break;
	case 'a':
		keyStatus['a'] = 1;
		break;
	case 'd':
		keyStatus['d'] = 1;
		break;
	case '1':
		keyStatus['1'] = 1;
		break;
	case '2':
		keyStatus['2'] = 1;
		break;
	case '3':
		keyStatus['3'] = 1;
		break;
	case '0':
		keyStatus['0'] = 1;
		break;

	}
	glutPostRedisplay();
}

void keyup(unsigned char key, int x, int y) {
	keyStatus[(int) (key)] = 0;
	glutPostRedisplay();
}

void idle(void) {
	// Detecta os limites da arena
	Rectangle* dadosArena = appSettings->getDadosArena();

	float limiteSuperior = dadosArena->getY();
	float limiteInferior = dadosArena->getY() + dadosArena->getHeight();
	float limiteEsquerdo = dadosArena->getX();
	float limiteDireito = dadosArena->getX() + dadosArena->getWidth();

	if (keyStatus['1'] == 1) {
		camType = 1;
	}

	if (keyStatus['2'] == 1) {
		camType = 2;
	}

	if (keyStatus['3'] == 1) {
		camType = 3;
	}

	if (keyStatus['0'] == 1) {
		camType = 0;
	}

	if (keyStatus['+'] == 1) {
		appSettings->getJogador()->aumentarGiroHelices();
	}

	if (keyStatus['-'] == 1) {

		appSettings->getJogador()->diminuirGiroHelices();
	}

	if (keyStatus['w'] == 1) {
		// so movimenta o helicoptero se o mesmo estiver dentro da arena
		appSettings->getJogador()->moverParaFrente(limiteSuperior,
				limiteInferior, limiteEsquerdo, limiteDireito,
				appSettings->getInimigos(), appSettings->getJogador());
	}

	if (keyStatus['s'] == 1) {
		// so movimenta o helicoptero se o mesmo estiver dentro da arena
		appSettings->getJogador()->moverParaTras(limiteSuperior, limiteInferior,
				limiteEsquerdo, limiteDireito, appSettings->getInimigos(),
				appSettings->getJogador());
	}

	if (keyStatus['a'] == 1) {
		if (appSettings->vision3d)
			appSettings->getJogador()->rotacionarDireita();
		else
			appSettings->getJogador()->rotacionarEsquerda();

	}

	if (keyStatus['d'] == 1) {
		if (appSettings->vision3d)
			appSettings->getJogador()->rotacionarEsquerda();
		else
			appSettings->getJogador()->rotacionarDireita();

	}

	appSettings->getJogador()->moverHelice();
	appSettings->getJogador()->movimentarTiros(limiteSuperior, limiteInferior,
			limiteEsquerdo, limiteDireito);

	int i = 0;
	Helicoptero* inimigo;
	for (i = 0; i < appSettings->getQuantidadeInimigos(); i++) {
		inimigo = &(appSettings->getInimigos()->at(i));
		inimigo->moverHelice();
		inimigo->movimentarTiros(limiteSuperior, limiteInferior, limiteEsquerdo,
				limiteDireito);
	}

	// Verifica os tiros dos helicopteros
	appSettings->verificaTiros();

	// Atualiza o combustível do jogador
	appSettings->getJogador()->atualizarCombustivel(
			appSettings->getPostoAbastecimento());

	// Verificando quantos objetos foram resgatados
	int objetosResgatados = 0;
	objetosResgatados = appSettings->getJogador()->resgatarObjeto(
			appSettings->getObjetosResgate());

	// Definindo quantos objetos de resgate ainda faltam
	appSettings->objetosAindaDevemSerResgatados -= objetosResgatados;
	objetosResgatados = 0;

	// movimentar helicopteros inimigos
	appSettings->movimentarHelicopterosInimigos(limiteSuperior, limiteInferior,
			limiteEsquerdo, limiteDireito);

	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {

	if (state == GLUT_DOWN) {
		globalX = (float) x;
		globalY = (float) y;

		if (button == GLUT_RIGHT_BUTTON) {
			appSettings->getJogador()->mudarEscalaMovimento();
		}
		if (button == GLUT_LEFT_BUTTON) {
			appSettings->getJogador()->realizarTiro(appSettings->getTiro());
		}
	}
}

void mouseMove(int x, int y) {
	appSettings->getJogador()->rotacionarMira(x, y, appSettings->vision3d);
}

// 0 -> superior
// 1 -> atrás do helicoptero
void mudarCamera(int cameraPosition) {
	if (cameraPosition == 0) {
		//visão superior
		camPosition[0] = appSettings->getJogador()->dadosCircle->getCx();
		camPosition[1] = appSettings->getJogador()->dadosCircle->getCy();
		camPosition[2] = 400;

		camLook[0] = appSettings->getJogador()->dadosCircle->getCx() - 1;
		camLook[1] = appSettings->getJogador()->dadosCircle->getCy() - 1;
		camLook[2] = 0;

		camUp[0] = 0;
		camUp[1] = 1;
		camUp[2] = 0;

	} else if (cameraPosition == 1) {
		Helicoptero* jogador;
		jogador = appSettings->getJogador();

		// camera cokpit
		camPosition[0] = jogador->dadosCircle->getCx();
		camPosition[1] = jogador->dadosCircle->getCy();
		camPosition[2] = jogador->cz*2;// jogador->corpo->getHeight() * 2;

		camLook[0] = jogador->dadosCircle->getCx()
				+ 50 * (jogador->corpo->getWidth())
						* cos((-90 + jogador->anguloGiro) * M_PI / 180);
		camLook[1] = jogador->dadosCircle->getCy()
				+ 50 * (jogador->corpo->getWidth())
						* sin((-90 + jogador->anguloGiro) * M_PI / 180);
		camLook[2] = jogador->corpo->getHeight();//jogador->corpo->getHeight();

		camUp[0] = 0;
		camUp[1] = 0;
		camUp[2] = 1;
	} else if (cameraPosition == 2) {
		//visão atrás do helicoptero

		camPosition[0] = appSettings->getJogador()->dadosCircle->getCx();
		camPosition[1] = appSettings->getJogador()->dadosCircle->getCy() - 200;
		camPosition[2] = 100;

		camLook[0] = appSettings->getJogador()->dadosCircle->getCx() - 1;
		camLook[1] = appSettings->getJogador()->dadosCircle->getCy() - 1;
		camLook[2] = 0;

		camUp[0] = 0;
		camUp[1] = 1;
		camUp[2] = 0;

	} else {
		mudarCamera(1);
	}

}

void display(void) {
	if (appSettings->vision3d) {

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		mudarCamera(camType);

		gluLookAt(camPosition[0], camPosition[1], camPosition[2], camLook[0],
				camLook[1], camLook[2], camUp[0], camUp[1], camUp[2]);

		appSettings->desenharObjetos();

		glutSwapBuffers();
	} else {
		glClear(GL_COLOR_BUFFER_BIT);

		appSettings->desenharObjetos();

		glutSwapBuffers();
	}
}

void init(void) {
	if (appSettings->vision3d) {
		// Selecionar cor de fundo (preto)
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glEnable(GL_DEPTH_TEST);

		// Inicializar sistema de viz
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		//glOrtho(0.0, DISPLAY_WIDTH, DISPLAY_HEIGHT, 0.0, 0.0, 1.0);
		//glViewport(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT);
		//gluPerspective(60, 1, 0.01, 500);
		gluPerspective(60, 1, 0.01, 800);

		glMatrixMode(GL_MODELVIEW);
	} else {
		// Selecionar cor de fundo (preto)
		glClearColor(0.0, 0.0, 0.0, 0.0);

		// Inicializar sistema de viz
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0.0, DISPLAY_WIDTH, DISPLAY_HEIGHT, 0.0, 0.0, 1.0);
	}
}

int main(int argc, char** argv) {
	appSettings->loadConfigXML(argv);
	appSettings->loadSvgFile();

	appSettings->carregarDadosCombustivel();
	appSettings->carregarInformacoesHelicopteros();
	appSettings->carregarInformacoesArena();

	// Iniciando tela e demais variáveis
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// Setando variáveis da tela
	DISPLAY_WIDTH = appSettings->getDadosArena()->getWidth();
	DISPLAY_HEIGHT = appSettings->getDadosArena()->getHeight();

	glutInitWindowSize(DISPLAY_WIDTH, DISPLAY_HEIGHT);
	glutInitWindowPosition(100, 100);

	glutCreateWindow("Trabalho 3");

	appSettings->vision3d = true;

	// Inicializa a janela
	init();
	glutDisplayFunc(display);
	glutIdleFunc(idle);

	glutKeyboardFunc(keyPress);
	glutKeyboardUpFunc(keyup);

	glutMouseFunc(mouse);
	glutPassiveMotionFunc(mouseMove);

	glutMainLoop();

	return 0;
}
