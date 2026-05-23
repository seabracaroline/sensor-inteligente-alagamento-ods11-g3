# Sensor Inteligente de Alagamento para Cidades Sustentáveis

Projeto acadêmico desenvolvido com foco no ODS 11 – Cidades e Comunidades Sustentáveis.

## Descrição
Este projeto utiliza Internet das Coisas (IoT) para monitoramento preventivo de alagamentos urbanos.

O sistema utiliza:

- ESP32
- Sensor ultrassônico HC-SR04
- LED vermelho (alerta visual)
- Buzzer (alerta sonoro)
- Wi-Fi
- MQTT

## Funcionamento
O sensor mede continuamente a distância até a superfície monitorada.

Quando a distância atinge ou fica abaixo de **10 cm**, o sistema identifica risco de alagamento e:

- aciona LED vermelho
- aciona buzzer
- publica dados via MQTT no tópico:

```text
mackenzie/iot/alagamento
```

## Tecnologias utilizadas
- Wokwi Simulator
- Arduino IDE / ESP32
- MQTT Protocol
- Wi-Fi

## Integrantes
- Nome 1
- Nome 2
- Nome 3

## Vídeo de demonstração
(Link do YouTube aqui)

## Artigo
(Se quiser adicionar)
