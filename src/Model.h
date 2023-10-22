//
// Created by Елизавета Кравченкова on 16.10.2023.
//

#pragma once
#include <SFML/Graphics.hpp>
#include <algorithm>
#include "iostream"

const int MaxSquareSize = 200;
const int LENGHT_SIZE = 1280;
const int WIGHT_SIZE = 720;
const int LeftWallCoord = 35;
const int DownWallCoord = 80;
const sf::Color BG = sf::Color(230, 230, 250); //Lavender
const sf::Color MediumSlateBlueColor = sf::Color(123, 104, 238); //MediumSlateBlue

class Model : public sf::Drawable, public sf::Transformable {
    bool active= false;
    int CollisionsCount = 0;
    int WidthLine = WIGHT_SIZE - DownWallCoord;
    sf::Font font;
    sf::Color color1 = sf::Color(255, 20, 147); //Deep Pink
    sf::Color color2 = sf::Color(123, 104, 238); //MediumSlateBlue
    std::pair<float,float> _speed = std::pair<float,float>(-5,0);
    int _mass1 = 100;
    int _mass2 = 1;
    sf::RectangleShape shape1 = sf::RectangleShape(sf::Vector2f((float)GetSquareSize(_mass1), (float)GetSquareSize(_mass1)));
    sf::RectangleShape shape2 = sf::RectangleShape(sf::Vector2f((float)GetSquareSize(_mass2), (float)GetSquareSize(_mass2)));
    sf::RectangleShape wallLeft = sf::RectangleShape(sf::Vector2f(LeftWallCoord , WIGHT_SIZE));
    sf::RectangleShape wallDown = sf::RectangleShape(sf::Vector2f(LENGHT_SIZE, DownWallCoord));
    sf::RectangleShape wallInvisible = sf::RectangleShape(sf::Vector2f(LeftWallCoord, WIGHT_SIZE));
public:
    void setActive(){
        active = !active;
    }
    void setSpeed(float v){
        _speed = std::make_pair(-v,0);
    }
    bool getActive(){
        return active;
    }
    Model();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void Move();

    int GetCollisions(){
        return CollisionsCount;
    }
    float GetSpeed1(){
        return _speed.first;
    }
    float GetSpeed2(){
        return _speed.second;
    }
    void setMass(int mass1, int mass2){
        if (GetSquareSize(_mass1) == GetSquareSize(mass1) && GetSquareSize(_mass2) == GetSquareSize(mass2)){
            return;
        }
        _mass1 = mass1;
        _mass2 = mass2;
        auto coord = getSquareCoord();
        shape1.setPosition(coord.first.first,coord.first.second);
        shape2.setPosition(coord.second.first,coord.second.second);

        shape1.setSize(sf::Vector2f(GetSquareSize(_mass1),GetSquareSize(_mass1)));
        shape2.setSize(sf::Vector2f(GetSquareSize(_mass2),GetSquareSize(_mass2)));

        shape1.setOutlineThickness(2.f);
        shape1.setOutlineColor(color1);
        shape1.setFillColor(color1);

        shape2.setOutlineThickness(2.f);
        shape2.setOutlineColor(color2);
        shape2.setFillColor(color2);

    }
    void setStartSpeed(float v){
        _speed = std::make_pair(0,v);
    }

    std::pair<std::pair<float,float>,std::pair<float,float>> getSquareCoord() const {
        int size1 = GetSquareSize(_mass1);
        int size2 = GetSquareSize(_mass2);
        float LeftDist = 200;
        float RightDIst = 20;
        std::pair<float,float> first = std::make_pair(LENGHT_SIZE-std::max(RightDIst, (float)GetSquareSize(_mass1)) ,WidthLine-size1);
        std::pair<float,float> second = std::make_pair(LeftWallCoord + std::max(LeftDist, (float)GetSquareSize(_mass2)),WidthLine-size2);
        return std::make_pair(first,second);
    }

    int GetSquareSize(int mass) const {
        if (mass < 30){
            if (mass<10){
                return 30;
            }
            return 35;
        }
        if (mass>=10000){
            return 300;
        }
        if (mass > 100){
            return MaxSquareSize;
        }
        return (MaxSquareSize * mass)/100;
    }

    void Collision(){
        float speed1 = (2*(float)_mass2*_speed.second + (float)(_mass1-_mass2)*_speed.first)/(float)(_mass1+_mass2);
        float speed2 = (2*(float)_mass1*_speed.first + (float)(_mass2-_mass1)*_speed.second)/(float)(_mass1+_mass2);
        //std::cout<< "speed1 = " << speed1 << " speed2 = "<< speed2<< '\n' ;
        _speed =  std::make_pair(speed1,speed2);
    }
};

