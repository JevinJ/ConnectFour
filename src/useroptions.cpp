/*
 * options.cpp
 *
 *  Created on: Feb 8, 2018
 *      Author: Jevin
 */
#include <SFML/Graphics.hpp>
#include "config.hpp"
#include "useroptions.hpp"


void UserOptions::set_player_colors(sf::Color player_one_color, sf::Color player_two_color) {
    this->player_one_color = player_one_color;
    this->player_two_color = player_two_color;
}
