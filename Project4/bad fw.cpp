
/*
FireworksBase::FireworksBase(sf::Vector2f l_position, float l_velocityMag, float l_theta, int l_size):
	initVelocity(l_velocityMag*cos(l_theta),l_velocityMag*sin(l_theta)), position(l_position), theta(l_theta), FWsize(l_size), initPos(l_position)
{
	m_fwBody.setOrigin(l_size / 2, l_size / 2);
	m_fwBody.setSize(sf::Vector2<float>(FWsize,FWsize));
	m_fwBody.setFillColor(sf::Color::Red);
	fireworkTimer.restart();
	
}
void FireworksBase::Start(float l_timer) {
	isThereATimer = 1; 
	timeToStart = sf::seconds(l_timer);
	fireworkTimer.restart(); 
	if (doRandomThetaOffset) {
		createRTO(); 
	}
	//setDestroyTimeRelativeToBurst(sf::seconds(0.01));
}
FireworksBase::~FireworksBase()
{
}

sf::Vector2f FireworksBase::GetPosition()
{
	return position; 
}
void FireworksBase::SetPosition(sf::Vector2f newPos)
{
	position = newPos; 
}
void FireworksBase::UpdatePosition()
{
	if (fireworkTimer.getElapsedTime() > timeToStart && active == 0 && isThereATimer && first == 1) {
		fireworkTimer.restart();
		toggleActive(1);
		first = 0;
	}
	if (active == 1) {

		float seconds = fireworkTimer.getElapsedTime().asSeconds();
		position.x = initVelocity.x * seconds + initPos.x;
		position.y = initPos.y + (initVelocity.y * seconds) + 0.5 * gravity * pow(seconds, 2);
	}
	if (fireworkTimer.getElapsedTime() > fireWorkBurstTime && didFireWorkBurst == 0) {
		didFireWorkBurst = 1;
		m_fwBody.setFillColor(sf::Color::Transparent);
		if (currentLevelOfRecursion < LevelsOfRecursionToDo) CreateChildren();
		//std::cout << "BURST!" << std::endl; 
		
		//toggleActive(0);
	}
	for (int i = 0; i < childrenFireworks.size(); i++) {
		childrenFireworks[i].UpdatePosition();
		if (childrenFireworks[i].finishing == 1 && childrenFireworks[i].childrenFireworks.size() == 0) { // fix this later 
			if (childrenFireworks[i].isTrailFinished()) {
				//std::cout << "test" << std::endl; 
				childrenFireworks.clear(); 
			}
		}
	}
	if (fireworkTimer.getElapsedTime() >= destroyTime) {
		//std::cout << "time exceeded destroy time!" << std::endl; 
		finishing = 1; 
	}
}

sf::Vector2f FireworksBase::GetDirection()
{
	return direction; 
}
void FireworksBase::SetDirection(sf::Vector2f newDir)
{
	direction = newDir; 
}

float FireworksBase::GetTheta()
{
	return theta; 
}
void FireworksBase::SetTheta(float l_theta) {
	theta = l_theta; 
}
void FireworksBase::SetRandomThetaOffset(bool doOffset)
{
	doRandomThetaOffset = doOffset;
}

void FireworksBase::SetSize(int l_size) {
	FWsize = l_size; 
}
int FireworksBase::GetSize() {
	return FWsize; 
}

void FireworksBase::SetBurstToPeak() {
	fireWorkBurstTime = sf::seconds(-initVelocity.y / gravity);
}
void FireworksBase::SetBurstSecond(sf::Time l_timeToBurst) {
	if (l_timeToBurst == sf::seconds(-1)) {
		didFireWorkBurst = 1; 
	}
	fireWorkBurstTime = l_timeToBurst; 
}
void FireworksBase::SetBurstDetails(BurstDetails& l_BurstDetail)
{
	burstDetail = l_BurstDetail; 
}
void FireworksBase::setFireWorkDontBurst()
{
	didFireWorkBurst = 1;
	setRecursionsToDo(0);
}

void FireworksBase::setCurrentRecursionLevel(int crntlvl)
{
	currentLevelOfRecursion = crntlvl; 
}

void FireworksBase::setRecursionsToDo(int todo)
{
	LevelsOfRecursionToDo = todo; 
}

void FireworksBase::setDestroyTime(sf::Time time )
{
	destroyTime = fireworkTimer.getElapsedTime() + time;
}
void FireworksBase::setDestroyTimeRelativeToBurst(sf::Time time)
{
	destroyTime = fireworkTimer.getElapsedTime() + time + fireWorkBurstTime; 
}

void FireworksBase::setChildrenCount(int children) {
	burstDetail.amountOfChildren = children;
	burstDetail.thetaBetweenChildren = 2 * M_PI / children;
}
void FireworksBase::SetVelocity(float mag, float theta)
{
	initVelocity = sf::Vector2f{ mag * cos(theta), mag * sin(theta) };
}
void FireworksBase::CreateChildren()
{
	//consoleLog("creating children"); 
	float currentTheta;
	for (int i = 0; i < burstDetail.amountOfChildren; i++) {
		currentTheta = randomThetaOffset + burstDetail.thetaBetweenChildren * (i);
		FireworksBase temp(GetPosition(), 20, currentTheta, 10);

		temp.setCurrentRecursionLevel(currentLevelOfRecursion + 1);
		temp.setRecursionsToDo(LevelsOfRecursionToDo);
		temp.setChildrenCount(12);
		temp.SetBurstSecond(sf::seconds(1));
		temp.setDestroyTime(sf::seconds(0.10)); // make this back to normal later 
		temp.SetTrailColors(trailColors);
		temp.Start();

		childrenFireworks.push_back(temp);
	}
}

void FireworksBase::Render(Window* m_window)
{
	int width = m_window->GetWindowSize().x;
	int height = m_window->GetWindowSize().y;

	
	int tempX = (position.x / roomWidth) * width;
	int tempY = height - (position.y / roomHeight) * height; \

		if (tempX > width || tempY > (height + 10) && active == 1) {
			m_fwBody.setFillColor(sf::Color::Transparent);
			toggleActive(0);
		}
		else  if (didFireWorkBurst == 0) {
			m_fwBody.setFillColor(sf::Color::Transparent);
		}
	m_fwBody.setPosition(tempX, tempY);
	m_window->Draw(m_fwBody);
	for (int i = 0; i < childrenFireworks.size(); i++) {
		childrenFireworks[i].Render(m_window); // rendering baby fireworks 
	}

	sf::Vector2i posOnScreen(tempX, tempY); // idk it wasnt letting me pass it without making a new variable so i just did 
	if (didFireWorkBurst == 1 && finishing ==1) {
		myTrail.Update();
	}
	else {
		myTrail.Update(posOnScreen);
	}
	// updating the trail, had to do it here instead of in update because here is where i defined the location on screen for stuff, though i guess maybe i could define the location on screen somewhere else? idk 
	myTrail.Render(m_window); // rendering the trail 
}

bool FireworksBase::isTrailFinished()
{
	return myTrail.isFinished();
}
void FireworksBase::SetTrailColors(int slot, sf::Color newColor)
{
	if (slot == 1) {
		trailColors.first = newColor; 
	}
	else if (slot == 2) {
		trailColors.second = newColor; 
	}
	else {
		std::cout << "(setting trail colors)ERROR! i require a number between 1 and 2" << std::endl; 
	}
	myTrail.SetTrailColors(trailColors);
}
void FireworksBase::SetTrailColors(colorpair pair)
{
	trailColors = pair; 
	myTrail.SetTrailColors(trailColors);
}

void FireworksBase::toggleActive(bool l_active)
{
	//std::cout << "active is now " << (l_active ? " on " : "off") << std::endl; 
	active = l_active; 
}

void FireworksBase::createRTO() {
	srand(time(NULL));
	randomThetaOffset = rand() % 1000;
	randomThetaOffset /= 1000;
	randomThetaOffset *= 2 * (M_PI); 
}

/*
		FireworkWVec temp(GetPosition(), currentTheta, currentLevelOfRecursion + 1, LevelsOfRecursionToDo);

		SetTrailColors(*trailcolors);
		SetBurstTimes(*burstTimes);
		SetDestroyTimes(*destroyTimes);
		SetVelocitiesMag(*velocities);
		SetChildrenVec(*childrenVec);
		temp.Start();
*/


