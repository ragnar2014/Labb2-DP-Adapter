//--- PowerSource.cpp  --------------------------------


#include <iostream>

#include "PowerSource.h"

using std::cout;
using std::endl;


// --- V8Classic -----------------------------

void V8Classic::ignitionOn() {
  ignition=true;
  cout << "ignition ON " << endl;
}



void V8Classic::ignitionOff() {
  ignition=false;
  running=false;
  cout << "ignition OFF " << endl;
}



void V8Classic::chokeOn() {
  choke=true;
  cout << "choke ON " << endl;
}



void V8Classic::chokeOff() {
  choke=false;
  cout << "choke OFF " << endl;
}



int V8Classic::getThrottle() const {
  return throttle;
}



bool V8Classic::setThrottle(int t) {
  if(t<0 || t>100)
    return false;
  throttle = t;
  cout << "Throttle is open " << throttle << " % " << endl;
  return true;
}


void V8Classic::runStarter() {
  if(running) {
    cout <<"Already running" << endl;
    return;
  }
  cout << "Running starter...\n";
  if(ignition && choke && throttle>25) {
    running=true;
    cout << "The V8 is running" << endl;
  }
  else
    cout << "The V8 won't start." << endl;
}



bool V8Classic::isRunning() const {
  return running;
}



// --- GasTurbine ----------------------------

bool GasTurbine::startCompressors() {
  if(running)
    return false;
  cout << "Compressors started\n";
  compressors = true;
  checkRunning();
  return true;
}


bool GasTurbine::stopCompressors() {
  if(!compressors)
    return false;
  cout << "Compressors stopped\n";
  compressors = false;
  checkRunning();
  return true;
}


bool GasTurbine::burnerOn() {
  if(running || !pressure)
    return false;
  cout << "Burner started\n";
  burner = true;
  checkRunning();
  return true;
}


bool GasTurbine::burnerOff() {
  if(!burner)
    return false;
  cout << "Burner stopped\n";
  burner = false;
  checkRunning();
  return true;
}


bool GasTurbine::setCompressorPressure(int p) {
  if(p<0 || p>100 ||!compressors)
    return false;

  pressure = p;
  cout << "Pressure is " << pressure << " units\n";
  return true;
}


void GasTurbine::checkRunning() {
  running = pressure && compressors && burner;
}


bool GasTurbine::isRunning() const {
  return running;
}


// --- FuelCell ------------------------------


void FuelCell::fuelOn() {
  if(active)
    return;
  active=true;
  battery.charge();
  cout << "Fuelcell active and charging\n";
}


void FuelCell::fuelOff(){
  active=false;
  cout << "Fuelcell inactive\n";
}


bool FuelCell::isActive() const {
  return active;
}


bool PowerRegulator::setElectricPower(int p) {
  if(p<0 || p>100)
    return false;
  power = p;
  cout << "Electric power set to " << power << endl;
  return true;
}


int PowerRegulator::getElectricPower() const {
  return power;
}


/***********************************************************************************/
/*ADAPTER KLASSER*/
/***********************************************************************************/
//Labb2- Designmönster
//Examinatör: Örjan Sterner
//Av: David Nilsson Löfvall

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

	int thrott = V8Classic::getThrottle();
	p = p + thrott;
	return V8Classic::setThrottle(p);

}

bool V8interface::decPower(int p){

	int thrott = V8Classic::getThrottle();
	p = thrott - p;
	return V8Classic::setThrottle(p);

}
/****************************************/
/*GASTURBINEINTERFACE*/
/****************************************/
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
	return GasTurbine::setCompressorPressure(p);

}

/****************************************/
/*Fuelcell*/
/****************************************/

FuelCellInterface::~FuelCellInterface(){}

bool FuelCellInterface::isRunning() const{

	return FuelCell::isActive();

}
bool FuelCellInterface::tryStart(){

	FuelCell::fuelOn();
	return FuelCell::isActive();

}
bool FuelCellInterface::stop(){

	regulator.setElectricPower(0);
	fuelOff();

	return FuelCell::isActive();


}
bool FuelCellInterface::incPower(int p){

	p = p + regulator.getElectricPower();
	
	if (regulator.setElectricPower(p))
	{
		return true;

	}

	else
	{
		return false;
	}


}
bool FuelCellInterface::decPower(int p){
	int val;
	val = regulator.getElectricPower()-p;

	if (regulator.setElectricPower(val))
	{
		return true;

	}

	else
	{
		return false;
	}

}