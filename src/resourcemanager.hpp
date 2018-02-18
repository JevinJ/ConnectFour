/*
 * resources.hpp
 *
 *  Created on: Feb 10, 2018
 *      Author: Jevin
 */

#ifndef RESOURCEMANAGER_HPP_
#define RESOURCEMANAGER_HPP_
#include <SFML/Graphics.hpp>
#include <Thor/Resources.hpp>


namespace Fonts {
    enum Id {
        TitilliumWeb
    };
}

namespace Textures {
    enum Id {
        TokenTexture
    };
}

namespace Images {
    enum Id {
        ControlsArrowIcon,
        ControlsSpacebarIcon,
        ControlsRestartIcon,
        TokenRed,
        TokenBlack
    };
}

struct ResourceManager {
    ResourceManager();
    thor::ResourceHolder<sf::Font, Fonts::Id> fonts;
    thor::ResourceHolder<sf::Texture, Textures::Id> textures;
    thor::ResourceHolder<sf::Image, Images::Id> images;
};

extern ResourceManager resource_manager;


#endif /* RESOURCEMANAGER_HPP_ */
