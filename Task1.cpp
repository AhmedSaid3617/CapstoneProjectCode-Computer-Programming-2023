#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

// Takes circuit discription as a string as input and returns 1 if it's invalid. 0 if it is valid.
int error(string circuitStr)
{
    char allowed[] = {'S', 'P', '.', ' ', 'e', 'E'};
    int flag;
    // If first letter is neither S nor P, or final letter is not E return error.
    if (circuitStr[0] != 'S' && circuitStr[0] != 'P' || circuitStr[circuitStr.length() - 1] != 'E')
    {
        return 1;
    }
    for (int i = 0; i < circuitStr.length(); i++)
    {
        flag = 1;
        // If char is a number, then no error, sets flag to 0 and continue to next char.
        if (circuitStr[i] >= 48 && circuitStr[i] <= 57)
        {
            flag = 0;
            continue;
        }
        // Else char is not a number
        // Checks if char is one of the allowed characters.
        // If so,sets flag to 0 and breaks out of the inner loop
        for (int j = 0; j < sizeof(allowed); j++)
        {
            if (circuitStr[i] == allowed[j])
            {
                flag = 0;
                break;
            }
        }
        // If after all checks, flag is still 1 then this is an invalid character, return 1.
        if (flag)
        {
            return 1;
        }
    }
    return 0;
}

// Takes circuit discription as a string as input and returns it as a tokenized vector.
std::vector<string> split(string circuitStr)
{

    vector<string> circuitVect;
    circuitVect.push_back(circuitStr.substr(0, 1));
    int breakPoint = 2;
    for (int i = 2; i < circuitStr.length(); i++)
    {
        if (circuitStr[i] == ' ')
        {
            circuitVect.push_back(circuitStr.substr(breakPoint, i - breakPoint));
            breakPoint = i + 1;
        }
    }
    circuitVect.push_back("E");

    circuitVect.push_back(circuitStr.substr(breakPoint + 1, circuitStr.length() - 1));

    return circuitVect;
}

float series(vector<string> wire)
{
    float rEq = 0;
    int nextE;
    vector<string> newWire;
    for (int i = 0; i < size(wire); i++)
    {
        if (wire[i] == "S")
        {
            // Find the e that ends this new wire.
            for (int j = i + 1; j < size(wire); j++)
            {
                if (wire[j] == "e" || wire[j] == "E"){
                    nextE = j;
                    break;
                }
            }

            for (int j = i + 1; j <= nextE; j++)
            {
                newWire.push_back(wire[j]);
            }

            i = nextE;

            rEq += series(newWire);

            newWire.clear();

        }
        else if (wire[i] == "P")
        {
            /* code */
        }
        else if (wire[i] == "e" || wire[i] == "E")
        {
            return rEq;
        }
        else
        {
            rEq += stof(wire[i]);
        }
    }
}

int main()
{
    string circuit = "S 1 S 2 3 e S 1 1 e 2 E";

    vector<string> circuitVect = split(circuit);

    //cout << series(circuitVect);

    vector<string> circuitVectNo1let;

    if (circuitVect[0] == "S"){
        for (int i = 1; i < size(circuitVect); i++){
            circuitVectNo1let.push_back(circuitVect[i]);
        }
        cout << series(circuitVectNo1let);
    }

    // cout << series(circuitVect);

    // Initialize variables.
    float newR, rEq, volt, current;
    char connection;

    int breakPoint = 1;

    // Check connection.
    if (connection != 'S' && connection != 'P')
    {
    }
    else
    {
        // Get first resistance.
        // This loop finds the second space character (breakpoint).
        // First resistance is between index 1 and breakpoint.
        for (int i = 2; i < circuit.length(); i++)
        {
            if (circuit[i] == ' ')
            {
                rEq = stof(circuit.substr(1, i - 1));
                breakPoint = i;
                break;
            }
        }

        // Loops over input from breakpoint, resistance is between breakpoint and next space.
        // Adds resistance to rEq.

        // Calculate equivalent series resistance.
        if (connection == 'S')
        {
            for (int i = breakPoint + 1; i < circuit.length(); i++)
            {
                if (circuit[i] == ' ')
                {
                    // Resistance is between breakpoint and space.
                    newR = stof(circuit.substr(breakPoint, i - breakPoint));

                    // Add resistance to rEq.
                    rEq += newR;

                    // Set breakpoint to new space character index.
                    breakPoint = i;
                }
            }
        }

        // Calculate equivalent parallel resistance.
        else
        {
            for (int i = breakPoint + 1; i < circuit.length(); i++)
            {
                if (circuit[i] == ' ')
                {
                    newR = stof(circuit.substr(breakPoint, i - breakPoint));

                    // Calculates rEq parallel with new resistance.
                    rEq = 1 / (1 / rEq + 1 / newR);

                    breakPoint = i;
                }
            }
        }

        // Calculate and output current.
        current = volt / rEq;
        cout << "Current: " << current;
    }

    return 0;
}