#include "Button.h"
#include <iostream>

sf::Button::Button(sf::RenderWindow *_window)
{
    if (!font.loadFromFile("/Users/indo.evri.momint/PhysicsModel1/src/fonts/Raleway-Light.ttf"))
    {
        throw std::runtime_error("Cannot load font");
    }

    window = _window;

    size = sf::Vector2f(120, 40);
    position = sf::Vector2f(0, 0);
    fontSize = sf::Button::Default_Font_Size;

    text.setFont(font);
    text.setString("Click me!");
    text.setCharacterSize(Button::Default_Font_Size);
    text.setFillColor(sf::Color::Black);

    fixTextPosition();

    shape = sf::RectangleShape(size);
    shape.setSize(size);
    shape.setFillColor(color[0]);
    shape.setPosition(position);

    activeButtons.insert(sf::Mouse::Button::Left);
    enabled = false;
}

sf::Button::Button(sf::RenderWindow *_window, sf::Vector2f initialSize, sf::Vector2f initialPosition, std::string initialText)
{
    if (!font.loadFromFile("/Users/indo.evri.momint/PhysicsModel1/src/fonts/Raleway-Light.ttf"))
    {
        throw std::runtime_error("Cannot load font");
    }

    window = _window;

    size = initialSize;
    position = initialPosition;
    fontSize = sf::Button::Default_Font_Size;

    text.setFont(font);
    text.setString(initialText);
    text.setCharacterSize(fontSize);
    text.setFillColor(sf::Color::Black);

    fixTextPosition();

    shape = sf::RectangleShape(size);
    shape.setSize(size);
    shape.setFillColor(color[0]);
    shape.setPosition(position);

    activeButtons.insert(sf::Mouse::Button::Left);
    enabled = false;
}

void sf::Button::draw(sf::RenderTarget &target, sf::RenderStates state) const
{
    target.draw(shape);
    target.draw(text);
}

void sf::Button::setOnClickListener(std::function<void()> callback)
{
    this->callback = callback;
}
void sf::Button::setOnClickListener2(std::function<void()> callback)
{
    this->callback2 = callback;
}

bool sf::Button::tryActivate()
{
    bool shouldActivate = false;

    /*
    for (sf::Mouse::Button button : activeButtons)
    {
        if ((shape.getPosition().x <= sf::Mouse::getPosition(*window).x <= shape.getPosition().x+size.x) && (shape.getPosition().y <= sf::Mouse::getPosition(*window).y <= shape.getPosition().y+size.y))
        {
            shouldActivate = true;
        }
    }
*/

    if ((shape.getPosition().x <= sf::Mouse::getPosition(*window).x &&  sf::Mouse::getPosition(*window).x <= shape.getPosition().x+size.x) && (shape.getPosition().y <= sf::Mouse::getPosition(*window).y && sf::Mouse::getPosition(*window).y  <= shape.getPosition().y+size.y))
    {
        shouldActivate = true;
    }

    if (!shouldActivate || callback == NULL)
    {
        return false;
    }
    ++cur_color;
    shape.setFillColor(color[cur_color%2]);
    if (cur_color% 2 == 1){
        callback();
    }
    else{
        callback2();
    }
    return true;
}

void sf::Button::setPosition(sf::Vector2f position)
{
    shape.setPosition(position);
    this->position = position;

    fixTextPosition();
}

void sf::Button::setSize(sf::Vector2f size)
{
    shape.setSize(size);
    this->size = size;

    fixTextPosition();
}

void sf::Button::fixTextPosition()
{
    float offset_y = (size.y - sf::Button::Default_Font_Size) / 2;
    float offset_x = (size.x - text.getLocalBounds().width) / 2;
    textPosition = sf::Vector2f(position.x + offset_x, position.y + offset_y);

    text.setPosition(textPosition);
}

void sf::Button::addActiveButton(sf::Mouse::Button button)
{
    activeButtons.insert(button);
}

void sf::Button::removeActiveButton(sf::Mouse::Button button)
{
    activeButtons.erase(button);
}