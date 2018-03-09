boolean c;

void setup() {
  // Barramento de transmissão de dados
  DDRA = B11111111;
  // Barramento de clock
  DDRB = B00000001;
  
  Serial.begin(9600);
}

void loop() {
  // dependendo do que se deseja enviar deve-se modificar o OP
  // B10000000 -> (+)
  // B01000000 -> (-)
  // B00100000 -> (*)
  // B00010000 -> (/)
  byte op = B00010000;
  byte n1 = B00000110;
  byte n2 = B00000010;

  if (c) {
    // Configura o barramento de clock que no caso seria utilizado para 
    // sincronia.
    PORTB = B00000001;
    send_bits(op);  
    send_bits(n1);
    send_bits(n2);
    c = !c;
  } else {
    c = !c;
  }
}

void send_bits(byte b) {
  // Envia o byte de dados no barramento A.
  PORTA = b;
  delay(200);
}

