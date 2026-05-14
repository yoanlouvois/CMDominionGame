
#include <fstream>
#include <iostream>
#include "KingdomCard.h"
#include "Jeux.h"
#include "Plateau.h"
/*


Guide d'utilisation du jeu Dominion

HELP [nomCarte]
Effet : Affiche les détails d'une carte spécifique (carte de trésor, royaume ou victoire) si elle existe dans la réserve.
Exemple : HELP OR affiche les détails de la carte "OR".
----------------------------------------------------------------------------
INFO
Effet : Affiche des informations sur les autres joueurs
-----------------------------------------------------------------------------
END
Effet : Termine la phase ou l'action en cours (si exitOption est activé).


COMMANDE SPECIFIQUE AUX PHASES

-------------------Phase ACTION-------------------------
PLAY [nomCarte]
Effet : Joue une carte d'action depuis la main du joueur actif.
Conditions : Disponible uniquement pendant la phase d'action.

----------------------Phase BUY---------------------------

BUY [nomCarte]
Effet : Achète une carte de la réserve.
Conditions : Disponible uniquement pendant la phase d'achat.

SELL [nomCarte]
Effet : Vend une carte spécifique pour obtenir des pièces.
Conditions : Disponible uniquement pendant la phase d'achat.
Exemple : SELL OR vend la carte "OR".

SELL ALL
Effet : Vend toutes les cartes de trésor du joueur actif pour obtenir des pièces.
Conditions : Disponible uniquement pendant la phase d'achat.
Commandes pour sélectionner une carte

------------------Phase quelconque-------------------------

PICK [nomCarte]
Effet : Sélectionne une carte dans la réserve et retourne son nom.
Conditions : Disponible uniquement si un pointeur cardNameOption est fourni à la fonction.
*
 **/

int main()
{

    std::system("cls");
    KingdomCard::GenerateKingdomFromFile("royaume.txt");
    Jeux j;
    j.initGame();
    j.playGame();



    return 0;
}
