/*
Title: Array File Functions
File Name : ArrayFileFunctions.h
Programmer : Brion Blais
Date : 10 / 2024
Requirements :
Short program to test some functions I added to a header file.
*/

#include "ArrayFileFunctions.h"
using namespace std;

int main()
{
    bool buildArray = false;
    string answer;

    cout << "Will you be outputting the contents of this file to an array?\t";
    cin >> answer;
    buildArray = flagValidation(answer);
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    openFile();
    readFile(buildArray);
    closeFile();
           
    return 0;
}