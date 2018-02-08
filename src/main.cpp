#include <ctime>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "config.hpp"
#include "state.hpp"


int main()
{
    srand(time(NULL));
    // create the window
    State state(sf::Color::Black, sf::Color::Red);

    bool isBlackTurn = true;
    while (state.render_window.isOpen()) {
        sf::Event event;
        while(state.render_window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                state.render_window.close();
                return 0;
            }

            //Fill preplace token.
            if(state.board.get_preplace_token() == nullptr) {
                Token new_token;
                if(isBlackTurn and state.player_one.get_token_count() > 0) {
                    new_token = state.player_one.take_token();
                    state.board.set_preplace_token(new_token);
                }
                if(!isBlackTurn and state.player_two.get_token_count() > 0) {
                    new_token = state.player_two.take_token();
                    state.board.set_preplace_token(new_token);
                }
            }

            if(state.board.get_preplace_token() != nullptr) {
                //Player turn
                if(isBlackTurn) {
                    if(event.type == sf::Event::KeyPressed) {
                        if(event.key.code == sf::Keyboard::Left or event.key.code == sf::Keyboard::Right) {
                            state.board.move_preplace_token(event.key.code);
                        }
                        if(event.key.code == sf::Keyboard::Space) {
                            const Token* preplace_token = state.board.get_preplace_token();
                            if(not state.board.slotIsFull(preplace_token->get_x_position())) {
                                state.board.drop_preplace_token();
                                std::vector<std::vector<Token>> wall = state.board.get_token_wall();
                                if(isWinState(state.board.get_int_token_wall(), INT_HUMAN_COLOR)) {
                                    std::cout << "WINNING HUMAN" << '\n';
                                }
                                isBlackTurn = !isBlackTurn;
                            }
                            else {
                                //TODO
                            }
                        }
                    }
                }
                //AI turn
                else {
                    unsigned int best_x_pos = state.get_best_move(INT_AI_COLOR);
                    unsigned int current_pos = state.board.get_preplace_token()->get_x_position();
                    while(current_pos != best_x_pos) {
                        if(current_pos < best_x_pos) {
                            state.board.move_preplace_token(sf::Keyboard::Right);

                        }
                        if(current_pos > best_x_pos) {
                            state.board.move_preplace_token(sf::Keyboard::Left);
                        }
                        current_pos = state.board.get_preplace_token()->get_x_position();
                    }
                    state.board.drop_preplace_token();
                    isBlackTurn = !isBlackTurn;
                }
            }

            state.render_window.clear(sf::Color(99,99,99));
            state.draw();
            state.render_window.display();
        }
    }
    return 0;
}
