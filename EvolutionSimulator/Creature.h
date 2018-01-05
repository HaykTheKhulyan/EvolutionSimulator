#pragma once
#include <string>
#include <random>

#include "SFML/Graphics.hpp"


class Creature {
public:
	Creature();
	~Creature();

	void Draw(sf::RenderWindow& window);
	void Update(float deltaTime, sf::Image& map);

	std::string FEATURE_LIST[10] = {
		"offense" ,
		"defense",
		"speed",
		"camouflage",
		"reproductionRate",
		"lifeSpan",
		"metabolism",
		"intelligence",
		"teamwork",
		"eyesight"
	};

	float currentEnergy;

	bool swimming = false;

	bool herbivore = false;
	bool carnivore = false;

	short int features[10];

private:

	float xOffset;
	float yOffset;
	bool up = false;
	bool right = false;

	float myDeltaTime = 0.0f;

	void allocateStats(int skillPoints = 500);

	sf::Texture bodyTexture;
	sf::Sprite body;
};

