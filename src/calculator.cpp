#include "calculator.h"
#include <sstream>
#include <iomanip>
#include <iostream>
#include <thread>
#include <chrono>

const std::string button_titles1[40] {
    "(", ")", "1/x", "mc", "m+", "m-", "mr",
    "x^2", "x^3", "x^y", "C", "/", "\327", "del",
    "x!", "", "", "7", "8", "9", "-",
    "e", "ln", "log", "4", "5", "6", "+",
    "sin", "cos", "tan", "1", "2", "3", "Inv",
    "Deg", "", "%", "0", "."};

const std::string button_titles2[40] {
    "", "", "", "", "", "", "",
    "", "", "", "", "", "", "",
    "", "", "", "", "", "", "",
    "", "", "", "", "", "", "",
    "arcsin", "arccos", "arctan", "", "", "", "",
    "Rad", "", "", "", ""};

const std::string input_titles1[40] {
    "(", ")", "^(-1)", "", "", "", "",
    "^(2)", "^(3)", "^(", "", "/", "\327", "",
    "!", "sqrt(", "^(1/", "7", "8", "9", "-",
    "e", "ln(", "log(", "4", "5", "6", "+",
    "sin(", "cos(", "tan(", "1", "2", "3", "",
    "", "pi", "%", "0", "."};

const std::string input_titles2[40] {
    "(", ")", "^(-1)", "", "", "", "",
    "^(2)", "^(3)", "^(", "", "/", "\327", "",
    "!", "sqrt(", "^(1/", "7", "8", "9", "-",
    "e", "ln(", "log(", "4", "5", "6", "+",
    "arcsin(", "arccos(", "arctan(", "1", "2", "3", "",
    "", "pi", "%", "0", "."};

void Calculator::initializeTitles()
{
    for (int h = 0; h < 3; h++)
    {
        for (int l = 0; l < 3; l++)
        {
            const int id = 17 + 7*h + l;
            this->buttons[id]->setColor(sf::Color::White);
            this->buttons[id]->setCharacterSize(24);
            this->buttons[id]->setTitleColor(sf::Color::Black);
        }
    }
    for (int i = 37; i < 40; i++)
    {
        this->buttons[i]->setColor(sf::Color::White);
        this->buttons[i]->setCharacterSize(24);
        this->buttons[i]->setTitleColor(sf::Color::Black);
    }
    this->buttons[10]->setTitleColor(sf::Color::Blue);
    this->buttons[11]->setTitleColor(sf::Color::Blue);
    this->buttons[12]->setTitleColor(sf::Color(40, 20, 255, 180));
    this->buttons[12]->setCharacterSize(28);
    this->buttons[13]->setTitleColor(sf::Color::Blue);
    this->buttons[20]->setTitleColor(sf::Color(40, 20, 255, 200));
    this->buttons[20]->setCharacterSize(28);
    this->buttons[27]->setTitleColor(sf::Color(40, 20, 255, 200));
    this->buttons[27]->setCharacterSize(28);
    this->bigButton->setCharacterSize(28);

    for (int i = 0; i < 40; i++)
        this->buttons[i]->setTitle(button_titles1[i]);
    this->bigButton->setTitle("=");
}

Calculator::Calculator(const std::string& resourceFolder) : rectangleNet(sf::Vector2i(700, 300), sf::Vector2i(100, 50)),
                                                            current_state(Operator::NONE, 0.0)
{
    this->button_mode = false;
    this->angle_mode = false;
    this->mem = 0.0;
    this->font.loadFromFile(resourceFolder + "/Comfortaa-Regular.ttf");
    this->textures["PI"] = new sf::Texture;
    this->textures["PI"]->loadFromFile(resourceFolder + "/IMG_PI.png");
    this->textures["SQRT2"] = new sf::Texture;
    this->textures["SQRT2"]->loadFromFile(resourceFolder + "/IMG_SQRT2.png");
    this->textures["SQRT"] = new sf::Texture;
    this->textures["SQRT"]->loadFromFile(resourceFolder + "/IMG_SQRT.png");

    for (int i = 0; i < 34; i++)
    {
        this->buttons[i] = new ButtonTXT(sf::Vector2f(99.f, 49.f), &font, sf::Color(44, 44, 44),
                                            sf::Vector2f((i % 7)*100.f, 300.f + (i / 7)*50.f), sf::Color(220, 220, 220, 240));
        if (i % 7 == 6 || ((i > 2 && i < 6) || (i > 9 && i < 13)))
            this->buttons[i]->setColor(sf::Color(240, 240, 240, 250));
    }
    for (int i = 34; i < 40; i++)
    {
        this->buttons[i] = new ButtonTXT(sf::Vector2f(99.f, 49.f), &font, sf::Color(44, 44, 44),
                                         sf::Vector2f(((i + 1) % 7)*100.f, 550.f), sf::Color(220, 220, 220, 240));
    }
    this->bigButton = new ButtonTXT(sf::Vector2f(99.f, 99.f), &font, sf::Color::White, sf::Vector2f(600.f, 500.f), sf::Color(80, 40, 255));
    initializeTitles();

    this->rectangleNet.setPosition(0.f, 300.f);
    this->rectangleNet.setColor(sf::Color(52, 52, 52));

    this->bar = new InputBar(sf::Vector2f(650.f, 100.f), &font, 52);\

    this->whiteBar = new sf::RectangleShape(sf::Vector2f(60.f, 120.f));
    this->whiteBar->setPosition(0.f, 65.f);
    this->whiteBar->setFillColor(sf::Color::White);

    this->result = new InputBar(sf::Vector2f(650.f, 180.f), &font, 28);
    this->result->setFillColor(sf::Color(200, 200, 200));

    this->topleft = new sf::Text;
    this->topleft->setFont(font);
    this->topleft->setPosition(25.f, 10.f);
    this->topleft->setCharacterSize(15);
    this->topleft->setFillColor(sf::Color(120, 120, 120));
    this->topleft->setString("Rad");

    this->memText = new sf::Text;
    this->memText->setFont(font);
    this->memText->setPosition(80.f, 10.f);
    this->memText->setCharacterSize(15);
    this->memText->setFillColor(sf::Color(120, 120, 120));
    this->memText->setString("Memory: 0.000");

    this->isolation = new sf::Text;
    this->isolation->setFont(font);
    this->isolation->setPosition(65.f, 9.f);
    this->isolation->setCharacterSize(16);
    this->isolation->setFillColor(sf::Color(120, 120, 120));
    this->isolation->setString("|");

    this->piTexture = new sf::Sprite;
    this->piTexture->setTexture(*textures["PI"]);
    this->piTexture->setPosition(209.f, 541.f);
    this->piTexture->setColor(sf::Color(180, 180, 180));

    this->sqrtTexture = new sf::Sprite;
    this->sqrtTexture->setTexture(*textures["SQRT"]);
    this->sqrtTexture->setPosition(105.f, 386.f);
    this->sqrtTexture->setColor(sf::Color(180, 180, 180));

    this->sqrt2Texture = new sf::Sprite;
    this->sqrt2Texture->setTexture(*textures["SQRT2"]);
    this->sqrt2Texture->setPosition(217.f, 394.f);
    this->sqrt2Texture->setColor(sf::Color(180, 180, 180));

    this->parsing = new std::thread(&Calculator::executeParsing, this);
}

Calculator::~Calculator()
{
    is_running = false;
    for (auto p = textures.begin(); p != textures.end(); p++)
        delete p->second;
    delete piTexture;
    delete sqrtTexture;
    delete sqrt2Texture;
    for (int i = 0; i < 40; i++)
        delete buttons[i];
    delete bigButton;
    delete bar;
    delete whiteBar;
    delete topleft;
    delete memText;
    delete isolation;
    parsing->join();
    delete parsing;
}

void Calculator::updateMouse()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        this->mouse_statement = true;
    else
        this->mouse_statement = false;
}

void Calculator::clearContainers()
{
    operations.clear();
    while (addons.size() > 0)
        addons.pop();
}

bool Calculator::updateOperators(int key)
{
    bool any_change = true;
    switch (key)
    {
    case 0:
        operations.push_back(Operator(Operator::OPEN_BRACKET));
        addons.push(1);
        break;
    case 1:
        operations.push_back(Operator(Operator::CLOSE_BRACKET));
        addons.push(1);
        break;
    case 2:
        operations.push_back(Operator(Operator::POWER));
        operations.push_back(Operator(Operator::NUM, -1.0));
        addons.push(2);
        break;
    case 6:
        if (mem != 0.0)
        {
            operations.push_back(Operator(Operator::NUM, mem));
            addons.push(1);
        }
        break;
    case 7:
        operations.push_back(Operator(Operator::POWER));
        operations.push_back(Operator(Operator::NUM, 2.0));
        addons.push(2);
        break;
    case 8:
        operations.push_back(Operator(Operator::POWER));
        operations.push_back(Operator(Operator::NUM, 3.0));
        addons.push(2);
        break;
    case 9:
        operations.push_back(Operator(Operator::POWER));
        operations.push_back(Operator(Operator::OPEN_BRACKET));
        addons.push(2);
        break;
    case 10:
        clearContainers();
        break;
    case 11:
        operations.push_back(Operator(Operator::DIVIDE));
        addons.push(1);
        break;
    case 12:
        operations.push_back(Operator(Operator::MULTIPLY));
        addons.push(1);
        break;
    case 13:
        if (addons.size() > 0)
        {
            for (int i = 0; i < addons.top(); i++)
                operations.pop_back();
            addons.pop();
        }
        break;
    case 14:
        operations.push_back(Operator(Operator::STRONG));
        addons.push(1);
        break;
    case 15:
        operations.push_back(Operator(Operator::SQRT, 1.0));
        operations.push_back(Operator(Operator::OPEN_BRACKET));
        addons.push(2);
        break;
    case 16:
        operations.push_back(Operator(Operator::POWER));
        operations.push_back(Operator(Operator::OPEN_BRACKET));
        operations.push_back(Operator(Operator::DIVIDE, 1.0));
        addons.push(3);
        break;
    case 17:
        operations.push_back(Operator(Operator::NUM, 7.0));
        addons.push(1);
        break;
    case 18:
        operations.push_back(Operator(Operator::NUM, 8.0));
        addons.push(1);
        break;
    case 19:
        operations.push_back(Operator(Operator::NUM, 9.0));
        addons.push(1);
        break;
    case 20:
        operations.push_back(Operator(Operator::MINUS));
        addons.push(1);
        break;
    case 21:
        operations.push_back(Operator(Operator::E, 2.71828182845904523560));
        addons.push(1);
        break;
    case 22:
        operations.push_back(Operator(Operator::LN, 1.0));
        operations.push_back(Operator(Operator::OPEN_BRACKET));
        addons.push(2);
        break;
    case 23:
        operations.push_back(Operator(Operator::LOG, 1.0));
        operations.push_back(Operator(Operator::OPEN_BRACKET));
        addons.push(2);
        break;
    case 24:
        operations.push_back(Operator(Operator::NUM, 4.0));
        addons.push(1);
        break;
    case 25:
        operations.push_back(Operator(Operator::NUM, 5.0));
        addons.push(1);
        break;
    case 26:
        operations.push_back(Operator(Operator::NUM, 6.0));
        addons.push(1);
        break;
    case 27:
        operations.push_back(Operator(Operator::PLUS));
        addons.push(1);
        break;
    case 28:
        if (!button_mode)
            operations.push_back(Operator(Operator::SIN, 1.0));
        else
            operations.push_back(Operator(Operator::ARCSIN, 1.0));
        operations.push_back(Operator(Operator::OPEN_BRACKET));
        addons.push(2);
        break;
    case 29:
        if (!button_mode)
            operations.push_back(Operator(Operator::COS, 1.0));
        else
            operations.push_back(Operator(Operator::ARCCOS, 1.0));
        operations.push_back(Operator(Operator::OPEN_BRACKET));
        addons.push(2);
        break;
    case 30:
        if (!button_mode)
            operations.push_back(Operator(Operator::TAN, 1.0));
        else
            operations.push_back(Operator(Operator::ARCTAN, 1.0));
        operations.push_back(Operator(Operator::OPEN_BRACKET));
        addons.push(2);
        break;
    case 31:
        operations.push_back(Operator(Operator::NUM, 1.0));
        addons.push(1);
        break;
    case 32:
        operations.push_back(Operator(Operator::NUM, 2.0));
        addons.push(1);
        break;
    case 33:
        operations.push_back(Operator(Operator::NUM, 3.0));
        addons.push(1);
        break;
    case 36:
        operations.push_back(Operator(Operator::PI, 3.14159265359793238462));
        addons.push(1);
        break;
    case 37:
        operations.push_back(Operator(Operator::PERCENT));
        addons.push(1);
        break;
    case 38:
        operations.push_back(Operator(Operator::NUM, 0.0, 1));
        addons.push(1);
        break;
    case 39:
        operations.push_back(Operator(Operator::COMMA));
        addons.push(1);
        break;
    default:
        any_change = false;
        break;
    }
    return any_change;
}

Operator Calculator::parseOperators() const
{
    if (operations.size() == 0)
        return Operator(Operator::NONE);
    std::stack<Operator> S;
    unsigned int i = 0;
    unsigned int prev_lvl = 7;
    while (true)
    {
        if (S.size() == 0)
        {
            S.push(operations[i]);
            i++;
        }
        while (i < operations.size() && (operations[i].lvl < S.top().lvl || S.top().getMode() == Operator::OPEN_BRACKET))
        {
            prev_lvl = S.top().lvl;
            S.push(operations[i]);
            i++;
        }
        while (i < operations.size() && operations[i].lvl == 0 && S.top().lvl == 0)
        {
            Operator p = S.top()&operations[i];
            S.pop();
            S.push(p);
            i++;
        }
        unsigned int next_lvl = i != operations.size() ? operations[i].lvl : 7;
        while (S.size() > 1 && (prev_lvl <= next_lvl || next_lvl == 2) && (prev_lvl != 2 || S.top().lvl == 2 || next_lvl == 7))
        {
            Operator q = S.top();
            S.pop();
            Operator p = S.top();
            S.pop();
            prev_lvl = (S.size() != 0 ? S.top().lvl : 7);
            Operator r = p&q;
            S.push(r);
        }
        if (i == operations.size())
            break;
        if (S.top().lvl == next_lvl && next_lvl != 2)
            return Operator(Operator::ERROR);
        Operator p = S.top()&operations[i];
        S.pop();
        S.push(p);
        i++;
    }
    return S.top();
}

void Calculator::setResultText()
{
    if (current_state.lvl == 0)
    {
        double val = current_state.getVal();
        std::ostringstream valstr;
        valstr<<std::setprecision(15)<<val;
        this->result->setInput(valstr.str());
    }
    else if (current_state.getMode() == Operator::ERROR)
        this->result->setInput("Error");
    else
        this->result->setInput(" ");
}

void Calculator::setMemText()
{
    std::ostringstream strval;
    strval<<std::fixed<<std::setprecision(3)<<mem;
    this->memText->setString("Memory: " + strval.str());
}

void Calculator::executeParsing()
{
    while (is_running)
    {
        int count = change_count;
        if (count > 0)
        {
            current_state = parseOperators();
            change_count -= count;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void Calculator::prepareScreen()
{
    long double val = current_state.getVal();
    std::ostringstream valstr;
    valstr<<std::setprecision(15)<<val;
    this->bar->setInput(valstr.str());
    this->bar->repairAddons();
    clearContainers();
    this->operations.push_back(Operator(Operator::NUM, val));
    this->addons.push(1);
    this->current_state = Operator(Operator::NONE, val);
}

bool Calculator::updateButtons(sf::RenderWindow& window)
{
    int key = -1;
    for (int i = 0; i < 40; i++)
    {
        if (buttons[i]->updateState(window) && !mouse_statement)
        {
            key = i;
            switch (i)
            {
            case 3:
                this->mem = 0.0;
                setMemText();
                break;
            case 4:
                if (current_state.getMode() != Operator::ERROR)
                    this->mem += current_state.getVal();
                setMemText();
                break;
            case 5:
                if (current_state.getMode() != Operator::ERROR)
                    this->mem -= current_state.getVal();
                setMemText();
                break;
            case 6:
                if (mem != 0.0)
                {
                    std::ostringstream strval1;
                    strval1<<std::setprecision(15)<<mem;
                    this->bar->addToInput(strval1.str());
                    break;
                }
                break;
            case 10:
                this->bar->setInput("");
                this->bar->repairAddons();
                break;
            case 13:
                this->bar->popFromInput();
                break;
            case 34:
                this->button_mode = !button_mode;
                if (!button_mode)
                {
                    this->buttons[28]->setTitle(button_titles1[28]);
                    this->buttons[29]->setTitle(button_titles1[29]);
                    this->buttons[30]->setTitle(button_titles1[30]);
                }
                else
                {
                    this->buttons[28]->setTitle(button_titles2[28]);
                    this->buttons[29]->setTitle(button_titles2[29]);
                    this->buttons[30]->setTitle(button_titles2[30]);
                }
                break;
            case 35:
                this->angle_mode = !angle_mode;
                if (!angle_mode)
                {
                    this->topleft->setString("Rad");
                    this->buttons[35]->setTitle(button_titles1[35]);
                }
                else
                {
                    this->topleft->setString("Deg");
                    this->buttons[35]->setTitle(button_titles2[35]);
                }
                break;
            default:
                if (!button_mode)
                    this->bar->addToInput(input_titles1[i]);
                else
                    this->bar->addToInput(input_titles2[i]);
                break;
            }
        }
    }
    bool any_change = updateOperators(key);
    return any_change;
}

void Calculator::update(sf::RenderWindow& window)
{
    bool any_change = updateButtons(window);
    if (any_change)
        change_count += 1;
    if (bigButton->updateState(window) && !mouse_statement && current_state.getMode() != Operator::ERROR)
        prepareScreen();
    setResultText();
    this->bar->updateTime(timer);
    updateMouse();

}

void Calculator::render(sf::RenderTarget& target) const
{
    for (int i = 0; i < 40; i++)
        buttons[i]->render(target);
    target.draw(rectangleNet);
    bigButton->render(target);
    bar->render(target);
    result->render(target);
    target.draw(*whiteBar);
    target.draw(*piTexture);
    target.draw(*sqrtTexture);
    target.draw(*sqrt2Texture);
    target.draw(*topleft);
    target.draw(*memText);
    target.draw(*isolation);
}

