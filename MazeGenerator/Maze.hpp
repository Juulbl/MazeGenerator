//
//  Maze.hpp
//  MazeGenerator
//
//  Created by Juul Bloemers on 17/05/2018.
//  Copyright © 2018 Juul Bloemers. All rights reserved.
//

#ifndef Maze_hpp
#define Maze_hpp

#include <stdio.h>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <ctime>

#include "MazeCell.hpp"

class Maze {
    
public:
    Maze(sf::Vector2f position, sf::Vector2f size, int wallWidth, sf::Vector2i cells, sf::Color backgroundColor, sf::Color wallColor);
    ~Maze();
    
    void Draw(sf::RenderWindow *window);
    
    sf::Vector2i GetSize();
    
    void Update();
    void RemoveWalls(MazeCell *cell1, MazeCell *cell2);
    
    MazeCell* GetCell(sf::Vector2i position);
    MazeCell* GetRandomNeighbor(MazeCell* cell);
    
private:
    std::vector<std::vector<MazeCell*>> cells;
    sf::Vector2i size;
    MazeCell *currentCell;
    std::vector<MazeCell*> stack;
};

#endif /* Maze_hpp */
