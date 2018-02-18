/*
 * menu.cpp
 *
 *  Created on: Feb 7, 2018
 *      Author: Jevin
 */

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "menu.hpp"
#include "resourcemanager.hpp"


Menu::Menu() :
    difficultyIsSet(false),
    playerColorIsSet(false),
    playerIsReady(false),
    render_window(sf::VideoMode(MENU_WINDOW_WIDTH, MENU_WINDOW_HEIGHT), "Main Menu") {
        render_window.setFramerateLimit(60);
        render_window.resetGLStates();

        master_desktop.GetEngine().GetResourceManager().SetDefaultFont(std::make_shared<sf::Font>(resource_manager.fonts[Fonts::TitilliumWeb]));
        master_desktop.LoadThemeFromFile("../media/menu_theme.theme");
        //-----------------------------
        //Start setting text, ids and images.
        //Controls.
        controls_title->SetText("Controls");
        controls_title->SetId("controls_title");

        controls_movement_text->SetText("Move left & right with arrow keys");
        controls_drop_text->SetText("Drop a token with the spacebar");
        controls_restart_text->SetText("Restart the game with the R button");

        controls_movement_icon->SetImage(resource_manager.images[Images::ControlsArrowIcon]);
        controls_drop_icon->SetImage(resource_manager.images[Images::ControlsSpacebarIcon]);
        controls_restart_icon->SetImage(resource_manager.images[Images::ControlsRestartIcon]);

        //Difficulty select.
        difficulty_select_title->SetText("Select a difficulty");
        difficulty_select_title->SetId("difficulty_select_title");

        difficulty_select_button_easy->SetLabel("Easy");
        difficulty_select_button_easy->SetId("easy_button");
        difficulty_select_button_easy->GetSignal(sfg::Widget::OnLeftClick).Connect([this] {
            this->on_click_difficulty_button(difficulty_select_button_easy);
        });
        difficulty_select_button_medium->SetLabel("Medium");
        difficulty_select_button_medium->SetId("medium_button");
        difficulty_select_button_medium->GetSignal(sfg::Widget::OnLeftClick).Connect([this] {
            this->on_click_difficulty_button(difficulty_select_button_medium);
        });
        difficulty_select_button_hard->SetLabel("Hard");
        difficulty_select_button_hard->SetId("hard_button");
        difficulty_select_button_hard->GetSignal(sfg::Widget::OnLeftClick).Connect([this] {
            this->on_click_difficulty_button(difficulty_select_button_hard);
        });

        //Token select.
        token_select_title->SetText("Select your token");
        token_select_title->SetId("token_select_title");

        token_select_red_icon->SetImage(resource_manager.images[Images::TokenRed]);
        token_select_black_icon->SetImage(resource_manager.images[Images::TokenBlack]);

        token_select_button_red->SetImage(token_select_red_icon);
        token_select_button_red->SetId("red_token_button");
        token_select_button_red->GetSignal(sfg::Widget::OnLeftClick).Connect([this] {
            this->on_click_token_button(token_select_button_red);
        });
        token_select_button_black->SetImage(token_select_black_icon);
        token_select_button_black->SetId("black_token_button");
        token_select_button_black->GetSignal(sfg::Widget::OnLeftClick).Connect([this] {
            this->on_click_token_button(token_select_button_black);
        });

        //Start
        start_button->SetLabel("Start!");
        start_button->GetSignal(sfg::Widget::OnLeftClick).Connect([this] {
            this->playerIsReady = true;
        });
        start_button->Show(false);

        //-------------------------------------------------
        //Start packing and aligning elements into subboxes.
        master_box->SetSpacing(7.5f);
        //Controls.
        controls_text_box->SetSpacing(5.0f);
        controls_icon_box->SetSpacing(5.0f);

        auto controls_title_alignment = sfg::Alignment::Create();
        controls_title_alignment->SetScale(sf::Vector2f(.0f, .0f));
        controls_title_alignment->SetAlignment(sf::Vector2f(.5f, .0f));
        controls_title_alignment->Add(controls_title);

        controls_main_box->Pack(controls_title_alignment);

        auto movement_text_alignment = sfg::Alignment::Create();
        movement_text_alignment->SetScale(sf::Vector2f(.0f, .0f));
        movement_text_alignment->SetAlignment(sf::Vector2f(.0f, .5f));
        movement_text_alignment->Add(controls_movement_text);

        auto drop_text_alignment = sfg::Alignment::Create();
        drop_text_alignment->SetScale(sf::Vector2f(.0f, .0f));
        drop_text_alignment->SetAlignment(sf::Vector2f(.0f, .5f));
        drop_text_alignment->Add(controls_drop_text);

        auto restart_text_alignment = sfg::Alignment::Create();
        restart_text_alignment->SetScale(sf::Vector2f(.0f, .0f));
        restart_text_alignment->SetAlignment(sf::Vector2f(.0f, .5f));
        restart_text_alignment->Add(controls_restart_text);

        controls_text_box->Pack(movement_text_alignment);
        controls_text_box->Pack(drop_text_alignment);
        controls_text_box->Pack(restart_text_alignment);

        controls_icon_box->Pack(controls_movement_icon);
        controls_icon_box->Pack(controls_drop_icon);
        controls_icon_box->Pack(controls_restart_icon);

        controls_text_icon_box->Pack(controls_text_box);
        controls_text_icon_box->Pack(controls_icon_box);

        controls_main_box->Pack(controls_text_icon_box);

        //Difficulty select.
        difficulty_select_main_box->SetSpacing(10.0f);
        difficulty_select_button_box->SetSpacing(2.0f);

        auto difficulty_select_title_alignment = sfg::Alignment::Create();
        difficulty_select_title_alignment->SetScale(sf::Vector2f(.0f, .0f));
        difficulty_select_title_alignment->SetAlignment(sf::Vector2f(.5f, .0f));
        difficulty_select_title_alignment->Add(difficulty_select_title);

        difficulty_select_button_box->Pack(difficulty_select_button_easy);
        difficulty_select_button_box->Pack(difficulty_select_button_medium);
        difficulty_select_button_box->Pack(difficulty_select_button_hard);

        difficulty_select_main_box->Pack(difficulty_select_title_alignment);
        difficulty_select_main_box->Pack(difficulty_select_button_box);

        //Token select.
        token_select_main_box->SetSpacing(10.0f);
        token_select_button_box->SetSpacing(132.0f);

        auto token_select_title_alignment = sfg::Alignment::Create();
        token_select_title_alignment->SetScale(sf::Vector2f(.0f, .0f));
        token_select_title_alignment->SetAlignment(sf::Vector2f(.5f, .0f));
        token_select_title_alignment->Add(token_select_title);

        token_select_main_box->Pack(token_select_title_alignment);

        token_select_button_box->Pack(token_select_button_red);
        token_select_button_box->Pack(token_select_button_black);

        token_select_main_box->Pack(token_select_button_box);

        //-------------------------------------------------
        //Start packing everything into master box/gui box.
        master_box->Pack(controls_main_box);
        master_box->Pack(sfg::Separator::Create());
        master_box->Pack(difficulty_select_main_box);
        master_box->Pack(sfg::Separator::Create());
        master_box->Pack(token_select_main_box);
        master_box->Pack(start_button);

        gui_window->Add(master_box);
        master_desktop.Add(master_box);
}

void Menu::on_click_difficulty_button(const sfg::Button::Ptr& clicked_button) {
    difficultyIsSet = true;
    const auto current_text_color = master_desktop.GetEngine().GetProperty<std::string>("Color", clicked_button);
    const auto altered_text_color = deviate_hex_color(current_text_color, 50.0);
    if(clicked_button == difficulty_select_button_easy and user_options.difficulty != Difficulty::Easy) {
        user_options.difficulty = Difficulty::Easy;
        master_desktop.GetEngine().SetProperties(std::string(
                "Window difficulty_select_button_box Button#easy_button {"
                "    Color: ") + altered_text_color + std::string(";}") +
                std::string(
                "Window difficulty_select_button_box Button#medium_button {"
                "    Color: ") + current_text_color + std::string(";}") +
                std::string(
                "Window difficulty_select_button_box Button#hard_button {"
                "    Color: ") + current_text_color + std::string(";}"));
    }
    else if(clicked_button == difficulty_select_button_medium and user_options.difficulty != Difficulty::Medium) {
        user_options.difficulty = Difficulty::Medium;
        master_desktop.GetEngine().SetProperties(std::string(
                "Window difficulty_select_button_box Button#easy_button {"
                "    Color: ") + current_text_color + std::string(";}") +
                std::string(
                "Window difficulty_select_button_box Button#medium_button {"
                "    Color: ") + altered_text_color + std::string(";}") +
                std::string(
                "Window difficulty_select_button_box Button#hard_button {"
                "    Color: ") + current_text_color + std::string(";}"));
    }
    else if(clicked_button == difficulty_select_button_hard and user_options.difficulty != Difficulty::Hard) {
        user_options.difficulty = Difficulty::Hard;
        master_desktop.GetEngine().SetProperties(std::string(
                "Window difficulty_select_button_box Button#easy_button {"
                "    Color: ") + current_text_color + std::string(";}") +
                std::string(
                "Window difficulty_select_button_box Button#medium_button {"
                "    Color: ") + current_text_color + std::string(";}") +
                std::string(
                "Window difficulty_select_button_box Button#hard_button {"
                "    Color: ") + altered_text_color + std::string(";}"));
    }
}

void Menu::on_click_token_button(const sfg::Button::Ptr& clicked_button) {
    this->playerColorIsSet = true;
    const auto current_background_color = master_desktop.GetEngine().GetProperty<std::string>("BackgroundColor", clicked_button);
    const auto altered_background_color = deviate_hex_color(current_background_color, 50.0);
    if(clicked_button == token_select_button_red and user_options.player_one_color != CustomColor::Red) {
        this->user_options.set_player_colors(CustomColor::Red, CustomColor::Black);
        master_desktop.GetEngine().SetProperties(std::string(
                "Window token_select_button_box Button#red_token_button {"
                "    BackgroundColor: ") + altered_background_color + std::string(";}") +
                std::string(
                "Window token_select_button_box Button#black_token_button {"
                "    BackgroundColor: ") + current_background_color + std::string(";}"));
    }
    else if(clicked_button == token_select_button_black and user_options.player_one_color != CustomColor::Black) {
        this->user_options.set_player_colors(CustomColor::Black, CustomColor::Red);
        master_desktop.GetEngine().SetProperties(std::string(
                "Window token_select_button_box Button#red_token_button {"
                "    BackgroundColor: ") + current_background_color + std::string(";}") +
                std::string(
                "Window token_select_button_box Button#black_token_button {"
                "    BackgroundColor: ") + altered_background_color + std::string(";}"));
    }
}

/*
 * description:
 *     Returns an altered copy of a given hex color(with alpha) to a percentage of lightening/darkening.
 * param hex_code:
 *     A string hex code, with alpha, in the format "#F0F0F000", can be retrieved from sfgui::Desktop.GetEngine().GetProperty()
 */
std::string Menu::deviate_hex_color(std::string hex_code, const float percentage) {
    if(hex_code.length() != 9 or percentage == 0) {
        return "#FFFFFFFF";
    }

    //Strip the # character
    hex_code.erase(0, 1);
    std::vector<int> rgba_values = convert_to_rgb(hex_code);
    for(int i = 0; i < 3; ++i) {
        const int color_value = rgba_values[i];
        const int combined_value = color_value + int(255 * (percentage/100.0));
        if(combined_value >= 255) {
            rgba_values[i] = 255;
        }
        else if (combined_value <= 0) {
            rgba_values[i] = 0;
        }
        else {
            rgba_values[i] = combined_value;
        }
    }
    return "#" + convert_to_hex(rgba_values);
}

std::string Menu::convert_to_hex(const std::vector<int> rgba_values) {
    if(rgba_values.size() != 4) {
        return "FFFFFFFF";
    }

    std::unordered_map<int, char> hex_values = {{0, '0'}, {1, '1'}, {2, '2'}, {3, '3'}, {4, '4'},
                                                {5, '5'}, {6, '6'}, {7, '7'}, {8, '8'}, {9, '9'},
                                                {10, 'A'}, {11, 'B'}, {12, 'C'}, {13, 'D'}, {14, 'E'},
                                                {15, 'F'}};
    //For each value in rgba, divide by 16(round down) and convert it to a hex character,
    //then modulo the same value by 16 and append the chars.
    std::string result = "";
    for(const auto& code : rgba_values) {
        result += hex_values[int(code/16)];
        result += hex_values[code%16];
    }
    return result;
}

std::vector<int> Menu::convert_to_rgb(const std::string hex_color) {
    if(hex_color.length() != 8) {
        return std::vector<int>{255, 255, 255, 255};
    }

    std::unordered_map<char, int> hex_values = {{'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4},
                                                {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9},
                                                {'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}, {'E', 14},
                                                {'F', 15}};
    //Separate RGB Hex codes into pairs and convert the pair to decimal values, then for the first element
    //multiply by 16 then add the second element.
    std::string red_hex = hex_color.substr(0, 2);
    std::string green_hex = hex_color.substr(2, 2);
    std::string blue_hex = hex_color.substr(4, 2);
    std::string alpha_hex = hex_color.substr(6, 2);
    return std::vector<int>{(hex_values[red_hex[0]]*16) + hex_values[red_hex[1]],
                            (hex_values[green_hex[0]]*16) + hex_values[green_hex[1]],
                            (hex_values[blue_hex[0]]*16) + hex_values[blue_hex[1]],
                            (hex_values[alpha_hex[0]]*16) + hex_values[alpha_hex[1]]};
}

UserOptions Menu::get_user_options() const {
    return user_options;
}

void Menu::draw() {
    render_window.clear(CustomColor::DarkGrey);
    if(difficultyIsSet and playerColorIsSet) {
        start_button->Show(true);
        sf::Vector2f gui_dimensions = gui_window->GetRequisition();
        const int width = int(gui_dimensions.x);
        const int height = int(gui_dimensions.y);
        render_window.setSize(sf::Vector2u(width, height));
    }
    if(playerIsReady) {
        render_window.close();
    }
    master_desktop.Update(0.1f);
    gui_window->Update(0.1f);
    sfgui.Display(render_window);
    render_window.display();
}


