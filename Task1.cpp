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
    // Add first letter.
    circuitVect.push_back(circuitStr.substr(0, 1));
    int breakPoint = 2;

    // Loop over string and add all tokens separated by space.
    for (int i = 2; i < circuitStr.length(); i++)
    {
        if (circuitStr[i] == ' ')
        {
            circuitVect.push_back(circuitStr.substr(breakPoint, i - breakPoint));
            breakPoint = i + 1;
        }
    }

    // Add final letter.
    circuitVect.push_back("E");

    return circuitVect;
}


// Takes two floats and returns their parallel equivalent.
float simpleParallel(float x, float y)
{
    return (x * y) / (x + y);
}


// Takes circuit description as string vector and returns equivalent resistance.
float evaluate(vector<string> wire, char connection)
{
    // Set equivalent resistance to zero in case of series connection and infinity in
    // case of parallel connection.
    float rEq = (connection == 'S') ? 0 : INFINITY;

    int nextE;
    vector<string> newWire;

    // Loop over each item in the wire.
    for (int i = 0; i < size(wire); i++)
    {
        // If item is S or P then there is a new wire.
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

            // Create newWire from after S or P to the first e.
            for (int j = i + 1; j <= nextE; j++)
            {
                newWire.push_back(wire[j]);
            }
            
            // Use recursion.
            // evaluate the value of the new wire according to its type.
            // Add it to rEq if this is a series connection.
            // Parallel it to rEq if this is a parallel connection.
            // 
            if (connection == 'S')
                rEq += evaluate(newWire, wire[i][0]);
            else if (connection == 'P')
                rEq = simpleParallel(rEq, evaluate(newWire, wire[i][0]));

            // Set i to the nextE to continue after it.
            i = nextE;

            // Clear newWire for next loops.
            newWire.clear();
        }

        else if (wire[i] == "e" || wire[i] == "E")
        {
            return rEq;
        }

        // Calculates new rEq if it's a number.
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
    // Get circuit description.
    string circuit;
    cout << "Enter circuit description: ";
    getline(cin, circuit);

    // Check for error.
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

        // Turn circuit description to vector.
        vector<string> circuitVect = split(circuit);

        // Create circuitVectNo1let which is the same as circuitVect
        // without the first item.
        vector<string> circuitVectNo1let;
        for (int i = 1; i < size(circuitVect); i++)
        {
            circuitVectNo1let.push_back(circuitVect[i]);
        }

        // Calculate the resistance according to the first letter
        // of circuit.
        resistance = evaluate(circuitVectNo1let, circuit[0]);

        cout << "Equivalent resistance: " << resistance << " Ohm" << endl;

        current = voltage/resistance;
        
        cout << "Current: " << current << " A";
    }
    return 0;
}