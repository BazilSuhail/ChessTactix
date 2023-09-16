#include<iostream>
#include <fstream>
#include"bscs22072_chess.h"
#include<Windows.h>
#include<SFML/Graphics.hpp>
using namespace sf;
using namespace std;
struct pos {
    int r, c;
};
pos get_xy(RenderWindow& W)
{
    sf::Event ev;
    while (1)
    {
        while (W.pollEvent(ev))
        {
            if (ev.type == ev.Closed)
                W.close();
            if (ev.type == ev.MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                auto po = sf::Mouse::getPosition(W);
                return { po.y,po.x };
            }
        }
    }
}
int main() {
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);
    //ShowWindow(hWnd, SW_MINIMIZE);

   /* HWND hWnd = GetConsoleWindow();
    FreeConsole(); */



    RenderWindow window(sf::VideoMode(1600, 850), "CHESS");

    Texture intro;
    intro.loadFromFile("Images/Introduction.png");
    sf::Sprite intr(intro);
    window.draw(intr);
    window.display();
    sf::sleep(sf::seconds(3.5));

    Texture S1, b1, b2;
    b1.loadFromFile("Images/back2.png");
    b2.loadFromFile("Images/back1.png");

    sf::Sprite back1(b1), back2(b2);
    int currentOption = 1;
    bool eval = false;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {

                window.close(); exit(0);
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::Up) {
                    currentOption = currentOption ^ 1;
                }
                else if (event.key.code == sf::Keyboard::Up) {
                    currentOption = (currentOption + 2) % 2;
                }
                else if (event.key.code == sf::Keyboard::Return) {
                    if (currentOption == 1) {
                        chess game;
                        game.play(window);
                    }
                    else if (currentOption == 0) {
                        chess game;
                        game.play_load(window);
                    }
                }
            }
        }
        window.clear();
        // Draw the current selected option
        if (currentOption == 1)
            window.draw(back1);
        else if (currentOption == 0)
            window.draw(back2);


        window.display();

    }






    //if (!S1.loadFromFile("background.png")) {
    //    cout << "Failed to load texture!";
    //}
    //Sprite s(S1);
    //s.setPosition(0, 0);
    //window.draw(s);
    //window.display();
    //pos p = get_xy(window);
    //int br = 101, bc = 101;
    //p.r = p.r / br;
    //p.c = p.c / bc;
    //if (p.r == 4 && p.c == 5) {
    //    chess game;
    //    game.play(window);
    //}
    //else {
    //    chess game;
    //    game.play_load(window);
    //}
    // 
    // 
    // 
    // 







    //Texture bck;

    //if (!bck.loadFromFile("chessback.png")) {
    //    cout << "Failed to load texture!" << std::endl;
    //    //return;
    //}

    //while (window.isOpen())
    //{
    //    Sprite b3(bck);
    //    b3.setPosition(0, 0);
    //    // Main game loop
    //    // Handle events
    //    sf::Event event;
    //    while (window.pollEvent(event))
    //    {
    //        switch (event.type)
    //        {
    //            // Window closed
    //        case sf::Event::Closed:
    //            window.close();
    //            break;

    //            // Key pressed
    //        case sf::Event::KeyPressed:
    //            if (event.key.code == sf::Keyboard::U)
    //            {
    //                chess game;
    //                game.play(window);
    //            }
    //            else if (event.key.code == sf::Keyboard::U)
    //            {
    //                std::cout << "The 'n' key was pressed!\n";
    //            }
    //            else if (event.key.code == sf::Keyboard::Escape)
    //            {
    //                window.close();
    //            }
    //            break;

    //        default:
    //            break;
    //        }
    //    }

    //}


    return 0;

}