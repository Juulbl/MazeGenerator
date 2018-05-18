//
//  MazeCell.hpp
//  MazeGenerator
//
//  Created by Juul Bloemers on 17/05/2018.
//  Copyright © 2018 Juul Bloemers. All rights reserved.
//

#ifndef MazeCell_hpp
#define MazeCell_hpp

#include <stdio.h>
#include <iostream>
#include <stdint.h>
#include <SFML/Graphics.hpp>

class MazeCell {
    
public:
    MazeCell(sf::Vector2f position, sf::Vector2f size, int column, int row, float wallWidth, sf::Color backgroundColor, sf::Color wallColor);
    ~MazeCell();
    
    void Draw(sf::RenderWindow *window);
    
    uint8_t GetActiveWalls();
    void SetActiveWalls(uint8_t walls);
    void RemoveWalls(uint8_t walls);
    
    int GetColumn();
    int GetRow();
    
    bool isVisited = false;

private:
    int column = 0;
    int row = 0;
    
    sf::RectangleShape background;
    sf::RectangleShape walls[4];
    
    uint8_t activeWalls = 0b1111;
        
};

#endif /* MazeCell_hpp */
