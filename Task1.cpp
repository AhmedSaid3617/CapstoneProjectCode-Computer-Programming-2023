#include <iostream>
using namespace std;


// Takes a string as input and returns 1 if it's invalid. 0 if it is valid.
int error(string circuit){
    char allowed[] = {'S', 'P', '.', ' ', 'e', 'E'};
    int flag;
    // If first letter is neither S nor P, or final letter is not E return error.
    if (circuit[0] != 'S' && circuit[0] != 'P' || circuit[circuit.length()-1] != 'E'){
        return 1;
    }
    for (int i = 0; i < circuit.length(); i++){
        flag = 1;
        // If char is a number, then no error, sets flag to 0 and continue to next char.
        if (circuit[i] >= 48 && circuit[i] <= 57){
            flag = 0;
            continue;
        }
        // Else char is not a number
        // Checks if char is one of the allowed characters.
        // If so,sets flag to 0 and breaks out of the inner loop
        for (int j = 0; j < sizeof(allowed); j++){
            if (circuit[i] == allowed[j]){
                flag = 0;
                break;
            }
        }
        // If after all checks, flag is still 1 then this is an invalid character, return 1.
        if (flag){
            return 1;
        }
    }
    return 0;
}

int main(){
    // Initialize variables.
    float newR, rEq, volt, current;
    char connection;
    string circuit;
    int breakPoint = 1;

    cout << error("P S 8.2 3.1 e S 1.3 7.8 e E");

    //Get circuit.
    //cout << "Circuit description: ";
    //getline(cin, circuit);

    // Get voltage.
    //cout << "Voltage applied: ";
    //cin >> volt;
    
    // Get connection.
    connection = circuit[0];

    // Check connection.
    if (connection != 'S' && connection != 'P') {
        cout << "Wrong circuit description.";
    }
    else {
        // Get first resistance.
        // This loop finds the second space character (breakpoint). 
        // First resistance is between index 1 and breakpoint.
        for (int i=2; i < circuit.length(); i++){
            if (circuit[i] == ' ') {
                rEq = stof(circuit.substr(1, i-1));
                breakPoint = i;
                break;
            }
        }

        // Loops over input from breakpoint, resistance is between breakpoint and next space. 
        // Adds resistance to rEq.

        // Calculate equivalent series resistance.
        if (connection == 'S'){
            for (int i=breakPoint + 1; i < circuit.length(); i++){
                if (circuit[i] == ' ') {
                    // Resistance is between breakpoint and space.
                    newR = stof(circuit.substr(breakPoint, i-breakPoint));

                    // Add resistance to rEq.
                    rEq += newR;

                    // Set breakpoint to new space character index.
                    breakPoint = i;
                }
            }
        }

        // Calculate equivalent parallel resistance.
        else {
            for (int i=breakPoint + 1; i < circuit.length(); i++){
                if (circuit[i] == ' ') {
                    newR = stof(circuit.substr(breakPoint, i-breakPoint));

                    // Calculates rEq parallel with new resistance.
                    rEq = 1/(1/rEq + 1/newR);

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