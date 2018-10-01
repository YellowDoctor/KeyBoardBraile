#include <Keypad.h>
#include <Keyboard.h>
const byte ROWS = 4; // 4 строчки
const byte COLS = 3; // 3 столбца
char keys[ROWS][COLS] = {
  {'1', '2', 'a'},
  {'3', '4', 'b'},
  {'5', '6', 'c'},
  {'7', '8', 'd'}
};

char Package;
byte rowPins[ROWS] = {9, 8, 7, 6}; //массив строк клавиатуры
byte colPins[COLS] = {5, 4, 3};
bool SwitchLang = false;
byte BraileEN[] = {0b00000001, 0b00000101, 0b00000011, 0b00001011, 0b00001001, 0b00000111, 0b00001111, 0b00001101, 0b00000110, 0b00001110, 0b00010001, 0b00010101, 0b00010011, 0b00011011, 0b00011001, 0b00010111, 0b00011111, 0b00011101, 0b00010110, 0b00011110, 0b00110001, 0b00110101, 0b00110011, 0b00111011, 0b00111001, 0b00101110, 0b00101100, 0b00011100, 0b00110000, 0b00110100, 0b00111000, 0b00100101, 0b00011010, 0b00000100, 0b00100100, 0b00000000};
byte BraileRUS[] = {0b00000001, 0b00000101, 0b00101110, 0b00001111, 0b00001011, 0b00001001, 0b00100001, 0b00001110, 0b00111001, 0b00000110, 0b00110111, 0b00010001, 0b00010101, 0b00010011, 0b00011011, 0b00011001, 0b00010111, 0b00011101, 0b00010110, 0b00011110, 0b00110001, 0b00000111, 0b00001101, 0b00000011, 0b00011111, 0b00101001, 0b00110011, 0b00111101, 0b00110110, 0b00111110, 0b00100110, 0b00101101, 0b00100111, 0b00101100, 0b00011100, 0b00110000, 0b00110100, 0b00111000, 0b00100101, 0b00011010, 0b00000100, 0b00100100, 0b00000000};
char LettersEN[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'x', 'y', 'z', 'w', '.', '!', '-', '«', '»', '(', ')', ',', '?', ' '};
char LettersRUS[] = {'f', ',', 'd', 'u', 'l', 't', '`', ';', 'p', 'b', 'q', 'r', 'k', 'v', 'y', 'j', 'g', 'h', 'c', 'n', 'e', 'a', '[', 'w', 'x', 'i', 'o', ']', 's', 'm', '\'', '.', 'z', '.', '!', '-', '"', '"', '(', ')', ',', '?', ' '};
//String LettersRUS[] = {"f", "б", "d", "u", "l", "t"};
bool flag1 = 1;
byte KeyByte = 0;
int i = 0;
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
void setup() {
  Serial.begin(115200);
  keypad.addEventListener(keypadEvent);
  Keyboard.begin();

}

void loop() {
  char key = keypad.getKey();
}

void keypadEvent(KeypadEvent key) { // функция обратного вызова
  switch (keypad.getState()) {
    case PRESSED: {
        switch (key) {
          // Serial.println("PRESSED");
          case 'a':
            break;
          case 'b':
            break;
          case 'c':
            break;
          case 'd':
            KeyByte = 0;
            break;
          case '1':
            ByteWrite(0);
            break;
          case '2':
            ByteWrite(1);
            break;
          case '3':
            ByteWrite(2);
            break;
          case '4':
            ByteWrite(3);
            break;
          case '5':
            ByteWrite(4);
            break;
          case '6':
            ByteWrite(5);
            break;

        }
        break;
      }
    case HOLD: {
        switch (key) {
          case 'a':
            Keyboard.write(KEY_RETURN);
            //Serial.println("HOLD");
           // flag1 = 1;
            break;
        }
        break;
      }
    case RELEASED: {
        switch (key) {
          case 'a':
            //if (flag1) {
             // Keyboard.write(KEY_BACKSPACE);
              //flag1 = 0;
            //}
            Go();
            Keyboard.print(Package);
            KeyByte = 0;
            Package = 0x00;
            //Serial.println("RELEASED");
            break;
          case 'b':
            Keyboard.write(KEY_BACKSPACE);
            //Serial.println("Key b");
            break;
          case 'c':
            SwitchLang = !SwitchLang;
            //Serial.println(SwitchLang);
            Keyboard.press(KEY_LEFT_SHIFT);
            Keyboard.press(KEY_LEFT_ALT);
            delay(100);
            Keyboard.releaseAll();
            break;
          case 'd':

            break;
          case '1':

            break;
          case '2':

            break;
          case '3':

            break;
          case '4':

            break;
          case '5':

            break;
          case '6':

            break;
        }
        break;
      }
  }
}
void ByteWrite(byte key) {
  KeyByte |= 1 << (key);
}

void Go() {
  if (SwitchLang) {
    for (i = 0; i <= sizeof(BraileRUS); i++) {
      if (KeyByte == BraileRUS[i]) {
        //KeyByte = 0;
                Serial.println(LettersRUS[i]);
                Serial.println(LettersRUS[i], HEX);
                Serial.println("Ru");
        Package = LettersRUS[i];

      }
    }
    KeyByte = 0;
  } else {
    for (i = 0; i <= sizeof(BraileEN); i++) {
      if (KeyByte == BraileEN[i]) {
        //        KeyByte = 0;
                Serial.println(LettersEN[i]);
                Serial.println(LettersEN[i], HEX);
                Serial.println("En");
        Package =  LettersEN[i];

      }
    }
  }

}
