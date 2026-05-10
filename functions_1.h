//1.1
#pragma once
#include <string>
#include <vector>
using namespace std;

class Material {
public:
    string name;
    double yieldStrength;
    double density;

    Material(string n, double ys, double d);
};

extern vector<Material> materials;


//Motor Class
class Motor
{
public:
    float torque, diameter, speed, width, mass;
};

//Gearbox Class
class Gearbox
{
public:
    float ratio, diameter, efficiency, width, mass;
};


extern int motorCount;
extern Motor motors[5];

extern int gearCount;
extern Gearbox gears[5];




// Functions
double calcLinkMass_Rectangle(double density, double b, double h, double L);
double calcLinkMass_Circle(double density, double r, double L);
double calcBendingMoment(double m1, double mp, double L, double amax);

double calcInertia_Rectangle(double b, double h);
double calcInertia_Circle(double r);

double calcStress_Rectangle(double M, double h, double I);
double calcStress_Circle(double M, double r, double I);

void optRectangle(double& b, double& h, double density, double mp, double L, double amax, double yieldStrength_MPa, double& finalMass);
void optCircle(double& r, double density, double mp, double L, double amax, double yieldStrength_MPa, double& finalMass);


void solvebestcombination(float T_required, float speed_required);