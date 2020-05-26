#include <Music.h>


Music::Music()
{
    path = "./resources/music";
    current = 0;
    for (const auto& entry : std::filesystem::directory_iterator(path))
    {
        currentPath = entry.path().string();
        songs.push_back(currentPath);
    }
}

void Music::update()
{
    if (m_music.getStatus() == 0)
    {
        if (current >= songs.size())
            current = 0;
        m_music.openFromFile(songs[current]);
        current++;
        m_music.play();
    }
}