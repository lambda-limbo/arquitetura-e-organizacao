#include <EEPROM.h>

short ptr;
byte data[3];

void setup() {
  // Imprime valor aos leds
  DDRA = B11111111;
  // Recebe instruções do primeiro arduino
  DDRC = B0;
  // Led indicador de clock
  DDRL = B00000010;
  // Informação do clock
  DDRB = B11111110;
  
  // indexador global de memória
  ptr = 0;

  Serial.begin(9600);
}

void loop() {
  p_write(p_fetch());
  if (PINB == B00000001) {
    Serial.println("To recebendo");
    PORTL = B00000010;
  } else {
    PORTL = B00000000;
  }
  
  // Se o ponteiro global chegar a três nosso processador inicia o processo de leitura
  // e interpretação da instrução
  if (ptr == 3) {
    p_read();
    Serial.println(EEPROM.get(0, data[0]));
    Serial.println(EEPROM.get(1, data[1]));
    Serial.println(EEPROM.get(2, data[2]));
    PORTL = B00000000;
    p_execute();
    
    ptr = 0;
  }
  
  delay(200);
}

byte p_fetch() {
  return PINC;
}

void p_write(byte b) {
  EEPROM.write(ptr, b);
  ptr++;
}

void p_read() {
  while (ptr >= 0) {
    EEPROM.get(ptr, data[ptr]);
    ptr--;
  }

  ptr = 0;
}


void p_execute() {
  // posição da operação no vetor de dados
  switch(data[2]) {
    case B10000000: // +
      Serial.println("To somando");
      PORTA = data[0] + data[1];
      break;
    case B01000000: // -
      Serial.println("To subtraindo");   
      PORTA = data[0] - data[1];
      break;
    case B00100000: // *
      Serial.println("To multiplicando");
      PORTA = data[0] * data[1];
      break;
    case B00010000: // /
      Serial.println("To dividindo");
      PORTA = data[0] / data[1];
      break;
    default:
      PORTA = B11111111;
      for (int i = 0; i < 8; i++) {
        delay(125);
        PORTA = PORTA >> 1;
      }
      break;
  }
  EEPROM.write(4, PINA);
}

