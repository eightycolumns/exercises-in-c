#include <math.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

double getFrequencyOfMidiNote(int);
bool isValidMidiNote(char *);
bool stringMatchesPattern(char *, char *);

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Error: expected 1 argument\n");
    return 0;
  } else if (!isValidMidiNote(argv[1])) {
    printf("Error: invalid MIDI note\n");
    return 0;
  }

  int midiNote = atoi(argv[1]);
  double frequency = getFrequencyOfMidiNote(midiNote);

  printf("The frequency of MIDI note %d is %.2f Hz.\n", midiNote, frequency);

  return 0;
}

double getFrequencyOfMidiNote(int midiNote) {
  double semitoneRatio = pow(2, 1/12.0);
  double a4 = 440; // MIDI note 69

  double frequency;

  if (midiNote == 69) {
    frequency = a4;
  } else if (midiNote < 69) {
    frequency = a4 / pow(semitoneRatio, 69 - midiNote);
  } else if (midiNote > 69) {
    frequency = a4 * pow(semitoneRatio, midiNote - 69);
  }

  return frequency;
}

bool isValidMidiNote(char *string) {
  char *pattern = "^(0|[1-9][0-9]*)$";

  if (!stringMatchesPattern(string, pattern)) {
    return false;
  }

  int number = atoi(string);

  if (number < 0 || number > 127) {
    return false;
  }

  return true;
}

bool stringMatchesPattern(char *string, char *pattern) {
  regex_t regex;

  if (regcomp(&regex, pattern, REG_EXTENDED|REG_NOSUB) != 0) {
    return false;
  }

  bool stringMatchesPattern;

  if (regexec(&regex, string, 0, NULL, 0) == 0) {
    stringMatchesPattern = true;
  } else {
    stringMatchesPattern = false;
  }

  regfree(&regex);

  return stringMatchesPattern;
}
