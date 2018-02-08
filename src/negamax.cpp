/*
 * negamax.cpp
 *
 *  Created on: Jan 24, 2018
 *      Author: Jevin
 */

#include <vector>
#include "config.hpp"
#include "negamax.hpp"
#include "state.hpp"


/*
 * description:
 *     Returns a score for use in negamax algorithm.
 */
int score(const int int_color, const int depth) {
    if(int_color == INT_AI_COLOR) {
        return (int_color*10) - depth;
    }
    return (int_color*10) + depth;
}

/*
 * description:
 *     Negamax algorithm with alpha-beta pruning. Needs to be called in a separate loop to compare all
 *         available moves as this will only return a score for one move.(State.get_best_move(int_color))
 * how it works:
 *     For each move, recursively call for the next player to make a move on a copy of the token wall.
 *         if the depth == NEGAMAX_MAX_DEPTH(config.hpp) or the wall is in a tie state return 0 as the score,
 *         if the wall is in a win state, return a score based on who won and the depth,
 *         else recur with the next player.
 */
int negamax(std::vector<std::vector<int>>& int_token_wall, const int int_color, int alpha, const int beta, const int current_depth) {
    if(current_depth == NEGAMAX_MAX_DEPTH or isTieState(int_token_wall)) {
        return 0;
    }
    if(isWinState(int_token_wall, int_color)) {
        return score(int_color, current_depth);
    }

    int best_score = INT_MAX;
    for(const int x : get_available_moves(int_token_wall)) {
        int_token_wall[x].push_back(-int_color);
        const int score = negamax(int_token_wall, -int_color, -beta, -alpha, current_depth+1);
        int_token_wall[x].pop_back();
        best_score = std::min(best_score, score);
        alpha = std::max(alpha, score);
        if(alpha >= beta) {
            break;
        }
    }
    return best_score;
}






