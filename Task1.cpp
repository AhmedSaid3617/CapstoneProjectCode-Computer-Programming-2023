#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

const int INFINITY = 99999999;

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

float simpleParallel(float x, float y)
{
    return (x * y) / (x + y);
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
                if (wire[j] == "e" || wire[j] == "E")
                {
                    nextE = j;
                    break;
                }
            }

            // Create newWire.
            for (int j = i + 1; j <= nextE; j++)
            {
                newWire.push_back(wire[j]);
            }
            // set i to the nextE to continue after it.
            i = nextE;

            rEq += series(newWire);

            // Clear newWire for next loops.
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

float parallel(vector<string> wire)
{
    float rEq = INFINITY;
    int nextE;
    vector<string> newWire;
    for (int i = 0; i < size(wire); i++)
    {
        if (wire[i] == "S")
        {
            // Find the e that ends this new wire.
            for (int j = i + 1; j < size(wire); j++)
            {
                if (wire[j] == "e" || wire[j] == "E")
                {
                    nextE = j;
                    break;
                }
            }

            // Create newWire.
            for (int j = i + 1; j <= nextE; j++)
            {
                newWire.push_back(wire[j]);
            }
            // set i to the nextE to continue after it.
            i = nextE;

            rEq = simpleParallel(rEq, series(newWire));

            // Clear newWire for next loops.
            newWire.clear();
        }

        else if (wire[i] == "P")
        {
            // Find the e that ends this new wire.
            for (int j = i + 1; j < size(wire); j++)
            {
                if (wire[j] == "e" || wire[j] == "E")
                {
                    nextE = j;
                    break;
                }
            }

            // Create newWire.
            for (int j = i + 1; j <= nextE; j++)
            {
                newWire.push_back(wire[j]);
            }
            // set i to the nextE to continue after it.
            i = nextE;

            rEq = simpleParallel(rEq, parallel(newWire));

            // Clear newWire for next loops.
            newWire.clear();
        }
        else if (wire[i] == "e" || wire[i] == "E")
        {
            return rEq;
        }
        else
        {
            rEq = simpleParallel(rEq, stof(wire[i]));
        }
    }
}

float evaluate(vector<string> wire, char connection)
{
    float rEq = (connection == 'S') ? 0 : INFINITY;
    int nextE;
    vector<string> newWire;
    for (int i = 0; i < size(wire); i++)
    {
        if (wire[i] == "S" || (wire[i] == "P"))
        {
            // Find the e that ends this new wire.
            for (int j = i + 1; j < size(wire); j++)
            {
                if (wire[j] == "e" || wire[j] == "E")
                {
                    nextE = j;
                    break;
                }
            }

            // Create newWire.
            for (int j = i + 1; j <= nextE; j++)
            {
                newWire.push_back(wire[j]);
            }
            // set i to the nextE to continue after it.

            // rEq += series(newWire);

            if (connection == 'S')
                rEq += evaluate(newWire, wire[i][0]);
            else if (connection == 'P')
                rEq = simpleParallel(rEq, evaluate(newWire, wire[i][0]));

            i = nextE;

            // Clear newWire for next loops.
            newWire.clear();
        }

        else if (wire[i] == "e" || wire[i] == "E")
        {
            return rEq;
        }
        else
        {
            if (connection == 'S')
                rEq += stof(wire[i]);
            else if (connection == 'P')
                rEq = simpleParallel(rEq, stof(wire[i]));
        }
    }
    return 0;
}

int main()
{
    string circuit;
    cout << "Enter circuit description: ";
    getline(cin, circuit);
    if (error(circuit))
    {
        cout << "Wrong circuit desciription";
    }
    else
    {
        float voltage;
        float current;
        float resistance;
        cout << "Enter voltage: ";
        cin >> voltage;

        vector<string> circuitVect = split(circuit);

        vector<string> circuitVectNo1let;
        for (int i = 1; i < size(circuitVect); i++)
        {
            circuitVectNo1let.push_back(circuitVect[i]);
        }

        resistance = evaluate(circuitVectNo1let, circuit[0]);

        cout << "Equivalent resistance: " << resistance << endl;

        current = voltage/resistance;
        
        cout << "Current: " << current;
    }
    return 0;
}