# FF-MS1

## But

Créer un système de communication entre Master et Slave à l'aide d'une liaison SPI.

Cette liaison doit pouvoir supporter une interruption brutale sans nécessiter un redémarrage des cartes.

La communication se fera par l'envoi de trames de 1 octet chacunes.
Un envoi contiendra deux trames de début, puis le message, puis deux trames de fin.
Un message ne respectant pas ces règles ne sera pas pris en compte.

##Progression actuelle

Le Master a été correctement configuré pour envoyer des messages simples, à l'aide d'une fonction modulable.
La configuration basique du SPI a été effectuée.

##Ce qu'il reste à faire

Le Slave ne reçoit pas les trames du Master, il faudrait mettre cela en place.
Le format de messages ne contient pas encore de trames de début ou de fin.
Il n'y a pas encore de gestion du débranchement.