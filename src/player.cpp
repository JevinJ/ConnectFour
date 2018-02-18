/*
 * player.cpp
 *
 *  Created on: Dec 26, 2017
 *      Author: Jevin
 */

#include <SFML/Graphics.hpp>
#include "config.hpp"
#include "player.hpp"


Player::Player(const sf::Color token_color) {
    for(unsigned int i = 0; i < MAX_PLAYER_TOKENS; ++i) {
        player_tokens.push(Token(token_color));
    }
}

Token Player::take_token() {
    if(player_tokens.size() != 0) {
        Token top = player_tokens.top();
        player_tokens.pop();
        return top;
    }
}

int Player::get_token_count() const {
    return player_tokens.size();
}


