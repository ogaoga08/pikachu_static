#include "M5StickCPlus2.h"

int PinG26 = 26;
int PinG36 = 36;

// 音階
#define NOTE_C4 261.626  //ド4 C4
#define NOTE_C4b 277.183 //ド#4 C#4
#define NOTE_D4 293.665  //レ4 D4
#define NOTE_D4b 311.127 //レ#4 D#4
#define NOTE_E4 329.628  //ミ4 E4
#define NOTE_F4 349.228  //ファ4 F4
#define NOTE_F4b 369.994 //ファ#4 F#4
#define NOTE_G4 391.995  //ソ4 G4
#define NOTE_G4b 415.305 //ソ#4 G#4
#define NOTE_A4 440.000  //ラ4 A4
#define NOTE_A4b 466.164 //ラ#4 A#4
#define NOTE_B4 493.883  //シ4 B4
#define NOTE_C5 523.251  //ド5 C5
#define NOTE_C5b 554.365 //ド#5 C#5
#define NOTE_D5 587.330  //レ5 D5
#define NOTE_D5b 622.254 //レ#5 D#5
#define NOTE_E5 659.255  //ミ5 E5
#define NOTE_F5 698.456  //ファ5 F5
#define NOTE_F5b 739.989 //ファ#5 F#5
#define NOTE_G5 783.991  //ソ5 G5
#define NOTE_G5b 830.609 //ソ#5 G#5
#define NOTE_A5 880.000  //ラ5 A5
#define NOTE_A5b 932.328 //ラ#5 A#5
#define NOTE_B5 987.767  //シ5 B5
#define NOTE_C6 1046.502 //ド6 C6

//音符の長さ
#define R_4 2800
#define R_3 2100
#define R_2 1400
#define R_1 700
#define R_1_2 350
#define R_1_3 233.3
#define R_1_4 175
#define R_1_6 116.6
#define R_1_8 87.5
#define R_1_12 58.3
#define R_1_16 43.75

// ピカチュウの鳴き声のメロディ
// float pikachu[][2] = {
//   {NOTE_C5, R_1_4},  {NOTE_A4b, R_1_16}, {NOTE_A4, R_1_16},
//   {NOTE_G4b, R_1_16}, {NOTE_G4, R_1_16}, {NOTE_F4b, R_1_16},
//   {NOTE_E4, R_1_16}, {NOTE_D4b, R_1_16}, {NOTE_D4, R_1_16}, {NOTE_C4b, R_1_16},
//   {NOTE_C4, R_1_4}
// };
float pikachu[][2] = {
  {256, 100},  {515, 100}, {610, 150},
  {452, 150}, {518, 150}
};

void setup() {
  M5.Lcd.setFont(&fonts::lgfxJapanGothicP_32); 
  StickCP2.begin();                  
  StickCP2.Lcd.setTextSize(1);       
  StickCP2.Lcd.setRotation(0);       
  StickCP2.Lcd.setTextColor(WHITE);  
  M5.Speaker.setVolume(255);
}

void loop() {
  int valG26 = analogRead(PinG26);  
  int valG36 = analogRead(PinG36);  
  
  StickCP2.Lcd.fillScreen(BLACK);            
  StickCP2.Lcd.setCursor(0, 0);
  StickCP2.Lcd.printf("L:     %d\n", valG26); 
  StickCP2.Lcd.printf("R:     %d\n", valG36);

  // G26またはG36が0の場合に音を鳴らす
  if (valG26 == 0 || valG36 == 0) {
    StickCP2.Lcd.fillScreen(YELLOW);  
    StickCP2.Lcd.setTextColor(BLACK);
    StickCP2.Lcd.setTextSize(1); 
    StickCP2.Lcd.setCursor(20, 20); 
    StickCP2.Lcd.printf("ピカァ");
    for (int i = 0; i < sizeof(pikachu) / sizeof(pikachu[0]); i++) {
        M5.Speaker.tone(pikachu[i][0]);
        delay(pikachu[i][1] * 0.8);
        M5.Speaker.stop();
        delay(pikachu[i][1] * 0.1);
    }
    M5.Speaker.stop();
  }

  delay(400);  // 繰り返しの間隔を設定
}
