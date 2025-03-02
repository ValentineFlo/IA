#pragma once
#include "IGameObjects.h"
#include "Pieces.h"
#include "Scenes.h"
#include "Boss.h"
#include "MegaBoss.h"
#include "Projectiles.h"
#include "Save.h"

/**
 * @class Game
 * @brief Boucle de jeu
 *
 * Cette classe g�re les comportements les �v�nements, l'update et les dessines
 */

class Game
{
public:
    /**
     * @brief Constructeur du Game.
     */
    Game();
    /**
     * @brief Destructeur du Game.
     */
    ~Game();
    /**
     * @brief Execute la boucle 
     */
    void Run();

private:
    /**
     * @brief G�re les events
     */
    void Events();
    /**
     * @brief Met � jour le game.
     * @param deltatime Temps �coul� depuis la derni�re mise � jour.
     */
    void Update(const float& deltaTime);
    /**
     * @brief Dessine le m�gaboss � l'�cran.
     * @param window Fen�tre SFML dans laquelle dessiner.
     */
    void Draw();


private:
    sf::RenderWindow window;
    sf::Clock clock;
    float deltaTime;
    sf::Font font;
    sf::Text m_textScore;
    sf::Text m_textPV_Player;
    sf::Text m_textPV_Boss;
    sf::Text m_textPV_MegaBoss;
    std::vector<IGameObject*> gameObjects;
    int score = 0;
    bool spaceRelach;
    SaveFile saveFile;
    Pieces* pieces;
    Projectiles* projectiles;
    ProjectilesMegaBoss* projectilesMegaBoss;
    Player* player;
    Boss* boss;
    MegaBoss* megaboss;

};