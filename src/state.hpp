/*
 * state.hpp
 *
 *  Created on: Dec 26, 2017
 *      Author: Jevin
 */

#ifndef STATE_HPP_
#define STATE_HPP_
#include <CTPL/ctpl_stl.h>
#include <SFML/Graphics.hpp>
#include "board.hpp"
#include "config.hpp"
#include "player.hpp"
#include "useroptions.hpp"


/*
 * description:
 *     Main interface for the objects and functions in this project, handles general game state.
 * State(): Constructs a board and player objects with default token colors(black for player, red for ai).
 * State(sf::Color, sf::Color): Same as default but you can use any colors supported by SFML,
 *     param1: player_one token color:
 *     param2: player_two token color.
 */
struct State {
    State(const UserOptions user_options);
    State& operator=(State&& original);
    void draw();
    int get_best_move(const bool bool_color);
    void signal_end_of_game(const std::string message);
    bool isPlayerOneTurn;
    bool isEndOfGame;
    const UserOptions user_options;
    Board board;
    Player player_one;
    Player player_two;
    sf::RenderWindow render_window;
    sf::Text endgame_message;
    sf::ContextSettings render_window_settings;
    ctpl::thread_pool negamax_thread_pool;
};


/*
 * description:
 *     Checks if the token wall is in a winning state for a given color.
 * params:
 *     bool_token_wall: a bool representation of the token wall(Board.get_bool_token_wall())
 *     bool_color: a bool representation of a token color(in config.hpp).
 */
template <class T>
bool isWinState(const std::vector<std::vector<T>>& token_wall, const T color) {
    auto isCorrectColor = [&](const std::pair<int, int> x_y) {
        const unsigned int x = x_y.first;
        const unsigned int y = x_y.second;
        return y < token_wall[x].size() and token_wall[x][y] == color;
    };

    std::vector<std::pair<int, int>> winning_tokens;
    winning_tokens.reserve(4);
    for(int x = 0; x < TOKEN_WALL_WIDTH; ++x) {
        for(int y = 0; y < TOKEN_WALL_HEIGHT; ++y) {
            //Upwards win check.
            if(y + 3 < TOKEN_WALL_HEIGHT) {
                winning_tokens.clear();
                for(int i = 0; i < 4; ++i) {
                    winning_tokens.push_back(std::make_pair(x, y+i));
                }
                if(all_of(winning_tokens.begin(), winning_tokens.end(), isCorrectColor)) {
                    return true;
                }
            }
            //Upwards right diagonal win check.
            if(x + 3 < TOKEN_WALL_WIDTH and y + 3 < TOKEN_WALL_HEIGHT) {
                winning_tokens.clear();
                for(int i = 0; i < 4; ++i) {
                    winning_tokens.push_back(std::make_pair(x+i, y+i));
                }
                if(all_of(winning_tokens.begin(), winning_tokens.end(), isCorrectColor)) {
                    return true;
                }
            }

            //Right win check.
            if(x + 3 < TOKEN_WALL_WIDTH) {
                winning_tokens.clear();
                for(int i = 0; i < 4; ++i) {
                    winning_tokens.push_back(std::make_pair(x+i, y));
                }
                if(all_of(winning_tokens.begin(), winning_tokens.end(), isCorrectColor)) {
                    return true;
                }
            }

            //Downwards right win check.
            if(x + 3 < TOKEN_WALL_WIDTH and y - 3 >= 0) {
                winning_tokens.clear();
                for(int i = 0; i < 4; ++i) {
                    winning_tokens.push_back(std::make_pair(x+i, y-i));
                }
                if(all_of(winning_tokens.begin(), winning_tokens.end(), isCorrectColor)) {
                    return true;
                }
            }

            //Downwards win check.
            if(y - 3 >= 0) {
                winning_tokens.clear();
                for(int i = 0; i < 4; ++i) {
                    winning_tokens.push_back(std::make_pair(x, y-i));
                }
                if(all_of(winning_tokens.begin(), winning_tokens.end(), isCorrectColor)) {
                    return true;
                }
            }

            //Downwards left win check.
            if(x - 3 >= 0 and y - 3 >= 0) {
                winning_tokens.clear();
                for(int i = 0; i < 4; ++i) {
                    winning_tokens.push_back(std::make_pair(x-i, y-i));
                }
                if(all_of(winning_tokens.begin(), winning_tokens.end(), isCorrectColor)) {
                    return true;
                }
            }

            //Left side win check.
            if(x - 3 >= 0) {
                winning_tokens.clear();
                for(int i = 0; i < 4; ++i) {
                    winning_tokens.push_back(std::make_pair(x-i, y));
                }
                if(all_of(winning_tokens.begin(), winning_tokens.end(), isCorrectColor)) {
                    return true;
                }
            }

            //Upwards left diagonal win check.
            if(x - 3 >= 0 and y + 3 < TOKEN_WALL_HEIGHT) {
                winning_tokens.clear();
                for(int i = 0; i < 4; ++i) {
                    winning_tokens.push_back(std::make_pair(x-i, y+i));
                }
                if(all_of(winning_tokens.begin(), winning_tokens.end(), isCorrectColor)) {
                    return true;
                }
            }
        }
    }
    return false;
}

/*
 * description:
 *     Checks if the token wall is filled with no winners.
 *     WARNING: This does NOT check if someone has won(use isWinState instead).
 * params:
 *     bool_token_wall: a bool representation of the token wall(Board.get_bool_token_wall())
 */
template<class T>
bool isTieState(const std::vector<std::vector<T>>& bool_token_wall) {
    for(auto col : bool_token_wall) {
        if(col.size() < TOKEN_WALL_HEIGHT) {
            return false;
        }
    }
    return true;
}
std::vector<int> get_available_moves(const std::vector<std::vector<bool>>& bool_token_wall);


#endif /* STATE_HPP_ */
