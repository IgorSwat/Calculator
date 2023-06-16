#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <map>
#include <vector>
#include <thread>
#include "operator.h"
#include "inputbar.h"

class Calculator
{
private:
    // graphic objects
    ButtonTXT* buttons[40];
    ButtonTXT* bigButton;
    InputBar* bar;
    InputBar* result;
    sf::RectangleShape* whiteBar;
    sf::Sprite* piTexture;
    sf::Sprite* sqrtTexture;
    sf::Sprite* sqrt2Texture;
    sf::Text* topleft;
    sf::Text* memText;
    sf::Text* isolation;
    Net rectangleNet;
    // calculations and others
    sf::Clock timer;
    Operator current_state;
    std::vector<Operator> operations;
    std::stack<int> addons;
    long double mem;
    bool mouse_statement;
    bool button_mode;
    bool angle_mode;
    bool is_running = true;
    int change_count = 0;
    // threads
    std::thread* parsing;
    // private functions
    void initializeTitles(void);
    void updateMouse(void);
    bool updateButtons(sf::RenderWindow& window);
    void changeButtons();
    bool updateOperators(int key);
    Operator parseOperators(void) const;
    void executeParsing(void);
    void clearContainers(void);
    void setResultText(void);
    void setMemText(void);
    void prepareScreen(void);
    // resources
    sf::Font font;
    std::map<std::string, sf::Texture*> textures;
public:
    Calculator(const std::string& resourceFolder);
    ~Calculator();
    void update(sf::RenderWindow& window);
    void render(sf::RenderTarget& target) const;
};

#endif // CALCULATOR_H
