#include <vitasdk.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "soloud.h"
#include "soloud_wavstream.h"

#define MAX_SOUNDS_NUM (1250)

typedef struct {
	int handle;
	SoLoud::WavStream source;
	bool valid;
	bool is_music;
} audio_instance;

SoLoud::Soloud soloud;
audio_instance snd[MAX_SOUNDS_NUM];

extern "C" {

void audio_player_init() {
	soloud.init();
}

void audio_player_set_volume(void *m, float vol) {
	audio_instance *mus = (audio_instance *)m;
	mus->source.setVolume(vol);
	soloud.setVolume(mus->handle, vol);
}

void *audio_player_play(char *path, uint8_t loop, float vol, int id) {
	if (loop) {
		//sceClibPrintf("Loading %s in music slot %d\n", path, curr_snd_loop);
		snd[id].valid = true;
		snd[id].source.load(path);
		snd[id].source.setVolume(vol);
		snd[id].source.setLooping(true);
		snd[id].source.setSingleInstance(true);
		snd[id].handle = soloud.playBackground(snd[id].source);
		snd[id].is_music = true;
		void *r = (void *)&snd[id];
		return r;
	} else {
		//sceClibPrintf("Loading %s in sound slot %d\n", path, curr_snd);
		snd[id].valid = true;
		snd[id].source.load(path);
		snd[id].source.setVolume(vol);
		snd[id].source.setLooping(false);
		snd[id].source.setSingleInstance(true);
		snd[id].handle = soloud.play(snd[id].source);
		snd[id].is_music = false;
		void *r = (void *)&snd[id];
		return r;
	}
}

void audio_player_instance(void *m, uint8_t loop, float vol) {
	audio_instance *mus = (audio_instance *)m;
	if (loop) {
		mus->handle = soloud.playBackground(mus->source);
	} else {
		mus->handle = soloud.play(mus->source);
	}
	audio_player_set_volume(m, vol);
}

int audio_player_is_playing(void *m) {
	audio_instance *mus = (audio_instance *)m;
	return (soloud.isValidVoiceHandle(mus->handle) && !soloud.getPause(mus->handle));
}

void audio_player_stop(void *m) {
	audio_instance *mus = (audio_instance *)m;
	mus->source.stop();
	mus->valid = false;
}

void audio_player_set_pause(void *m, uint8_t val) {
	audio_instance *mus = (audio_instance *)m;
	soloud.setPause(mus->handle, val);
}

void audio_player_stop_all_sounds() {
	soloud.stopAll();
	for (int i = 0; i < MAX_SOUNDS_NUM; i++) {
		snd[i].valid = false;
	}
}

void audio_player_set_pause_all_sounds(uint8_t val) {
	soloud.setPauseAll(val);
}

void audio_player_change_bgm_volume(float vol) {
	for (int i = 0; i < MAX_SOUNDS_NUM; i++) {
		if (snd[i].valid && snd[i].is_music) {
			audio_player_set_volume((void *)&snd[i], vol);
		}
	}
}

void audio_player_change_sfx_volume(float vol) {
	for (int i = 0; i < MAX_SOUNDS_NUM; i++) {
		if (snd[i].valid && !snd[i].is_music) {
			audio_player_set_volume((void *)&snd[i], vol);
		}
	}
}
};