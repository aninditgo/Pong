#ifndef BOARDOBJECT_H_INCLUDED
#define BOARDOBJECT_H_INCLUDED

#include <SFML/Graphics.hpp>
class BoardObject{
    public :
        BoardObject(float width, float height);
        float x, y, width, height, speed;
        sf::Shape shape;
        void draw(const sf::RenderWindow& window);
        void setPosition(float x, float y);
        void move(float dX, float dY);
    static :
        bool collision(BoardObject a, BoardObject b);

};


#endif // BOARDOBJECT_H_INCLUDED
