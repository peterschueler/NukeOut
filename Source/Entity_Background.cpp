#include "../Include/Entity_Background.hpp"
#include "../Include/TextureManager.hpp"

#include <iostream>

Entity_Background::Entity_Background() : sprite() {
	attachTexture();
}

Entity_Background::Entity_Background(Tile tile, const std::shared_ptr<TextureManager>& mgr) : sprite(), txtManager(mgr), tile(tile) {
	attachTexture();
}

void Entity_Background::update(sf::Time delta) {
}

sf::FloatRect Entity_Background::borders() const {
	sf::FloatRect bounds = getTransform().transformRect(sprite.getGlobalBounds());
	return bounds;
}

void Entity_Background::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	
	target.draw(sprite, states);
}

void Entity_Background::attachTexture() {
	int y_axis = 240;
	int x_axis = 320;
	
	sf::IntRect rect = sf::IntRect(0,0,x_axis, y_axis);
	txtManager->load(tile.type);
	sprite.setTexture(txtManager->get(tile.type));
	sprite.setTextureRect(rect);
}