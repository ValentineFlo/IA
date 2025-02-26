#include "Save.h"


SaveFile::SaveFile(const std::string& filename) : m_filename(filename) {}

bool SaveFile::save(int& score)
{
    std::ofstream file(m_filename);
    if (file.is_open())
    {
        /// Mettre les trucs a save
        file << score;
        file.close();
        std::cout << "Partie sauvegardee!" << std::endl;
        std::cout << "Score save : " << score << std::endl;
        return true;
    }
    else
        std::cout << "Erreur: Impossible de sauvegarder la partie" << std::endl;
    return false;
}

bool SaveFile::load(int& score)
{
    std::ifstream file(m_filename);
    if (file.is_open())
    {
        if (file.good())
        {
            file >> score;
            file.close();
            std::cout << "Partie chargee!" << std::endl;
            std::cout << "Score charge : " << score << std::endl;
            std::cout << "Score charge afficher : " << score << std::endl;
            return true;
        }
    }
}