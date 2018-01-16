#include "../Include/Entity_Brick.hpp"
#include "../Include/TextureManager.hpp"

#include <iostream>

int combine(int a, int b) {
	int times = 1;
	while (times <= b) {
		times *= 10;
	}
	return a*times + b;
}

std::pair<int, int> convertTileSpaceToRealSpace(Tile tile) {
	std::map<int, std::pair<int, int> > vals;
	int combValue = combine(tile.y, tile.x);
	
	unsigned int xVal = 0;
	unsigned int yVal = 40;
	for (int it = 10; it < 70; it++) {
		yVal += 20;
		if (it > 10 && it < 20) {
			xVal = 180;
		} else if (it > 20 && it < 30) {
			xVal = 160;
		} else if (it > 30 && it < 40) {
			xVal = 140;
		} else if (it > 40 && it < 50) {
			xVal = 120;
		} else if (it > 50 && it < 60) {
			xVal = 100;
		} else if (it > 60 && it < 70) {
			xVal = 80;
		} else if (it > 70 && it < 80) {
			xVal = 60;
		}
		vals.insert(std::pair<int, std::pair<int, int> >(it, {xVal,yVal}));
		if (it % 10 == 0) {
			yVal = 40;
		}
	}
	
	for (auto val : vals) {
		if (combValue == val.first) {
			return val.second;
		}
	}
	return std::make_pair(-100, -100);
}

Entity_Brick::Entity_Brick(): sprite(), isDestroyed(false) {
	tile.x = 0;
	tile.y = 0;
	tile.type = Tile::Type::Default;
	setDestructable(true);
	attachTexture();
	txtManager = new TextureManager();
}

Entity_Brick::Entity_Brick(Tile tile, TextureManager& mgr): sprite(), isDestroyed(false), tile(tile), txtManager(&mgr) {
	if (tile.type == Tile::Type::Brick_Hard) {
		setDestructable(false);
	} else {
		setDestructable(true);
	}
	attachTexture();
	std::pair<int, int> coords = convertTileSpaceToRealSpace(tile);
	setPosition(coords.first, coords.second);
}

void Entity_Brick::update(sf::Time) {
}
	
sf::FloatRect Entity_Brick::borders() const {
	sf::FloatRect bounds = getTransform().transformRect(sprite.getGlobalBounds());
	return bounds;
}
	
void Entity_Brick::destroy() {
	isDestroyed = true;
}

bool Entity_Brick::getDestroyed() const {
	return isDestroyed;
}

void Entity_Brick::setDestructable(bool destr) {
	if (tile.type == Tile::Type::Brick_Hard) {
		return;
	}
	isDestructable = destr;
}

bool Entity_Brick::getGestructable() const {
	return isDestructable;
}

void Entity_Brick::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	
	target.draw(sprite, states);
}

void Entity_Brick::attachTexture() {
	sf::IntRect rect = sf::IntRect(0,0,15,20);
	txtManager->load(tile.type);
	sprite.setTexture(txtManager->get(tile.type));
	sprite.setTextureRect(rect);
}