#ifndef POLYMER_H_
#define POLYMER_H_

#ifdef SNAKE_VIZ
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include "GLUT/glut.h"
#else
#include <GL/gl.h>
#endif
#endif

#include "UsualHeaders.h"
#include "ArithmeticPrecision.h"
#include "Vector3.h"
#include "Matrix3.h"
#include "PolymerIntegrator.h"
#include "GeometryFunctions.h"
//#include "MRAGProfiler.h"

#define SNAKE_POV  //to avoid the SNAKE_VIZ thing

using namespace std;

class Polymer
{
protected:
	static const unsigned int PRINTPRECISION = 6;

	int numRods;
	int numPistons;

	REAL startTimeStats;
	REAL endTimeStats;
	Vector3 avgVel;

	//rods
	vector<Rod*> rodptrs;
	vector<ExternalForces*> efptrs;
	vector<RodBC*> bcptrs;
	vector<Interaction*> interptrs;
	vector<ExternalContact*> ecptrs;
	PolymerIntegrator * pint;

	REAL bendingEnergy;
	REAL shearEnergy;
	REAL translationalEnergy;
	REAL rotationalEnergy;
	REAL totalInternalEnergy;

#ifdef SNAKE_VIZ
	void _paint(Rod * snake);
#endif

public:
	Polymer(PolymerIntegrator * pint): startTimeStats(0.0), endTimeStats(0.0), avgVel(Vector3()), pint(pint)
	{
		rodptrs = pint->getRods();
		efptrs = pint->getExternalForces();
		bcptrs = pint->getBoundaryConditions();
		interptrs = pint->getInteractions();

		numRods = (int) rodptrs.size();
		computeEnergies();
	}

	bool simulate(const REAL simulationTime, const REAL dt0, const unsigned int diagPerUnitTime, const unsigned int povrayFramesPerUnitTime, const string diagnostics, const string integrationType = "VELOCITY_VERLET_2ND", const REAL CFL = 0.01);
	bool nanCheck();
	void computeEnergies();
	void printEnergies(const int step, const int povrayStep);
	void printRod_X(const int step, const int povrayStep);
	void print_Nest_Stuff(const int step, const REAL time, const int povrayStep);
	void printX(const int step, const REAL time, const string outfilename);
	void printXV(const int step, const REAL time, const string outfilename);
	void print_s_internalTorques(const string outfilename);
	void print_s_coordinates(const string outfilename);
	void print_s_internalShears(const string outfilename);
	void print_s_curvatures(const string outfilename);
	void setWindowStats(const REAL _startTimeStats, const REAL _endTimeStats){ startTimeStats = _startTimeStats; endTimeStats = _endTimeStats; };

	REAL getTotalBendingEnergy(){ return bendingEnergy; }
	REAL getTotalTranslationalEnergy(){ return translationalEnergy; }
	REAL getTotalEnergy(){ return totalInternalEnergy; }
	REAL getTotalRotationalEnergy(){ return rotationalEnergy; }
	Vector3 getAverageVelocity(){ return avgVel; }
};

#endif

