#ifndef Entity_Wall_hpp
#define Entity_Wall_hpp

#include "Entity.hpp"
#include "Level.hpp"

class TextureManager;

class Entity_Wall : public Entity {
public:
	Entity_Wall();
	Entity_Wall(Tile, unsigned int, TextureManager&);
	// x, y, rotation, level
	Entity_Wall(int, int, int, Tile::Type, unsigned int);
	
	void update(sf::Time);
	
	sf::FloatRect borders() const;
	
protected:
	void draw(sf::RenderTarget&, sf::RenderStates) const;
	void attachTexture();
	
private:
	sf::Sprite sprite;
	
	Tile tile;
	
	unsigned int level;
	
	TextureManager* txtManager;
};

#endif