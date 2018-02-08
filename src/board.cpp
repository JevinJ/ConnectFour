 /*
 * board.cpp
 *
 *  Created on: Dec 25, 2017
 *      Author: Jevin
 */

#include <memory>
#include <SFML/Graphics.hpp>
#include <vector>
#include "board.hpp"
#include "config.hpp"
#include "token.hpp"


Board::Board() :
    token_wall(TOKEN_WALL_WIDTH, std::vector<Token>(0)),
    preplace_token(nullptr) {
    for(auto& col : token_wall) {
        col.reserve(TOKEN_WALL_HEIGHT);
    }
}

std::vector<std::vector<Token>> Board::get_token_wall() const {
    return token_wall;
}

/*
 * description:
 *     Returns an integer representation of the token wall. Used to check win/tie state,
 *         use negamax, etc.
 */
std::vector<std::vector<int>> Board::get_int_token_wall() const {
    std::vector<std::vector<int>> token_wall_as_int;
    for(auto col : token_wall) {
        std::vector<int> whole_column;
        std::transform(col.begin(), col.end(), std::back_inserter(whole_column),
            [&](const Token& token){if(token.get_fill_color() == sf::Color::Red) return 1; else return -1;});
        token_wall_as_int.push_back(whole_column);
    }
    return token_wall_as_int;
}

/*
 * description:
 *     Returns the token that is in "preplacement", movable token that the player controls to place a token.
 */
Token* Board::get_preplace_token() const {
    return preplace_token.get();
}

/*
 * description:
 *     Set the preplace token to a token taken from the current player and set it's visible position.
 */
void Board::set_preplace_token(Token& token) {
    preplace_token = std::make_shared<Token>(token);
    preplace_token->set_pixel_position(DEFAULT_PREPLACE_X_POS, TOKEN_WALL_HEIGHT+1);
}

/*
 * description:
 *     Move the preplace token in a given direction(sf::Keyboard::Left/Right)
 */
void Board::move_preplace_token(sf::Keyboard::Key direction) {
    if(preplace_token != nullptr) {
        const unsigned int x_pos = preplace_token->get_x_position();
        if(direction == sf::Keyboard::Left) {
            if(x_pos >= 1) {
                preplace_token->set_x_position(x_pos-1);
            }
            else {
                preplace_token->set_x_position(TOKEN_WALL_WIDTH-1);
            }
        }
        if(direction == sf::Keyboard::Right) {
            preplace_token->set_x_position((x_pos+1) % TOKEN_WALL_WIDTH);
        }
        preplace_token->set_pixel_position(preplace_token->get_x_position(), TOKEN_WALL_HEIGHT+1);
    }
}

void Board::drop_preplace_token() {
    if(preplace_token != nullptr and not slotIsFull(preplace_token->get_x_position())) {
        const unsigned int x_pos = preplace_token->get_x_position();
        token_wall[x_pos].push_back(*preplace_token);
        token_wall[x_pos].back().set_pixel_position(x_pos, token_wall[x_pos].size());
        preplace_token = nullptr;
    }
}

bool Board::slotIsFull(const int x_pos) {
    if(x_pos < 0 or x_pos >= token_wall.size()) {
        return true;
    }
    return token_wall[x_pos].size() >= TOKEN_WALL_HEIGHT;
}


