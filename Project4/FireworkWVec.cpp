#include "FireworkWVec.h"


FireworkWVec::FireworkWVec(sf::Vector2f l_position, float l_theta, int currentlvl, int MaxLevelOfRecursion, std::vector<colorpair>& l_trailcolors, std::vector<sf::Time>& l_burstTimes, std::vector<sf::Time>& l_destroyTimes, std::vector<float>& l_velocities, std::vector<int>& l_vchildrenVec)
	: position(l_position), initPos(l_position), theta(l_theta), LevelsOfRecursionToDo(MaxLevelOfRecursion), currentLevelOfRecursion(currentlvl), trailcolors(&l_trailcolors), burstTimes(&l_burstTimes), destroyTimes(&l_destroyTimes), velocities(&l_velocities), childrenVec(&l_vchildrenVec)
{
	SetVelocity(CurrentVelocityMag(), theta); 
	m_fwBody.setOrigin(1 / 2, 1 / 2);
	m_fwBody.setSize(sf::Vector2<float>(1, 1));
	m_fwBody.setFillColor(sf::Color::Transparent);
	myTrail.SetTrailColors(getCurrentTrailPair()); 

	fireworkTimer.restart();
}

void FireworkWVec::SetRecusionsToDo(int numOfRecursions)
{
	LevelsOfRecursionToDo = numOfRecursions;
}

void FireworkWVec::SetCurrentRecursionLevel(int crntlvl)
{
	currentLevelOfRecursion = crntlvl; 
}

void FireworkWVec::SetTrailColors(std::vector<colorpair>& l_trailcolors)
{
	trailcolors = &l_trailcolors;
}

void FireworkWVec::SetBurstTimes(std::vector<float>& l_burstTimesInSeconds)
{
	for (int i = 0; i < l_burstTimesInSeconds.size();i++) {
		burstTimes->push_back(sf::seconds(l_burstTimesInSeconds[i]));
	}
}

void FireworkWVec::SetBurstTimes(std::vector<sf::Time>& l_burstTimes)
{
	burstTimes = &l_burstTimes; 
}

void FireworkWVec::SetDestroyTimes(std::vector<float>& l_fwDestroyTimesInSeconds)
{
	for (int i = 0; i < l_fwDestroyTimesInSeconds.size(); i++) {
		destroyTimes->push_back(sf::seconds(l_fwDestroyTimesInSeconds[i]));
	}
}
void FireworkWVec::SetDestroyTimes(std::vector<sf::Time>& l_fwDestroyTimes)
{
	destroyTimes = &l_fwDestroyTimes; 
}

void FireworkWVec::SetVelocitiesMag(std::vector<float>& l_velocitiesMag)
{
	velocities = &l_velocitiesMag; 
	

}
void FireworkWVec::SetChildrenVec(std::vector<int>& l_childrenVec)
{
	childrenVec = &l_childrenVec;
	SetVelocity(childrenVec->at(currentLevelOfRecursion), theta); 
}

void FireworkWVec::SetBurstToPeak(bool destroyHereAsWell) {
	burstTimes->at(currentLevelOfRecursion) = sf::seconds(initVelocity.y / M_G);
	if (destroyHereAsWell == 1) {
		destroyTimes->at(currentLevelOfRecursion) = burstTimes->at(currentLevelOfRecursion);
	}
}

void FireworkWVec::Update()
{
	if (fireworkTimer.getElapsedTime() > timeToStart && isThereATimer) {
		fireworkTimer.restart();
		toggleActive(1);
		isThereATimer = 0; 
	}
	if (active == 1) {
		float seconds = fireworkTimer.getElapsedTime().asSeconds();
		position.x = initVelocity.x * seconds + initPos.x;
		position.y = initPos.y + (initVelocity.y * seconds) + 0.5 * (-M_G) * pow(seconds, 2);
	}
	if (fireworkTimer.getElapsedTime() > currentBurstTime() && didFireWorkBurst == 0) {
		//std::cout << "burst!" << std::endl; 
		Burst(); 
	}
	for (int i = 0; i < childrenFireworks.size(); i++) {
		childrenFireworks[i].Update();
		//make it so when the children fireworks die out so does the current firework 
	}
	if (fireworkTimer.getElapsedTime() >= currentDestroyTime()) {
		//std::cout << "time exceeded destroy time!" << std::endl; 
		finishing = 1;
		active = 0; 
	}
}

void FireworkWVec::Render(Window* m_window)
{
	int width = m_window->GetWindowSize().x;
	int height = m_window->GetWindowSize().y;
	sf::Vector2i positionOnScreen = sf::Vector2i((position.x / roomWidth) * width, height - (position.y / roomHeight) * height);

	if (positionOnScreen.x > width || positionOnScreen.y > height && active == 1) {
		toggleActive(0); // if the position of the firework falls off the screen then turn it off. 
	}

	if (active == 0 ) myTrail.Update();//updating the trail without making a new one
	else myTrail.Update(positionOnScreen); // updating the trail with making a new piece of it
	myTrail.Render(m_window); 

	for (int i = 0; i < childrenFireworks.size(); i++) {
		//std::cout << "rendering kids" << std::endl; 
		childrenFireworks[i].Render(m_window); 
	}
}

void FireworkWVec::SetVelocity(float mag, float theta)
{
	initVelocity = sf::Vector2f{ mag * cos(theta), mag * sin(theta) };
}

void FireworkWVec::Start(float countDown)
{
	 if(countDown == 0){
		 isThereATimer = 0; 
		 toggleActive(1);
		 fireworkTimer.restart();
	 }
	 else {
		 timeToStart = sf::seconds(countDown);
		 fireworkTimer.restart();
	 }

	 //figure out later if the random theta offset is worth doing lol 
}

void FireworkWVec::Burst()
{
	didFireWorkBurst = 1; 
	CreateChildren(); 
}

bool FireworkWVec::isTrailFinished()
{
	return myTrail.isFinished(); 
}

colorpair FireworkWVec::getCurrentTrailPair()
{
	if (currentLevelOfRecursion>= trailcolors->size()) {
		return trailcolors->back(); 
	}
	else {
		return trailcolors->at(currentLevelOfRecursion);
	}
}

sf::Time FireworkWVec::currentBurstTime()
{
	if (currentLevelOfRecursion >= burstTimes->size()) {
		return burstTimes->back();
	}
	else {
		return burstTimes->at(currentLevelOfRecursion);

	}
}

sf::Time FireworkWVec::currentDestroyTime()
{
	if (currentLevelOfRecursion >= destroyTimes->size()) {
		return destroyTimes->back();
	}
	else {
		return destroyTimes->at(currentLevelOfRecursion);
	}
}

sf::Vector2f FireworkWVec::currentInitVelocity()
{
	int tempVelo; 
	if (currentLevelOfRecursion >= destroyTimes->size()) {
		tempVelo = velocities->back();
	}
	else {
		tempVelo = velocities->at(currentLevelOfRecursion); 
	}
	return sf::Vector2f(tempVelo * cos(theta), tempVelo * sin(theta));
}

float FireworkWVec::CurrentVelocityMag()
{
	if (currentLevelOfRecursion >= velocities->size()) {
		return velocities->back(); 
	}
	else {
		return velocities->at(currentLevelOfRecursion);
		
	}
}

int FireworkWVec::currentChildrenCount()
{
	if (currentLevelOfRecursion >= LevelsOfRecursionToDo) {
		return 0; 
	}
	else if(currentLevelOfRecursion>=childrenVec->size()) {
		return childrenVec->back(); 
	}
	else {
		return childrenVec->at(currentLevelOfRecursion); // this will be ran if the vector for chidlren is big enough and the current level of recursion isnt bigger than the levels of recursion to do 
	}
}

void FireworkWVec::CreateChildren()
{
	float currentTheta;
	float thetaBetweenChildren =( 2* M_PI )/  currentChildrenCount(); 
	//std::cout << "creating children!" << std::endl; 
	for (int i = 0; i < currentChildrenCount(); i++) {
		currentTheta =  thetaBetweenChildren * (i); // remember to test later if random theta offset is worth having
		FireworkWVec temp(position, currentTheta, currentLevelOfRecursion + 1, LevelsOfRecursionToDo,
			*trailcolors, *burstTimes, *destroyTimes, *velocities, *childrenVec
		);

		temp.Start();

		childrenFireworks.push_back(temp);
	}
}

void FireworkWVec::toggleActive(bool l_activity)
{
	//std::cout << "firework is now :" << l_activity <<std::endl;
	active = l_activity; 
}
