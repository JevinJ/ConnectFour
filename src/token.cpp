/*
 * token.cpp
 *
 *  Created on: Dec 24, 2017
 *      Author: Jevin
 */

#include <iostream>
#include "config.hpp"
#include "token.hpp"
#include "resourcemanager.hpp"


Token::Token() :
    x_pos(0),
    y_pos(0) {
        model.setRadius(TOKEN_RADIUS);
        model.setTexture(&resource_manager.textures[Textures::TokenTexture]);
        model.setFillColor(sf::Color::Cyan);
}

Token::Token(sf::Color token_color) :
    x_pos(0),
    y_pos(0) {
        model.setRadius(TOKEN_RADIUS);
        model.setTexture(&resource_manager.textures[Textures::TokenTexture]);
        model.setFillColor(token_color);
}

//Copy constructor so we don't lose the token texture when it is invalidated.
Token::Token(const Token& original) {
    x_pos = original.x_pos;
    y_pos = original.y_pos;
    model = original.model;
    model.setTexture(&resource_manager.textures[Textures::TokenTexture]);
}

sf::Color Token::get_fill_color() const {
    return model.getFillColor();
}

float Token::get_radius() const {
    return model.getRadius();
}

/*
 * description:
 *     Sets the token model's position in pixels for use in drawing the model.
 */
void Token::set_pixel_position(const int x_pos_in_wall, const int y_pos_in_wall) {
    if(x_pos_in_wall < TOKEN_WALL_WIDTH and y_pos_in_wall <= TOKEN_WALL_HEIGHT+1) {
        x_pos = x_pos_in_wall;
        y_pos = y_pos_in_wall;
        const float token_diameter = TOKEN_RADIUS * 2;
        const unsigned int x_pos_in_pix = token_diameter * x_pos;
        const unsigned int y_pos_in_pix = (MAIN_WINDOW_HEIGHT-token_diameter) - (token_diameter*(y_pos-1));
        model.setPosition(x_pos_in_pix, y_pos_in_pix);
    }
}

/*
 * description:
 *     Sets the x position in as it is the token wall.
 *     WARNING: this is not the same as pixel position used to draw the model.
 */
void Token::set_x_position(const int x) {
    if(x >= 0 and x <= TOKEN_WALL_WIDTH) {
        x_pos = x;
    }
}

int Token::get_x_position() const {
    return x_pos;
}

/*
 * description:
 *     Sets the y position in as it is the token wall.
 *     WARNING: this is not the same as pixel position used to draw the model.
 */
void Token::set_y_position(const int y) {
    if(y >= 0 and y <= TOKEN_WALL_HEIGHT) {
        y_pos = y;
    }
}

int Token::get_y_position() const {
    return y_pos;
}

void Token::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(model, states);
}







