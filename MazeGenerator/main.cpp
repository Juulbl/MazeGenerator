#include <SFML/Graphics.hpp>

//Includes
#include "Maze.hpp"

int main(int argc, char** argv)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Maze generator", sf::Style::Fullscreen);
    
    window.setFramerateLimit(0);
    
    //Create maze
    Maze *maze = new Maze(sf::Vector2f(0, 0), sf::Vector2f(window.getSize().x, window.getSize().y), 4, sf::Vector2i(80, 45), sf::Color::White, sf::Color::Black);
	
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch(event.type){
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }
        
        maze->Update();

        // Clear screen
        window.clear();
        
        maze->Draw(&window);

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
