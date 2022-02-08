/*
 * AppSettings.h
 *
 *  Created on: 20/08/2015
 *      Author: rodrigo
 */

#ifndef APPSETTINGS_H_
#define APPSETTINGS_H_

#include "Ponto.h"
#include <vector>

class AppSettings {
protected:
	int numeroDeVertices;

public:
	vector<Ponto> vertices;
	AppSettings();
	virtual ~AppSettings();
	void load (char** path);
	void showValues ();
};

#endif /* APPSETTINGS_H_ */
