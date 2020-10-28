
//#define UNTITLED1_GA_H

#include <iostream>
#include<algorithm>
#include <fstream>
#include<typeinfo>
#include<sstream>
#include <vector>
#include <string>
#include <cstring>
#include<ctime>
#include<cstdlib>
#include <math.h>
//#include <windows.h>
#include <time.h>
using namespace std;
using std::vector;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct cdp
{
    int Name;
    double longitude;
    double latitude;
    int Demande;
    double ServiceTime;
    double Frequence;
    vector <vector<int>> JourCombinaison;
    int NumJourCombinaison;
    vector<int> APR;
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct solution {
    int Name;
    vector<int> Chromosome;
    vector<int> Pointer;
    vector<double> CoutPeriod;
    vector<double> CoutVehicle;
    vector<double> CoutRecharge;
    double Fitness;
    vector<vector<int> > list_client;
    vector<vector<int> > list_pointrecharge;
    vector<vector<vector<int> > > R;//deposer les tournees
    vector<vector<solution> > S;//deposer les solution de reparer
    vector<int> InOut;
    double Time;
    double cout1;
    double cout2;
    double cout3;
    int DayChoose[201];
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct route{
    vector<int> r;
    bool F;
    solution repair;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "ReadText.cpp"
#include "PresentSolution.cpp"
#include "Generate.cpp"
#include "Trier.cpp"
#include "Evaluer.cpp"
#include "Crossover.cpp"
#include "Selection.cpp"
#include "Mutation.cpp"
#include "Replace.cpp"
#include "VerifierSolution.cpp"




