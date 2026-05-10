#include <iostream>
#include <vector>
#include <cfloat>
#include "functions_1.h"
using namespace std;

extern vector<Material> materials;


      
int main() {

//part1

    int shape;
    cout << "Choose cross-section:\n1 - Rectangle\n2 - Circle\n";
    cin >> shape;

    cout << "\nAvailable materials:\n";
    for (int i = 0; i < materials.size(); i++) {
        cout << i << " - " << materials[i].name << endl;
    }

    int matChoice;
    cout << "Select material: ";
    cin >> matChoice;

    Material selected = materials[matChoice];

    double L, mp, amax;
    cout << "\nEnter link length (L) in meters: ";
    cin >> L;
    cout << "Enter payload mass (mp) in Kg: ";
    cin >> mp;
    cout << "Enter max acceleration (amax) Rad/s^2: ";
    cin >> amax;

    double finalMass = 0;

    if (shape == 1) {
        double b, h;
        cout << "\nEnter width (b) in meters: ";
        cin >> b;
        cout << "Enter height (h) in meters: ";
        cin >> h;

        optRectangle(b, h, selected.density, mp, L, amax, selected.yieldStrength, finalMass);

        cout << "\nFinal: b = " << b << " m, h = " << h << " m\n";
    }
    else if (shape == 2) {
        double r;
        cout << "\nEnter radius (r) in meters: ";
        cin >> r;

        optCircle(r, selected.density, mp, L, amax,
                  selected.yieldStrength, finalMass);

        cout << "\nFinal: r = " << r << " m\n";
    }
    else {
        cout << "Invalid choice\n";
        return 0;
    }

    cout << "\nFinal Link Mass = " << finalMass << " kg\n";


//PART2

float T_required;
      T_required=(finalMass*9.81*(L/2))+(mp*9.81*L)+(finalMass*(L/2)*(L/2)*amax)+(mp*L*L*amax);
    cout << "\nRequired Torque =" << T_required << "Nm\n";
  
    float speed_required;

    cout << "Enter required speed: ";
    cin >> speed_required;
      
    solvebestcombination(T_required, speed_required);

    return 0;
}