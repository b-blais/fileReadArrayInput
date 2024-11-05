/*
Title: Array File Functions
File Name : ArrayFileFunctions.h
Programmer : Brion Blais
Date : 10 / 2024
Requirements :
Small group of functions to find, open, read and close a file.  Also incudes a function
to create a vector array from the file contents.
*/

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

ifstream fileStreamObject;

// call these functions from the main program
void openFile();
void readFile(bool);
void closeFile();
void createArray(string);

// secondary functions called
int flagValidation(string);
int countLines();
int arraySize(string);

int arraySize(string arrayType) {
    int arraySizeRequired;
    if (arrayType == "char") {
        char charGroup;
        int charCount = 0;
        while (fileStreamObject.get(charGroup)) {
            charCount++;
        }
        arraySizeRequired = charCount;
        cout << "There are " << charCount << " characters.\n";
    }
    else {
        arraySizeRequired = countLines();
    }
    fileStreamObject.clear();
    fileStreamObject.seekg(0, ios::beg);
    return arraySizeRequired;
}

void openFile() {
    string fileName;
    string localFileFlag;
    bool fileFlag;
    cout << "What is the name of the file you are opening? \t";
    cin >> fileName;
    cout << "Is the file you are trying to open in the same folder as this program? \t";
    cin >> localFileFlag;
    fileFlag = flagValidation(localFileFlag);
    if (fileFlag == false) {
        string filePath;
        cout << "Please enter the path to the folder where the file you are trying to open is located.\n";
        cout << "Use the following format:  " << R"(C:\Users\myname\Desktop)" << "\n";
        cin >> filePath;
        fileName = filePath + R"(\)" + fileName;
    }
    if (fileFlag == true) {
        cout << "Finding the file ... ";

        fileStreamObject.open(fileName);
        if (fileStreamObject) {
            cout << "file open.\n";
        }
        else {
            cout << "The file was not found or could not be opened. \n";
            cout << "Please check to see if the file is in the correct folder and rerun the program. Exiting ...\n";
            exit(0);
        }
    }
    else {
        cout << "Finding the file at the following at " << fileName << " ... ";
        fileStreamObject.open(fileName);
        if (fileStreamObject) {
            cout << "file open.\n";
        }
        else {
            cout << "the file was not found or could not be opened. \n";
            cout << "Please check to see if the file is in the correct location and rerun the program. Exiting ...\n";
            exit(0);
        }
    }
}

int flagValidation(string input) {
    int output = 2;
    do {
        if (input == "True" || input == "true" || input == "TRUE" ||
            input == "Yes" || input == "yes" || input == "YES") {
            output = 1;
        }
        else if (input == "False" || input == "false" || input == "FALSE" ||
            input == "No" || input == "no" || input == "NO") {
            output = 0;
        }
        else {
            cout << R"(You must anwser either "true / false or yes / no" to continue.)" << endl;
            cout << "Is the file you are trying to open in the same folder as this program?\t";
            cin >> input;
        }
    } while (output != 0 && output != 1);
    return output;
}

void readFile(bool buildArray) {
    int menuSelection = 0;
    while (menuSelection < 1 || menuSelection > 4) {
        cout << "Are you reading numbers, characters, or lines of text? Please make a numerical selection:\n";
        cout << "--------------------\n";
        cout << "1 for numbers.\n";
        cout << "2 for characters.\n";
        cout << "3 for lines of text.\n";
        cout << "4 to exit.\n";
        cin >> menuSelection;
        cout << "\n";
        if (menuSelection < 1 || menuSelection > 4) cout << "Invalid entry, try again. \n";
    }
    if (menuSelection == 1) {
        int subMenuSelection = 0;
        while (subMenuSelection < 1 || subMenuSelection > 3) {
            cout << "Does this file contain integers or floating point numbers?  Please make a numerical selection:\n";
            cout << "-----------------------------\n";
            cout << "1 for integers.\n";
            cout << "2 for floating point numbers.\n";
            cout << "3 to exit the program.\n";
            cin >> subMenuSelection;
            if (subMenuSelection < 1 || subMenuSelection > 3) cout << "Invalid entry, try again. \n";
        }
        if (subMenuSelection == 1) {
            int fileContents;
            while (fileStreamObject >> fileContents) {
                cout << fileContents << endl;
            }
            if (buildArray == true) createArray("int");
        }
        else if (subMenuSelection == 2) {
            double fileContents;
            while (fileStreamObject >> fileContents) {
                cout << showpoint << fileContents << endl;
            }
            if (buildArray == true) createArray("double");
        }
        else if (subMenuSelection == 3) {
            cout << "Exiting ... ";
        }
    }
    else if (menuSelection == 2) {
        char fileContents;
        while (fileStreamObject.get(fileContents)) {
            cout << fileContents << endl;
        }
        if (buildArray == true) createArray("char");
    }
    else if (menuSelection == 3) {
        string lineContents;
        while (getline(fileStreamObject, lineContents)) {
            cout << lineContents << endl;
        }
        if (buildArray == true) createArray("string");
    }
    else if (menuSelection == 4) {
        cout << "Exiting the program ...\n";
    }
}

void createArray(string arrayType) {
     fileStreamObject.clear();
     fileStreamObject.seekg(0, std::ios::beg);
     int size = (arraySize(arrayType));
     if (arrayType == "int") {
         vector<int> intArray(size);
         for (int elementCount = 0; elementCount < size; elementCount++) {
             fileStreamObject >> intArray[elementCount];
             cout << "Element #" << elementCount << " of the array is: " << intArray[elementCount] << endl;
         }
     }
     else if (arrayType == "double") {
         vector<double> doubleArray(size);
         for (int elementCount = 0; elementCount < size; elementCount++) {
             fileStreamObject >> doubleArray[elementCount];
             cout << "Element #" << elementCount << " of the array is: " << doubleArray[elementCount] << endl;
         }
     }
     else if (arrayType == "char") {
         vector<char> charArray(size);
         char nextChar;
         for (int elementCount = 0; elementCount < size; elementCount++) {
             fileStreamObject.get(nextChar);
             charArray[elementCount] = nextChar;
             cout << "Element #" << elementCount << " of the array is: " << charArray[elementCount] << " with an ascii value of " << (int(charArray[elementCount])) << endl;
         }
     }
     else if (arrayType == "string") {
         vector<string> stringArray(size);
         for (int elementCount = 0; elementCount < size; elementCount++) {
            string lineContents;
            getline(fileStreamObject, lineContents);
            stringArray[elementCount] = lineContents;
            cout << "Element #" << elementCount << " of the array is: " << stringArray[elementCount] << endl;
         }
     }
}

int countLines() {
    int lineCount = 0;
    string fileContents;
    while (getline(fileStreamObject, fileContents)) {
        lineCount += 1;
    }
    cout << "There are " << lineCount << " lines in this file.\n";
    fileStreamObject.clear();
    fileStreamObject.seekg(0, ios::beg);
    return lineCount;
}

void closeFile() {
    cout << "Closing file ...";
    fileStreamObject.close();
    cout << "File closed.";
}