#include "net.h"

void Net::initialize_vertices()
{
    const int xfact = net_size.x / square_size.x;
    const int yfact = net_size.y / square_size.y;
    const int vertices_num = 2*(xfact + 1) + 2*(yfact + 1);
    for (int i = 0; i < 2*(yfact + 1); i += 2)
    {
        (*vertices)[i].position = sf::Vector2f(0.f, static_cast<float>((i/2)*square_size.y));
        (*vertices)[i + 1].position = sf::Vector2f(static_cast<float>(net_size.x), static_cast<float>((i/2)*square_size.y));
    }
    for (int i = 2*(yfact + 1); i < vertices_num; i += 2)
    {
        (*vertices)[i].position = sf::Vector2f(static_cast<float>((i - 2*(yfact + 1))*square_size.x/2), 0.f);
        (*vertices)[i + 1].position = sf::Vector2f(static_cast<float>((i - 2*(yfact + 1))*square_size.x/2), static_cast<float>(net_size.y));
    }
}

Net::Net(const sf::Vector2i& nsize, const sf::Vector2i& ssize) : net_size(nsize), square_size(ssize)
{
    if (net_size.x < square_size.x)
        square_size.x = net_size.x;
    if (net_size.y < square_size.y)
        square_size.y = net_size.y;
    this->vertices = new sf::VertexArray(sf::Lines, 2*(net_size.x / square_size.x + 1) + 2*(net_size.y / square_size.y + 1));
    initialize_vertices();
}

Net::Net(int nx, int ny, int sx, int sy) : net_size(nx, ny), square_size(sx, sy)
{
    if (net_size.x < square_size.x)
        square_size.x = net_size.x;
    if (net_size.y < square_size.y)
        square_size.y = net_size.y;
    this->vertices = new sf::VertexArray(sf::Lines, 2*(net_size.x / square_size.x + 1) + 2*(net_size.y / square_size.y + 1));
    initialize_vertices();
}

void Net::setColor(const sf::Color& color)
{
    const int vertices_num = 2*(net_size.x / square_size.x + 1) + 2*(net_size.y / square_size.y + 1);
    for (int i = 0; i < vertices_num; i++)
        (*vertices)[i].color = color;
}

void Net::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = nullptr;
    target.draw(*vertices, states);
}
