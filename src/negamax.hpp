/*
 * negamax.hpp
 *
 *  Created on: Jan 24, 2018
 *      Author: Jevin
 */

#ifndef NEGAMAX_HPP_
#define NEGAMAX_HPP_
#include <SFML/Graphics.hpp>
#include <vector>
#include "state.hpp"


int score(const int int_color, const int depth);
int negamax(std::vector<std::vector<int>>& int_token_wall, const int int_color, int alpha, const int beta, const int current_depth=0);


#endif /* NEGAMAX_HPP_ */
