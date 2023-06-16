#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include "net.h"
// Buttons
class Button
{
protected:
    sf::RectangleShape* ground;
private:
    sf::Color def;
    sf::Color onCursor;
    sf::Color onClick;
    bool state1;
    bool state2;
public:
    explicit Button(const sf::Vector2f& size, const sf::Vector2f& pos, const sf::Color& fillColor);
    virtual ~Button() {delete ground;}
    bool updateState(const sf::RenderWindow& window);
    void setColor(const sf::Color& color);
    virtual void move(float x_move, float y_move);
    virtual void render(sf::RenderTarget& target) const;
};

class ButtonIMG : public Button
{
private:
    sf::Sprite* title;
public:
    explicit ButtonIMG(const sf::Vector2f& size, sf::Texture* texture, const sf::Vector2f& pos = sf::Vector2f(0.f, 0.f),
                       const sf::Color& fillColor = sf::Color(60, 80, 120, 120));
    virtual ~ButtonIMG() {delete title;}
    void setTitleScale(float xs, float ys);
    virtual void move(float x_move, float y_move);
    virtual void render(sf::RenderTarget& target) const;
};

class ButtonTXT : public Button
{
private:
    sf::Text* title;
    void updateTitlePosition(void);
public:
    explicit ButtonTXT(const sf::Vector2f& size, sf::Font* font, const sf::Color& titleColor = sf::Color::Black,
                       const sf::Vector2f& pos = sf::Vector2f(0.f, 0.f),
                       const sf::Color& fillColor = sf::Color(60, 80, 120, 120));
    virtual ~ButtonTXT() {delete title;}
    void setCharacterSize(unsigned int s);
    void setTitle(const std::string& caption);
    void setTitleColor(const sf::Color& color);
    virtual void move(float x_move, float y_move);
    virtual void render(sf::RenderTarget& target) const;
};

#endif // BUTTON_H
