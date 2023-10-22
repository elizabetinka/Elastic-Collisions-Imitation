//
// Created by Елизавета Кравченкова on 16.10.2023.
//

#include "Model.h"

Model::Model()
{
    shape1.setOutlineThickness(2.f);
    shape1.setOutlineColor(color1);
    shape1.setFillColor(color1);

    shape2.setOutlineThickness(2.f);
    shape2.setOutlineColor(color2);
    shape2.setFillColor(color2);

    auto coord = getSquareCoord();
    shape1.setPosition(coord.first.first,coord.first.second);
    shape2.setPosition(coord.second.first,coord.second.second);

    wallDown.setPosition(0,WidthLine);
    wallLeft.setPosition(0,0);
    wallInvisible.setPosition(LENGHT_SIZE,0);
    wallInvisible.setFillColor(BG);
    wallDown.setFillColor(sf::Color(105,105,105));
    wallLeft.setFillColor(sf::Color(105,105,105));
}

void Model::Move()
{
    if (shape2.getPosition().x > LENGHT_SIZE && _speed.second > _speed.first){
        ++CollisionsCount;
        Collision();
    }
    /*
    else if (shape2.getPosition().x > LENGHT_SIZE && _speed.second <0){
        shape2.setPosition(LENGHT_SIZE-_speed.second,shape2.getPosition().y);
    }
     */
    else if (shape2.getGlobalBounds().intersects(wallLeft.getGlobalBounds())){
        ++CollisionsCount;
        _speed.second = -_speed.second;
        shape2.setPosition(std::max((float)LeftWallCoord,shape2.getPosition().x),shape2.getPosition().y);
        //std::cout<< "l speed1 = " << _speed.first << " speed2 = "<< _speed.second<< '\n' ;
    }
    else if (shape2.getGlobalBounds().intersects(shape1.getGlobalBounds()))
        {
            ++CollisionsCount;
            Collision();
        }
    else if (shape1.getGlobalBounds().intersects(shape2.getGlobalBounds()))
    {
        ++CollisionsCount;
        Collision();
    }

    else if (shape1.getGlobalBounds().intersects(wallLeft.getGlobalBounds())){
        //_speed.first = -_speed.first;
        //std::cout<< "l2 speed1 = " << _speed.first << " speed2 = "<< _speed.second<< '\n' ;
    }
/*
    if (shape2.getGlobalBounds().intersects(wallInvisible.getGlobalBounds())){
        _speed.second = -_speed.second;
    }
    if (shape1.getGlobalBounds().intersects(wallInvisible.getGlobalBounds())){
        if (_speed.first > 0){
            _speed.first = -_speed.first;
        }
    }
     */
    //_speed = SpeedAfterCollision(_speed,_mass1,_mass2);
    shape2.setPosition(std::max(shape2.getPosition().x+_speed.second,(float)LeftWallCoord),shape2.getPosition().y);
    shape1.setPosition(std::max(shape1.getPosition().x+_speed.first,shape2.getPosition().x),shape1.getPosition().y);

    if (shape1.getPosition().x < (shape2.getPosition().x + (float)GetSquareSize(_mass2))){
        shape1.setPosition(shape2.getPosition().x + (float)GetSquareSize(_mass2),shape1.getPosition().y);
    }

}

void Model::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();

    // Рисуем рамку игрового поля
    target.draw(shape1, states);
    target.draw(shape2, states);
    target.draw(wallDown,states);
    target.draw(wallLeft,states);

}
