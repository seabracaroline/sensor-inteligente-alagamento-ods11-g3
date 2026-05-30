# Sensor Inteligente de Alagamento para Cidades Sustentáveis

Projeto acadêmico desenvolvido para a disciplina de Internet das Coisas (IoT), alinhado ao Objetivo de Desenvolvimento Sustentável 11 (ODS 11), que busca promover cidades e comunidades mais seguras, resilientes e sustentáveis.

## Descrição do Projeto

O projeto consiste em um sistema inteligente para monitoramento preventivo de alagamentos urbanos utilizando tecnologias de Internet das Coisas (IoT). A solução realiza a medição contínua do nível da água por meio de um sensor ultrassônico e, ao identificar uma condição crítica, aciona alertas locais e transmite informações para monitoramento remoto utilizando o protocolo MQTT.

## Componentes Utilizados

### Implementação Física Proposta

* ESP32 WROOM-32
* Sensor ultrassônico HC-SR04
* Módulo relé
* Sirene ou buzzer piezoelétrico
* Sinalizador luminoso
* Fonte de alimentação

### Componentes Utilizados na Simulação

* ESP32
* Sensor HC-SR04
* LED vermelho (alerta visual)
* Buzzer (alerta sonoro)

## Funcionamento

O sensor ultrassônico realiza medições contínuas da distância entre o dispositivo e a superfície monitorada, simulando o nível da água.

Foi definido um limite crítico de 10 centímetros. Quando a distância medida é igual ou inferior a esse valor, o sistema identifica uma condição de risco de alagamento e:

* Aciona o LED vermelho (alerta visual);
* Aciona o buzzer (alerta sonoro);
* Publica os dados via MQTT para monitoramento remoto.

Quando a distância permanece acima do limite estabelecido, o sistema mantém os alertas desligados e continua monitorando normalmente.

## Comunicação MQTT

A comunicação remota é realizada utilizando o protocolo MQTT.

**Tópico utilizado:**

mackenzie/iot/alagamento

A ESP32 atua como cliente publicador, enviando continuamente os dados coletados pelo sensor para monitoramento remoto em tempo real.

## Ferramentas Utilizadas

* Arduino IDE
* Wokwi Simulator
* HiveMQ Broker
* Fritzing
* Draw.io (diagrams.net)
* GitHub

## Estrutura do Repositório

* `sketch.ino` → código-fonte do projeto
* `diagram.json` → circuito utilizado no Wokwi
* `libraries.txt` → bibliotecas utilizadas
* `docs/` → artigo, fluxograma, diagramas e documentação
* `imagens/` → imagens da simulação e resultados obtidos

## Artigo

O artigo completo do projeto encontra-se disponível na pasta `docs`.

## Vídeos de Demonstrações

Links do vídeos:
https://youtu.be/hsig3chYI24
https://youtu.be/SpFpVo_yZT8

## Integrantes

* Caroline Aparecida Seabra
* Lara Camargo Vianna
* Natália D'Almeida Madeira




