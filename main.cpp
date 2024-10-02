#include <iostream>
#include "SDLWindow.hpp"
#include <unistd.h> // For sleep

int main()
{
	SDLWindow window("SANC", 1080, 1920);

	window.run();
	return 0;
}
