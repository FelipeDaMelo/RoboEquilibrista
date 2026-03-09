
double kp = 15.0; // Subindo um pouco para dar mais firmeza
double kd = 6.0;  // Aumentado para 4 para "frear" mais o robô
double ki = 0.3;  // Baixado um pouco para ele não "correr" tanto

int OUTMAX = 150; // Reduzido de 200 para 150 para segurança
int OUTMIN = -150;

double SetPoint =
    -3.5; // Ajustado de -1.36 para -1.70 para combater o drift para frente
float lastInput =
    -3.5; // Inicializado com o setpoint para evitar o "kick" inicial

double ITerm = 0.0;

double Compute(double input) {

  /* Calculo do Erro (Ajustado: input - SetPoint para girar no sentido da queda)
   */
  double erro = input - SetPoint;

  /* Termo Integral acumulando o erro */
  ITerm += (ki * erro);

  /* Saturation for ITerm */
  if (ITerm > OUTMAX)
    ITerm = OUTMAX;
  else if (ITerm < OUTMIN)
    ITerm = OUTMIN;

  /* Diferença da entrada (Diferenciação) */
  double dInput = input - lastInput;

  /* Calculo do PID
     Nota: kd * dInput costuma ser subtraído se dInput for (input - lastInput)
     para evitar o "derivative kick" ou agir como amortecimento.
  */
  double output = (kp * erro) + ITerm - (kd * dInput);

  /* Saturation for Output */
  if (output > OUTMAX)
    output = OUTMAX;
  else if (output < OUTMIN)
    output = OUTMIN;

  lastInput = input;

  return output;
}
