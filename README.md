# FF-MS1

## But

Créer un système de communication entre Master et Slave à l'aide d'une liaison SPI.

Cette liaison doit pouvoir supporter une interruption brutale sans nécessiter un redémarrage des cartes.

La communication se fera par l'envoi de trames contenant des paquets de 1 octet.
Un envoi contiendra deux octets de début, puis le message, puis deux octets de fin.
Un message ne respectant pas ces règles ne sera pas pris en compte.

## Progression actuelle

Le Master a été correctement configuré pour envoyer des messages simples, à l'aide d'une fonction modulable.
Le Slave reçoit parfaitement les messages à longueur variable du Master.
Le SPI a été correctement configuré.
Un message n'est accepté uniquement lorsqu'il est accompagné de deux octets spécifiques de début de message et de deux octets spécifiques de fin de message.
Le message peut avoir une longueur entre 1 et 5, cette valeur changera plus tard.

Le débranchement est géré de façon basique : Tant qu'un message ne contient pas les deux octets de fin, il n'est pas pris en compte.
On vérifie ensuite les deux octets de début, puis on transfère le message (et le message uniquement) dans un buffer spécialisé.

## Ce qu'il reste à faire

Il faudrait créer une fonction qui centraliserait le transfert côté Master et le décodage côté Slave, pour rendre la communication plus facile, et rendre le contenu du message plus accessible par les autres modules.