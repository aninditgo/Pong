#include "GameObjects.h"
#include <cmath>
#include "Players.h"
#include <iostream>
using namespace std;

Player::Player(float X, float Y, float w, float h, int l, bool le) : paddle (X,Y,w,h){
    limit = l;
    left = le;
    score = 0;
}
void Player::setScore(int s){ score = s;}
void Player::incScore(int inc){ score += inc;}
int Player::getScore(){return score;}
BoardObject& Player::getPaddle(){return paddle;}
bool Player::checkLost(const Ball& b) const { return ((left && b.getX() < limit) || (!left && b.getX() + b.getWidth() >= limit)) && !BoardObject::collision(b, paddle); }
void Player::setPaddleYPosition(float Y){
    paddle.setY(Y-paddle.getHeight()/2);
}


AIPlayer::AIPlayer(float X, float Y, float w, float h, float speed, int l, bool le) : Player(X, Y, w, h, l, le) {
    paddle.setSpeedY(speed);
}
void AIPlayer::makeMove(Ball& b, float time_elapsed) {
    float centerY = paddle.getY() + paddle.getHeight()/2;
    if (centerY > b.getY()){
        paddle.setY(paddle.getY() - paddle.getSpeedY()*time_elapsed);
    }
    else {
        paddle.setY(paddle.getY() + paddle.getSpeedY()*time_elapsed);
    }
}
