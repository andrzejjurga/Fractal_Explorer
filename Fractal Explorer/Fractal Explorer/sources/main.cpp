#include "scenes.h"

int main()
{
    scenes::currentScene = scene::menu;

    while (scenes::currentScene != scene::exit)
    {
        switch (scenes::currentScene)
        {

        case scene::menu:
            scenes::menu();
        break;

        case scene::game:
            scenes::game();
        break;

        default:
            scenes::currentScene = scene::exit;
        break;

        }
    }
}