#include <SFML/Audio.hpp>
#include <filesystem>
#include <string>
#include <iostream>
#include <vector>


class Music
{
	std::string path;
	std::string currentPath;
	sf::Music m_music;
	std::vector<std::string> songs;
	int current;
public:
	Music();
	void update();
};