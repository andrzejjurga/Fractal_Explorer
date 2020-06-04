/*
 *author: Sebastian Jerzykiewicz
 */

#pragma once
#include <iostream>
#include <SFML/Audio.hpp>

class Sounds
{
public:
    Sounds();
    
    Sounds(std::string _filename);
    
    sf::Sound sound;
    
private:
    std::string filename;
    sf::SoundBuffer buffer;
};
