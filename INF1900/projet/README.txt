Le repertoire suivant contient le code source pour notre robot vous trouverez dans projet_src, un Makefile commun qui lors d'un make
appelle les autres Makefiles dans la librairie et pour l'executable qui apres compilation se trouvera sous un .hex dans projet_src/execdir.

Lors du chargement du firmware, il faut allumer le courant pour le boutton poussoir et allumer les sonar. Maintenant la simulation peut commencer.

Lors de l'appui du boutton poussoir maintenir appuye plutot que de faire un click vite.

Des fois le 7 egment diplay afficher de la niaiserie, apres de nombreses heures, on a conclut que l'erreur ne peut que venir de la part du logiciel de 
simulation, si cela arrive, redemarer la simulation avec le boutton en haut.

Pour faire en sorte que la luminostie du 7 segment diplay soit plus forte, augmente le courant threshold a 0.005 dans ses proprietes