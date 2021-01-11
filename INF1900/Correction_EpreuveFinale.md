# Polytechnique Montréal

Département de génie informatique et génie logiciel

INF1900: Projet initial de système embarqué

## Grille de correction du projet final
### Robot conservant ses distances sociales

Identification:
+ Travail    : Epreuve Finale H20
+ Section #  : 3
+ Équipe #   : 4081
+ Correcteur : Claudia Onorato

__Barème:__  
1,2,3 : Très faible  4,5 : Faible  6,7 : Bon  8,9 : Très bon 10 : Excellent  
(Établir une échelle proportionnelle pour les notes sur 20 et sur 40.)

### Écran LCD

- Le message "manoeuvre x" est affiché pendant l'exécution d'une manœuvre. 
- Le message "Combinaison non evaluee" est affiché lorsque nécessaire. 
- En mode détection, le message affiché respecte le bon format et les catégories  
  correspondent bien aux distances.  

|__Pondération:  7/10__|
|---------------------|

### Sonar
- Les distances affichées correspondent bien aux voltages des sources de  
 tensions. (+/- 0.1 mètre d'écart est toléré)
- La détection des distances et l'affichage de celles-ci se font au moins  
  4 fois par seconde.

|__Pondération:  20/20__|
|---------------------|

### Transitions
- Appuyer sur le bouton poussoir fait passer au mode manœuvre.
- Le système retourne au mode détection après l'exécution d'une manœuvre.

|__Pondération:  5/10__|
|---------------------|

### Manoeuvre
- Pour chaque manœuvre, toutes les étapes sont présentes et exécutées  
  dans l'ordre demandé.
- Les délais demandés sont de la bonne durée. ("On laisse passer x ms")
- Les bons pourcentages de puissance des roues sont présentés sur les  
  afficheurs 7 segments.
- Les bons signaux PWM sont générés sur les broches 4 et 5 du port D.
- Les DEL de direction appropriées sont allumées en fonction du sens des roues.
- Les montées et descentes de vitesse graduelles sont correctement exécutées.  
  (manœuvres 1, 2, 5 et 6)

|__Pondération:  40/40__|
|---------------------|

### Afficheur 7 segments
- L'affichage de tous les chiffres et du trait d'union ont été implémentés.
- Le taux de rafraichissement des afficheurs donne une impression  
  d'affichage continu. Il n'y a pas d'effet de clignotement et on ne se  
  rend pas compte que les afficheurs sont activés individuellement à tour  
  de rôle.

|__Pondération:  20/20__|
|---------------------|

# Résultat

__Total des points: 92/100__

# Commentaires du correcteur:

Beau travail! 

Écran LCD
- L'écran clignote parfois.

Transitions
- Lorsqu'on appuie rapidement sur le bouton, les manoeuvres ne sont pas déclenchées.

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
======================= Sortie de make dans projet/ =============================
make : on entre dans le répertoire « /home/william/Documents/inf1900-grader/correction_claudia_epreuve_finale/4081/projet »
make: *** Pas de cible spécifiée et aucun makefile n'a été trouvé. Arrêt.
make : on quitte le répertoire « /home/william/Documents/inf1900-grader/correction_claudia_epreuve_finale/4081/projet »


```