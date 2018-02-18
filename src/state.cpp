/*
 * state.cpp
 *
 *  Created on: Dec 26, 2017
 *      Author: Jevin
 */

#include "config.hpp"
#include "negamax.hpp"
#include "resourcemanager.hpp"
#include "state.hpp"
#include "token.hpp"


State::State(const UserOptions user_options) :
    isEndOfGame(false),
    user_options(user_options),
    player_one(user_options.player_one_color),
    player_two(user_options.player_two_color) {
        //Whoever has the black token goes first.
        if(user_options.player_one_color == CustomColor::Black) {
            isPlayerOneTurn = true;
        }
        else {
            isPlayerOneTurn = false;
        }
        //Set thread pool count.
        const int detected_cores = std::thread::hardware_concurrency();
        if(detected_cores == 0) {
            throw(std::runtime_error("Error detecting core count with thread::hardware_concurrency() during creation of thread pool."));
        }
        else if(detected_cores >= 1 and detected_cores < TOKEN_WALL_WIDTH) {
            negamax_thread_pool.resize(detected_cores);
        }
        else {
            negamax_thread_pool.resize(TOKEN_WALL_WIDTH);
        }
        render_window_settings.antialiasingLevel = MAIN_WINDOW_AA_LEVEL;
        render_window.create(sf::VideoMode(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT), "Connect Four", sf::Style::Close, render_window_settings);
        render_window.setFramerateLimit(60);
}

//Move assignment constructor so we can reset the game when the user requests to.
State& State::operator=(State&& original) {
    //Whoever has the black token goes first.
    if(original.user_options.player_one_color == CustomColor::Black) {
        this->isPlayerOneTurn = true;
    }
    else {
        this->isPlayerOneTurn = false;
    }
    this->isEndOfGame = false;
    this->endgame_message = sf::Text();
    this->board = Board();
    this->player_one = Player(original.user_options.player_one_color);
    this->player_two = Player(original.user_options.player_two_color);
    return *this;
}

/*
 * description:
 *     Draws all objects via a sf::RenderWindow object in State.
 */
void State::draw() {
    render_window.clear(CustomColor::LightGrey);

    const Token* preplace_token = board.get_preplace_token();
    if(preplace_token != nullptr) {
        render_window.draw(*preplace_token);
    }

    const std::vector<std::vector<Token>> token_wall = board.get_token_wall();
    for(const auto& x_pos : token_wall) {
        for(const auto& y_pos : x_pos) {
            render_window.draw(y_pos);
        }
    }

    if(isEndOfGame) {
        render_window.draw(endgame_message);
    }

    render_window.display();
}

/*
 * description:
 *     Feeds into the negamax(negamax.hpp) algorithm to get the best x position for the ai to drop a token at.
 * how it works:
 *     For each possible move, push the move onto it's position in a copy of the current token_wall,
 *     get a score from negamax, then pop the move.
 * params:
 *     bool_color: a bool representation of a token color(in config.hpp) which we will return a best move for.
 */
int State::get_best_move(const bool bool_color) {
    std::vector<std::vector<bool>> bool_token_wall = board.get_bool_token_wall(user_options.player_one_color);
    std::vector<std::pair<int, std::shared_future<int>>> move_scores;
    move_scores.reserve(TOKEN_WALL_WIDTH);

    Difficulty difficulty = user_options.difficulty;
    for(const int& x_pos : get_available_moves(bool_token_wall)) {
        bool_token_wall[x_pos].push_back(true);
        move_scores.push_back(std::make_pair(x_pos, negamax_thread_pool.push(
                [bool_token_wall, bool_color, difficulty](const int id) mutable {return negamax(bool_token_wall, true, INT_MIN, INT_MAX, difficulty);})));
        bool_token_wall[x_pos].pop_back();
    }

    //Find the largest score.
    const int best_score = std::max_element(move_scores.begin(), move_scores.end(),
            [&](const auto& move_score_a, const auto& move_score_b){return move_score_a.second.get() < move_score_b.second.get();})->second.get();

    //Get the best moves and store them in a new vector to replace std::future with it's value.
    std::vector<std::pair<int, int>> best_moves;
    for(const auto& move_score : move_scores) {
        if(move_score.second.get() >= best_score) {
            best_moves.push_back(std::make_pair(move_score.first, move_score.second.get()));
        }
    }
    return best_moves[rand()%best_moves.size()].first;
}

void State::signal_end_of_game(const std::string message) {
    isEndOfGame = true;
    endgame_message.setFont(resource_manager.fonts[Fonts::TitilliumWeb]);
    endgame_message.setString(message + "\nPress 'R' to restart.");
    endgame_message.setCharacterSize(36);
    endgame_message.setStyle(sf::Text::Bold);
    endgame_message.setFillColor(sf::Color::White);
    //Centering the text
    sf::FloatRect text_rect = endgame_message.getLocalBounds();
    endgame_message.setOrigin((text_rect.left + text_rect.width/2.0f), (text_rect.top + text_rect.height/2.0f));
    endgame_message.setPosition(sf::Vector2f(MAIN_WINDOW_WIDTH/2.0f, MAIN_WINDOW_HEIGHT/2.0f));
}

/*
 * params:
 *     bool_token_wall: a bool representation of the token wall(Board.get_bool_token_wall())
 * returns:
 *     vector<int> of x positions that a token can be dropped at.
 */
std::vector<int> get_available_moves(const std::vector<std::vector<bool>>& bool_token_wall) {
    std::vector<int> empty_indexes;
    empty_indexes.reserve(TOKEN_WALL_WIDTH);
    for(int x_pos = 0; x_pos < TOKEN_WALL_WIDTH; ++x_pos) {
        if(bool_token_wall[x_pos].size() < TOKEN_WALL_HEIGHT) {
            empty_indexes.push_back(x_pos);
        }
    }
    return empty_indexes;
}
