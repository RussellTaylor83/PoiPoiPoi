#include <IRremote.h>
#include <FastLED.h>
#include <vector>

#include "imagestruct.h" //has to be done like this to give the type the correct scope
#include "sequences.h"

#define NUM_BUTTONS   2       // number of remote buttons
#define NUM_LEDS      60      // number of leds in strip length on one side
#define DATA_PIN      2       // 7 = second hardware spi data
#define CLOCK_PIN     3       // 14 = second hardware spi clock
#define RECV_PIN      6

uint16_t lastCode = 0;        // keeps track of last ir code
boolean ledEnable = 1;
int chosenSequence = 0;       
int numberOfSequences = 0; //sizeof(Sequences);

const uint16_t BUTTON_ON = 0xFFE21D; //ir remote codes
const uint16_t BUTTON_OFF = 0xFFA25D;

CRGB leds[NUM_LEDS];
IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode (RECV_PIN, INPUT);

  attachInterrupt(RECV_PIN, CheckIR, CHANGE);

  delay(200);

  FastLED.addLeds<APA102, 2, 3, BGR>(leds, NUM_LEDS);
}

//The main event, where all run time stuff happens
void loop()
{
  if (ledEnable)
  {
    //for (unsigned int x = 0; x < sizeof(Sequences[chosenSequence]); x++) {      // for each image in the chosen sequence
        //PoiSonic(&Sequences[chosenSequence][x]);
    //}
        
    //    PoiSonic(10000, 150, flower, 200); //call method, length of time image displayed, number of slices in image, image name, rotation speed
    //    PoiSonic(10000, 150, arrows, 200);
    //    PoiSonic(10000, 77, skullxbones, 200);
    //    PoiSonic(20000, 231, justeat, 200);
    //    PoiSonic(10000, 70, celticknot, 500);
    //    PoiSonic(10000, 100, infernopattern, 500);
    //    PoiSonic(10000, 150, lightning3white, 500);
    //    PoiSonic(10000, 125, holdinghands, 500);
  }
}

//void SequenceUp() {
//  if (chosenSequence == numberOfSequences) {
//    chosenSequence = 0;
//  } else {
//    chosenSequence++;
//  }
//}
//
//void SequenceDown() {
//  if (chosenSequence == 0) {
//    chosenSequence = numberOfSequences;
//  } else {
//    chosenSequence--;
//  }
//}

void ResetStrips()
{
  FastLED.clear();
  FastLED.show();
}

void CheckIR()
{
  if (irrecv.decode(&results)) {
    uint16_t resultCode = (results.value & 0xFFFF);
    if (resultCode == 0xFFFF)
      resultCode = lastCode;
    else
      lastCode = resultCode;
    switch (resultCode)
    {
      case BUTTON_ON:
        ledEnable = 1;
        break;

      case BUTTON_OFF:
        ledEnable = 0;
        break;

      default:
        Serial.print("Unrecognized code received: 0x");
        Serial.println(results.value, HEX);
        break;
    }

    irrecv.resume();
  }
}

void PoiSonic(ImageStruct *image) {
  if (ledEnable == 0) {
    return;
  }
  unsigned long currentTime = millis();
  while (millis() < currentTime + (image->duration)) {

    int z; //just a count, should be able to move this into the second for loop? same as int x =
    
    for (int x = 0; x < image->numberOfSlices; x++) {                  // for each slice
      for (z = NUM_LEDS; z > 0; z--) {                                // for each led
        leds[z - 1] = image->image[x + ((NUM_LEDS - z) * image->numberOfSlices)];   //
        if (ledEnable == 0) {
          ResetStrips();
          return;
        }
      }
      FastLED.show();

      delayMicroseconds(image->rotationSpeed); //may need to increase / decrease depending on spin rate
    }
  }
}
