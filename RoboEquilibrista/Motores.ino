
const int OUTA = 5;  // IN1
const int OUTB = 6;  // IN2
const int OUTC = 9;  // IN3
const int OUTD = 10; // IN4

void init_motores() {
  pinMode(OUTA, OUTPUT);
  pinMode(OUTB, OUTPUT);
  pinMode(OUTC, OUTPUT);
  pinMode(OUTD, OUTPUT);
}

void PWMControleMotores(double comando) {

  int val = (int)abs(comando);

  if (comando > 0) {
    analogWrite(OUTA, 0);   /* Controlando o Motor da Direita Para T.*/
    analogWrite(OUTB, val); /* Controlando o Motor da Direita Para F.*/
    analogWrite(OUTC, val); /* INVERTIDO: Faz o motor esquerdo ir para F junto
                               com o direito */
    analogWrite(OUTD, 0);
  } else {
    analogWrite(OUTA, val); /* Controlando o Motor da Direita Para T.*/
    analogWrite(OUTB, 0);   /* Controlando o Motor da Direita Para F.*/
    analogWrite(
        OUTC,
        0); /* INVERTIDO: Faz o motor esquerdo ir para T junto com o direito */
    analogWrite(OUTD, val);
  }
}
