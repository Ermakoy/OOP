#include <iostream>
#include "WavException.h"
#include "Wav.h"

using namespace std;


int main() {
    const char *input_fname = "0.wav";
    const char *output_fname = "out.wav";
    try {
        Wav wav,monoWav;
        wav.createFromFile(input_fname);
        cout << wav.getInfo();
        // #### Make several changes to PCM data.
        // # Making signal mono from stereo.
        wav.makeMono();
        cout << "--------------------------" << endl;
        // #### Making new WAV file using edited PCM data.
        wav.makeWavFile(output_fname);
        // #### Reading the file just created to check its header ctness.
        monoWav.createFromFile(output_fname);
        cout << wav.getInfo();
    }
    catch (WavException e) {
        cout << e.what() << endl;
    }
    return 0;
}