#include <iostream>
using namespace std;

int main(){
    // Initialize variables.
    float r1 = 5, r2, r3, rEq, volt, current;
    char connection;
    string input;
    int breakPoint = 1;

    //Get input.
    cout << "Circuit description: ";
    getline(cin, input);
    
    // Get connection.
    connection = input[0];

    // Check connection.
    if (connection != 'S' && connection != 'P') {
        cout << "Wrong circuit description.";
    }
    else {
        // Get first resistance.
        // This loop finds the second space character (breakpoint). First resistance is between index 1 and breakpoint.
        for (int i=2; i < input.length(); i++){
            if (input[i] == ' ') {
                rEq = stof(input.substr(1, i-1));
                breakPoint = i;
                break;
            }
        }


        // Calculate equivalent series resistance.
        // Loops over input from breakpoint, resistance is between breakpoint and next space. Adds resistance to rEq.
        if (connection == 'S'){
            for (int i=breakPoint + 1; i < input.length(); i++){
                if (input[i] == ' ') {
                    // Resistance is between breakpoint and space.
                    r1 = stof(input.substr(breakPoint, i-breakPoint));

                    // Add resistance to rEq.
                    rEq += r1;

                    // Set breakpoint to new space character index.
                    breakPoint = i;
                }
            }
        }

        else {
            for (int i=breakPoint + 1; i < input.length(); i++){
                if (input[i] == ' ') {
                    r1 = stof(input.substr(breakPoint, i-breakPoint));

                    // Calculates rEq parallel with new resistance.
                    rEq = 1/(1/rEq + 1/r1);

                    breakPoint = i;
                }
            }
        }

        // Get voltage and output current.
        cout << "Voltage applied: ";
        cin >> volt;
        current = volt/rEq;
        cout << "Current: " << current;
    }

    return 0;
}