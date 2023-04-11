#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <map>
#include <unordered_map>
#include <vector>
#include <fstream>
#include "TextureManager.h"
#include "Random.h"
#include "Clicker.h"
#include "Board.h"
#include "Numbers.h"
using namespace std;
using namespace sf;


int main()
{
    sf::Sprite number1Sprite(TextureManager::GetTexture("number_1"));
    sf::Sprite number2Sprite(TextureManager::GetTexture("number_2"));    
    sf::Sprite number3Sprite(TextureManager::GetTexture("number_3"));
    sf::Sprite number4Sprite(TextureManager::GetTexture("number_4"));
    sf::Sprite number5Sprite(TextureManager::GetTexture("number_5"));
    sf::Sprite number6Sprite(TextureManager::GetTexture("number_6"));
    sf::Sprite number7Sprite(TextureManager::GetTexture("number_7"));
    sf::Sprite number8Sprite(TextureManager::GetTexture("number_8"));
    sf::Sprite debug(TextureManager::GetTexture("debug"));
    sf::Sprite digits(TextureManager::GetTexture("digits"));
    sf::Sprite facehappy(TextureManager::GetTexture("face_happy"));
    sf::Sprite facelose(TextureManager::GetTexture("face_lose"));
    sf::Sprite facewin(TextureManager::GetTexture("face_win"));
    sf::Sprite flag(TextureManager::GetTexture("flag"));
    sf::Sprite mine(TextureManager::GetTexture("mine"));
    sf::Sprite test1(TextureManager::GetTexture("test_1"));
    sf::Sprite test2(TextureManager::GetTexture("test_2"));
    sf::Sprite test3(TextureManager::GetTexture("test_3"));
    sf::Sprite tilehidden(TextureManager::GetTexture("tile_hidden"));
    sf::Sprite tilerevealed(TextureManager::GetTexture("tile_revealed"));

    sf::Sprite digNeg(TextureManager::GetTexture("digits"));
    digNeg.setTextureRect(sf::IntRect(210, 0, 25, 128));
    sf::Sprite digOne(TextureManager::GetTexture("digits"));
    digOne.setTextureRect(sf::IntRect(32, 0, 8, 128));
    sf::Sprite digTwo(TextureManager::GetTexture("digits"));
    digTwo.setTextureRect(sf::IntRect(40, 0, 20, 128));
    sf::Sprite digThree(TextureManager::GetTexture("digits"));
    digThree.setTextureRect(sf::IntRect(64, 0, 20, 128));
    sf::Sprite digFour(TextureManager::GetTexture("digits"));
    digFour.setTextureRect(sf::IntRect(84, 0, 20, 128));
    sf::Sprite digFive(TextureManager::GetTexture("digits"));
    digFive.setTextureRect(sf::IntRect(104, 0, 20, 128));
    sf::Sprite digSix(TextureManager::GetTexture("digits"));
    digSix.setTextureRect(sf::IntRect(124, 0, 20, 128));
    sf::Sprite digSeven(TextureManager::GetTexture("digits"));
    digSeven.setTextureRect(sf::IntRect(150, 0, 20, 128));
    sf::Sprite digEight(TextureManager::GetTexture("digits"));
    digEight.setTextureRect(sf::IntRect(170, 0, 20, 128));
    sf::Sprite digNine(TextureManager::GetTexture("digits"));
    digNine.setTextureRect(sf::IntRect(190, 0, 20, 128));
    sf::Sprite digZero(TextureManager::GetTexture("digits"));
    digZero.setTextureRect(sf::IntRect(0, 0, 32, 128));

    int width = 0;
    int height = 0;
    int mineCount = 0;

        ifstream file("boards/config.cfg");
        if (file.is_open()) {
            string line;
            string temp;
            int index = 0;
            getline(file, temp);
            width = stoi(temp);
            getline(file, temp);
            height = stoi(temp);
            getline(file, temp);
            mineCount = stoi(temp);
            while (getline(file, line)) {
                index = line.find(' ');
                width = stoi(line.substr(0, index));
                line = line.substr(index + 1);
                index = line.find(' ');
                height = stoi(line.substr(0, index));
                line = line.substr(index + 1);
                index = line.find(' ');
                mineCount = stoi(line.substr(0, index));
                line = line.substr(index + 1);
            }
        }
   
    int boardHiddenTestArray[50][50];
    int boardHiddenArray[50][50];
    int boardHiddenArrayRevealing[50][50];
    int boardHiddenArrayExtra[50][50];

    int mineCountCounter = 0;
    int g, h, i, j;

    for (i = 0; i < width; i++) {
        for (j = 0; j < height; j++) {
            boardHiddenArrayRevealing[i][j] = 10;
            g = Random::Int(0, width - 1);
            h = Random::Int(0, height - 1);
        
            if ((mineCountCounter < mineCount)) {
                    boardHiddenArray[g][h] = 9;
                    mineCountCounter++;   
                }
          
        }
        if (mineCountCounter < mineCount&& i == width-1 && j == height -1) {
            for (int i = 0; i < width; i++) {
                for (int j = 0; j < height; j++) {
                    if (boardHiddenArray[g][h] != 9) {
                        boardHiddenArray[g][h] = 9;
                        mineCountCounter++;
                    }
                }
            }
        }
    }


    Numbers::numberCalculator(width, height, boardHiddenArray); //calculates number of mines around a space

    //tester under here
    sf::RenderWindow window(sf::VideoMode(width *32, height *32 + 88), "Minesweeper");
  //  int randomX = Random::Int(0, window.getSize().x);
  //  int RandomY = Random::Int(0, window.getSize().y);



    int counter = 0;
    while (window.isOpen())
    {
        
       // window.clear();
        int x = Mouse::getPosition(window).x / 32;
        int y = Mouse::getPosition(window).y / 32;
        
        sf::Event event;
        sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            //

            
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.key.code == Mouse::Left && boardHiddenArray[x][y] != 43 && boardHiddenArray[x][y] != 9) {
                    if (x >= 0 && x < width && y >= 0 && y < height) {
                        cout << boardHiddenArrayRevealing[x][y] << " " << boardHiddenArray[x][y] << endl;//this code reveals the top layer when clicked on
                    boardHiddenArrayRevealing[x][y] = 44;
                   //this section should send to reveal
                    Numbers::recursion(width, height, boardHiddenArray, x , y , boardHiddenArrayRevealing);
                   
                   //
                }
                    
                    
                   // cout << "Array : " << boardHiddenArray[x][y] << endl << "Array hidden: " << boardHiddenArrayRevealing[x][y];
                   // boardHiddenArray[x][y] = boardHiddenArrayRevealing[x][y];
                   // cout << "clicked left x: " << x << " and y " <<  y;
                   // cout << "Array : " << boardHiddenArray[x][y] << endl << "Array hidden: " << boardHiddenArrayRevealing[x][y];

                }
                else if (event.key.code == Mouse::Left && (boardHiddenArray[x][y] == 43 || boardHiddenArray[x][y] == 9)) {
                    if (x >= 0 && x < width && y >= 0 && y < height) {
                        cout << boardHiddenArrayRevealing[x][y] << " " << boardHiddenArray[x][y] << endl;
                        boardHiddenArrayRevealing[x][y] = 44;
                        for (i = 0; i < width; i++) {
                            for (j = 0; j < height; j++) {
                                if (boardHiddenArray[i][j] == 9) {
                                    boardHiddenArray[i][j] = 43;
                                }
                            }
                        }
                        facelose.setPosition(width * 32 - 384, height * 32);
                        facehappy.setScale(0.0f, 0.0f);
                    }
                }
                else if ((event.key.code == Mouse::Right) && boardHiddenArrayRevealing[x][y] != 44) { //works great don't you dare touch it -_-
                    //places flag correctly
                    boardHiddenArrayRevealing[x][y] = 11;
                    if (Clicker::mouseClickerCheckerRight(flag, mouse) == 1) {
                        mineCount++;
                        boardHiddenArrayRevealing[x][y] = 10;

                    }else if (Clicker::mouseClickerCheckerRight(flag, mouse) != 1) {//works ok
                        boardHiddenArrayRevealing[x][y] = 11;

                        mineCount--;
                    }
                    
                }
            }
           
            if (facehappy.getScale().x != 0.0f && facehappy.getScale().y != 0.0f) {
                for (i = 0; i < width; i++) {
                    for (j = 0; j < height; j++) {
                        if (boardHiddenArray[i][j] == 44 && boardHiddenArray[i][j] != 9) {

                        }
                        else {
                            break;
                        }
                    }
                    if (i == width - 1 && j == height - 1) {
                        cout << "win";
                        facewin.setPosition(facehappy.getPosition());
                        window.draw(facewin);

                        for (i = 0; i < width; i++) {
                            for (j = 0; j < height; j++) {
                                if (boardHiddenArray[i][j] == 9) {
                                    boardHiddenArray[i][j] = 43;
                                }
                            }
                        }




                    }
                }

            }
            
        }
     

        window.clear();

        //-------------temp maybe ---------------//
        int j = 0;
        int i = 0;
        for (i = 0; i < width; i++) {
            for (j = 0; j < height; j++) { //draw bottom board
                tilerevealed.setPosition(i * 32, j * 32);
                window.draw(tilerevealed);
            }
        }
    
        //-------------temp maybe ---------------//

 
        for ( i = 0; i < width; i++) {
            for (j = 0; j < height; j++) {
                if (boardHiddenArray[i][j] == 9) {
                    mine.setPosition(i * 32, j * 32);
                    window.draw(mine);

                }
                if (boardHiddenArray[i][j] == 1) {
                    number1Sprite.setPosition(i * 32, j * 32);
                    window.draw(number1Sprite);
                }
                if (boardHiddenArray[i][j] == 2) {
                    number2Sprite.setPosition(i * 32, j * 32);
                    window.draw(number2Sprite);

                }
                if (boardHiddenArray[i][j] == 3) {
                    number3Sprite.setPosition(i * 32, j * 32);
                    window.draw(number3Sprite);

                }
                if (boardHiddenArray[i][j] == 4) {
                    number4Sprite.setPosition(i * 32, j * 32);
                    window.draw(number4Sprite);

                }
                if (boardHiddenArray[i][j] == 5) {
                    number5Sprite.setPosition(i * 32, j * 32);
                    window.draw(number5Sprite);

                }
                if (boardHiddenArray[i][j] == 6) {
                    number6Sprite.setPosition(i * 32, j * 32);
                    window.draw(number6Sprite);
                }
                if (boardHiddenArray[i][j] ==7) {
                    number7Sprite.setPosition(i * 32, j * 32);
                    window.draw(number7Sprite);

                }
                if (boardHiddenArray[i][j] == 8) {
                    number8Sprite.setPosition(i * 32, j * 32);
                    window.draw(number8Sprite);

                }
                if (boardHiddenArray[i][j] == 25) {
                    boardHiddenArrayRevealing[i][j] = 11;// boardHiddenArray[i][j]; //use this late to click on flags
                }
                // boardHiddenArrayRevealing[i][j] = boardHiddenArray[i][j];
                 //tilehidden.setTextureRect(IntRect(boardHiddenArrayRevealing[i][j] * 32, 32     , 32, 32));
                if (boardHiddenArrayRevealing[i][j] == 20) {
                    boardHiddenArrayRevealing[i][j] = 8;
                }

                else if (boardHiddenArray[i][j] == 43) {
                    //boardHiddenArray[i][j] = 0;
                    mine.setPosition(i * 32, j * 32);
                    window.draw(mine);
                }
                else if(boardHiddenArrayRevealing[i][j] != 44)/*(boardHiddenArrayRevealing[i][j] == 1, 2, 3, 4, 5, 6, 7, 8, 9)*/ {
                    tilehidden.setPosition(i * 32, j * 32);
                    window.draw(tilehidden); /////////////////////////////////////////////////////////////////////////////////////////////iportant part of code

                }
                
            }
        }

         j = 0;
         i = 0;
        
        for (i = 0; i < width; i++) {
             for (j = 0; j < height; j++) {
                 if (boardHiddenArrayRevealing[i][j] == 11 || boardHiddenArrayRevealing[i][j] == 25) {
                     flag.setPosition(i * 32, j * 32);
                     window.draw(flag);
                 }
             }
         }
       
        window.draw(facehappy);
        facehappy.setPosition(width * 32 - 384, height * 32);
        window.draw(debug);
        debug.setPosition(width*32 - 256, height*32);
        window.draw(test1);
        test1.setPosition(width * 32 - 192, height * 32 );
        window.draw(test2);
        test2.setPosition(width * 32 - 128, height * 32 );
        window.draw(test3);
        test3.setPosition(width * 32-64, height * 32 );
     

        // -----------------------------------------------------//
        

       
        sf::Vector2f location;
        

        if (Clicker::mouseClickerChecker(test1, mouse) == 1) {//return 1 means it is contained by mouse                           
            Board::testImplementation("testboard1", width, boardHiddenTestArray, boardHiddenArray,  boardHiddenArrayRevealing,  height);
            for (i = 0; i < width; i++) {
                for (j = 0; j < height; j++) {
                    if (boardHiddenTestArray[i][j] == 1) {
                        boardHiddenTestArray[i][j] = 9; 
                    }
                    boardHiddenArrayRevealing[i][j] = 10;

                    boardHiddenArray[i][j] = boardHiddenTestArray[i][j];
                }
            }
            Numbers::numberCalculator(width, height, boardHiddenArray);

        }
        else if (Clicker::mouseClickerChecker(test2, mouse) == 1) {//return 1 means it is contained by mouse                           
            Board::testImplementation("testboard2", width, boardHiddenTestArray, boardHiddenArray, boardHiddenArrayRevealing, height);
            for (i = 0; i < width; i++) {
                for (j = 0; j < height; j++) {
                    if (boardHiddenTestArray[i][j] == 1) {
                        boardHiddenTestArray[i][j] = 9;
                    }
                    boardHiddenArrayRevealing[i][j] = 10;
                    boardHiddenArray[i][j] = boardHiddenTestArray[i][j];
                }
            }
            Numbers::numberCalculator(width, height, boardHiddenArray);

        }
        else if (Clicker::mouseClickerChecker(test3, mouse) == 1) {//return 1 means it is contained by mouse                           
            Board::testImplementation("testboard3", width, boardHiddenTestArray, boardHiddenArray, boardHiddenArrayRevealing, height);
            for (i = 0; i < width; i++) {
                for (j = 0; j < height; j++) {
                    if (boardHiddenTestArray[i][j] == 1) {
                        boardHiddenTestArray[i][j] = 9;
                    }
                    boardHiddenArrayRevealing[i][j] = 10;

                    boardHiddenArray[i][j] = boardHiddenTestArray[i][j];
                }
            }
            Numbers::numberCalculator(width, height, boardHiddenArray);

        }
        
        else if (Clicker::mouseClickerChecker(facehappy, mouse) == 1) {
            for (i = 0; i < width; i++) {
                for (j = 0; j < height; j++) {
                    boardHiddenArrayRevealing[i][j] = 10;
                }
            }
            Board::reset(width, height, boardHiddenArray, mineCount, mineCountCounter, boardHiddenArrayRevealing);
            //facelose.setScale(0.0f, 0.0f);
          //  facehappy.setPosition(width * 32 - 384, height * 32);
            Numbers::numberCalculator(width, height, boardHiddenArray);
        }
        
        else if (Clicker::mouseClickerChecker(facelose, mouse) == 1) {
            for (i = 0; i < width; i++) {
                for (j = 0; j < height; j++) {
                    boardHiddenArrayRevealing[i][j] = 10;
                }
            }
            Board::reset( width, height,boardHiddenArray,mineCount, mineCountCounter, boardHiddenArrayRevealing);
           // facelose.setScale(0.0f, 0.0f);
          //  facehappy.setPosition(width * 32 - 384, height * 32);
            Numbers::numberCalculator(width, height, boardHiddenArray);
        }
     


        /*
        else if (Clicker::mouseClickerChecker(facewin, mouse) == 1) {
            for (i = 0; i < width; i++) {
                for (j = 0; j < height; j++) {
                    boardHiddenArrayRevealing[i][j] = 10;
                }
            }
            Board::reset(width, height, boardHiddenArray, mineCount, mineCountCounter, boardHiddenArrayRevealing);

        }
        */
     
      
        if (Clicker::mouseRightClicker(tilehidden, mouse) == 1) {//return 1 means it is contained by mouse
            
            boardHiddenArray[i][j] = 25;
            }
         
        
        if (Clicker::mouseClickerChecker(debug, mouse) == 1) {//return 1 means it is contained by mouse//works great
            //while (true){
           // if (oddEvenCount % 2 == 0) {
            for (i = 0; i < width; i++) {
                for (j = 0; j < height; j++) {
                    if (boardHiddenArray[i][j] == 9) {
                        boardHiddenArray[i][j] = 43;
                    }
                }
            }
        }
        x = mouse.x;
        y = mouse.y;
        x = x / 32;
        y = y / 32;

     
        if (facehappy.getScale().x == (0.0f) && facehappy.getScale().y == (0.0f)) {
            window.draw(facelose);
        }
        Numbers::NumberCounter(window,mineCount,height,  digNeg,  digOne,digTwo, digThree,  digFour, digFive, digSix, digSeven,  digEight,  digNine, digZero);
        window.display();
      
    }
    //clear out any textures before end
    TextureManager::Clear();
    return 0;
}