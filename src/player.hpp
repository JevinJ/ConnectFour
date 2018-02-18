/*
 * player.hpp
 *
 *  Created on: Dec 26, 2017
 *      Author: Jevin
 */

#ifndef PLAYER_HPP_
#define PLAYER_HPP_
#include <stack>
#include "token.hpp"


class Player {
    std::stack<Token> player_tokens;
public:
    Player(const sf::Color token_color);
    Token take_token();
    int get_token_count() const;
};


#endif /* PLAYER_HPP_ */
