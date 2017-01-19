/*
   File:      PowerSourceTest.cpp
   Objective: Test program lab DP Adapter
   Created:   2007 / Orjan Sterner
*/

#include <vector>
#include <iostream>
#include "PowerSource.h"
#include <memory>
#include <algorithm>

using namespace std;

class PowerSourceTest{

public:
    PowerSourceTest() {

		
        /* Add instances of the PowerSource adapters to psVec */
		psVec.push_back(std::shared_ptr<PowerSource>(new V8interface("V8")));
		psVec.push_back(std::shared_ptr<PowerSource>(new GasturbineInterface("GasTurbine")));
		psVec.push_back(std::shared_ptr<PowerSource>(new FuelCellInterface("Fuelcell")));

    }

    void run() {


        /* For each PowerSpource adapter:
		*/

		/*H�r var jag tvungen att skapa en pekare av typen PowerSource f�r
		att kunna anv�nda basklassens funktioner som implementeras olika beroende p� vilken typ av element som k�rde dem. 
		Konceptet ocks� t�mligen ok�nt f�r en som endast l�st kursmaterialet och de utpekade kapitel i kurslitteraturen*/

        for_each(psVec.begin(), psVec.end(),[](shared_ptr<PowerSource> &newsource) 
		{
			newsource->tryStart();
			
			if (newsource->isRunning())
			{newsource->incPower(10);
			newsource->decPower(10);
			newsource->stop();
            }
			else
			{
				cerr << "Did not start." << endl;
			}
		});

      /*  */
    }

private:
    vector<shared_ptr<PowerSource>> psVec;

};

int main() {

    PowerSourceTest test;
    test.run();
    system("pause");
    return 0;
}