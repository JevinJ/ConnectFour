#include <ctime>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "config.hpp"
#include "menu.hpp"
#include "state.hpp"


int main()
{
    srand(time(NULL));

    //Open main menu and give the user game options.
    Menu menu;
    while(menu.render_window.isOpen()) {
        sf::Event event;
        while(menu.render_window.pollEvent(event)) {
            menu.gui_window->HandleEvent(event);
            if(event.type == sf::Event::Closed) {
                menu.render_window.close();
                return 0;
            }
            menu.draw();
        }
    }

    //Create a game using the user's settings.
    State state(menu.get_user_options());
    state.draw();
    while(state.render_window.isOpen()) {
        sf::Event event;
        //Fill preplace token if empty.
        if(state.board.get_preplace_token() == nullptr) {
            Token new_token;
            if(state.isPlayerOneTurn and state.player_one.get_token_count() > 0) {
                new_token = state.player_one.take_token();
                state.board.set_preplace_token(new_token);
            }
            else if(not state.isPlayerOneTurn and state.player_two.get_token_count() > 0) {
                new_token = state.player_two.take_token();
                state.board.set_preplace_token(new_token);
            }
        }
        //User input.
        if(state.render_window.pollEvent(event)) {
            //Close the window.
            if(event.type == sf::Event::Closed) {
                state.render_window.close();
                return 0;
            }
            if(event.type == sf::Event::KeyReleased) {
                //Reset the board if R is pressed.
                if(event.key.code == sf::Keyboard::R) {
                    state = State(menu.get_user_options());
                    break;
                }
                //Preplace contains a token, so we can make a move. Player one turn.
                if(state.board.get_preplace_token() != nullptr and not state.isEndOfGame and state.isPlayerOneTurn) {
                    //Movement.
                    if(event.key.code == sf::Keyboard::Left or event.key.code == sf::Keyboard::Right) {
                        state.board.move_preplace_token(event.key.code);
                    }

                    //Drop token if slot is not full.
                    if(event.key.code == sf::Keyboard::Space) {
                        const Token* preplace_token = state.board.get_preplace_token();
                        if(not state.board.slotIsFull(preplace_token->get_x_position())) {
                            state.board.drop_preplace_token();
                            //Check if win or tie.
                            if(isTieState(state.board.get_bool_token_wall(state.user_options.player_one_color))) {
                                state.signal_end_of_game("Tied!");
                            }
                            if(isWinState(state.board.get_bool_token_wall(state.user_options.player_one_color), BOOL_HUMAN_COLOR)) {
                                state.signal_end_of_game("Player one wins!");
                            }
                            state.isPlayerOneTurn = !state.isPlayerOneTurn;
                        }
                    }
                }
            }
        }
        //Preplace contains a token, so we can make a move. AI or player two turn.
        if(state.board.get_preplace_token() != nullptr and not state.isEndOfGame and not state.isPlayerOneTurn) {
            const int best_x_pos = state.get_best_move(BOOL_AI_COLOR);
            int current_pos = state.board.get_preplace_token()->get_x_position();
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
            //Check if win or tie.
            if(isTieState(state.board.get_bool_token_wall(state.user_options.player_one_color))) {
                state.signal_end_of_game("Tied!");
            }
            if(isWinState(state.board.get_bool_token_wall(state.user_options.player_one_color), BOOL_AI_COLOR)) {
                state.signal_end_of_game("Player two wins!");
            }
            state.isPlayerOneTurn = !state.isPlayerOneTurn;
        }
        state.draw();
    }
    return 0;
}
