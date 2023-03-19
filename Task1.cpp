#include <iostream>
using namespace std;

int main(){
    // Initialize variables.
    float r1 = 5, r2, r3, rEq, volt, current;
    char connection;
    string circuit;
    int breakPoint = 1;

    //Get circuit.
    cout << "Circuit description: ";
    getline(cin, circuit);

    // Get voltage.
    cout << "Voltage applied: ";
    cin >> volt;
    
    // Get connection.
    connection = circuit[0];

    // Check connection.
    if (connection != 'S' && connection != 'P') {
        cout << "Wrong circuit description.";
    }
    else {
        // Get first resistance.
        // This loop finds the second space character (breakpoint). First resistance is between index 1 and breakpoint.
        for (int i=2; i < circuit.length(); i++){
            if (circuit[i] == ' ') {
                rEq = stof(circuit.substr(1, i-1));
                breakPoint = i;
                break;
            }
        }

        // Loops over input from breakpoint, resistance is between breakpoint and next space. Adds resistance to rEq.

        // Calculate equivalent series resistance.
        if (connection == 'S'){
            for (int i=breakPoint + 1; i < circuit.length(); i++){
                if (circuit[i] == ' ') {
                    // Resistance is between breakpoint and space.
                    r1 = stof(circuit.substr(breakPoint, i-breakPoint));

                    // Add resistance to rEq.
                    rEq += r1;

                    // Set breakpoint to new space character index.
                    breakPoint = i;
                }
            }
        }

        // Calculate equivalent parallel resistance.
        else {
            for (int i=breakPoint + 1; i < circuit.length(); i++){
                if (circuit[i] == ' ') {
                    r1 = stof(circuit.substr(breakPoint, i-breakPoint));

                    // Calculates rEq parallel with new resistance.
                    rEq = 1/(1/rEq + 1/r1);

                    breakPoint = i;
                }
            }
        }

        // Calculate and output current.
        current = volt/rEq;
        cout << "Current: " << current;
    }

    return 0;
}