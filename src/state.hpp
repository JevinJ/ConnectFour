/*
 * state.hpp
 *
 *  Created on: Dec 26, 2017
 *      Author: Jevin
 */

#ifndef STATE_HPP_
#define STATE_HPP_
#include <SFML/Graphics.hpp>
#include <vector>
#include "board.hpp"
#include "player.hpp"


/*
 * description:
 *     Main interface for the objects and functions in this project.
 * State(): Constructs a board and player objects with default token colors(black for player, red for ai).
 * State(sf::Color, sf::Color): Same as default but you can use any colors supported by SFML,
 *                              param1: player_one token color:
 *                              param2: player_two token color.
 */
struct State {
    State();
    State(sf::Color, sf::Color);
    void draw();
    int get_best_move(const int int_color);
    Board board;
    Player player_one;
    Player player_two;
    sf::Clock alert_clock;
    std::string alert_message;
    sf::RenderWindow render_window;
};

bool isWinState(const std::vector<std::vector<int>>& int_token_wall, const int int_color);
bool isTieState(const std::vector<std::vector<int>>& int_token_wall);
std::vector<unsigned int> get_available_moves(const std::vector<std::vector<int>>& int_token_wall);


#endif /* STATE_HPP_ */
