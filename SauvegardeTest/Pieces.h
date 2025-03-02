#pragma once
#include "Player.h"
class Game;

class Pieces : public IGameObject
{
public:
    /**
     * @brief Constructeur du MegaBoss.
     * @param pointeur vers player
     */
    Pieces(Player* player, int score);
    /**
     * @brief Destructeur du MegaBoss.
     */
    ~Pieces();
    /**
     * @brief initialise les pieces.
     */
    void Init() override;
    /**
     * @brief Met � jour les pieces.
     * @param deltatime Temps �coul� depuis la derni�re mise � jour.
     */
    void Update(float deltatime) override;
    /**
     * @brief Dessine les pieces � l'�cran.
     * @param window Fen�tre SFML dans laquelle dessiner.
     */
    void Draw(sf::RenderWindow& window) override;
    /**
     * @brief r�cup�re les pieces
     */
    int& getScore();
    /**
     * @brief change le score
     */
    void setScore(int score);

public:
    /**
     * @brief ajoute 5 au score lorsque l'on touche une piece
     */
    void winPieces();
    /**
     * @brief vole un certain score
     */
    void thievePieces();

public:
    /**
     * @brief ajoute au score
     */
    void addScore(int changeScore);
    /**
     * @brief soustrait au score
     */
    void subScore(int changeScore);

private:
    std::vector<sf::CircleShape> m_pieces;
    Player* m_player;
    int m_score;

};