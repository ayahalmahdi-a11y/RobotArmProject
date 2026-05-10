#include <iostream>
#include <cmath>
#include <cfloat>
#include <vector>
#include "functions_1.h"
using namespace std;

// Constructor
Material::Material(string n, double ys, double d)
    : name(n), yieldStrength(ys), density(d) {}

vector<Material> materials = {
    Material("Cast Iron", 130, 7300),
    Material("Copper Nickel", 130, 8940),
    Material("Brass", 200, 8730),
    Material("Aluminum", 241, 2700),
    Material("Steel", 247, 7580),
    Material("Acrylic", 72, 1160),
    Material("Copper", 70, 8920),
    Material("Stainless Steel", 275, 7860),
    Material("Tungsten", 941, 19250)
};


double calcLinkMass_Rectangle(double density, double b, double h, double L) {
    return density * (b * h * L);
}

double calcLinkMass_Circle(double density, double r, double L) {
    return density * (M_PI * r * r * L);
}

double calcBendingMoment(double m1, double mp, double L, double amax) {
    double g = 9.81;
    return (m1 * g * (L / 2.0)) +
           (mp * g * L) +
           (m1 * 0.25 * L * L * amax) +
           (mp * L * L * amax);
}

double calcInertia_Rectangle(double b, double h) {
    return (b * pow(h, 3)) / 12.0;
}

double calcInertia_Circle(double r) {
    return 0.25 * M_PI * pow(r, 4);
}

double calcStress_Rectangle(double M, double h, double I) {
    return (M * h) / (2.0 * I);
}

double calcStress_Circle(double M, double r, double I) {
    return (M * r) / I;
}

//Function to calculate cost
float calculateCost(Motor m, Gearbox g)
{
    return m.mass + g.mass +
        (m.diameter + g.diameter) / 100 +
        (m.width + g.width) / 100;
}

// Optimization Rectangle
void optRectangle(double& b, double& h, double density, double mp, double L, double amax, double yieldStrength_MPa, double& finalMass) {

    if (b <= 0 || h <= 0) {
        b = 0.01;
        h = 0.01;
    }

    int maxIterations = 10000;

    for (int i = 0; i < maxIterations; i++) {
        double m1 = calcLinkMass_Rectangle(density, b, h, L);
        double M = calcBendingMoment(m1, mp, L, amax);
        double I = calcInertia_Rectangle(b, h);

        double stress = calcStress_Rectangle(M, h, I) / 1e6;

        if (stress > yieldStrength_MPa) {
            b *= 1.01;
            h *= 1.01;
        }
        else if (stress < yieldStrength_MPa * 0.9) {
            b *= 0.99;
            h *= 0.99;
        }
        else {
            finalMass = m1;
            cout << "\nOptimized Rectangle: b = " << b
                 << " m, h = " << h << " m\n";
            cout << "Stress = " << stress << " MPa\n";
            cout << "Mass = " << m1 << " kg\n";
            return;
        }
    }

    cout << "Optimization failed.\n";
}

// Optimization Circle
void optCircle(double& r,
               double density, double mp, double L,
               double amax, double yieldStrength_MPa,
               double& finalMass) {

    if (r <= 0) r = 0.01;

    int maxIterations = 10000;

    for (int i = 0; i < maxIterations; i++) {
        double m1 = calcLinkMass_Circle(density, r, L);
        double M = calcBendingMoment(m1, mp, L, amax);
        double I = calcInertia_Circle(r);

        double stress = calcStress_Circle(M, r, I) / 1e6;

        if (stress > yieldStrength_MPa) {
            r *= 1.01;
        }
        else if (stress < yieldStrength_MPa * 0.9) {
            r *= 0.99;
        }
        else {
            finalMass = m1;
            cout << "\nOptimized Circle: r = " << r << " m\n";
            cout << "Stress = " << stress << " MPa\n";
            cout << "Mass = " << m1 << " kg\n";
            return;
        }
    }

    cout << "Optimization failed.\n";
}
   
    //Using float lliterals in arrays for memory optimization

//Motors Array
    int motorCount = 5;
    Motor motors[5] ={

    motors[0] = { 15.5f, 22.0f, 12100.0f, 20.0f, 1.0f },
    motors[1] = { 405.0f, 60.0f, 4300.0f, 25.0f, 1.3f },
    motors[2] = { 0.649f, 8.0f, 11700.0f, 30.0f, 1.5f },
    motors[3] = { 540.0f, 60.0f, 4300.0f, 35.0f, 1.7f },
    motors[4] = { 2.19f, 10.0f, 12000.0f, 40.0f, 2.0f },
    };
//Gearboxes Array
    int gearCount = 5;
    Gearbox gears[5] ={

    gears[0] = { 26.0f, 19.0f, 0.7f, 15.0f, 0.5f },
    gears[1] = { 150.0f, 14.0f, 0.75f, 20.0f, 0.7f },
    gears[2] = { 4.4f, 16.0f, 0.8f, 25.0f, 1.0f },
    gears[3] = { 84.0f, 16.0f, 0.85f, 30.0f, 1.3f },
    gears[4] = { 734.0f, 12.0f, 0.9f, 35.0f, 1.5f },
    };
    //Since some parameters (mass, width, efficiency) are not included in the provided dataset,
    //approximate values are assumed to allow the optimization process to function correctly.




//Optimization
void solvebestcombination(float T_required, float speed_required) 
{
    float bestCost = FLT_MAX;
    int bestMotorIndex = -1;
    int bestGearIndex = -1;
    
    for (int i = 0; i < motorCount; i++) {
        for (int j = 0; j < gearCount; j++) {

            float T_output = motors[i].torque * gears[j].ratio * gears[j].efficiency;
            float speed_output = motors[i].speed / gears[j].ratio;

            // Check conditions

            if (T_output >= T_required && speed_output >= speed_required) {

                float cost = calculateCost(motors[i], gears[j]);

                if (cost < bestCost) {
                    bestCost = cost;
                    bestMotorIndex = i;
                    bestGearIndex = j;
                }
            }
        }
    }
    // Output
    if (bestMotorIndex == -1) {
        cout << "\nNo suitable combination found.\n";
    }
    else {
        cout << "\nBest Combination Found:\n";

        cout << "\nMotor:\n";
        cout << "Torque: " << motors[bestMotorIndex].torque << "mNm\n";
        cout << "Speed: " << motors[bestMotorIndex].speed << "rpm\n";
        cout << "Mass: " << motors[bestMotorIndex].mass << "kg\n";

        cout << "\nGearbox:\n";
        cout << "Ratio: " << gears[bestGearIndex].ratio << endl;
        cout << "Efficiency: " << gears[bestGearIndex].efficiency << endl;

        cout << "\nTotal Cost: " << bestCost << endl;
    }

}