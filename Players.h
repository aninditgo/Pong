#ifndef PLAYERS_H_INCLUDED
#define PLAYERS_H_INCLUDED
#include "GameObjects.h"
#include "Players.h"

class Player{
    protected :
        int score, limit;
        BoardObject paddle;
        bool left;
    public :
        Player(float X, float Y, float w, float h, int l, bool le);
        int getScore();
        void incScore(int inc);
        void setScore(int s);
        bool checkLost (const Ball& b) const;
        void setPaddleYPosition(float y);
        BoardObject& getPaddle();

};
class AIPlayer : public Player{
    public :
        AIPlayer(float X, float Y, float w, float h, float speed, int l, bool le);
        void makeMove(Ball& b, float time_elapsed) ;
};

#endif // PLAYERS_H_INCLUDED
