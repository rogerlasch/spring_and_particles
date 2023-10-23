


#ifndef SOUND_H
#define SOUND_H

    FMOD::System* hsystem;

inline void sound_init(){
    FMOD_RESULT result = FMOD::System_Create(&hsystem);
    if (result != FMOD_OK) {
throw std::runtime_error("Error to Create Fmod System.");
    }

    result = hsystem->init(32, FMOD_INIT_NORMAL, nullptr);
    if (result != FMOD_OK) {
throw std::runtime_error("Error to init Fmod...");
    }
FMOD_VECTOR front={0.0f, 0.0f, 1.0f};
FMOD_VECTOR  top={0.0f, 1.0f, 0.0f};
FMOD_VECTOR listenerPosition={50.0f, 50.0f, 50.0f};
hsystem->set3DListenerAttributes(0, &listenerPosition, nullptr, &front, &top);
}


#endif
