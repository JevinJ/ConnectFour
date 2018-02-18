/*
 * options.hpp
 *
 *  Created on: Feb 8, 2018
 *      Author: Jevin
 */

#ifndef SRC_USEROPTIONS_HPP_
#define SRC_USEROPTIONS_HPP_
#include <SFML/Graphics.hpp>
#include "config.hpp"


struct UserOptions {
    void set_player_colors(sf::Color player_one_color, sf::Color player_two_color);
    bool isSinglePlayer = true;
    Difficulty difficulty;
    sf::Color player_one_color;
    sf::Color player_two_color;
};


#endif /* SRC_USEROPTIONS_HPP_ */
