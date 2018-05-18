//
//  Maze.cpp
//  MazeGenerator
//
//  Created by Juul Bloemers on 17/05/2018.
//  Copyright © 2018 Juul Bloemers. All rights reserved.
//

#include "Maze.hpp"

Maze::Maze(sf::Vector2f position, sf::Vector2f size, int wallWidth, sf::Vector2i cells, sf::Color backgroundColor, sf::Color wallColor) : size(cells)
{
    //Set random seed
    std::srand(std::time(nullptr));
    
    //Calculate cell size
    sf::Vector2f cellSize = sf::Vector2f(size.x / cells.x, size.y / cells.y);
    
    //Generate all cells and put them in cells
    for(int y = 0; y < cells.y; y++)
    {
        this->cells.push_back(std::vector<MazeCell*>());
        for(int x = 0; x < cells.x; x++)
        {
            this->cells[y].push_back(new MazeCell(sf::Vector2f(x * cellSize.x, y * cellSize.y), cellSize, x, y, wallWidth, backgroundColor, wallColor));
        }
    }
    
    //Set start cell
    this->currentCell = this->cells[0][0];
    this->stack.push_back(this->currentCell);
}

Maze::~Maze()
{
}

void Maze::Draw(sf::RenderWindow *window)
{
    //Draw all cells
    for(int y = 0; y < this->cells.size(); y++)
        for(int x = 0; x < this->cells[y].size(); x++)
            this->cells[y][x]->Draw(window);
}

void Maze::Update()
{
    this->currentCell->isVisited = true;
    MazeCell *nextCell = this->GetRandomNeighbor(this->currentCell);
    
    if(nextCell != nullptr)
    {
        //Remove walls between cells
        this->RemoveWalls(this->currentCell, nextCell);

        //Set current cell next cell
        this->currentCell = nextCell;
        
        this->stack.push_back(this->currentCell);
    }
    else
    {
        if(this->stack.size() > 1)
        {
            this->stack.pop_back();
            this->currentCell = this->stack[this->stack.size() - 1];
        }
    }
}

void Maze::RemoveWalls(MazeCell *cell1, MazeCell *cell2)
{
    if(cell1->GetColumn() == cell2->GetColumn() + 1)
    {
        cell1->RemoveWalls(0b1000);
        cell2->RemoveWalls(0b0010);
    }
    else if(cell1->GetColumn() == cell2->GetColumn() - 1)
    {
        cell1->RemoveWalls(0b0010);
        cell2->RemoveWalls(0b1000);
    }
    else if(cell1->GetRow() == cell2->GetRow() + 1)
    {
        cell1->RemoveWalls(0b0001);
        cell2->RemoveWalls(0b0100);
    }
    else  if(cell1->GetRow() == cell2->GetRow() - 1)
    {
        cell1->RemoveWalls(0b0100);
        cell2->RemoveWalls(0b0001);
    }
}

sf::Vector2i Maze::GetSize()
{
    return this->size;
}

MazeCell* Maze::GetCell(sf::Vector2i position)
{
    if(position.x < 0 || position.y < 0 || position.x >= this->size.x || position.y >= this->size.y)
    {
        return nullptr;
    }
    else return this->cells[position.y][position.x];
}

MazeCell* Maze::GetRandomNeighbor(MazeCell* cell)
{
    //Maze positon
    int column = cell->GetColumn();
    int row = cell->GetRow();
    
    std::vector<MazeCell*> availableNeighbors;
    
    MazeCell *tmpCell;
    //If can go up
    if(row > 0) {
        tmpCell = this->GetCell(sf::Vector2i(column, row - 1));
        if(!tmpCell->isVisited) availableNeighbors.push_back(tmpCell);
    }
    
    //If can go right
    if(column < this->size.x - 1) {
        tmpCell = this->GetCell(sf::Vector2i(column + 1, row));
        if(!tmpCell->isVisited) availableNeighbors.push_back(tmpCell);
    }
    
    //If can go down
    if(row < this->size.y - 1) {
        tmpCell = this->GetCell(sf::Vector2i(column, row + 1));
        if(!tmpCell->isVisited) availableNeighbors.push_back(tmpCell);
    }
    
    //If can go left
    if(column > 0) {
        tmpCell = this->GetCell(sf::Vector2i(column - 1, row));
        if(!tmpCell->isVisited) availableNeighbors.push_back(tmpCell);
    }
    
    //Return random neighbor
    if(availableNeighbors.size() == 0) return nullptr;
    else return availableNeighbors[(int)(std::rand() % availableNeighbors.size())];
}
