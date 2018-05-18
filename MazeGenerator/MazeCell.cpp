//
//  MazeCell.cpp
//  MazeGenerator
//
//  Created by Juul Bloemers on 17/05/2018.
//  Copyright © 2018 Juul Bloemers. All rights reserved.
//

#include "MazeCell.hpp"

MazeCell::MazeCell(sf::Vector2f position, sf::Vector2f size, int column, int row, float wallWidth, sf::Color backgroundColor, sf::Color wallColor)
{
    //Create background
    this->background = sf::RectangleShape(size);
    this->background.setPosition(position);
    this->background.setFillColor(backgroundColor);
    
    //Create walls
    this->walls[0] = sf::RectangleShape(sf::Vector2f(size.x, wallWidth));
    this->walls[0].setPosition(sf::Vector2f(position.x, position.y));
    this->walls[0].setFillColor(wallColor);
    
    this->walls[1] = sf::RectangleShape(sf::Vector2f(wallWidth, size.y));
    this->walls[1].setPosition(sf::Vector2f(position.x + size.x - wallWidth, position.y));
    this->walls[1].setFillColor(wallColor);
    
    this->walls[2] = sf::RectangleShape(sf::Vector2f(size.x, wallWidth));
    this->walls[2].setPosition(sf::Vector2f(position.x, position.y + size.y - wallWidth));
    this->walls[2].setFillColor(wallColor);
    
    this->walls[3] = sf::RectangleShape(sf::Vector2f(wallWidth, size.y));
    this->walls[3].setPosition(sf::Vector2f(position.x, position.y));
    this->walls[3].setFillColor(wallColor);
    
    //Set column and row
    this->column = column;
    this->row = row;
}

MazeCell::~MazeCell()
{
}

void MazeCell::Draw(sf::RenderWindow *window)
{
    if(this->isVisited) window->draw(this->background);
    if(this->activeWalls & 0b1) window->draw(this->walls[0]);
    if((this->activeWalls >> 1) & 0b1) window->draw(this->walls[1]);
    if((this->activeWalls >> 2) & 0b1) window->draw(this->walls[2]);
    if((this->activeWalls >> 3) & 0b1) window->draw(this->walls[3]);
}

uint8_t MazeCell::GetActiveWalls()
{
    return this->activeWalls;
}

void MazeCell::SetActiveWalls(uint8_t walls)
{
    this->activeWalls = walls;
}

void MazeCell::RemoveWalls(uint8_t walls)
{
    this->activeWalls &= (walls ^ 0b1111);
}

int MazeCell::GetColumn()
{
    return this->column;
}

int MazeCell::GetRow()
{
    return this->row;
}
