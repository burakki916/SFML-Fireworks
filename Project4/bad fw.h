/*
#pragma once
#include "Window.h"
#include <vector>
#include "trail.h"

enum burstTypes { normal, straight, special };
struct BurstDetails {
	int amountOfChildren = 0;
	float thetaBetweenChildren = 0 ;
	burstTypes typeOfBurst; 
};
class FireworksBase
{
public:
	FireworksBase(sf::Vector2f l_position, float l_velocityMag, float l_theta = (M_PI/2), int l_size = 20);
	void Start(float l_timer = 0);
	~FireworksBase();


	sf::Vector2f GetPosition();
	void SetPosition(sf::Vector2f newPos);
	void UpdatePosition();

	sf::Vector2f GetDirection();
	void SetDirection(sf::Vector2f newDir);
	
	void SetTheta(float l_theta);
	float GetTheta();
	void SetRandomThetaOffset(bool doOffset);

	void SetSize(int l_size);
	int GetSize();

	void SetBurstToPeak(); 
	void SetBurstSecond(sf::Time l_timeToBurst);
	void SetBurstDetails(BurstDetails& l_BurstDetail);
	void setFireWorkDontBurst();
	
	void setDestroyTime(sf::Time time);
	void setDestroyTimeRelativeToBurst(sf::Time time); 

	void setCurrentRecursionLevel(int crntlvl);
	void setRecursionsToDo(int todo);

	void setChildrenCount(int children); 

	int GetOpacity();
	void SetOpacity(int opacity); // overwrite current opacity 
	void UpdateOpacity(); // used to continiously change the opacity/color of firework 

	void SetColor(sf::Color l_color);
	sf::Color GetColor();

	bool isTrailFinished();
	void SetTrailColors(colorpair pair);
	void SetTrailColors(int slot /*1 is first, and  2 is second, sf::Color newColor);

	void Render(Window* m_window);
	
protected:
	float roomWidth = 1280 / 11; // games width and height, not window width and height. used to convert from cordinal cordinates to window cordinates
	float roomHeight = 720 / 11;

	sf::Vector2f position;
	const sf::Vector2f initPos;
	sf::Vector2f initVelocity;
	void SetVelocity(float mag, float theta); 

	sf::Vector2f direction;
	int opacity = 1;
	float theta;
	float randomThetaOffset = 0;
	void createRTO();
	bool doRandomThetaOffset = 1; 

	const float gravity = -9.8;
	sf::RectangleShape m_fwBody;
	int FWsize;
	
	sf::Clock fireworkTimer;
	sf::Time fireWorkBurstTime = sf::seconds(00.1);
	sf::Time timeToStart = sf::seconds(0);
	sf::Time destroyTime = sf::seconds(25); 
	
	bool isThereATimer = 0;
	bool active = 0;
	
	void toggleActive(bool l_active);
	bool didFireWorkBurst = 0;
	bool first = 1;
	
	void CreateChildren();
	std::vector<FireworksBase> childrenFireworks;
	BurstDetails burstDetail; 
	
	Trail myTrail; 
	colorpair trailColors;

	int LevelsOfRecursionToDo = 0;
	int currentLevelOfRecursion = 0;
	
};

*/