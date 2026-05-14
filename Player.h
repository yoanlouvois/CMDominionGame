//
// Created by Asus on 03/11/2024.
//

#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>



class Card;
class Jeux;
class Plateau;


/**
 * @class Player
 * @brief Représente un joueur dans le jeu Dominion, avec ses attributs et actions.
 *
 * La classe Player gère l'état et les actions d'un joueur, y compris :
 * - Les cartes dans son deck, sa main, sa défausse, et celles déjà jouées.
 * - Ses ressources actuelles : actions, achats, pièces, et points de victoire.
 * - Les interactions avec le plateau et les autres joueurs.
 */
class Player {
    std::vector<Card*> m_deck;       /**< Deck du joueur contenant les cartes à piocher. */
    std::vector<Card*> m_hand;       /**< Main actuelle du joueur. */
    std::vector<Card*> m_defausse;   /**< Pile de défausse du joueur, où vont les cartes utilisées ou défaussées. */
    std::vector<Card*> m_played;     /**< Cartes déjà jouées lors du tour en cours. */
    std::string m_name;              /**< Nom du joueur. */
    int m_actions;                   /**< Nombre d'actions restantes pour le joueur dans le tour. */
    int m_buys;                      /**< Nombre d'achats disponibles pour le joueur dans le tour. */
    int m_coins;                     /**< Nombre de pièces disponibles pour les achats. */
    int m_points;                    /**< Nombre de points de victoire accumulés par le joueur. */
    static int defaultId;            /**< Identifiant par défaut pour les joueurs, utilisé lors de leur création. */

    public:
    /**
     * @brief Constructeur avec nom de joueur.
     * @param name Nom du joueur.
     */
    explicit Player(std::string const& name);

    /**
     * @brief Constructeur par défaut.
     */
    Player();

    /**
     * @brief Destructeur de la classe Player.
     */
    ~Player();

    /**
     * @brief Pioche un nombre donné de cartes.
     * @param x Nombre de cartes à piocher.
     */
    void pioche(int x);

    /**
     * @brief Défause toutes les cartes de la main et des cartes jouées.
     */
    void defausseAll();

    /**
     * @brief Affiche les informations du joueur (nom, points, ressources, etc.).
     */
    void info() const;

    /**
     * @brief Défause une carte spécifique depuis la main.
     * @param cardName Nom de la carte à défaucher.
     * @return true si la carte a été défauchée, false sinon.
     */
    bool defausseFromHand(std::string const &cardName);

    /**
     * @brief Défause une liste de cartes.
     * @param cards Vecteur contenant les cartes à défaucher.
     * @return true si toutes les cartes ont été défauchées, false sinon.
     */
    bool defausseArray(std::vector<Card*>& cards);

    /**
     * @brief Joue une carte action depuis la main.
     * @param cardName Nom de la carte action.
     * @param jeux Instance de la partie en cours.
     * @return true si l'action a été jouée, false sinon.
     */
    bool playAction(std::string const& cardName, Jeux &jeux);

    /**
     * @brief Déplace une carte de la défausse vers le deck.
     * @param cardName Nom de la carte à déplacer.
     * @return true si l'opération a réussi, false sinon.
     */
    bool moveCardFromDefausseToDeck(std::string const& cardName);

    /**
     * @brief Vole une carte d'un autre joueur.
     * @param card Carte à voler.
     * @param fromCards Vecteur contenant les cartes de l'autre joueur.
     * @return true si la carte a été volée, false sinon.
     */
    bool stealCard(Card* card, std::vector<Card*>& fromCards);

    /**
     * @brief Défause tout le deck.
     */
    void defausseDeck();

    /**
     * @brief Défause une carte spécifique dans un vecteur donné.
     * @param array Vecteur contenant les cartes.
     * @param index Index de la carte à défaucher.
     */
    void defausseCard(std::vector<Card*>& array, int index);

    /**
     * @brief Gagne une carte depuis le plateau.
     * @param cardName Nom de la carte à gagner.
     * @param p Référence au plateau.
     * @param minCost Coût minimum (par défaut 0).
     * @param maxCost Coût maximum (par défaut 10).
     * @return true si la carte a été gagnée, false sinon.
     */
    bool gainCard(std::string const& cardName, Plateau &p, int minCost = 0, int maxCost = 10);

    /**
     * @brief Affiche la main du joueur.
     */
    void afficheHand() const;

    /**
     * @brief Mélange les cartes du deck.
     */
    void shuffle();

    /**
     * @brief Ajoute des points de victoire.
     * @param points Points à ajouter.
     */
    void AddPoint(int points);

    /**
     * @brief Ajoute des pièces au trésor du joueur.
     * @param treasure Nombre de pièces à ajouter.
     */
    void AddTreasure(int treasure);

    /**
     * @brief Ajoute des actions disponibles pour le tour.
     * @param action Nombre d'actions à ajouter.
     */
    void AddAction(int action);

    /**
     * @brief Ajoute des achats disponibles pour le tour.
     * @param buy Nombre d'achats à ajouter.
     */
    void AddBuy(int buy);

    /**
     * @brief Ajoute des pièces disponibles pour le tour.
     * @param coin Nombre de pièces à ajouter.
     */
    void AddCoin(int coin);

    /**
     * @brief Vérifie si le joueur peut réagir à une attaque.
     * @param index Référence pour l'index de la carte de réaction.
     * @return true si une réaction est possible, false sinon.
     */
    bool ReactTo(int& index) const;

    /**
     * @brief Vend une carte spécifique.
     * @param cardName Nom de la carte à vendre.
     * @return true si la carte a été vendue, false sinon.
     */
    bool sellCard(const std::string& cardName);

    /**
     * @brief Vend tous les trésors dans la main du joueur.
     * @return true si au moins un trésor a été vendu, false sinon.
     */
    bool sellAllTreasure();

    /**
     * @brief Achète une carte depuis le plateau.
     * @param cardName Nom de la carte à acheter.
     * @param j Instance de la partie en cours.
     * @return true si l'achat a été effectué, false sinon.
     */
    bool buyCard(std::string const& cardName, Jeux const& j);

    /**
     * @brief Pioche une carte depuis le dessus du deck.
     * @return Pointeur vers la carte piochée ou nullptr si le deck est vide.
     */
    Card* drawCard();

    /**
     * @brief Supprime définitivement une carte.
     * @param card Carte à supprimer.
     */
    static void trashCard(const Card* card);

    /**
     * @brief Jette une carte depuis la main.
     * @param cardName Nom de la carte à jeter.
     * @return true si la carte a été jetée, false sinon.
     */
    bool trashCardFromHand(std::string const& cardName);

    /**
     * @brief Jette une carte depuis les cartes jouées.
     * @param cardName Nom de la carte à jeter.
     * @return true si la carte a été jetée, false sinon.
     */
    bool trashCardFromPlayed(std::string const& cardName);

    /**
     * @brief Vérifie si une carte action est dans la main.
     * @return true si une carte action est disponible, false sinon.
     */
    bool canPlayAction();

    /**
     * @brief Vérifie si le joueur a assez de ressources pour effectuer un achat.
     * @return true si un achat est possible, false sinon.
     */
    bool canBuy() const;

    //getters
    [[nodiscard]]std::vector<Card*>& getDeck();
    [[nodiscard]]std::vector<Card*>& getHand();
    [[nodiscard]]std::vector<Card*>& getDefausse() ;
    [[nodiscard]]std::vector<Card*>& getPlayed();
    [[nodiscard]]int getPoints() const;
    [[nodiscard]]int getCoins() const;
    [[nodiscard]]int getActions() const;
    [[nodiscard]]int getBuys() const;
    [[nodiscard]] std::string getName() const;

    //setters
    void setDeck(std::vector<Card*> deck);
    void setHand(std::vector<Card*> hand);
    void setDefausse(std::vector<Card*> discard);
    void setPlayed(std::vector<Card*> played);
    void setCoins(int coins);
    void setActions(int actions);
    void setBuys(int buys);

};



#endif //PLAYER_H
