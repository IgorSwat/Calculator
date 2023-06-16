#include "calculator.h"
#include "Config.h"

int main()
{
    const sf::VideoMode mode(700, 600);
    sf::RenderWindow window(mode, "Calculator",
                            sf::Style::Close | sf::Style::Titlebar);
    window.setFramerateLimit(60);
    sf::Event event;
    Calculator myCalculator(RESOURCE_LOC);

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        myCalculator.update(window);
        myCalculator.render(window);
        window.display();
    }
    return 0;
}
