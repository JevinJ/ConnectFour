/*
 * negamax.hpp
 *
 *  Created on: Jan 24, 2018
 *      Author: Jevin
 */

#ifndef NEGAMAX_HPP_
#define NEGAMAX_HPP_


int score(const bool bool_color, const int depth);
int negamax(std::vector<std::vector<bool>>& bool_token_wall, const bool bool_color, int alpha, int beta, const Difficulty difficulty, const int current_depth=0);


#endif /* NEGAMAX_HPP_ */
