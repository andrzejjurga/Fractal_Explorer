/*
 *author: Sebastian Jerzykiewicz
 */

#include "Sounds.hpp"

Sounds::Sounds()
{
    
}

Sounds::Sounds(std::string _filename)
{
    buffer.loadFromFile(_filename);
    sound.setBuffer(buffer);
}
