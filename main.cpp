#include <SFML/Graphics.hpp>
#include <iostream>
#include "Players.h"
#include "GameObjects.h"
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace sf;
using namespace std;
const float BOARD_WIDTH = 700;
const float BOARD_HEIGHT = 400;
const float PADDLE_HEIGHT = 80;
const float PADDLE_WIDTH  = 100;
const float BALL_RAD = 20;
const float AI_SPEED  = 390;
const float FONT_SIZE  =40;
const float FRAME_RATE = 60;

int main()
{
    srand(time(NULL));
    BoardObject::boundY = BOARD_HEIGHT;
    RenderWindow window(sf::VideoMode(BOARD_WIDTH, BOARD_HEIGHT), "Pong");
    window.setFramerateLimit(FRAME_RATE);
    Clock clock;
    //Player p(-80, BOARD_HEIGHT/2 - PADDLE_HEIGHT/2, PADDLE_WIDTH, PADDLE_HEIGHT, 0, true);
    Player p(-90, BOARD_HEIGHT/2 - PADDLE_HEIGHT/2, PADDLE_WIDTH, PADDLE_HEIGHT, 0, true);
    Ball b(BOARD_WIDTH/2 - BALL_RAD/2, BOARD_HEIGHT/2 - BALL_RAD/2, BALL_RAD);
    AIPlayer ai(BOARD_WIDTH-10, BOARD_HEIGHT/2 - PADDLE_HEIGHT/2, PADDLE_WIDTH, PADDLE_HEIGHT, AI_SPEED, BOARD_WIDTH, false);
    sf::Font font;
    font.loadFromFile("score.ttf");
    sf::Text pscore;
    sf::Text aiscore;
    pscore.setFont(font);
    pscore.setString("0");
    pscore.setCharacterSize(FONT_SIZE);
    pscore.setPosition(BOARD_WIDTH/4-FONT_SIZE/2, FONT_SIZE);
    pscore.setFillColor(sf::Color::White);
    aiscore.setFont(font);
    aiscore.setString("0");
    aiscore.setFillColor(sf::Color::White);
    aiscore.setCharacterSize(FONT_SIZE);
    aiscore.setPosition(3*BOARD_WIDTH/4 - FONT_SIZE/2, FONT_SIZE);

    vector <RectangleShape> centerline;
    for (int i = 10; i < BOARD_HEIGHT; i +=30){
        RectangleShape r(sf::Vector2f(2,20));
        r.setPosition(BOARD_WIDTH/2-1, i);
        centerline.push_back(r);
    }
    bool playGame = false;
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed){
                playGame = true;
            }
        }
        Time elapsed = clock.restart();
        Vector2i localPosition = Mouse::getPosition(window);
        if (playGame){
            if (ai.getPaddle().getSpeedY() > abs(b.getSpeedY()))
                ai.getPaddle().setSpeedY(abs(b.getSpeedY()-15));
            p.setPaddleYPosition(localPosition.y);
            b.mve(elapsed.asSeconds());
            //p.makeMove(b, elapsed.asSeconds());
            ai.makeMove(b, elapsed.asSeconds());
            if (BoardObject::collision(p.getPaddle(), b) || BoardObject::collision(ai.getPaddle(), b))
                b.collidePaddle(elapsed.asSeconds());
            if (p.checkLost(b) || ai.checkLost(b)){
                if (p.checkLost(b)){
                    ai.incScore(1);
                    aiscore.setString(std::to_string((int)ai.getScore()));
                }
                else{
                    p.incScore(1);
                    pscore.setString(std::to_string((int)p.getScore()));
                }
                p.getPaddle().reset();
                ai.getPaddle().reset();
                b.reset();
                playGame = false;
            }
        }

        window.clear();
        for (RectangleShape r : centerline){
            window.draw(r);
        }
        b.drawSelf(window);
        p.getPaddle().drawSelf(window);
        ai.getPaddle().drawSelf(window);
        window.draw(aiscore);
        window.draw(pscore);
        window.display();
    }

    return 0;
}
