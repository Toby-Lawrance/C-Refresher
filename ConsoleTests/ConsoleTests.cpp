// ConsoleTests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <memory>
#include <math.h>
#include <chrono>
#include <thread>
#include <Windows.h>

#include "Circle.h"
#include "../ConsoleCommon/oof.h"
#include "../ConsoleCommon/ScreenWrapper.h"

int main()
{
    using namespace std;
    const auto sw = std::make_shared<ScreenWrapper>();
    const auto dimensions = sw->GetScreenCellDimensions();
    std::cout << "Dimensions: (" << dimensions.x << "," << dimensions.y << ")" << std::endl;
    int r;
    std::cin >> r;
    auto c = std::make_shared<Circle>();
    c->radius = r;
    c->color = oof::color(255, 255, 255);
    c->pos = Vector2D<double>(50, 50);
    sw->AddDrawObject("Circle", c);

    string test = "a";
    while(!(GetAsyncKeyState('Q') & 1))
    {
        sw->Draw();
        sw->GetDrawObject("Circle")->pos.x = std::fmod(sw->GetDrawObject("Circle")->pos.x + 5,100.0);

        std::this_thread::sleep_for(50ms);
    }
	

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
