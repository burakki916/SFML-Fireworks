#include "Trail.h"

Trail::Trail(int TrailStartOpacity, colorpair l_colorPair, int trailRecSize, float secondsBetweenTrailSegments, int l_OpacityDecreaseRate)
	: maxOpacity(TrailStartOpacity), m_colorPairforTrail(l_colorPair), maxSize(trailRecSize), updateInterval(sf::seconds(secondsBetweenTrailSegments)), OpacityDecreaseRate(l_OpacityDecreaseRate)
{	
}

void Trail::Update(sf::Vector2i& l_currentPosOnScreen)
{
	if (trailUpateTimer.getElapsedTime() > updateInterval) {
		trailUpateTimer.restart(); 

		TrailSegment tempObj(l_currentPosOnScreen, { m_colorPairforTrail }, maxOpacity);
		tempObj.segRec.setOrigin(maxSize / 2, maxSize / 2);
		trailVec.push_back(tempObj);
		Fade();
	}

}
void Trail::Update()
{
	if (trailUpateTimer.getElapsedTime() > updateInterval) {
		trailUpateTimer.restart();
		Fade();
	}
}
bool Trail::isFinished()
{
	if (trailVec.size() == 0) {
		return true; 
	}
	else {
		return false; 
	}
}
void Trail::Render(Window* m_window) {
	for (TrailSegment currentTrailSeg : trailVec) {
		m_window->BlurDraw(currentTrailSeg.segRec);		
	}
}
void Trail::SetTrailColors(colorpair l_pair)
{
	m_colorPairforTrail = l_pair; 
}
void Trail::Fade() {
	for (TrailSegment& segment : trailVec) {
		if (segment.segRec.getSize().x - sizeDecreateRate > 0) {
			segment.segRec.setSize(sf::Vector2f(segment.segRec.getSize().x - sizeDecreateRate, segment.segRec.getSize().x - sizeDecreateRate));
			segment.segRec.setOrigin(segment.segRec.getSize().x / 2, segment.segRec.getSize().y / 2);
		}
		else {
			segment.segRec.setSize(sf::Vector2f(0, 0));
		}
		tempColor = segment.segRec.getFillColor(); // using temp color to modify 

		ColorincrementToValue(tempColor.r, segment.trailColors.second.r);
		ColorincrementToValue(tempColor.g, segment.trailColors.second.g);
		ColorincrementToValue(tempColor.b, segment.trailColors.second.b);
		
		if (tempColor.a - OpacityDecreaseRate >= 0) {
			tempColor.a -= OpacityDecreaseRate;
			//std::cout << "opacity decrease rate is " << OpacityDecreaseRate << std::endl; 
			segment.segRec.setFillColor(tempColor);
		}
		else {
			trailVec.pop_front();
		}
	}
}

void Trail::ColorincrementToValue(sf::Uint8& valToMod, sf::Uint8& valGoal)
{
	if (abs(valToMod-valGoal)<colorChangeRate)
	{
		valToMod = valGoal;
	}
	else {
		if (valGoal < valToMod)
			valToMod -= colorChangeRate;
		if (valGoal > valToMod)
			valToMod += colorChangeRate;
	}
}
