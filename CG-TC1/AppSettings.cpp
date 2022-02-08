/*
 * AppSettings.cpp
 *
 *  Created on: 20/08/2015
 *      Author: rodrigo
 */

#include "AppSettings.h"
#include "tinyxml2.h"

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;
using namespace tinyxml2;

AppSettings::AppSettings() {
	// TODO Auto-generated constructor stub
	this->numeroDeVertices = 0;
}

AppSettings::~AppSettings() {
	// TODO Auto-generated destructor stub
}

void AppSettings::load(char** path) {
	XMLDocument* doc = new XMLDocument();

	// Buscando arquivo de configuração
	string strPath = path[1];
	strPath = strPath + "config.xml";

	const char* pFilename = NULL;
	pFilename = strPath.data();


	if (doc->LoadFile(pFilename) == XML_ERROR_FILE_NOT_FOUND) {
		printf ("Erro na hora de abrir arquivo! Finalizando programa...\n");
		exit(1);
	}

	XMLElement* aplicacao = doc->FirstChildElement("aplicacao");
	if (aplicacao == NULL) {
		printf ("Erro na hora de encontrar Element 'aplicacao'! Finalizando programa...\n");
		exit (1);
	}

	XMLElement* poligono = aplicacao->FirstChildElement("poligono");
	if (poligono == NULL) {
		printf ("Erro na hora de encontrar Element 'poligono'! Finalizando programa...\n");
		exit (1);
	}

	// definindo o número de vértices do nosso polígono
	int numeroDeVertices = 0;
	poligono->QueryIntAttribute("numeroDeVertices", &numeroDeVertices);
	this->numeroDeVertices = numeroDeVertices;

	// Programa só deve continuar se tiver 3 ou mais vértices
	if (this->numeroDeVertices < 3) {
		printf ("Saindo do programa! Número de vértices deve ser maior que 3!\n");
		exit(1);
	}

	// Definindo os vértices do nosso polígono
	XMLElement* vertice = poligono->FirstChildElement("vertice");
	int i, id;
	float coordX, coordY;

	for (i = 0; i < this->numeroDeVertices; i++) {
		vertice->QueryIntAttribute("id", &id);
		vertice->QueryFloatAttribute("coordX", &coordX);
		vertice->QueryFloatAttribute("coordY", &coordY);

		Ponto* p = new Ponto(coordX, coordY, id);
		this->vertices.push_back(*p);

		vertice = vertice->NextSiblingElement("vertice");
	}

	// Realiza um sort no vetor de vértices para ordenar o mesmo
	// de acordo com o número do identificador
	std::sort (this->vertices.begin(), this->vertices.end(), Ponto::compara);

	//printf ("Config.xml loaded!\n");
}

void AppSettings::showValues() {
	printf ("Imprimindo valores:\n");
	printf ("Polígono\n");
	printf ("Número de Vértices: %d\n", this->numeroDeVertices);

	vector<Ponto>::iterator it;

	for (it = this->vertices.begin(); it != this->vertices.end(); it++) {
		printf ("Vertice : identificador-> %d, x-> %f, y-> %f\n", it->getIdentificador(),it->getX(), it->getY());
	}

}
