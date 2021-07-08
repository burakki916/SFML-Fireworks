#pragma once
#define GRAV = -9.8
#include "Window.h"
#include <vector>
#include "trail.h"
//#include "FireworksBase.h"

class FireworkWVec 
    //private FireworksBase
{
public:
    FireworkWVec(sf::Vector2f l_position, float l_theta, int currentlvl, int MaxLevelOfRecursion,
            std::vector<colorpair>& l_trailcolors,
            std::vector<sf::Time>& l_burstTimes,
            std::vector<sf::Time>& l_destroyTimes,
            std::vector<float>& l_velocities,
            std::vector<int>& l_vchildrenVec
        );
    void SetRecusionsToDo(int numOfRecursions);
    void SetCurrentRecursionLevel(int crntlvl);

    void SetTrailColors(std::vector<colorpair>& l_trailcolors);
    void SetBurstTimes(std::vector<float>& l_burstTimesInSeconds);
    void SetBurstTimes(std::vector<sf::Time>& l_burstTimes);
    void SetDestroyTimes(std::vector<float>& l_fwDestroyTimesInSeconds);
    void SetDestroyTimes(std::vector<sf::Time>& l_fwDestroyTimes);
    void SetVelocitiesMag(std::vector<float>& l_velocitiesMag);
    void SetChildrenVec(std::vector<int>& l_childrenVec);
    void SetBurstToPeak(bool destroyHereAsWell = 1); 
  
    void Update();
    void Render(Window* m_window);

    void SetVelocity(float mag, float theta);


    void Start(float countDown = 0);
    void Burst(); 
    bool isTrailFinished();

    bool finishing = 0;
private: 
    Trail myTrail;
    float roomWidth = 1280 / 11; // games width and height, not window width and height. used to convert from cordinal cordinates to window cordinates
    float roomHeight = 720 / 11;
    sf::RectangleShape m_fwBody;


    colorpair getCurrentTrailPair();

    sf::Time currentBurstTime(); 
    sf::Time currentDestroyTime();

    sf::Vector2f currentInitVelocity();
    float CurrentVelocityMag();
    int currentChildrenCount();

    void CreateChildren(); 

    std::vector<colorpair>* trailcolors;
    std::vector<sf::Time>* burstTimes;
    std::vector<sf::Time>* destroyTimes;
    std::vector<float>* velocities;
    std::vector<int>* childrenVec;

    using fireworkContainer = std::vector<FireworkWVec>;
    fireworkContainer childrenFireworks; 

    int LevelsOfRecursionToDo = 0;
    int currentLevelOfRecursion = 0;

    sf::Vector2f position;
    const sf::Vector2f initPos;
    sf::Vector2f initVelocity; 
    float theta; 

    //time stuff 
    sf::Clock fireworkTimer;
    sf::Time fireWorkBurstTime = sf::seconds(5);
    sf::Time timeToStart = sf::seconds(0);
    sf::Time destroyTime = sf::seconds(25);
    bool isThereATimer = 0; 
   
    bool didFireWorkBurst = 0;

    bool active = 0;
    void toggleActive(bool l_activity);

    
};

