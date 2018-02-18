/*
 * menu.hpp
 *
 *  Created on: Feb 7, 2018
 *      Author: Jevin
 */

#ifndef SRC_MENU_HPP_
#define SRC_MENU_HPP_
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>
#include "useroptions.hpp"


class Menu {
    void on_click_difficulty_button(const sfg::Button::Ptr& clicked_button);
    void on_click_token_button(const sfg::Button::Ptr& clicked_button);
    std::string deviate_hex_color(std::string hex_color, const float percentage);
    std::string convert_to_hex(std::vector<int> rgba_color);
    std::vector<int> convert_to_rgb(std::string hex_color);
    UserOptions user_options;
    bool difficultyIsSet;
    bool playerColorIsSet;
    bool playerIsReady;
    //All boxes.
    sfg::Desktop master_desktop;
    sfg::Box::Ptr master_box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);

    sfg::Box::Ptr controls_main_box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
    sfg::Box::Ptr controls_text_icon_box = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);
    sfg::Box::Ptr controls_text_box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
    sfg::Box::Ptr controls_icon_box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);

    sfg::Box::Ptr difficulty_select_main_box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
    sfg::Box::Ptr difficulty_select_button_box = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);

    sfg::Box::Ptr token_select_main_box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
    sfg::Box::Ptr token_select_button_box = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);

    //Labels and images.
    //Controls.
    sfg::Label::Ptr controls_title = sfg::Label::Create();
    sfg::Label::Ptr controls_movement_text = sfg::Label::Create();
    sfg::Image::Ptr controls_movement_icon = sfg::Image::Create();
    sfg::Label::Ptr controls_drop_text = sfg::Label::Create();
    sfg::Image::Ptr controls_drop_icon = sfg::Image::Create();
    sfg::Label::Ptr controls_restart_text = sfg::Label::Create();
    sfg::Image::Ptr controls_restart_icon = sfg::Image::Create();

    //Difficulty select.
    sfg::Label::Ptr difficulty_select_title = sfg::Label::Create();
    sfg::Button::Ptr difficulty_select_button_easy = sfg::Button::Create();
    sfg::Button::Ptr difficulty_select_button_medium = sfg::Button::Create();
    sfg::Button::Ptr difficulty_select_button_hard = sfg::Button::Create();

    //Token select.
    sfg::Label::Ptr token_select_title = sfg::Label::Create();
    sfg::Image::Ptr token_select_red_icon = sfg::Image::Create();
    sfg::Image::Ptr token_select_black_icon = sfg::Image::Create();
    sfg::Button::Ptr token_select_button_red = sfg::Button::Create();
    sfg::Button::Ptr token_select_button_black = sfg::Button::Create();

    //Start.
    sfg::Button::Ptr start_button = sfg::Button::Create();
public:
    Menu();
    UserOptions get_user_options() const;
    void draw();
    sfg::SFGUI sfgui;
    sfg::Window::Ptr gui_window = sfg::Window::Create(sfg::Window::Style::NO_STYLE);
    sf::RenderWindow render_window;
};

sf::Image underline_button_icon(sfg::Button::Ptr button);


#endif /* SRC_MENU_HPP_ */
