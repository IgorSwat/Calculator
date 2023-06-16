#ifndef NET_H
#define NET_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class Net : public sf::Drawable, public sf::Transformable
{
private:
    sf::Vector2i net_size;
    sf::Vector2i square_size;
    sf::VertexArray* vertices;
    void initialize_vertices(void);
public:
    explicit Net(const sf::Vector2i& nsize, const sf::Vector2i& ssize);
    Net(int nx = 100, int ny = 100, int sx = 20, int sy = 20);
    ~Net() {delete vertices;}
    void setColor(const sf::Color& color);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // NET_H
