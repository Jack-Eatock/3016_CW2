#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include<irrKlang.h>
#include <string>
#include <iostream>
using namespace irrklang;

class AudioManager
{

public:
	static void PlayMusic(std::string Track);
	static void PlaySFX(std::string Track);
	static void StopSFX();
	static void Delete();
private:

	static void Setup();

};

#endif