//SFML C++ PACMAN pt 2
//created by Dr. Mo 11/21
//dynamicsofanasteroid.com

#include<iostream>
#include "SFML/Graphics.hpp"
#include"globals.h"
#include"ghost.h"
using namespace std;


int main() {
    //game set up (you'll need these lines in every game)
    sf::RenderWindow screen(sf::VideoMode(1600, 1600), "breakout"); //set up screen
    sf::Event event; //set up event queue
    sf::Clock clock; //set up the clock (needed for game timing)
    const float FPS = 60.0f; //FPS
    screen.setFramerateLimit(FPS); //set FPS

    //load in images
    sf::Texture brick;
    brick.loadFromFile("brick.png");
    sf::Sprite wall;
    wall.setTexture(brick);

    int map[20][20] = {
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,0,1,0,1,
        1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,1,1,1,0,1,
        1,0,0,0,1,1,0,0,1,1,1,1,1,0,0,0,0,0,0,1,
        1,1,0,0,0,1,0,0,0,0,0,1,1,0,1,1,1,1,0,1,
        1,0,0,1,0,0,0,1,1,0,0,0,1,0,1,0,0,1,0,1,
        0,0,1,1,1,0,1,1,1,1,0,0,1,0,0,0,0,0,0,0,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,1,
        1,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,0,1,
        1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,1,0,1,
        1,0,1,0,0,1,1,0,0,0,1,1,0,1,0,1,0,1,0,1,
        1,0,1,1,0,0,0,1,1,1,0,0,0,1,0,1,0,1,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,
        1,0,0,1,1,1,1,0,0,0,1,1,1,1,0,0,0,1,0,1,
        1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,1,0,0,1,
        1,0,0,1,1,1,1,1,1,1,1,0,1,0,1,1,0,1,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    };

    //player setup
    int xpos = 85;
    int ypos = 85;
    int vx = 0;
    int vy = 0;
    int radius = 25;
    sf::CircleShape dot(5);
    sf::CircleShape player(25);
    dot.setFillColor(sf::Color(250, 250, 250));
    player.setFillColor(sf::Color(250, 250, 0)); //using RGB value for color here (hex also works)
    player.setPosition(xpos, ypos); //top left "corner" of circle (not center!)
    bool keys[] = { false, false, false, false };


    ghost Blinky;
    Blinky.initGhost(215, 105, 1, 0, 1, sf::Color(123,211,222));

    ghost Bob;
    Bob.initGhost(230, 390, 1, 0, 1, sf::Color(255,0,255));

    ghost Greg;
    Greg.initGhost(1260, 545, 1, 0, 1, sf::Color(255, 140, 0));

    ghost Dwayne;
    Dwayne.initGhost(130, 1280, 1, 0, 1, sf::Color(205, 127, 50));
   

    
    //################### HOLD ONTO YOUR BUTTS, ITS THE GAME LOOP###############################################################
    while (screen.isOpen()) {//keep window open until user shuts it down
   cout << xpos << ", " << ypos << endl;
        while (screen.pollEvent(event)) { //look for events-----------------------
           
            //this checks if the user has clicked the little "x" button in the top right corner
            if (event.type == sf::Event::EventType::Closed)
                screen.close();
            //KEYBOARD INPUT 
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                keys[LEFT] = true;
            }
            else keys[LEFT] = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                keys[RIGHT] = true;
            }
            else keys[RIGHT] = false;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                keys[UP] = true;
            }
            else keys[UP] = false;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                keys[DOWN] = true;
            }
            else keys[DOWN] = false;



        }//end event loop---------------------------------------------------------------

         //move Mr. Pac
        if (keys[LEFT] == true)
            vx = -5;

        else if (keys[RIGHT] == true)
            vx = 5;

        else vx = 0;

        if (keys[UP] == true)
            vy = -5;

        else if (keys[DOWN] == true)
            vy = 5;

        else vy = 0;

        //RIGHT COLLISION
        if (vx > 0 &&
            //check if TOP right corner has hit
            ((map[(ypos) / 80]
                [(xpos + 5 + (radius * 2)) / 80] == 1) ||
                //check if BOTTOM right corner has bumped
                (map[(ypos + (radius * 2)) / 80]
                    [(xpos + 5 + (radius * 2)) / 80] == 1))) {
            vx = 0;
            cout << "colliding RIGHT";

        }
        //LEFT COLLISION
        else  if (vx < 0 && //check if you're going left
           //check if TOP left corner has hit
            ((map[(ypos) / 80]
                [(xpos - 5) / 80] == 1) ||
                //check if BOTTOM left corner has bumped
                (map[(ypos + (radius * 2)) / 80]
                    [(xpos - 5) / 80] == 1))) {
            vx = 0;
            cout << "colliding LEFT";

        }
        //DOWN COLLISION
        if (vy > 0 &&
            //check if bottom right corner has hit
            ((map[(ypos + 5 + (radius * 2)) / 80]
                [(xpos) / 80] == 1) ||
                //check if BOTTOM right corner has bumped
                (map[(ypos + 5 + (radius * 2)) / 80]
                    [(xpos + (radius * 2)) / 80] == 1))) {
            vy = 0;
            cout << "colliding DOWN";

        }
        //UP COLLISION
        else if (vy < 0 &&
            ((map[(ypos - 5) / 80]
                [(xpos + (radius * 2)) / 80] == 1) ||
                //check if BOTTOM right corner has bumped
                (map[(ypos - 5 + (radius * 2)) / 80]
                    [(xpos + (radius * 2)) / 80] == 1))) {
            vy = 0;
            cout << "colliding UP";

        }
        //warp zone
        if (xpos < -5 && ypos >= 585 && ypos < 645)
            xpos = 1543;
        if (xpos > 1543 && ypos >= 585 && ypos < 645)
            xpos = -5;
        
        xpos += vx;
        ypos += vy;
        player.setPosition(xpos, ypos);

        Blinky.chase1(xpos, ypos, map);
        Bob.chase2(xpos, ypos, map);
        Greg.chase3(xpos, ypos, map);
        Dwayne.chase4(xpos, ypos, map);
        if (map[ypos / 80][xpos / 80] == 0)
            map[ypos / 80][xpos / 80] = -1;


        //render section-----------------------------------------
        screen.clear(); //wipes screen, without this things smear

        //draw map
        for (int rows = 0; rows < 30; rows++)
            for (int cols = 0; cols < 30; cols++) {
                if (map[rows][cols] == 1) {
                    wall.setPosition(cols * 80, rows * 80);
                    screen.draw(wall);
                }
                if (map[rows][cols] == 0) {
                    dot.setPosition(cols * 80+40, rows * 80+40);
                    screen.draw(dot);
                }
            }

   
        Blinky.drawGhost(screen);
        Bob.drawGhost(screen);
        Greg.drawGhost(screen);
        Dwayne.drawGhost(screen);
        screen.draw(dot);
        screen.draw(player); //draw player
        screen.display(); //flips memory drawings onto screen

    }//######################## end game loop ###################################################################################

    cout << "goodbye!" << endl;
} //end of main





