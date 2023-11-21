#include <Arduino.h>
#include <vector>
#include <fileToVector.h>
#include <SD.h>                      // sd card library
#include <SPI.h>                     // spi library for sd card

std::vector<String> toStringVector(File file){
  std::vector<String> result;
  if(file){
    while(file.available()){
      String input = "";
      input = file.readStringUntil('\n'); 
      input.trim();
      result.push_back(input);
    }
    file.close();
  }
  else{
    Serial.println("file failed");
  }
  return result;
}

std::vector<String> splitString(String input, char character){
  std::vector<String> result;
  int firstCharacter = -1;

  for(int i=0; i<input.length(); i++){
    if((input.charAt(i) == character)){
      result.push_back(input.substring(firstCharacter+1, i));
      firstCharacter = i;
    }
    
    if(i == input.length()-1){
      result.push_back(input.substring(firstCharacter+1, i+1));
      firstCharacter = i;
    }
  }
  return result;
}

 std::vector<std::array<int, 3>> toIntVector(String input){
    std::vector<std::array<int, 3>> result;

    std::vector<String> stringVector = splitString(input, ';'); //{"0,0,0", "0,0,0", "0,0,0"}
    for(int i=0; i < stringVector.size(); i++){
        std::vector<String> string2Vector = splitString(stringVector[i], ','); //{"0","0","0"}
        std::array<int, 3> intVector;

        for(int i=0; i<string2Vector.size(); i++){
            intVector[i] = string2Vector[i].toInt(); //{0,0,0}
        }
        
        result.push_back(intVector);
    }
    return result;
}

