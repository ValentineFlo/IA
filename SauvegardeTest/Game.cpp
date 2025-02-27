#include "Game.h"
Game::Game() 
    : window(sf::VideoMode(800, 600), "Mario Collecteur de Pieces")
    , saveFile(SaveFile("MySave.txt"))
    , deltaTime(0)
    //, npc(*this)
{
    font.loadFromFile("ariali.ttf");
    m_textScore.setFont(font);
    m_textScore.setCharacterSize(30);
    m_textScore.setFillColor(sf::Color::White);
    m_textScore.setPosition(10, 10);

    m_textPV_Player.setFont(font);
    m_textPV_Player.setCharacterSize(20);
    m_textPV_Player.setFillColor(sf::Color::Green);
    m_textPV_Player.setPosition(710, 570);

    m_textPV_MegaBoss.setFont(font);
    m_textPV_MegaBoss.setCharacterSize(20);
    m_textPV_MegaBoss.setFillColor(sf::Color::Red);
    m_textPV_MegaBoss.setPosition(10, 570);

    m_textPV_Boss.setFont(font);
    m_textPV_Boss.setCharacterSize(20);
    m_textPV_Boss.setFillColor(sf::Color::Magenta);
    m_textPV_Boss.setPosition(710, 10);


    player = new Player;
    pieces = new Pieces(player, score);
    projectiles = new Projectiles();
    boss = new Boss();
    megaboss = new MegaBoss();
    boss->setPieces(pieces);
    projectiles->SetPlayer(player);
    projectiles->SetTargetMegaBoss(megaboss);
    projectiles->SetTargetBoss(boss);
    megaboss->SetPlayer(player);

    gameObjects.push_back(player);
    gameObjects.push_back(pieces);
    gameObjects.push_back(projectiles);
    gameObjects.push_back(boss);
    gameObjects.push_back(megaboss);

    window.setFramerateLimit(60);
}

Game::~Game()
{
    for (auto objects : gameObjects)
        delete objects;
}

void Game::Run()
{
    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds(); 
        Events();
        Update(deltaTime);
        Draw();
    }
}

void Game::Events()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed ||
            (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
        {
            window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            saveFile.save(score, player->getPV(), boss->getPV(), megaboss->getPV());
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
        {
            int playerPV = 0, bossPV = 0, megabossPV = 0;

            saveFile.load(score, playerPV, bossPV, megabossPV);
            player->setPV(playerPV);
            boss->setPV(bossPV);
            megaboss->setPV(megabossPV);


            pieces->setScore(score);
        }

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !spaceRelach)
		{
			spaceRelach = true;
            projectiles->Shoot();
		}

        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            spaceRelach = false;
        }


        if (player->isDead())
			window.close();
    }
}

void Game::Update(const float& deltaTime)
{
    boss->setTargetPosition(player->getPosition());

    for (auto objects : gameObjects)
    {
        objects->Update(deltaTime);
    }
    score = pieces->getScore();
    m_textScore.setString("Score : " + std::to_string(score));
    m_textPV_Player.setString("PV : " + std::to_string(player->getPV()));
    m_textPV_Boss.setString("PV : " + std::to_string(boss->getPV()));
    m_textPV_MegaBoss.setString("PV : " + std::to_string(megaboss->getPV()));

}


void Game::Draw()
{
    window.clear();
    for (auto objects : gameObjects)
    {
        objects->Draw(window);
    }

    window.draw(m_textScore);
    window.draw(m_textPV_Player);
    window.draw(m_textPV_Boss);
    window.draw(m_textPV_MegaBoss);
    window.display();
}

