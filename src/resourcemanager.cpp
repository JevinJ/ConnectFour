/*
 * resources.cpp
 *
 *  Created on: Feb 10, 2018
 *      Author: Jevin
 */

#include "resourcemanager.hpp"


ResourceManager::ResourceManager() {
    //Fonts
    fonts.acquire(Fonts::TitilliumWeb, thor::Resources::fromFile<sf::Font>("../media/TitilliumWeb.ttf"));
    //Token texture.
    textures.acquire(Textures::TokenTexture, thor::Resources::fromFile<sf::Texture>("../media/token_texture.png"));

    //Loading menu images.
    //Controls.
    images.acquire(Images::ControlsArrowIcon, thor::Resources::fromFile<sf::Image>("../media/controls_arrow_icon.png"));
    images.acquire(Images::ControlsSpacebarIcon, thor::Resources::fromFile<sf::Image>("../media/controls_spacebar_icon.png"));
    images.acquire(Images::ControlsRestartIcon, thor::Resources::fromFile<sf::Image>("../media/controls_restart_icon.png"));

    //Token select.
    images.acquire(Images::TokenRed, thor::Resources::fromFile<sf::Image>("../media/token_red.png"));
    images.acquire(Images::TokenBlack, thor::Resources::fromFile<sf::Image>("../media/token_black.png"));
}

ResourceManager resource_manager;





