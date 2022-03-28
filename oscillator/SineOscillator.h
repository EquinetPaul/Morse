//
// Created by cytech on 26/03/2022.
//

#ifndef MORSE_SINEOSCILLATOR_H
#define MORSE_SINEOSCILLATOR_H

#include <cmath>

const int sampleRate = 44100;
const int bitDepth = 16;

class SineOscillator {
    float frequency, amplitude, angle = 0.0f, offset = 0.0f;
public:
    SineOscillator(float freq, float amp) : frequency(freq), amplitude(amp) {
        offset = 2 * M_PI * frequency / sampleRate;
    }
    float process() {
        auto sample = amplitude * sin(angle);
        angle += offset;
        return sample;
        // Asin(2pif/sr)
    }

    void updateOffset(float frequency) {
        SineOscillator::offset = 2 * M_PI * frequency / sampleRate;
    }

    float getFrequency() const {
        return frequency;
    }

    void setFrequency(float frequency) {
        updateOffset(frequency);
        SineOscillator::frequency = frequency;
    }
};


#endif //MORSE_SINEOSCILLATOR_H
