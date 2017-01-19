#ifndef V8INTERFACE_H
#define V8INTERFACE_H

#include "PowerSource.h"
#include <string>

class V8interface : public PowerSource, private V8Classic{

public: 
	
	V8interface(string typ) : PowerSource(typ), V8Classic(){}
	~V8interface();
	 bool isRunning() const;
	 bool tryStart();
	 bool stop();
	 bool incPower(int p);
	 bool decPower(int p);





};


#endif

#ifndef GASTURBINEINTERFACE_H
#define GASTURBINEINTERFACE_H


class GasturbineInterface : public PowerSource, private GasTurbine{

public: 
	GasturbineInterface(string typ) : PowerSource(typ), GasTurbine(){}
	~GasturbineInterface();

	bool isRunning() const;
	bool tryStart();
	bool stop();
	bool incPower(int p);
	bool decPower(int p);



};





#endif