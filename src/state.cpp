/*
 * state.cpp
 *
 *  Created on: Dec 26, 2017
 *      Author: Jevin
 */


#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include "config.hpp"
#include "negamax.hpp"
#include "state.hpp"
#include "token.hpp"


State::State() :
    player_one(sf::Color::Black),
    player_two(sf::Color::Red) {
    render_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "ConnectFour");
    render_window.setFramerateLimit(60);
}

State::State(sf::Color player_one_color, sf::Color player_two_color) :
    player_one(player_one_color),
    player_two(player_two_color) {
        render_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "ConnectFour");
        render_window.setFramerateLimit(60);
}

/*
 * description:
 *     Draws all objects via a sf::RenderWindow object in State.
 */
void State::draw() {
    const Token* preplaceToken = board.get_preplace_token();
    if(preplaceToken != nullptr) {
        render_window.draw(preplaceToken->get_model());
    }

    const std::vector<std::vector<Token>> token_wall = board.get_token_wall();
    for(unsigned int i = 0; i < token_wall.size(); ++i) {
        for(unsigned int j = 0; j < token_wall[i].size(); ++j) {
            render_window.draw(token_wall[i][j].get_model());
        }
    }
}

/*
 * description:
 *     Feeds into the negamax(negamax.hpp) algorithm to get the best x position for the ai to drop a token at.
 * how it works:
 *     For each possible move, push the move onto it's position in a copy of the current token_wall,
 *     get a score from negamax, then pop the move.
 * params:
 *     int_color: an int representation of a token color(in config.hpp).
 */
int State::get_best_move(const int int_color) {
    std::vector<std::vector<int>> int_token_wall = board.get_int_token_wall();
    std::vector<unsigned int> available_moves = get_available_moves(int_token_wall);
    std::vector<std::pair<int, int>> move_scores;
    move_scores.reserve(TOKEN_WALL_WIDTH+1);
    int best_score = INT_MIN;

    for(int x : available_moves) {
        int_token_wall[x].push_back(int_color);
        const int score = negamax(int_token_wall, int_color, INT_MIN, INT_MAX);
        int_token_wall[x].pop_back();
        move_scores.push_back(std::make_pair(x, score));
        best_score = std::max(best_score, score);
    }
    std::vector<std::pair<int, int>> best_moves;
    std::copy_if(move_scores.begin(), move_scores.end(), std::back_inserter(best_moves),
            [&](std::pair<int, int> move_score){return move_score.second >= best_score;});

    if(best_moves.size() == 1) {
        return best_moves[0].first;
    }
    return best_moves[rand()%best_moves.size()].first;
}

/*
 * description:
 *     Checks if the token wall is in a winning state for a given color.
 * params:
 *     int_token_wall<vector<vector<unsigned int>>: an int representation of the token wall(Board.get_int_token_wall())
 *     int_color: an int representation of a token color(in config.hpp).
 */
bool isWinState(const std::vector<std::vector<int>>& int_token_wall, const int int_color) {
    auto isCorrectColor = [&](std::pair<int, int> x_y){
        const int x = x_y.first;
        const int y = x_y.second;
        return y < int_token_wall[x].size() and int_token_wall[x][y] == int_color;
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
 *     int_token_wall<vector<vector<unsigned int>>: an int representation of the token wall(Board.get_int_token_wall())
 */
bool isTieState(const std::vector<std::vector<int>>& int_token_wall) {
    for(auto col : int_token_wall) {
        if(col.size() < TOKEN_WALL_HEIGHT) {
            return false;
        }
    }
    return true;
}

/*
 * params:
 *     int_token_wall<vector<vector<unsigned int>>: an int representation of the token wall(Board.get_int_token_wall())
 * returns:
 *     vector<unsigned int> of x positions that a token can be dropped at.
 */
std::vector<unsigned int> get_available_moves(const std::vector<std::vector<int>>& int_token_wall) {
    std::vector<unsigned int> empty_indexes;
    for(unsigned int x = 0; x < TOKEN_WALL_WIDTH; ++x) {
        if(int_token_wall[x].size() < TOKEN_WALL_HEIGHT) {
            empty_indexes.push_back(x);
        }
    }
    return empty_indexes;
}
