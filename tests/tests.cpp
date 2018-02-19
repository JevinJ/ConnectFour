/*
 * tests.cpp
 *
 *  Created on: Feb 5, 2018
 *      Author: Jevin
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Suites
#include <algorithm>
#include <boost/test/unit_test.hpp>
#include <SFML/Graphics.hpp>
#include <type_traits>
#include <vector>
#include "src/board.hpp"
#include "src/config.hpp"
#include "src/player.hpp"
#include "src/state.hpp"
#include "src/token.hpp"



BOOST_AUTO_TEST_SUITE(TokenTests)
BOOST_AUTO_TEST_CASE(PositionTest) {
    Token token;

    BOOST_CHECK_EQUAL(token.get_x_position(), 0);
    BOOST_CHECK_EQUAL(token.get_y_position(), 0);

    token.set_x_position(-1);
    token.set_y_position(-1);
    BOOST_CHECK_EQUAL(token.get_x_position(), 0);
    BOOST_CHECK_EQUAL(token.get_y_position(), 0);

    token.set_x_position(3);
    token.set_y_position(3);
    BOOST_CHECK_EQUAL(token.get_x_position(), 3);
    BOOST_CHECK_EQUAL(token.get_y_position(), 3);

    token.set_x_position(TOKEN_WALL_WIDTH+1);
    token.set_y_position(TOKEN_WALL_HEIGHT+1);
    BOOST_CHECK_EQUAL(token.get_x_position(), 3);
    BOOST_CHECK_EQUAL(token.get_y_position(), 3);
}
BOOST_AUTO_TEST_CASE(CircleShapeTest) {
    Token token(sf::Color::Black);
    BOOST_CHECK(token.get_fill_color() == sf::Color::Black);

    token = Token(sf::Color::Red);
    BOOST_CHECK(token.get_fill_color() == sf::Color::Red);

    BOOST_CHECK_EQUAL(token.get_radius(), TOKEN_RADIUS);
}
BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(BoardTests)
BOOST_AUTO_TEST_CASE(SizeTest) {
    Board board;

    BOOST_REQUIRE_EQUAL(board.get_token_wall().size(), TOKEN_WALL_WIDTH);

    for(int i = 0; i <= TOKEN_WALL_HEIGHT+1; ++i) {
        Token token;
        board.set_preplace_token(token);
        board.drop_preplace_token();
    }
    BOOST_REQUIRE(board.get_token_wall()[DEFAULT_PREPLACE_X_POS].size() <= TOKEN_WALL_HEIGHT);

    BOOST_REQUIRE_EQUAL(board.slotIsFull(DEFAULT_PREPLACE_X_POS), true);
    BOOST_REQUIRE_EQUAL(board.slotIsFull(TOKEN_WALL_WIDTH+1), true);
    BOOST_REQUIRE_EQUAL(board.slotIsFull(-1), true);
}
BOOST_AUTO_TEST_CASE(PlacementTest) {
    Board board;
    Token token;
    Token* preplace_token;
    std::vector<std::vector<Token>> token_wall;

    BOOST_REQUIRE_EQUAL(board.get_preplace_token(), nullptr);

    token = Token(sf::Color::Black);
    board.set_preplace_token(token);
    board.drop_preplace_token();
    token_wall = board.get_token_wall();
    BOOST_REQUIRE(token_wall[DEFAULT_PREPLACE_X_POS].back().get_fill_color() == token.get_fill_color());

    BOOST_REQUIRE_EQUAL(board.get_preplace_token(), nullptr);

    token = Token(sf::Color::Red);
    board.set_preplace_token(token);
    board.drop_preplace_token();
    token_wall = board.get_token_wall();
    BOOST_REQUIRE(token_wall[DEFAULT_PREPLACE_X_POS].back().get_fill_color() == token.get_fill_color());

    board.set_preplace_token(token);
    preplace_token = board.get_preplace_token();
    board.move_preplace_token(sf::Keyboard::Left);
    BOOST_CHECK_EQUAL(preplace_token->get_x_position(), DEFAULT_PREPLACE_X_POS-1);
    board.move_preplace_token(sf::Keyboard::Right);
    BOOST_CHECK_EQUAL(preplace_token->get_x_position(), DEFAULT_PREPLACE_X_POS);
}
BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(PlayerTests)
BOOST_AUTO_TEST_CASE(PlayerTokenStackTest) {
    Player player_one(sf::Color::Black);
    Player player_two(sf::Color::Red);

    int beginning_token_count = (TOKEN_WALL_WIDTH*TOKEN_WALL_HEIGHT) / 2;
    BOOST_REQUIRE_EQUAL(player_one.get_token_count(), beginning_token_count);

    Token player_one_token = player_one.take_token();
    Token player_two_token = player_two.take_token();
    BOOST_REQUIRE(player_one_token.get_fill_color() == sf::Color::Black);
    BOOST_REQUIRE(player_two_token.get_fill_color() == sf::Color::Red);
    BOOST_REQUIRE_EQUAL(player_one.get_token_count(), beginning_token_count-1);
    BOOST_REQUIRE_EQUAL(player_two.get_token_count(), beginning_token_count-1);
}
BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(StateTests)
BOOST_AUTO_TEST_CASE(WinStateTest) {
    bool X = true;
    bool O = false;

    std::vector<std::vector<bool>> vertical_win_check;
    std::vector<std::vector<bool>> diagonal_win_check;
    std::vector<std::vector<bool>> horizontal_win_check;
    std::vector<std::vector<bool>> horizontal_small_size_check;
    vertical_win_check = {{X, X, X, X},
                          {},
                          {},
                          {},
                          {},
                          {},
                          {}};

    diagonal_win_check = {{X},
                          {O, X},
                          {O, O, X},
                          {O, O, O, X},
                          {},
                          {},
                          {}};

    horizontal_win_check = {{X},
                            {X},
                            {X},
                            {X},
                            {},
                            {},
                            {}};

    BOOST_REQUIRE_MESSAGE(isWinState(vertical_win_check, X) == true, "Vertical isWinState check starting from 0,0 to 0,3 with value{" << X << "}");
    for(auto& col: vertical_win_check) std::replace(col.begin(), col.end(), X, O);
    BOOST_REQUIRE_MESSAGE(isWinState(vertical_win_check, O) == true, "Vertical isWinState check starting from 0,0 to 0,3 with value{" << O << "}");

    BOOST_REQUIRE_MESSAGE(isWinState(diagonal_win_check, X) == true, "Diagonal isWinState check starting from 0,0 to 3,3 with value{" << X << "}");
    for(auto& col: diagonal_win_check) std::replace(col.begin(), col.end(), X, O);
    BOOST_REQUIRE_MESSAGE(isWinState(diagonal_win_check, O) == true, "Diagonal isWinState check starting from 0,0 to 3,3 with value{" << O << "}");

    BOOST_REQUIRE_MESSAGE(isWinState(horizontal_win_check, X) == true, "Horizontal isWinState check starting from 0,0 to 3,0 with value{" << X << "}");
    for(auto& col: horizontal_win_check) std::replace(col.begin(), col.end(), X, O);
    BOOST_REQUIRE_MESSAGE(isWinState(horizontal_win_check, O) == true, "Horizontal isWinState check starting from 0,0 to 3,0 with value{" << O << "}");

    vertical_win_check = {{},
                          {},
                          {},
                          {},
                          {},
                          {},
                          {X, X, X, X}};

    diagonal_win_check = {{},
                          {},
                          {},
                          {O, O, O, X},
                          {O, O, X},
                          {O, X},
                          {X}};

    horizontal_win_check = {{},
                            {},
                            {},
                            {X},
                            {X},
                            {X},
                            {X}};

    BOOST_REQUIRE_MESSAGE(isWinState(vertical_win_check, X) == true, "Vertical isWinState check starting from 6,0 to 6,3 with value{" << X << "}");
    for(auto& col: vertical_win_check) std::replace(col.begin(), col.end(), X, O);
    BOOST_REQUIRE_MESSAGE(isWinState(vertical_win_check, O) == true, "Vertical isWinState check starting from 6,0 to 6,3 with value{" << O << "}");

    BOOST_REQUIRE_MESSAGE(isWinState(diagonal_win_check, X) == true, "Diagonal isWinState check starting from 6,0 to 3,3 with value{" << X << "}");
    for(auto& col: diagonal_win_check) std::replace(col.begin(), col.end(), X, O);
    BOOST_REQUIRE_MESSAGE(isWinState(diagonal_win_check, O) == true, "Diagonal isWinState check starting from 6,0 to 3,3 with value{" << O << "}");

    BOOST_REQUIRE_MESSAGE(isWinState(horizontal_win_check, X) == true, "Horizontal isWinState check starting from 6,0 to 3,0 with value{" << X << "}");
    for(auto& col: horizontal_win_check) std::replace(col.begin(), col.end(), X, O);
    BOOST_REQUIRE_MESSAGE(isWinState(horizontal_win_check, O) == true, "Horizontal isWinState check starting from 6,0 to 3,0 with value{" << O << "}");


    horizontal_small_size_check = {{X},
                                   {X},
                                   {X},
                                   {X}};

    BOOST_REQUIRE_MESSAGE(isWinState(horizontal_small_size_check, X) == true, "Horizontal small size isWinState check starting from 0,0 to 3,0 with value{" << X << "}");
    for(auto& col: horizontal_small_size_check) std::replace(col.begin(), col.end(), X, O);
    BOOST_REQUIRE_MESSAGE(isWinState(horizontal_small_size_check, O) == true, "Horizontal small size isWinState check starting from 0,0 to 3,0 with value{" << O << "}");
}
BOOST_AUTO_TEST_CASE(TieStateTest) {
    //Todo tie state generation test
}
BOOST_AUTO_TEST_CASE(AvailableMovesTest) {
    bool X = true;
    bool O = false;
    std::vector<int> expected;
    std::vector<int> actual;
    std::vector<std::vector<bool>> bool_token_wall;

    bool_token_wall  = {{},
                        {},
                        {},
                        {O, O, O, X},
                        {O, O, X},
                        {O, X},
                        {X}};
    expected = {0, 1, 2, 3, 4, 5, 6};
    actual = get_available_moves(bool_token_wall);
    BOOST_REQUIRE_EQUAL(std::is_permutation(expected.begin(), expected.end(), actual.begin()), true);

    bool_token_wall  = {{},
                        {},
                        {},
                        {O, O, O, X, O, X},
                        {O, O, X, O, X, O},
                        {O, X, O, X, O, X},
                        {X, O, X, O, X, O}};
    expected = {0, 1, 2};
    actual = get_available_moves(bool_token_wall);
    BOOST_REQUIRE_EQUAL(std::is_permutation(expected.begin(), expected.end(), actual.begin()), true);

    bool_token_wall  = {{O, O, O, X, O, X},
                        {},
                        {},
                        {O, O, O, X, O, X},
                        {O, O, X, O, X},
                        {O, X, O, X, O, X},
                        {X, O, X, O, X}};
    expected = {1, 2, 4, 6};
    actual = get_available_moves(bool_token_wall);
    BOOST_REQUIRE_EQUAL(std::is_permutation(expected.begin(), expected.end(), actual.begin()), true);

    bool_token_wall  = {{O, O, O, X, O},
                        {O, O, O, X, O, X},
                        {},
                        {},
                        {O, O, X, O, X, O},
                        {O, X, O, X, O},
                        {X, O, X, O, X}};
    expected = {0, 2, 3, 5, 6};
    actual = get_available_moves(bool_token_wall);
    BOOST_REQUIRE_EQUAL(std::is_permutation(expected.begin(), expected.end(), actual.begin()), true);

}
BOOST_AUTO_TEST_SUITE_END()





