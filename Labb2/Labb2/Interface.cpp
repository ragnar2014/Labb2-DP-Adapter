#include "Interface.h"


V8interface::~V8interface(){}

bool V8interface::isRunning()const {

	return V8Classic::isRunning();


}

bool V8interface::tryStart(){

	V8Classic::ignitionOn();
	V8Classic::chokeOn();
	V8Classic::setThrottle(30);
	V8Classic::runStarter();
	if (V8Classic::isRunning())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool V8interface::stop(){

	if (V8Classic::setThrottle(0)){
		V8Classic::ignitionOff();
		return true;

	}
	else
	{
		return false;
	}

}

bool V8interface::incPower(int p){

	int thrott= V8Classic::getThrottle();
	p = p + thrott;
	return V8Classic::setThrottle(p);

}

bool V8interface::decPower(int p){

	int thrott = V8Classic::getThrottle();
	p = thrott-p;
	return V8Classic::setThrottle(thrott);

}

/*GASTURBINEINTERFACE*/

GasturbineInterface::~GasturbineInterface(){}

bool GasturbineInterface::tryStart(){

	if (GasTurbine::startCompressors())
	{
		if (GasTurbine::setCompressorPressure(30) && GasTurbine::burnerOn())
		{
			if (isRunning())
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}

	else
	{
		return false;
	}
	


}

bool GasturbineInterface::stop(){


	if (GasTurbine::setCompressorPressure(0))
	{
		if (GasTurbine::stopCompressors() && GasTurbine::burnerOff())
		{
			return true;
		}

		else
		{
			return false;
		}

	}

	else
	{
		return false;
	}
}

bool GasturbineInterface::isRunning() const{

	return GasTurbine::isRunning();




}

bool GasturbineInterface::incPower(int p){

	int thrott = GasTurbine::getCompressorPressure();
	p = p + thrott;
	return GasTurbine::setCompressorPressure(p);

}

bool GasturbineInterface::decPower(int p){

	int thrott = GasTurbine::getCompressorPressure();
	p = thrott - p;
	return GasTurbine::setCompressorPressure(thrott);

}