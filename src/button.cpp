#include "button.h"
#include <math.h>
// Buttons
Button::Button(const sf::Vector2f& size, const sf::Vector2f& pos, const sf::Color& fillColor): def(fillColor),
    onCursor(sf::Color(fillColor.r - 20, fillColor.g - 10, fillColor.b, fillColor.a)),
    onClick(sf::Color(fillColor.r - 60, fillColor.g - 20, fillColor.b, fillColor.a))
{
    this->ground = new sf::RectangleShape(size);
    this->ground->setFillColor(fillColor);
    this->ground->setPosition(pos);

    this->state1 = false;
    this->state2 = false;
}

bool Button::updateState(const sf::RenderWindow& window)
{
    bool isClicked = false;
    sf::FloatRect bound = ground->getGlobalBounds();
    sf::Vector2f mousePos(static_cast<float>(sf::Mouse::getPosition(window).x),
                           static_cast<float>(sf::Mouse::getPosition(window).y));
    if (!bound.contains(mousePos))
    {
        if (state1)
            this->ground->setFillColor(def);
        state1 = state2 = false;
    }
    else
    {
        if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (state2 || !state1)
                this->ground->setFillColor(onCursor);
            state1 = true;
            state2 = false;
        }
        else
        {
            if (!state2)
            {
                this->ground->setFillColor(onClick);
                isClicked = true;
            }
            state1 = true;
            state2 = true;
        }
    }
    return isClicked;
}

void Button::setColor(const sf::Color& color)
{
    this->def = color;
    this->ground->setFillColor(def);
    this->onCursor = sf::Color(def.r - 20, def.g - 10, def.b, def.a);
    this->onClick = sf::Color(def.r - 60, def.g - 20, def.b, def.a);
}

void Button::move(float x_move, float y_move)
{
    this->ground->move(x_move, y_move);
}

void Button::render(sf::RenderTarget& target) const
{
    target.draw(*ground);
}

ButtonIMG::ButtonIMG(const sf::Vector2f& size, sf::Texture* texture,
                     const sf::Vector2f& pos, const sf::Color& fillColor): Button(size, pos, fillColor)
{
    this->title = new sf::Sprite(*texture);
    this->title->setPosition(ground->getPosition().x + 0.2f*ground->getSize().x,
                             ground->getPosition().y + 0.2*ground->getSize().y);
    this->title->setScale(0.6f*ground->getSize().x / texture->getSize().x,
                          0.6f*ground->getSize().y / texture->getSize().y);
}

void ButtonIMG::setTitleScale(float xs, float ys)
{
    this->title->setScale(xs*ground->getSize().x / ground->getTexture()->getSize().x,
                          ys*ground->getSize().y / ground->getTexture()->getSize().y);
}

void ButtonIMG::move(float x_move, float y_move)
{
    Button::move(x_move, y_move);
    this->title->move(x_move, y_move);
}

void ButtonIMG::render(sf::RenderTarget& target) const
{
    Button::render(target);
    target.draw(*title);
}

void ButtonTXT::updateTitlePosition()
{
    const int chSize = title->getCharacterSize();
    float titleLen = title->findCharacterPos(title->getString().getSize() - 1).x - title->findCharacterPos(0).x + chSize / 2.f;
    this->title->setPosition(ground->getPosition().x + (ground->getSize().x - titleLen) / 2.f,
                             ground->getPosition().y + (ground->getSize().y - chSize) / 2.f);
}

ButtonTXT::ButtonTXT(const sf::Vector2f& size, sf::Font* font, const sf::Color& titleColor,
                     const sf::Vector2f& pos, const sf::Color& fillColor): Button(size, pos, fillColor)
{
    this->title = new sf::Text;
    this->title->setFont(*font);
    this->title->setCharacterSize(16);
    updateTitlePosition();
    this->title->setFillColor(titleColor);
}

void ButtonTXT::setCharacterSize(unsigned int s)
{
    this->title->setCharacterSize(s);
    updateTitlePosition();
}

void ButtonTXT::move(float x_move, float y_move)
{
    Button::move(x_move, y_move);
    this->title->move(x_move, y_move);
}

void ButtonTXT::setTitle(const std::string& caption)
{
    this->title->setString(caption);
    updateTitlePosition();
}

void ButtonTXT::setTitleColor(const sf::Color& color)
{
    this->title->setColor(color);
}

void ButtonTXT::render(sf::RenderTarget& target) const
{
    Button::render(target);
    target.draw(*title);
}
