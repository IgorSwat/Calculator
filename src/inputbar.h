#ifndef INPUTBAR_H
#define INPUTBAR_H

#include <stack>
#include <string>
#include "button.h"

class InputBar
{
private:
    struct Data
    {
        sf::Vector2f old_pos;
        sf::Color old_color;
        unsigned int old_char_size;
    };
    sf::Vector2f rmargin;
    sf::Text* input;
    sf::RectangleShape* cursor;
    sf::Time time_to_reset;
    bool cursor_state;
    std::stack<int> addons;
    Data data;
    float chChange;
    void updatePositioning(void);
    void updateCursorPosition(void);
public:
    InputBar(const sf::Vector2f& pos, sf::Font* font, unsigned int chrSize = 28);
    ~InputBar() {delete input; delete cursor;}
    void updateTime(sf::Clock& timer);
    void setInput(const std::string& in);
    void repairAddons(void);
    sf::String getInput(void) const;
    void setFillColor(const sf::Color& color);
    void addToInput(const std::string& in);
    void popFromInput(void);
    void render(sf::RenderTarget& target) const;
};

#endif // INPUTBAR_H
