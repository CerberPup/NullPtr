#pragma once
#include <SFML\Graphics.hpp>


using namespace sf;
using namespace std;

class Zaskroniec:public Transformable, public Drawable
{
private:
	
	virtual void draw(RenderTarget &target, RenderStates states) const;
	int animation;
	
public:
	Texture texture;
	bool direction;
	Zaskroniec();
	Zaskroniec(bool kierunek,Vector2f pos);
	~Zaskroniec();
	Sprite sprite;
	void update();
};

