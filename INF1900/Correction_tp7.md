Polytechnique Montréal

Département de génie informatique et génie logiciel

INF1900: Projet initial de système embarqué

Grille de correction des programmes:

Identification:
  Travail    : Mise en commun du code et formation de librairies
  Section #  : 3
  Équipe #   : 4081
  Correcteur : Claudia Onorato

Code:
– La qualités et le choix de vos portions de code choisies   (1/5)
– La qualités de vos modifications aux Makefiles             (2/5)

Le rapport:
– Explications cohérentes par rapport au code retenu
  pour former la librairie                                   (2/2)
– Explications cohérentes par rapport aux Makefiles modifiés (2/2)
– Explications claires avec un bon niveau de détails         (1/2)
– Bon français                                               (0/1)

Généralités:
– Bonne soumission de l'ensemble du code (compilation sans
  erreurs, …) et du rapport selon le format demandé          (2/3)

Total: 10/20

Commentaires du correcteur:

La qualités et le choix de vos portions de code choisies
- Veuillez suivre une seule convention de nommage de vos noms de fichier et de fonction (pas de camelCase et de snake_case dans une même librairie).
- Vos noms de fichier devraient aussi avoir des noms plus généraux que le nom de la seule fonction qui s'y trouve, comme vos **fichiers devraient en fait rassembler un ensemble cohérent de fonctionnalités**. Ainsi, si vous étiez pour ajouter une fonction en lien avec la minuterie (par exemple, pour l'arrêter), on n'aurait pas à ajuster le nom du fichier `partirminuterie` et tous les endroits où on l'inclut.
- Attention aux indentations...
- Mettez des include guards (https://en.wikipedia.org/wiki/Include_guard) au début de vos header files. 
- Votre fonction `ambre` ne semble pas fonctionner. Quand vous faites appel à `partirMinuterie`, vous configurez les registres pour qu'une routine d'interruption soit appelé après un certain temps. Vaudrait mieux utiliser un `_delay_ms` dans ce cas.
- On n'indique pas d'unité de temps pour le paramètre `duree` de `partirMinuterie`. Vous pourriez définir une macro qui équivaut à une seconde d'attente, par exemple, ce qui faciliterait l'utilisation de la librairie. 
- Votre module de gestion des roues ne permet pas de contrôler la direction, ou d'avoir des vitesses différentes pour les roues. De plus, le nom `pourcentage` porte à confusion, comme c'est en fait une valeur entre 0 et 255 et non entre 0 et 100.
- Certains fichiers ont des include inutiles (ex. dans `ifpressed.h`, vous incluez `"partirminuterie.h"` et `<avr/interrupt.h>`)

La qualités de vos modifications aux Makefiles 
- Il se trouve des variables dupliquées entre vos makefile. Il aurait été bien de faire un makefile commun, pour y définir les variables qui sont redondantes.
- Certaines variables et règles se trouvant dans le Makefile de la librairie sont inutiles (ex. `AVRDUDE` et `%.hex: %.out`).
- Des variables auraient pu être créées pour `avr-ar` et ses options.
- Dans votre code test, vous n'avez pas à préciser le path des fichiers d'en-têtes de la librairie, comme vous le spécifier avec l'option `-I ../libstatic`. Vous pouvez alors inclure comme ça `#include "led.h"` plutôt que `#include "../libstatic/led.h"`.

Bonne soumission de l'ensemble du code
- Il fallait soumettre le code dans un répertoire nommé `tp/tp7`. Vous avez aussi quelques warnings lié à `connect_pc` (je ne pénalise pas pour ceux de `memoire_24`).

# Basé sur le commit suivant
```
commit 4b3ebf079e90fdbdd5ed251f17423cde8ab06390
Author: Maximiliano <mfalicoff2001@mail.com>
Date:   Mon Mar 9 15:28:26 2020 -0400

    make sh
```

# Fichiers indésirables
```

```

# Sortie de make dans les sous-répertoires
```
======================= Sortie de make dans tp/tp7/lib =============================
avr-gcc -I. -MMD  -g -mmcu=atmega324pa -Os -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c PWM_roues_.cpp
avr-gcc -I. -MMD  -g -mmcu=atmega324pa -Os -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c Photovolt.cpp
avr-gcc -I. -MMD  -g -mmcu=atmega324pa -Os -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c can.cpp
avr-gcc -I. -MMD  -g -mmcu=atmega324pa -Os -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c connect_pc.cpp
In file included from connect_pc.h:1,
                 from connect_pc.cpp:10:
memoire_24.h:17:1: warning: "/*" within comment [-Wcomment]
   17 | /*                                                                            */
      |  
connect_pc.cpp: In function 'void Afficher(unsigned char*)':
connect_pc.cpp:60:28: warning: division 'sizeof (unsigned char*) / sizeof (unsigned char)' does not compute the number of array elements [-Wsizeof-pointer-div]
   60 |   uint8_t n = sizeof(mots) / sizeof(mots[0]);
      |               ~~~~~~~~~~~~~^~~~~~~~~~~~~~~~~
connect_pc.cpp:56:30: note: first 'sizeof' operand was declared here
   56 | void Afficher(unsigned char* mots )
      |               ~~~~~~~~~~~~~~~^~~~
avr-gcc -I. -MMD  -g -mmcu=atmega324pa -Os -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c controleMem.cpp
In file included from controleMem.h:1,
                 from controleMem.cpp:10:
memoire_24.h:17:1: warning: "/*" within comment [-Wcomment]
   17 | /*                                                                            */
      |  
avr-gcc -I. -MMD  -g -mmcu=atmega324pa -Os -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c ifpressed.cpp
avr-gcc -I. -MMD  -g -mmcu=atmega324pa -Os -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c led.cpp
avr-gcc -I. -MMD  -g -mmcu=atmega324pa -Os -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c memoire_24.cpp
memoire_24.cpp:30:3: warning: #warning "F_CPU pas defini pour 'memoire_24.cpp'" [-Wcpp]
   30 | # warning "F_CPU pas defini pour 'memoire_24.cpp'"
      |   ^~~~~~~
In file included from memoire_24.cpp:34:
memoire_24.h:17:1: warning: "/*" within comment [-Wcomment]
   17 | /*                                                                            */
      |  
memoire_24.cpp: In member function 'uint8_t Memoire24CXXX::lecture(uint16_t, uint8_t*, uint8_t)':
memoire_24.cpp:280:7: warning: this 'while' clause does not guard... [-Wmisleading-indentation]
  280 |       while ((TWCR & _BV(TWINT)) == 0) ; // Attente de fin de transmission
      |       ^~~~~
memoire_24.cpp:281:10: note: ...this statement, but the latter is misleadingly indented as if it were guarded by the 'while'
  281 |          *donnee++ = TWDR;               // Lecture
      |          ^
avr-gcc -I. -MMD  -g -mmcu=atmega324pa -Os -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c partirminuterie.cpp
avr-ar -crs libstatic.a  PWM_roues_.o Photovolt.o can.o connect_pc.o controleMem.o ifpressed.o led.o memoire_24.o partirminuterie.o

======================= Sortie de make dans tp/tp7/exec =============================
avr-gcc -I. -MMD -I ../libstatic -g -mmcu=atmega324pa -Os -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c main.cpp
In file included from ../libstatic/connect_pc.h:1,
                 from main.cpp:6:
../libstatic/memoire_24.h:17:1: warning: "/*" within comment [-Wcomment]
   17 | /*                                                                            */
      |  
In file included from main.cpp:8:
../libstatic/memoire_24.h:17:1: warning: "/*" within comment [-Wcomment]
   17 | /*                                                                            */
      |  
avr-gcc -Wl,-Map,main.out.map -mmcu=atmega324pa -o main.out  main.o \
        -lm -l static -L ../libstatic

```