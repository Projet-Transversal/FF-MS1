# FF-MS1

## But

Créer un système de communication entre Master et Slave à l'aide d'une liaison SPI.

Cette liaison doit pouvoir supporter une interruption brutale sans nécessiter un redémarrage des cartes.

La communication se fera par l'envoi de trames contenant des paquets de 1 octet.
Un envoi contiendra deux octets de début, puis le message, puis deux octets de fin.
Un message ne respectant pas ces règles ne sera pas pris en compte.

## Progression actuelle

Le Master a été correctement configuré pour envoyer des messages simples, à l'aide d'une fonction modulable.
Le Slave reçoit parfaitement les messages simples du Master.
Le SPI a été correctement configuré.
Un message n'est accepté uniquement lorsqu'il est accompagné de deux octets spécifiques de début de message et de deux octets spécifiques de fin de message.

## Ce qu'il reste à faire

Le message ne fait qu'un octet.
Il n'y a pas encore de gestion du débranchement.