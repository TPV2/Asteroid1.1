#pragma once

#include <string>

using namespace std;

/*
	Para efectos de sonido
	canal 0 para el efecto de los cohetes al disparar
	canal 1 para explosión de los asteroides
	canal 2 para error
	canal 3 para propulsión
	canal 4 para cuando pierdes
	canal 5 gameOver
	canal 6 para resetear
*/
class AudioManager {
public:
	AudioManager();
	virtual ~AudioManager();

	// supposed to be called before start using the object
	virtual bool init() = 0;

	// sound effects
	//Cargar un efecto de sonido
	virtual bool loadSound(int tag, const string& fileName) = 0;
	//Reproducir un efecto de sonido
	virtual int playChannel(int tag, int loops, int channel = -1) = 0;
	//Pausa un canal 
	virtual void pauseChannel(int channel = -1) = 0;
	//Reanuda un canal
	virtual void resumeChannel(int channel = -1) = 0;
	//Detiene un canal
	virtual void haltChannel(int channel = -1) = 0;
	//Cambia el volumen de un canal
	virtual int setChannelVolume(int volume, int channel = -1) = 0;
	virtual int channels() = 0;

	// music
	virtual bool loadMusic(int tag, const string& fileName) = 0;
	virtual void playMusic(int tag, int loops = -1) = 0;
	virtual int setMusicVolume(int volume) = 0;
	virtual void haltMusic() = 0;
	virtual void pauseMusic() = 0;
	virtual void resumeMusic() = 0;
};

