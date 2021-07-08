#pragma once
#include <vector>
#include "Window.h"
#include <deque>
using colorpair = std::pair<sf::Color, sf::Color>; 
struct TrailSegment {
	TrailSegment(sf::Vector2i l_segLocation, colorpair l_pair = { sf::Color::White, sf::Color::White }, int l_opacity = 200, float l_regSize = 5)
		: position(l_segLocation), opacity(l_opacity), trailColors(l_pair)
	{
		segRec.setFillColor(trailColors.first);
		segRec.setSize(sf::Vector2f(l_regSize, l_regSize));
		segRec.setPosition(position.x,position.y);
	}
	int opacity; 
	colorpair trailColors; 
	sf::Vector2i position;
	sf::RectangleShape segRec; 
};
class Trail	
{
public: 
	Trail(int TrailStartOpacity = 200, colorpair l_colorPair = {sf::Color::White,sf::Color::White}, int trailRecSize = 5, float secondsBetweenTrailSegments = 0.01, int l_OpacityDecreaseRate = 10);
	void Update(sf::Vector2i& l_currentPosOnScreen); // creates a new piece of the trail and adjusts color and size of other trail parts
	void Update();
	bool isFinished();
	void Render(Window* m_window);

	void SetTrailColors(colorpair l_pair);

private:
	int maxOpacity;
	int OpacityDecreaseRate =0; 
	int maxSize; 
	float sizeDecreateRate = 0.0;
	int colorChangeRate = 10; 

	using trailContainer = std::deque<TrailSegment>;
	trailContainer trailVec; 

	void Fade();
	void ColorincrementToValue(sf::Uint8& valToMod, sf::Uint8& valGoal);


	sf::Time generationCD; 
	colorpair m_colorPairforTrail;
	sf::Color tempColor = sf::Color::White; 

	sf::Clock trailUpateTimer; 
	sf::Time updateInterval = sf::seconds(0.01);

	//sf::Shader luminescence;
	//sf::Shader shader; 
};


