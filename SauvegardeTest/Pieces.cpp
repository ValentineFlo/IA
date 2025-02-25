#include "Pieces.h"


Pieces::Pieces(Player* player, int score) : m_player(player), m_score(score)
{
    Init();
}

void Pieces::Init()
{
    m_pieces.clear();
    if (m_pieces.empty())
    {
        for (int i = 0; i < 10; i++)
        {
            sf::CircleShape piece(15);
            piece.setFillColor(sf::Color::Yellow);
            piece.setPosition(std::rand() % 750, std::rand() % 450);
            m_pieces.push_back(piece);
        }
    }
}
void Pieces::Update(float deltatime)
{
    auto it = m_pieces.begin();
    while (it != m_pieces.end())
    {
        std::cout << "score: " << m_score << std::endl;
        if (m_player->GetBounds().intersects(it->getGlobalBounds()))
        {
            it = m_pieces.erase(it);
            m_score += 10;
        }
        else
        {
            ++it;
        }
    }

    if (m_pieces.empty())
    {
        Init();
    }
}

void Pieces::Draw(sf::RenderWindow& window)
{
    for (const auto& piece : m_pieces)
    {
        window.draw(piece);
    }
}

int& Pieces::getScore()
{
    return m_score;
}

void Pieces::setScore(int score) 
{
    m_score = score; 
}

