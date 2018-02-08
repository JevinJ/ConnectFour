/*
 * player.cpp
 *
 *  Created on: Dec 26, 2017
 *      Author: Jevin
 */

#include <SFML/Graphics.hpp>
#include <stack>
#include "config.hpp"
#include "player.hpp"
#include "token.hpp"


Player::Player(sf::Color token_color) {
    for(unsigned int i = 0; i < MAX_PLAYER_TOKENS; ++i) {
        player_tokens.push(Token(token_color));
    }
}

Token Player::take_token() {
    Token top = player_tokens.top();
    player_tokens.pop();
    return top;
}

int Player::get_token_count() {
    return player_tokens.size();
}


