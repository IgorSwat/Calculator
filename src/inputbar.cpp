#include "inputbar.h"

//InputBar class
InputBar::InputBar(const sf::Vector2f& pos, sf::Font* font, unsigned int chrSize) :rmargin(pos)
{
    this->input = new sf::Text;
    this->input->setFont(*font);
    this->input->setString(" ");
    this->input->setFillColor(sf::Color::Black);
    this->input->setCharacterSize(chrSize);
    this->input->setPosition(rmargin);

    const float cursor_width = 2.f;
    this->cursor = new sf::RectangleShape(sf::Vector2f(cursor_width, static_cast<float>(chrSize + 4)));
    this->cursor->setFillColor(sf::Color::Blue);
    this->cursor->setPosition(rmargin.x - cursor_width, rmargin.y);

    this->time_to_reset = sf::microseconds(0);

    this->cursor_state = false;
    this->chChange = 0.0f;
}

void InputBar::updatePositioning()
{
    float len = input->findCharacterPos(input->getString().getSize()).x - input->findCharacterPos(0).x + 1.f;
    this->input->setPosition(rmargin.x - len, rmargin.y);
}

void InputBar::updateCursorPosition()
{
    this->cursor->setPosition(rmargin.x - 2.f, rmargin.y);
}

void InputBar::updateTime(sf::Clock& timer)
{
    this->time_to_reset = timer.getElapsedTime();
    if (time_to_reset > sf::seconds(0.5f))
    {
        this->cursor_state = !cursor_state;
        timer.restart();
    }
}

void InputBar::setInput(const std::string& in)
{
    this->input->setString(in);
    updatePositioning();
}

void InputBar::repairAddons()
{
    while (addons.size() > 0)
        addons.pop();
    addons.push(input->getString().getSize());
}

sf::String InputBar::getInput() const
{
    return input->getString();
}

void InputBar::setFillColor(const sf::Color& color)
{
    this->input->setFillColor(color);
}

void InputBar::addToInput(const std::string& in)
{
    sf::String new_string = input->getString();
    new_string += sf::String(in);
    this->addons.push(in.size());
    setInput(new_string);
}

void InputBar::popFromInput()
{
    sf::String new_string("");
    sf::String old_string = input->getString();
    int lup_size = addons.size() > 0 ? addons.top() : -1;
    if (lup_size > -1 && old_string.getSize() - lup_size >= 0)
    {
        for (size_t i = 0; i < old_string.getSize() - lup_size; i++)
            new_string += old_string[i];
        setInput(new_string);
        addons.pop();
    }
}

void InputBar::render(sf::RenderTarget& target) const
{
    target.draw(*input);
    if (cursor_state)
        target.draw(*cursor);
}
