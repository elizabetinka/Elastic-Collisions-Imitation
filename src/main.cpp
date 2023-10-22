#include <SFML/Graphics.hpp>
#include <SFML/Window/Window.hpp>
#include "Model.h"
#include "TextField/TextField.h"
#include "Button/Button.h"
#include <iostream>

sf::Font font;



void ButtonFunc(Model& model){
    model.setActive();
}



enum MarksArray{
    m1Mark = 0,
    m2Mark = 1,
    vMark = 2,
    CollisionsNumberMark = 3,
    CollisionsNumber = 4,
    vMark1 = 5,
    vMark2 = 6,
    speed1 = 7,
    speed2 = 8
};

enum TextFieldArray{
    mass1 = 0,
    mass2 = 1,
    v = 2
};

void ButtonFunc2(Model& model,std::vector<TextField>& TestFields){
    model = Model();
    model.setPosition(0, 0);
    TestFields[mass1].setPlaceholder("100");
    TestFields[mass2].setPlaceholder("1");
    TestFields[v].setPlaceholder("5");
}

std::vector<sf::Text> initMarks(){
    std::vector<sf::Text> res(9);
    font.loadFromFile("/Users/indo.evri.momint/PhysicsModel1/src/fonts/Raleway-Light.ttf");

    res[m1Mark].setFont(font); //m1Mark
    res[m1Mark].setPosition(sf::Vector2f(LENGHT_SIZE-325,40));
    res[m1Mark].setString("m2:");
    res[m1Mark].setFillColor(MediumSlateBlueColor);

    res[m2Mark].setFont(font); //m2Mark
    res[m2Mark].setPosition(sf::Vector2f(LENGHT_SIZE-325,90));
    res[m2Mark].setString("m1:");
    res[m2Mark].setFillColor(MediumSlateBlueColor);


    res[vMark].setFont(font); //vMark
    res[vMark].setPosition(sf::Vector2f(LENGHT_SIZE-325,140));
    res[vMark].setString("v0:");
    res[vMark].setFillColor(MediumSlateBlueColor);

    res[CollisionsNumberMark].setFont(font); //CollisionsNumberMark
    res[CollisionsNumberMark].setPosition(sf::Vector2f(LENGHT_SIZE/2-3*res[CollisionsNumberMark].getCharacterSize(),120));
    res[CollisionsNumberMark].setString("Collision Count:");
    res[CollisionsNumberMark].setFillColor(sf::Color::Black);

    res[CollisionsNumber].setFont(font);
    res[CollisionsNumber].setPosition(sf::Vector2f(LENGHT_SIZE/2,160));
    res[CollisionsNumber].setString("Collision Count");
    res[CollisionsNumber].setFillColor(sf::Color::Black);


    res[vMark1].setFont(font);
    res[vMark1].setPosition(sf::Vector2f(135,40));
    res[vMark1].setString("v2:");
    res[vMark1].setFillColor(MediumSlateBlueColor);

    res[speed1].setFont(font);
    res[speed1].setPosition(sf::Vector2f(200,40));
    res[speed1].setString("speed1");
    res[speed1].setFillColor(sf::Color::Black);

    res[vMark2].setFont(font);
    res[vMark2].setPosition(sf::Vector2f(135,140));
    res[vMark2].setString("v1:");
    res[vMark2].setFillColor(MediumSlateBlueColor);

    res[speed2].setFont(font);
    res[speed2].setPosition(sf::Vector2f(200,140));
    res[speed2].setString("speed2");
    res[speed2].setFillColor(sf::Color::Black);

    return res;
}


std::vector<TextField> initTextField(){
    std::vector<TextField> res(3);
    font.loadFromFile("/Users/indo.evri.momint/PhysicsModel1/src/fonts/Raleway-Light.ttf");


    res[mass1].setFont(font);
    res[mass1].setPosition(sf::Vector2f(LENGHT_SIZE-250,40));
    res[mass1].setPlaceholder("100");
    res[mass1].setLength(16);


    res[mass2].setFont(font);
    res[mass2].setPosition(sf::Vector2f(LENGHT_SIZE-250,90));
    res[mass2].setPlaceholder("1");
    res[mass2].setLength(16);


    res[v].setFont(font);
    res[v].setPosition(sf::Vector2f(LENGHT_SIZE-250,140));
    res[v].setPlaceholder("5");
    res[v].setLength(16);
    //mass1.setLength(3);
    return res;

}
int main()
{
    auto window = sf::RenderWindow{ { LENGHT_SIZE, WIGHT_SIZE }, "Elastic Collisions Imitation" };
    window.setFramerateLimit(100);

    Model model;
    model.setPosition(0, 0);

    std::vector<sf::Text> Marks = initMarks();

    std::vector<TextField> TestFields = initTextField();

    // Create buttons
    sf::Button button1(&window, sf::Vector2f(100,40), sf::Vector2f(600, 50), "Start");

    button1.setOnClickListener([&]()
                               { model.setActive(); });

    button1.setOnClickListener2([&]()
                               { ButtonFunc2(model,TestFields); });

    for (auto & TestField : TestFields){
        TestField.render(window);
    }
    for (const auto & Mark : Marks){
        window.draw(Mark);
    }
    window.draw(model);
    window.display();

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed)
            {
                // Получаем нажатую клавишу - выполняем соответствующее действие
                if (event.key.code == sf::Keyboard::Space) {
                    window.close();
                }

                if (event.key.code == sf::Keyboard::Enter) {
                    for (auto & TestField : TestFields){
                        TestField.input(event);
                    }
                    try {
                    int m1 = std::stoi(TestFields[mass1].getText().toAnsiString());
                    int m2 = std::stoi(TestFields[mass2].getText().toAnsiString());
                    float vF = std::stof(TestFields[v].getText().toAnsiString());
                    model.setSpeed(vF);
                    model.setMass(m1,m2);
                }
                    catch (std::exception& e){
                        TestFields[mass1].setPlaceholder("100");
                        TestFields[mass2].setPlaceholder("1");
                        TestFields[v].setPlaceholder("5");
                    }
                }

            }
            // Check if event was mouse event
            if (event.type == sf::Event::MouseButtonPressed )
            {

                // Lazy evaluation because buttons are at the same position, therefore switching scenes
                // result in enabling button 2 and immidately going back to scene 1
                const bool pressed = button1.tryActivate();

                if (pressed)
                {
                    continue;
                }
            }
            for (auto & TestField : TestFields){
                TestField.input(event);
                TestField.render(window);
            }
        }
        if (model.getActive()){
            model.Move();
        }
        Marks[CollisionsNumber].setString(std::to_string(model.GetCollisions()));
        //Marks[speed1].setString(std::to_string(abs(model.GetSpeed1())));
        Marks[speed1].setString(std::to_string(model.GetSpeed1()));
        //Marks[speed2].setString(std::to_string(abs(model.GetSpeed2())));
        Marks[speed2].setString(std::to_string(model.GetSpeed2()));

        window.clear(BG);
        window.draw(model);
        window.draw(button1);

        for (const auto & Mark : Marks){
            window.draw(Mark);
        }
        for (auto & TestField : TestFields){
            TestField.render(window);
        }
        window.display();
    }
}