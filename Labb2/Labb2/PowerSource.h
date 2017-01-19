//--- PowerSource.h  -------------------------------------

#ifndef POWERSOURCEH
#define POWERSOURCEH

#include <string>

using std::string;

class PowerSource {

private:
  string typeStr;

public:
  PowerSource(string type):typeStr(type)
  { }
  virtual ~PowerSource() { };
  const string& type() const { return typeStr; }
  virtual bool isRunning() const =0;
  virtual bool tryStart()=0;
  virtual bool stop()=0;
  virtual bool incPower(int p=10)=0;
  virtual bool decPower(int p=10)=0;
};


// --- V8Classic -----------------------------

class V8Classic  {
protected:
   bool running, ignition, choke;
   int throttle; //throttle vent 0 .. 100 units
public:
   V8Classic()
   :running(false),ignition(false),
    choke(false),throttle(0)
    { }
   void ignitionOn();
   void ignitionOff();
   void chokeOn();
   void chokeOff();
   void runStarter();
   bool setThrottle(int);
   int getThrottle() const;
   bool isRunning() const;

  /*  F�r att starta en V8:a
        ignitionOn();
        chokeOn();
        setThrottle(30);
        runStarter();
        chokeOff();

      F�r att stanna en V8:a
        setThrottle(0);
        ignitionOff()

     �ndring av throttle ger �ndring av effekt
  */
};




// --- GasTurbine ----------------------------

class GasTurbine {

protected:
  int pressure; // 0 .. 100 units
  bool running, compressors, burner;
  void checkRunning();

public:
  GasTurbine()
  :pressure(0),running(false),
  compressors(false),burner(false)
  { }
  bool startCompressors();
  bool stopCompressors();
  bool burnerOn();
  bool burnerOff();
  bool setCompressorPressure(int);
  int getCompressorPressure( ) { return pressure; }
  bool isRunning() const;

  /* F�r att starta en GasTurbine
       startCompressors()
       setCompressorPressure(20)
       burnerOn()

     F�r att stanna en GasTurbine
       setCompressorPressure(0);
       stopCompressors();
       burnerOff();

     �ndring av pressure ger �ndring av effekt
  */

};



// --- FuelCell ------------------------------

class Ackumulator {

private:
  bool charged;

public:
  Ackumulator():charged(false)
  { }
  void charge() { charged=true; }
  bool hasPower() const { return charged; }
};

class PowerRegulator {

private:
  Ackumulator *theBattery;
  int power; // 0 .. 100 units

public:
  PowerRegulator(Ackumulator *ack)
  :theBattery(ack), power(0)
  { }
  bool setElectricPower(int);
  int getElectricPower() const;
};

class FuelCell {

protected:
  bool active;
  Ackumulator battery;
  PowerRegulator regulator;
public:
  FuelCell()
  : regulator(&battery), active(false)
  { }
  void fuelOn();
  void fuelOff();
  bool isActive() const;

   /* F�r att starta en FuelCell
        fuelOn()

      F�r att stanna en FuelCell
        regulator.setElectricPower(0);
        fuelOff();

      �ndring av effekt g�r med
        regulator.setElectricPower(int)
  */

};

/***********************************************************************************/
/*ADAPTER KLASSER*/
/***********************************************************************************/
//Labb2- Designm�nster
//Examinat�r: �rjan Sterner
//Av: David Nilsson L�fvall


class FuelCellInterface : public PowerSource, private FuelCell{

/* �terigen ska vi l�nka konstruktorer. Konceptet med detta hade jag till en b�rjan sv�rt att f�rst� d� jag inte anser att kurslitteraturen behandlar detta s�rskilt tydligt(inte de kapitel som 
tillh�r lab1+2 i alla fall) likas� lyser de med sin fr�nvaro i studiematerialet. Dock ser jag hur de kan fungera i det h�r exemplet.Genom en �verlagring av () skapas konstruktorn f�r den deriverade klassen.  

Varje adapterklass implementerar de funktioner som basklassen PowerSource har. D�remot inneb�r varje funktion att olika funktioner i de olika typer av PowerSource aktiveras. 
*/
public: 
	FuelCellInterface(string typ) : PowerSource(typ), FuelCell(){}
	~FuelCellInterface();

	bool isRunning() const;
	bool tryStart();
	bool stop();
	bool incPower(int p);
	bool decPower(int p);



};

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
