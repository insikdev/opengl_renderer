#include "pch.h"
#include "app.h"

int main(int argc, char* argv[])
{
    const int WIDTH = 1024;
    const int HEIGHT = 768;
    const char* title = "OpenGL";
    std::make_unique<App>(WIDTH, HEIGHT, title)->Run();
    return 0;
}