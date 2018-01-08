#pragma once
#include <string>
#include <random>

#include "SFML/Graphics.hpp"


class Creature {
public:
	Creature(sf::Image& map, sf::Font& statsFont, sf::Texture& bodyTexture, sf::Texture& targetTexture);
	~Creature();

	void Draw(sf::RenderWindow& window);
	void Update(float deltaTime, sf::Image& map);

	void createStatsText(sf::Font& myStatsFont);
	bool isTouchingMouse(sf::Vector2i mousePosition);

	bool selected = false;

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

	// true by default, if the creature is a swimmer, 30% chance it can't walk
	bool canWalk = true;
	// false by default, if creature is spawned on water OR rolls a 30% chance, it can swim
	bool canSwim = false;

	// can the creature eat plants?
	bool herbivore = false;
	// can the creature eat meat?
	bool carnivore = false;

	short int features[10];
private:
	float xOffset;
	float yOffset;

	// DIAGONAL MOTION, CURRENTLY DISABLED
	// bool up = false;
	// bool right = false;

	float myDeltaTime = 0.0f;

	void allocateStats(int skillPoints = 500);

	sf::Sprite body;
	sf::Sprite target;

	sf::Text offenseText;
	sf::Text defenseText;
	sf::Text speedText;
	sf::Text camouflageText;
	sf::Text reproductionRateText;
	sf::Text lifeSpanText;
	sf::Text metabolismText;
	sf::Text intelligenceText;
	sf::Text teamworkText;
	sf::Text eyesightText;

	sf::Text swimmerText;
	sf::Text walkerText;
};

