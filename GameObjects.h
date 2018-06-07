#ifndef GAMEOBJECTS_H_INCLUDED
#define GAMEOBJECTS_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <random>
class BoardObject{
    protected :
        float x, y, startX, startY, width, height, speedX, speedY;
        sf::RectangleShape shape;
    public :
        static float boundY;
        static bool collision(const BoardObject& a, const BoardObject& b);

        BoardObject(float X, float Y, float w, float h);

        float getX() const ;
        float getY() const ;
        void setX(float X);
        virtual void setY(float Y);
        void setPosition(float X, float Y);
        void mve(float time_elapsed);
        virtual void reset();

        float getWidth() const ;
        float getHeight() const ;

        float getSpeedX() const;
        float getSpeedY() const;
        void setSpeedX(float dX);
        void setSpeedY(float dy);

        sf::RectangleShape& getShape() ;
        void drawSelf(sf::RenderWindow& window);
};
class Ball : public BoardObject{
    private:
        std::normal_distribution<float> noiseX, noiseY;
        std::default_random_engine generator;
    public:
        Ball(float X, float Y, float R);
        void collidePaddle(float time_elapsed);
        void randomizeSpeeds();
        void reset() override;
        void setY(float Y)override;
};
#endif // GAMEOBJECTS_H_INCLUDED
