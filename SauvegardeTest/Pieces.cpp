#include "Pieces.h"


Pieces::Pieces(Player* player, int score) : m_player(player), m_score(score)
{
    Init();
}

Pieces::~Pieces()
{

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
    winPieces();

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

void Pieces::setScore(int score)
{
    m_score = score;
}

int& Pieces::getScore()
{
    return m_score;
}

void Pieces::winPieces()
{
    for (auto it = m_pieces.begin(); it != m_pieces.end(); ++it)
    {
        if (m_player->GetBounds().intersects(it->getGlobalBounds()))
        {
            addScore(5);
            it = m_pieces.erase(it);
            break;
        }
    }
}

void Pieces::thievePieces()
{
    if (m_score > 0)
	{
		subScore(1);
	}
    else
    {
        m_score = 0;
    }

}

void Pieces::addScore(int changeScore)
{
    m_score += changeScore;
}

void Pieces::subScore(int changeScore)
{
    m_score -= changeScore;
}
