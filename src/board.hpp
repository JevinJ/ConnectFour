/*
 * board.hpp
 *
 *  Created on: Dec 25, 2017
 *      Author: Jevin
 */

#ifndef BOARD_HPP_
#define BOARD_HPP_
#include "token.hpp"


/*
 * description:
 *     Board class containing all the tokens that are visible to the player and a controllable preplace token.
 */
class Board {
    std::vector<std::vector<Token>> token_wall;
    std::shared_ptr<Token> preplace_token;
public:
    Board();
    std::vector<std::vector<Token>> get_token_wall() const;
    std::vector<std::vector<bool>> get_bool_token_wall(const sf::Color human_color) const;
    Token* get_preplace_token() const;
    void set_preplace_token(Token& token);
    void move_preplace_token(sf::Keyboard::Key direction);
    void drop_preplace_token();
    bool slotIsFull(const int x_pos);
};


#endif /* BOARD_HPP_ */
