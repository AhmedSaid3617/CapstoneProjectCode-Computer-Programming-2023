#include <iostream>
using namespace std;
int main()
{
    string x = "g g g g";
    for (int i = 0; i < x.length(); i++){
        if (x[i] == ' '){
            cout << i;
        }
    }
}