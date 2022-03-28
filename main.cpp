#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"
#include "morse/morse.hpp"
#include "oscillator/SineOscillator.h"

// TODO(paul) refaire la gestion des arguments?
// TODO(paul) mettre en minuscule l'argument text
// TODO(paul) interrompre si caractère inconnu

string convert_sentence(const char *string, json json);

using namespace std;
using json = nlohmann::json;

const string file_name("alphabet.json");
const string audio_file("result.wav");
const int defaultFrequency(440);


ifstream openFile(string fileName) {
    ifstream file(fileName);
    return file;
}

void writeToFile(ofstream &file, int value, int size) {
    file.write(reinterpret_cast<const char *> (&value), size);
}

void writeSongData(double duration, SineOscillator sineOscillator, ofstream &audioFile) {
    auto maxAmplitude = pow(2, bitDepth - 1) - 1;
    int intSample;
    auto sample = sineOscillator.process();

    maxAmplitude = pow(2, bitDepth - 1) - 1;
    for (int i = 0; i < sampleRate * duration; i++) {
        sample = sineOscillator.process();
        intSample = static_cast<int> (sample * maxAmplitude);
        writeToFile(audioFile, intSample, 2);
    }
}

void writeHeadWawFile(ofstream &audioFile) {
    //Header chunk
    audioFile << "RIFF";
    audioFile << "----";
    audioFile << "WAVE";

    // Format chunk
    audioFile << "fmt ";
    writeToFile(audioFile, 16, 4); // Size
    writeToFile(audioFile, 1, 2); // Compression code
    writeToFile(audioFile, 1, 2); // Number of channels
    writeToFile(audioFile, sampleRate, 4); // Sample rate
    writeToFile(audioFile, sampleRate * bitDepth / 8, 4); // Byte rate
    writeToFile(audioFile, bitDepth / 8, 2); // Block align
    writeToFile(audioFile, bitDepth, 2); // Bit depth

    //Data chunk
    audioFile << "data";
    audioFile << "----";
}

void create(string toTranslate, int frequency) {
    // Load Alphabet (JSON FORMAT)
    ifstream file = openFile(file_name);
    json json_alphabet;
    file >> json_alphabet;

    // Translate in Morse using the Alphabet
    string translated;
    translated = convertSentence(toTranslate, json_alphabet);

    cout << "MORSE" << " > " << translated << "\n";

    // Creating the Audio File
    double duration;
    ofstream audioFile;
    audioFile.open(audio_file, ios::binary);
    SineOscillator sineOscillator(frequency, 0.5);

    writeHeadWawFile(audioFile);

    int preAudioPosition;
    int postAudioPosition;
    // For each char we create a binary
    // We write this binary in a WAV file
    for (char c: translated) {
        switch (c) {
            case '.':
                duration = 0.1;
                sineOscillator.setFrequency(frequency);
                break;
            case '-':
                duration = 0.2;
                sineOscillator.setFrequency(frequency);
                break;
            case ' ':
                duration = 0.1;
                sineOscillator.setFrequency(0);
                break;
            case '/':
                duration = 0.3;
                sineOscillator.setFrequency(0);
                break;
            default:
                break;
        }
        preAudioPosition = audioFile.tellp();
        writeSongData(duration, sineOscillator, audioFile);

        sineOscillator.setFrequency(0);
        writeSongData(0.02, sineOscillator, audioFile);
        postAudioPosition = audioFile.tellp();

    }

    audioFile.seekp(preAudioPosition - 4);
    writeToFile(audioFile, postAudioPosition - preAudioPosition, 4);

    audioFile.seekp(4, ios::beg);
    writeToFile(audioFile, postAudioPosition - 8, 4);

    audioFile.close();
};

void display_Help() {
    cout << "HELP!\n";
}

int main(int argc, char *argv[]) {
    int frequency;
    string toTranslate;

    bool displayHelp, textArg, freqArg;
    int idTextArg, idFreqArg;
    string arg;
    for (int i = 0; i < argc; ++i) {
        arg = argv[i];
        if(arg == "-help") {
            displayHelp = true;
        }
        if(arg == "-text") {
            textArg = true;
            idTextArg = i;
        }
        if(arg == "-freq") {
            freqArg = true;
            idFreqArg = i;
        }
    }

    if(displayHelp) {
        display_Help();
    }
    if(textArg) {
        try {
            toTranslate = argv[idTextArg+1];
        }
        catch (...) {
            cout << "Invalid or Missing argument for text. Try -help to get more information.\n";
        }
    }
    if(freqArg) {
        try {
            frequency = atoi(argv[idFreqArg+1]);
            if (frequency==0) {
                frequency = defaultFrequency;
            }
        }
        catch (...) {
            cout << "Invalid or Missing argument for frequency. Try -help to get more information.\n";
        }
    }
    else {
        frequency = defaultFrequency;
    }

    if(textArg) {
        cout << "INPUT >" << "\n";
        cout << "\t text: " << toTranslate << "\n";
        cout << "\t freq: " << frequency << "\n";
        create(toTranslate, frequency);
        cout << "OUTPUT > result.wav \n";
    }

    return 0;
}

