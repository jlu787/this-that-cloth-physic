#include "audio.h"

CAudioManager::CAudioManager()
{
}

CAudioManager::~CAudioManager()
{
	/*background->release();
	collect->release();
	hit->release();*/
	m_audioSystem->release();
}

bool CAudioManager::Initialise()
{
	FMOD_RESULT result;
	result = FMOD::System_Create(&m_audioSystem);
	if (result != FMOD_OK)
		return false;

	result = m_audioSystem->init(100, FMOD_INIT_NORMAL | FMOD_INIT_3D_RIGHTHANDED, 0);
	if (result != FMOD_OK)
		return false;

	// Load in sounds
	result = m_audioSystem->createSound(
		"Resources/Audio/dance.mp3",
		FMOD_LOOP_NORMAL,
		0,
		&m_SOUNDS["BACKGROUND"]
	);

	if (result != FMOD_OK)
		return false;

	result = m_audioSystem->createSound(
		"Resources/Audio/MUDA.wav",
		FMOD_DEFAULT,
		0,
		&m_SOUNDS["MUDA"]
	);


	if (result != FMOD_OK)
		return false;

	result = m_audioSystem->createSound(
		"Resources/Audio/thump.wav",
		FMOD_DEFAULT,
		0,
		&m_SOUNDS["HURT"]
	);
	if (result != FMOD_OK)
		return false;

	result = m_audioSystem->createSound(
		"Resources/Audio/pickup_coin.wav",
		FMOD_DEFAULT,
		0,
		&m_SOUNDS["PING"]
	);
	if (result != FMOD_OK)
		return false;



	return true;
}

void CAudioManager::Update()
{
	m_audioSystem->update();
}

bool CAudioManager::playSound(std::string _soundName)
{
	FMOD_RESULT result = m_audioSystem->playSound(m_SOUNDS[_soundName], 0, false, 0);
		if (result != FMOD_OK)
			return false;
	
		return true;
}



//bool CAudioManager::playBackground()
//{
//	FMOD_RESULT result = m_audioSystem->playSound(background, 0, false, 0);
//	if (result != FMOD_OK)
//		return false;
//
//	return true;
//}
//
//bool CAudioManager::playCollect()
//{
//	FMOD_RESULT result = m_audioSystem->playSound(collect, 0, false, 0);
//	if (result != FMOD_OK)
//		return false;
//
//	return true;
//}
//
//bool CAudioManager::playHit()
//{
//	FMOD_RESULT result = m_audioSystem->playSound(hit, 0, false, 0);
//	if (result != FMOD_OK)
//		return false;
//
//	return true;
//}
