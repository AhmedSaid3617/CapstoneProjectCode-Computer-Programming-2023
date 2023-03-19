#include <iostream>
using namespace std;

int main(){
    // Initialize variables.
    float r1, r2, r3, rEq, volt, current;
    char connection;

    // Input resistance values.
    cout << "Circuit descrption: ";
    cin >> connection >> r1 >> r2 >> r3;
    cout << "\n";

    // Input current.
    cout << "Voltage applied: ";
    cin >> volt;

    // Calculate equivalent resistance.
    if (connection == 'S') {
        rEq = r1 + r2 + r3;
    }
    else if (connection == 'P') {
        rEq = 1/((1/r1) + (1/r2) + (1/r3));
    }

    // Calculate current.
    current = volt/rEq;

    // Output results.
    cout << "Equivalent Resistance: " << rEq << endl;
    cout << "Current: " << current << endl;

    return 0;
}
