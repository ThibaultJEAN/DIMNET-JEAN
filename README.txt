****************************************README***************************************************

==================================Douche INSAtelligent=======================================

Se projet fait la démonstration du fonctionnement d’un ensemble de capteurs et actionneur
 appliqué à une cabine de douche afin de rendre l’expérience utilisateur plus simple et 
agréable. Cette démonstration se fait à l’aide d’un simulateur assez élémentaire.

======================================Commencer==============================================

Ses instructions servent à obtenir une copie du projet sur votre machine local afin de 
pouvoir le tester et le développer à votre guise.

================================Conditions préalables===========================================

Vous avez besoin d’un invité de commande, d’un compilateur pouvant compiler et exécuter 
des fichier C++.
Vous avez aussi besoin d’un éditeur de texte acceptant les fichier .cpp et .h.

****Installation 
Le projet est récupérable à l’adresse suivante : https://github.com/ThibaultJEAN/DIMNET-JEAN
Ou à récupérer avec git : « git clone https://github.com/ThibaultJEAN/DIMNET-JEAN.git»

****Exécution et tests
Le projet est compilable et exécutable avec la commande suivante :
« g++ -Wall -Wextra -Werror -g *.cpp -o appli -lpthread  && ./appli »
L’exécution engendre une série de message périodique informant sur l’état du système.
Pour tester les fonctionnalités du projet il vous est possible d’appuyer sur ‘o’ puis « Entrée » 
pour ouvrir la porte et ‘f’ puis « Entrée » pour fermer la porte.
Les ouvertures et fermetures de porte peuvent prendre plus d’une itération d’affichage 
de l’état du système.

======================================Réalisé avec==============================================

•	Gedit - éditeur de texte
•	WSL – interface Linux sous Windows

========================================Auteurs=================================================

•	JEAN Thibault
•	DIMNET Alexandre


========================================Remerciements==============================================

•	DEAU Raphaël
•	GAUCHARD David
•	MONTEIL Thierry
•	Ensemble des intervenants pour la réalisation du simulateur et pour le bon déroulement 
	de ce bureau d'étude