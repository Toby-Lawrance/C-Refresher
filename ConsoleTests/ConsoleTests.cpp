// ConsoleTests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <memory>
#include "../ConsoleCommon/oof.h"
#include "../ConsoleCommon/ScreenWrapper.h"
#include "../ConsoleCommon/TestClass.h"

int main()
{
    const auto t = std::make_shared<TestClass>();
    std::cout << t->testMethod() << std::endl;
    const auto sw = std::make_shared<ScreenWrapper>();
    const auto dimensions = sw->GetScreenCellDimensions();
    std::cout << "Dimensions: (" << std::get<0>(dimensions) << "," << std::get<1>(dimensions) << ")" << std::endl;
    std::cin;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file