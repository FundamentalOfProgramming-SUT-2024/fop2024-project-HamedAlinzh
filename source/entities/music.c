#include <rogue.h>

pthread_t music_thread;

void *play_music_background(void *arg) {
    const char *music_file = (const char *)arg;

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! Mix_Error: %s\n", Mix_GetError());
        return NULL;
    }

    Mix_Music *music = Mix_LoadMUS(music_file);
    if (!music) {
        printf("Error loading music: %s\n", Mix_GetError());
        return NULL;
    }

    if (Mix_PlayMusic(music, -1) == -1) {
        printf("Error playing music: %s\n", Mix_GetError());
    }
    while (Mix_PlayingMusic()) {
        SDL_Delay(100); 
    }

    Mix_FreeMusic(music);
    Mix_CloseAudio();
    return NULL;
}
void play_music(const char *file) {
    Mix_Music *music = Mix_LoadMUS(file);
    if (!music) {
        printf("Failed to load music: %s\n", Mix_GetError());
        return;
    }

    Mix_PlayMusic(music, -1);
}
void stop_music() {
    Mix_HaltMusic();          
    pthread_cancel(music_thread);
    pthread_join(music_thread, NULL); 
}
void start_music(const char *music_file) {
    if (pthread_create(&music_thread, NULL, play_music_background, (void *)music_file) != 0) {
        printf("Failed to create music thread\n");
    }
}