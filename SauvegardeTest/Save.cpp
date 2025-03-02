#include "Save.h"


SaveFile::SaveFile(const std::string& filename) : m_filename(filename) {}

bool SaveFile::save(int score, int PV_Player, int PV_Boss, int PV_MegaBoss)
{
    std::ofstream file(m_filename);
    if (file.is_open())
    {
        /// Mettre les trucs a save
        file << score << std::endl;
        file << PV_Player << std::endl;
        file << PV_Boss << std::endl;
        file << PV_MegaBoss << std::endl;
        file.close();
        std::cout << "Partie sauvegardee!" << std::endl;
        return true;
    }
    else
        std::cout << "Erreur: Impossible de sauvegarder la partie" << std::endl;
    return false;
}

bool SaveFile::load(int& score, int& PV_Player, int& PV_Boss, int& PV_MegaBoss)
{
    std::ifstream file(m_filename);
    {
        if (file.is_open())
        {
            if (file >> score >> PV_Player >> PV_Boss >> PV_MegaBoss)
            {
                std::cout << "Partie chargee !" << std::endl;
                return true;
            }
            else
            {
                std::cout << "Erreur : Impossible de charger la partie" << std::endl;
            }
            file.close();
        }
        return false;

    }
}