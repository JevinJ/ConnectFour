/*
 * negamax.cpp
 *
 *  Created on: Jan 24, 2018
 *      Author: Jevin
 */

#include "config.hpp"
#include "negamax.hpp"
#include "state.hpp"


/*
 * description:
 *     Returns a score for use in negamax algorithm.
 */
int score(const bool bool_color, const int depth) {
    if(bool_color == BOOL_AI_COLOR) {
        return 10 - depth;
    }
    return -10 + depth;
}

/*
 * description:
 *     https://en.wikipedia.org/wiki/Negamax
 *     Modified negamax algorithm with alpha-beta pruning. Needs to be called in a separate loop to compare all
 *         available moves as this will only return a score for one move(State.get_best_move(bool_color)).
 * how it works:
 *     For each move, recursively call for the next player to make a move on a copy of the token wall.
 *         if the depth == difficulty+NEGAMAX_MAX_DEPTH(config.hpp) or the wall is in a tie state return 0 as the score,
 *         if the wall is in a win state, return a score based on who won and the depth,
 *         else recur with the next player.
 */
int negamax(std::vector<std::vector<bool>>& bool_token_wall, const bool bool_color, int alpha, int beta, const Difficulty difficulty, const int current_depth) {
    if(isWinState(bool_token_wall, bool_color)) {
        return score(bool_color, current_depth);
    }
    if(current_depth >= NEGAMAX_DEFAULT_DEPTH+difficulty or isTieState(bool_token_wall)) {
        return 0;
    }

    int best_score = INT_MAX;
    for(const int x_pos : get_available_moves(bool_token_wall)) {
        bool_token_wall[x_pos].push_back(!bool_color);
        int score = negamax(bool_token_wall, !bool_color, -beta, -alpha, difficulty, current_depth+1);
        bool_token_wall[x_pos].pop_back();
        best_score = std::min(best_score, score);
        alpha = std::min(alpha, score);
        if(alpha >= beta) {
            break;
        }
    }
    return best_score;
}
