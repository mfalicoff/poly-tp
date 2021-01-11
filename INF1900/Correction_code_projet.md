# Polytechnique Montréal

Département de génie informatique et génie logiciel

INF1900: Projet initial de système embarqué

# Grille de correction des programmes:

Identification:
+ Travail    : Robot qui détecte des obstacles et qui effectue des manoeuvresd’évitement
+ Section #  : 3
+ Équipe #   : 4081
+ Correcteur : Yoan Gauthier

# LISIBILITÉ
## En-têtes en début de programme   

| Pénalité par erreur                       | -1.5          |
| ----------------------------------------- | ------------- |
| Noms des auteurs                          |               |
| Description du programme                  |               |
| Identifications matérielles (Broches I/O) |               |
| Table des états ou autres s'il y a lieu   |               |
| __Résultat partiel__                      | __(1.5/1.5)__ |

## Identificateurs significatifs (Autodocumentation)

| Points importants                       | Poids         |
| --------------------------------------- | ------------- |
| Absence de *chiffres magiques*          | (0.0/0.5)     |
| Noms de variables décrivent l'intention | (0.5/0.5)     |
| Noms de fonctions décrivent l'intention | (0.0/0.5)     |
| __Résultat partiel__                    | __(0.5/1.5)__ |

## Commentaires pertinents

Bonnes raisons d'un commentaire
 + Explication d'un algorithme ou procédure 
 + peu évidente (ou *hack*)
 + Référence d'extraits de code copiés d'internet
 + Détail du POURQUOI d'un extrait de code

| Pénalité par erreur  | -0.5          |
| -------------------- | ------------- |
| __Résultat partiel__ | __(0.5/1.0)__ |


## Indentation   

| Pénalité par erreur                    | -0.5          |
| -------------------------------------- | ------------- |
| Indentation structurée                 | -0.5          |
| Indentation uniforme dans le programme | -0.5          |
| __Résultat partiel__                   | __(0.0/1.0)__ |


# MODULARITÉ ET COMPRÉHENSION
## Fonctions bien définies

| Pénalité par erreur                  | -0.5          |
| ------------------------------------ | ------------- |
| Responsabilité unique d'une fonction | -0.5          |
| Maximum de 4 paramètres              |               |
| Absence de code dupliqué             |               |
| __Résultat partiel__                 | __(0.5/1.0)__ |


## Bonne application des concepts de systèmes embarqués

| Pénalité par erreur                          | -1.0          |
| -------------------------------------------- | ------------- |
| Utilisation des registres appropriée         |               |
| Machine à états codée clairement             | -1.0          |
| Délais et minuteries utilisés judicieusement |               |
| PWM bien établi                              |               |
| Scrutation et interruptions bien utilisés    |               |
| etc                                          |               |
| __Résultat partiel__                         | __(3.0/4.0)__ |

# FONCTIONNALITÉS
## Git

| Points importants            | Poids         |
| ---------------------------- | ------------- |
| Fichiers aux bons endroits   | (1.5/1.5)     |
| Absence de fichiers inutiles | (1.5/1.5)     |
| __Résultat partiel__         | __(3.0/3.0)__ |


## Compilation    

| Pénalité par erreur                          | -2.0          |
| -------------------------------------------- | ------------- |
| Absence de messages d'erreurs de compilation |               |
| Absence de messages d'attention (*warning*)  | -1.0          |
| __Résultat partiel__                         | __(1.0/2.0)__ |
   

## Évaluation boîte noire  

| Points importants            | Poids         |
| ---------------------------- | ------------- |
| Cas normal de fonctionnement | (2.5/2.5)     |
| Cas limites observables      | (2.5/2.5)     |
| __Résultat partiel__         | __(5.0/5.0)__ |

# Résultat

__Total des points: 15/20__

# Commentaires du correcteur:

+ indentation non constante
+ Le switch case devrait être extrait dans des fonctions. Pourquoi détect dans un case et le reste normal?
+ beaucoup de chiffres magiques
+ Lignes trop longues
+ Mélange anglais francais
+ Méthode ayant plusieurs responsabilités
+ Préciser les pins sur les entrées et sorties


# Basé sur le commit suivant
```
commit 3f12bee0abbf1c195f4bb587a35bd7d492cbf662
Author: mfalicoff <mfalicoff2001@mail.com>
Date:   Fri Apr 17 14:20:35 2020 -0400

    update readme
```

# Fichiers indésirables
```

```

# Sortie de make dans les sous-répertoires
```
======================= Sortie de make dans projet/lib_dir =============================
make: *** code_projet/4081/projet/lib_dir: No such file or directory.  Stop.
avr-gcc -I. -MMD  -g -mmcu=atmega324pa -Os -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c affichage7Seg.cpp
avr-gcc -I. -MMD  -g -mmcu=atmega324pa -Os -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c customprocs.cpp
avr-gcc -I. -MMD  -g -mmcu=atmega324pa -Os -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c ifPressed.cpp
ifPressed.cpp: In function 'bool ifpressed()':
ifPressed.cpp:19:8: warning: suggest parentheses around operand of '!' or change '&' to '&&' or '!' to '~' [-Wparentheses]
   19 |     if(!PIND & bouton)
      |        ^
ifPressed.cpp:22:10: warning: suggest parentheses around operand of '!' or change '&' to '&&' or '!' to '~' [-Wparentheses]
   22 |       if(!PIND & bouton)
      |          ^
avr-gcc -I. -MMD  -g -mmcu=atmega324pa -Os -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c LCD.cpp
avr-gcc -I. -MMD  -g -mmcu=atmega324pa -Os -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c lcm_so1602dtr_m.cpp
avr-gcc -I. -MMD  -g -mmcu=atmega324pa -Os -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c lcm_so1602dtr_m_fw.cpp
avr-gcc -I. -MMD  -g -mmcu=atmega324pa -Os -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c pwmRoues.cpp
avr-gcc -I. -MMD  -g -mmcu=atmega324pa -Os -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c sonar.cpp
sonar.cpp: In function 'Distances evaluerDistances()':
sonar.cpp:63:5: warning: this 'while' clause does not guard... [-Wmisleading-indentation]
   63 |     while ( ( PINA & ( 1 << SONAR_1 ) ) && ( TCNT1 < 58800 ) );
      |     ^~~~~
sonar.cpp:64:2: note: ...this statement, but the latter is misleadingly indented as if it were guarded by the 'while'
   64 |  distances.distanceSonar1 = (TCNT1 *8)/580;
      |  ^~~~~~~~~
sonar.cpp:73:5: warning: this 'while' clause does not guard... [-Wmisleading-indentation]
   73 |     while ( ( PINA & ( 1 << SONAR_2 ) ) && ( TCNT1 < 58800 ) );
      |     ^~~~~
sonar.cpp:74:2: note: ...this statement, but the latter is misleadingly indented as if it were guarded by the 'while'
   74 |  distances.distanceSonar2 = (TCNT1 *8)/580;
      |  ^~~~~~~~~
sonar.cpp:83:5: warning: this 'while' clause does not guard... [-Wmisleading-indentation]
   83 |     while ( ( PINA & ( 1 << SONAR_3 ) ) && ( TCNT1 < 58800 ) );
      |     ^~~~~
sonar.cpp:84:2: note: ...this statement, but the latter is misleadingly indented as if it were guarded by the 'while'
   84 |  distances.distanceSonar3 = (TCNT1 *8)/580;
      |  ^~~~~~~~~
avr-ar -crs libstatic.a  affichage7Seg.o customprocs.o ifPressed.o LCD.o lcm_so1602dtr_m.o lcm_so1602dtr_m_fw.o pwmRoues.o sonar.o
======================= Sortie de make dans projet/exec_dir =============================
make: *** code_projet/4081/projet/exec_dir: No such file or directory.  Stop.

avr-gcc -I. -I/usr/include/simavr  -MMD -I ../libstatic -g -mmcu=atmega324pa -Os -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c main.cpp
avr-gcc -I. -I/usr/include/simavr  -MMD -I ../libstatic -g -mmcu=atmega324pa -Os -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c manoeuvres.cpp
avr-gcc -Wl,-Map,main.elf.map -mmcu=atmega324pa -o main.elf  main.o manoeuvres.o \
-lm -l static -L ../libstatic
avr-objcopy -j .text -j .data \
        -O ihex main.elf main.hex
```