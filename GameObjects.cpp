#include <SFML/Graphics.hpp>
#include "GameObjects.h"
#include <cstdlib>
#include <iostream>
#include <random>
#include <cmath>



using namespace std;

const float BALL_SPEED_X_LOW = 800;
const float BALL_SPEED_X_RANGE= 100;
const float BALL_SPEED_Y_LOW = 400;
const float BALL_SPEED_Y_RANGE = 50;

float BoardObject::boundY = 500;
const float OFFSET = 5;
bool BoardObject::collision(const BoardObject& a, const BoardObject& b){
    return b.x + b.width > a.x && b.y + b.height > a.y && a.x + a.width > b.x && a.y + a.height > b.y;
}

BoardObject::BoardObject(float X, float Y, float w, float h) : shape(sf::Vector2f(w,h)) {
    width = w;
    height = h;
    startX = x = X;
    startY = y = Y;
    shape.setFillColor(sf::Color::White);
    speedX = 0;
    speedY = 0;
}
float BoardObject::getX() const{ return x;}
float BoardObject::getY() const{ return y;}
void BoardObject::setX(float X){x = X;}
void BoardObject::setY(float Y){
    if (Y + height + OFFSET > BoardObject::boundY){
        y = BoardObject::boundY - height - OFFSET;
    }
    else if (Y < OFFSET){
        y = OFFSET;
    }
    else {
        y = Y;
    }
}
void BoardObject::setPosition(float X, float Y){
    setX(X);
    setY(Y);
}
void BoardObject::mve(float time_elapsed){
    setPosition(x + speedX*time_elapsed, y + speedY*time_elapsed);
}
void BoardObject::reset(){
    setPosition(startX, startY);
}
float BoardObject::getWidth() const { return width;}
float BoardObject::getHeight()const { return height;}
float BoardObject::getSpeedX()const {return speedX;}
float BoardObject::getSpeedY()const {return speedY;}
void BoardObject::setSpeedX(float dX){speedX = dX;}
void BoardObject::setSpeedY(float dY){speedY = dY;}

sf::RectangleShape& BoardObject::getShape(){return shape;}

void BoardObject::drawSelf(sf::RenderWindow& window){
    shape.setPosition(x,y);
    window.draw(shape);
}


Ball::Ball(float X, float Y, float R):BoardObject(X,Y,R,R), noiseX(0,BALL_SPEED_X_LOW/7), noiseY(0,BALL_SPEED_Y_LOW/5) {
    randomizeSpeeds();
}

void Ball::setY(float Y){
    if (Y+height + OFFSET > boundY || Y < 0 + OFFSET){
        speedY *= -1;
        speedY +=  noiseY(generator);
    }
    else{
        y = Y;
    }
}
void Ball::collidePaddle(float time_elapsed){
    speedX *= -1;
    mve(time_elapsed);
    speedX += noiseX(generator);
}
void Ball::randomizeSpeeds(){
    int xfac = 1;
    int yfac = 1;
    if (rand()%10 >= 5) xfac = -1;
    if (rand()%10 >= 5) yfac = -1;
    speedX = xfac*(BALL_SPEED_X_LOW+rand()%(int)BALL_SPEED_X_RANGE);
    speedY = yfac*(BALL_SPEED_Y_LOW+rand()%(int)BALL_SPEED_Y_RANGE);
}
void Ball::reset(){
    BoardObject::reset();
    randomizeSpeeds();

}
