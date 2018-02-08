/*
 * token.hpp
 *
 *  Created on: Dec 25, 2017
 *      Author: Jevin
 */

#ifndef TOKEN_HPP_
#define TOKEN_HPP_
#include <SFML/Graphics.hpp>


/*
 * description:
 *     Contains a sf::CircleShape model with a set radius(config.hpp), sf::Color, pixel location and
 *         physical location in the token wall.
 * Token(sf::Color):
 *                  param1: Sets token color to this color.
 */
class Token : public sf::CircleShape {
    sf::CircleShape model;
    unsigned int x_pos;
    unsigned int y_pos;
public:
    Token();
    Token(sf::Color token_color);
    sf::CircleShape get_model() const;
    sf::Color get_fill_color() const;
    float get_radius() const;
    void set_pixel_position(const int x_pos_in_wall, const int y_pos_in_wall);
    int get_x_position() const;
    void set_x_position(const int x);
    int get_y_position() const;
    void set_y_position(const int y);
};


#endif /* TOKEN_HPP_ */
