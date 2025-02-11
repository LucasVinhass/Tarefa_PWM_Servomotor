# Controle de Servomotor por PWM com Raspberry Pi Pico W

Este projeto implementa o controle de um servomotor micro servo padrão usando o módulo PWM (Pulse Width Modulation) presente no microcontrolador Raspberry Pi Pico W. 
A simulação foi realizada utilizando o simulador de eletrônica online Wokwi. A atividade visa praticar o controle do ângulo do servomotor e entender o funcionamento do PWM para o controle de dispositivos como servos.

## Componentes Simulados

1. **Microcontrolador Raspberry Pi Pico W**: Usado como o controlador para gerar o sinal PWM.
2. **Servomotor**: Motor micro servo padrão, configurado no simulador Wokwi.

## Requisitos

### 1. Configuração do PWM

- Configurar a GPIO 22 para gerar um sinal PWM com frequência de 50Hz (20ms de período).
  
### 2. Ajuste de Posições do Servomotor

- **Posição 180°**: Defina o ciclo ativo do PWM para 2400µs, ajustando o servomotor para a posição de 180°.
  - Aguarde 5 segundos nesta posição.
  
- **Posição 90°**: Defina o ciclo ativo do PWM para 1470µs, ajustando o servomotor para a posição de 90°.
  - Aguarde 5 segundos nesta posição.

- **Posição 0°**: Defina o ciclo ativo do PWM para 500µs, ajustando o servomotor para a posição de 0°.
  - Aguarde 5 segundos nesta posição.

### 3. Movimentação Periódica

- Crie uma rotina que movimente o braço do servomotor suavemente entre os ângulos de 0° e 180°.
  - Incremento de ciclo ativo de ±5µs.
  - Atraso de 10ms entre os ajustes.

### 4. Controle do LED RGB

- Utilize o GPIO 12 para controlar o brilho de um LED RGB conforme o ângulo do servomotor.
  - A iluminação do LED deve variar com o ângulo: vermelho (baixa intensidade), laranja (média intensidade) e verde (alta intensidade).

## Instruções para Execução

### Pré-requisitos

1. **Raspberry Pi Pico W**: Microcontrolador que será usado para controlar o servomotor.
2. **Simulador Wokwi**: Utilize o [simulador Wokwi](https://wokwi.com/) para simular o circuito com o Raspberry Pi Pico W e o servomotor.
3. **Ferramenta Educacional BitDogLab**: Para realizar o experimento com o LED RGB.

### Passos para simulação

1. **Acessar o simulador Wokwi**:
   - Abra o [Wokwi](https://wokwi.com/) e crie um novo projeto.
   - Selecione o microcontrolador Raspberry Pi Pico W.
   - Adicione o servomotor micro servo padrão e conecte-o à GPIO 22 do Raspberry Pi Pico W.

2. **Carregar o código**:
   - Baixe o arquivo de código em C (com a extensão `.c`).
   - Compile e envie o código para o Raspberry Pi Pico W através da ferramenta Pico SDK.

3. **Observação do LED RGB**:
   - No simulador, adicione o LED RGB conectado à GPIO 12.
   - O LED deverá iluminar com intensidade variável conforme a posição do servomotor.

4. **Resultado esperado**:
   - O servomotor deve se mover suavemente entre os ângulos de 0° a 180°.
   - O LED RGB irá mudar a sua intensidade com base nos ângulos do servomotor.
