#include "WProgram.h"
#include "brollyflock_sculpture.h"

int roundColor(int inputColor){
   if(inputColor < 0){
     return 0;
   }
   if(inputColor > 1023){
     return 1023;
   }
   return inputColor;
};
/*
Sculpture::Sculpture(){
  numberOfBrollies = NumLEDs;
};

Sculpture::Sculpture(int in_numberOfBrollies,int in_numberOfPropSteps,Brolly in_brollies[],ColorList in_colorScheme[]){
  numberOfBrollies = in_numberOfBrollies;
  numberOfPropSteps = in_numberOfPropSteps;
  brollies = in_brollies;
  colorScheme = in_colorScheme;
}

void Sculpture::initializeBrollies(Brolly firstBrollies[],Propigation showMovement){
  Serial.println("in init");
   for(int i = 0;i < numberOfPropSteps;i++){
      unsigned long newDelay = firstBrollies[showMovement.movement[i].from].extraDelay + showMovement.movement[i].extraTime;
      Serial.println(newDelay);
      firstBrollies[showMovement.movement[i].to].extraDelay = newDelay;
      firstBrollies[showMovement.movement[i].to].delaying = true;
   }
};
*/
/*
Brolly::Brolly(){
     lastStep = 0;
     timeInStep = 0;
     currentStep = 0;
     numberOfSteps = 10;
     currentColor = Color(0,0,0);
//     lastColor = Color(0,0,0);
//     nextColor = Color(0,0,0);
     delaying = false;
     extraDelay = 0;
};

void Brolly::nextStep(){
   delaying = false;
   extraDelay = 0;
   currentStep++;
   if(currentStep > numberOfSteps - 1){
     currentStep = 0;
   }
};

void Brolly::stepProgress(ColorList* colorScheme){
   timeInStep = millis() - lastStep;
   
   float totalTime = colorScheme[currentStep].getDelay(2);
   if(delaying){
     totalTime = totalTime + extraDelay;
   }

   
   if(timeInStep >= totalTime ){
     nextStep();
     lastStep = millis();
     timeInStep = 0;
   }
};


void Brolly::moveColor(ColorList* colorScheme){
   float totalTime = colorScheme[currentStep].getDelay(2);
   if(delaying){
     totalTime = totalTime + extraDelay;
   }
   
   float ratio = float(timeInStep) / float(totalTime);

   //currentColor.progressColor(lastColor,nextColor,ratio);
};

Brolly firstBrollies[NumLEDs];
*/
//Sculpture sculpture(NumLEDs,PropigationSteps,firstBrollies,colorScheme);

