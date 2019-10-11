#pragma once
#include <fmod.hpp>
#include <vector>
#include <map>

class CAudioManager
{
public:
	CAudioManager();
	~CAudioManager();
	bool Initialise();
	void Update();
	bool playSound(std::string _soundName);
private:
	FMOD::System* m_audioSystem;
	std::map<std::string, FMOD::Sound*> m_SOUNDS;
};