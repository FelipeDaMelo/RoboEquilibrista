# Instruções para Construção e Ajuste do Robô Equilibrista

Este guia contém as etapas fundamentais para configurar, ligar e calibrar o seu robô equilibrista.

---

## 1. Configuração Inicial e Hardware

### Biblioteca Necessária
1. Abra o **Arduino IDE**.
2. Vá no menu **Sketch** -> **Incluir Biblioteca** -> **Gerenciar Bibliotecas...**
3. Na barra de busca, digite: **"Kalman Filter Library"**.
4. Procure a versão feita por **TKJ Electronics**.
5. Clique em **Instalar**.

### Pinagem Obrigatória
O código está configurado para usar as portas PWM para controle preciso:
*   `OUTA` = **Pino 5** (IN1)
*   `OUTB` = **Pino 6** (IN2)
*   `OUTC` = **Pino 9** (IN3)
*   `OUTD` = **Pino 10** (IN4)

###  Regra de Ouro (Elétrica)
*   **IMPORTANTE:** Conecte um fio do **GND** da bateria (ou da Ponte H) ao **GND** do Arduino. Sem o negativo comum, os motores não receberão o sinal de comando.

---

##  2. Calibração do Equilíbrio (SetPoint)

O `SetPoint` é o ângulo onde o robô entende que está perfeitamente equilibrado.

1.  Abra o **Monitor Serial** (115200 baud).
2.  Coloque o robô manualmente na posição vertical de equilíbrio ("peso morto").
3.  Observe o valor de `KalAngY`.
4.  Substitua este valor no arquivo `PID.ino`:
    `double SetPoint = -1.58; // (Exemplo: use o seu valor medido)`

> **Nota:** Se o robô estiver "andando" sozinho para um lado mesmo estando em pé, ajuste o `SetPoint` em pequenas variações (ex: de -1.58 para -1.70 ou -1.40).


---

##  3. Direção dos Motores

*   **Sincronia:** As duas rodas devem girar para o **mesmo lado**. Se girarem opostas, troque a polaridade dos fios de um dos motores na ponte H.
*   **Ação e Reação:** Se o robô inclinar para a frente, as rodas devem girar para a **frente**.
    Definir "para frente" é a direção onde o valor do SetPoint aumenta.
*   **Lógica Invertida:** Se o robô "acelerar a própria queda" (girar loucamente ao inclinar), a lógica no arquivo `PID.ino` deve ser invertida:
    *   Mudar de: `erro = SetPoint - input;`
    *   Para: `erro = input - SetPoint;`

---

##  4. Entendendo o PID (Os "Ks")

O PID é o controle que decide a força dos motores baseando-se na inclinação.

### 1. **KP (Ganho Proporcional) - O "Músculo"**
Ele olha para o **agora**. Aplica força proporcional à inclinação atual.
*   *Mito:* "Se inclina 1 grau, gira devagar. Se inclina 10, gira forte."
*   *Problema:* Se for muito baixo, o robô cai por fraqueza. Se for muito alto, o robô oscila violentamente (nervoso).

### 2. **KD (Ganho Derivativo) - O "Reflexo/Amortecedor"**
Ele olha para a **velocidade da queda**. Tenta prever o futuro para frear o robô antes de ele passar do ponto.
*   *Efeito:* Tira a tremedeira causada pelo KP.
*   *Problema:* Se for muito alto, o robô fica lento (como se estivesse no mel) ou vibra em alta frequência.

### 3. **KI (Ganho Integral) - A "Memória/Persistência"**
Ele olha para o **passado**. Soma o erro acumulado ao longo do tempo.
*   *Função:* Corrige erros pequenos e persistentes (ex: robô que fica sempre um pouco tortinho).
*   *Problema:* Se for muito alto, causa uma oscilação lenta que acaba derrubando o robô.

---

##  5. Guia de Ajustes (Tuning)

1.  Comece com **KI e KD em zero** Nessas etapas vai segurando o robô com a mão.
2.  Aumente o **KP** até o robô começar a reagir e quase conseguir ficar em pé.
3.  Aumente o **KD** para tirar a oscilação e fazer ele parar "seco" no centro.
4.  Se ele ficar equilibrado mas "andando" devagar, ajuste o **SetPoint**.

### Dicas Práticas:
*   **Caindo rápido:** Aumente o `kp`.
*   **Vibrando muito:** Aumente o `kd` ou diminua o `kp`.
*   **Drift (Andando sozinho):** Ajuste fino do `SetPoint`.
