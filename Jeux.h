//
// Created by Asus on 08/11/2024.
//

#ifndef JEUX_H
#define JEUX_H
#include "vector"
#include "GameCommand.h"



class Plateau;
class Player;


/**
 * Classe principale représentant le jeu Dominion.
 *
 * La classe `Jeux` gère les phases principales du jeu, l'état des joueurs, le plateau,
 * ainsi que les interactions entre ces éléments.
 */
class Jeux {
private:
    Plateau* m_plateau; // Pointeur vers le plateau de jeu contenant les réserves de cartes.
    std::vector<Player*> m_players; //  Liste des joueurs participant à la partie.
    size_t actifIndex; //  Index du joueur actuellement actif.

    /**
     * @brief Distribue les cartes initiales aux joueurs.
     */
    void DistributeCards();

    /**
     * @brief Définit un joueur pour initialiser certains aspects de son état.
     *
     * @param player Pointeur vers le joueur à initialiser.
     */
    static void setPlayer(Player* player);

    /**
     * @brief Gère la phase d'action d'un joueur.
     *
     * @param player Pointeur vers le joueur actif effectuant des actions.
     */
    void actionPhase(Player* player);

    /**
     * @brief Gère la phase d'achat d'un joueur.
     *
     * @param player Pointeur vers le joueur actif effectuant des achats.
     */
    void buyPhase(Player* player);

    /**
     * @brief Gère la fin du tour d'un joueur.
     *
     * @param player Pointeur vers le joueur terminant son tour.
     */
    void endTurn(Player* player);

    /**
     * @brief Gère la fin du jeu, calcule les scores et affiche le gagnant.
     */
    void endGame();

    /**
     * @brief Affiche un guide pour expliquer les règles ou commandes du jeu.
     */
    void afficheGuide() const;

    /**
     * @brief Affiche le classement final des joueurs à la fin de la partie.
     */
    void afficheClassement() const;

public:
    /**
     * @brief Constructeur par défaut de la classe `Jeux`.
     */
    Jeux();

    /**
     * @brief Destructeur de la classe `Jeux`.
     */
    ~Jeux();

    /**
     * @brief Initialise une partie.
     */
    void initGame();

    /**
     * @brief Affiche les informations détaillées du plateau pour un joueur donné.
     *
     * @param player Pointeur constant vers le joueur dont on affiche le plateau.
     */
    void playerBoard(const Player* player) const;

    /**
     * @brief Initialise une partie avec les noms des joueurs spécifiés.
     * cette methode est utilise seulement pour les tests
     * @param nom1 Nom du premier joueur.
     * @param nom2 Nom du deuxième joueur.
     */
    void initGame(std::string const& nom1, std::string const& nom2);

    /**
     * @brief Lance la boucle principale du jeu.
     */
    void playGame();

    /**
     * @brief Affiche un message spécifique à une phase du jeu.
     *
     * @param phase La phase actuelle (ACTION, BUY, etc.).
     */
    static void phaseMessage(Phase phase);

    /**
     * @brief Récupère la liste des joueurs.
     *
     * @return Un vecteur contenant des pointeurs vers les joueurs.
     */
    [[nodiscard]] std::vector<Player*> getPlayers() const;

    /**
     * @brief Récupère une référence au joueur actuellement actif.
     *
     * @return Référence vers le joueur actif.
     */
    [[nodiscard]] Player& getActifPlayer() const;

    /**
     * @brief Récupère l'index du joueur actif.
     *
     * @return L'index du joueur actuellement actif.
     */
    [[nodiscard]] size_t getActifIndex() const;

    /**
     * @brief Récupère une référence au plateau de jeu.
     *
     * @return Référence vers le plateau de jeu.
     */
    [[nodiscard]] Plateau& getPlateau() const;
};

/**
 * @brief Permet de choisir 10 éléments parmi une liste d'options.
 *
 * @param options Vecteur contenant les options disponibles.
 * @return Un vecteur contenant 10 éléments choisis.
 */
std::vector<std::string> choisirDixElements(const std::vector<std::string>& options);

#endif // JEUX_H