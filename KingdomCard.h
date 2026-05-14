//
// Created by Asus on 03/11/2024.
//

#ifndef KINGDOMCARD_H
#define KINGDOMCARD_H
#include <string>
#include <vector>
#include <map>
#include "Card.h"
class Player;
class Jeux;

/**
 * @brief Classe représentant les cartes Royaume dans le jeu Dominion.
 *
 * Les cartes Royaume ont des effets spécifiques et peuvent être utilisées pour
 * diverses actions telles que l'attaque, les réactions, ou l'obtention de ressources.
 */
class KingdomCard : public Card {
    bool m_attack; /**< Indique si la carte est une carte d'attaque. */
    bool m_reaction; /**< Indique si la carte est une carte de réaction. */
    std::string m_description; /**< Description textuelle de la carte. */
    int m_cards; /**< Nombre de cartes supplémentaires à piocher. */
    int m_actions; /**< Nombre d'actions supplémentaires. */
    int m_coins; /**< Nombre de pièces supplémentaires. */
    int m_buys; /**< Nombre d'achats supplémentaires. */

    // Méthodes statiques représentant les effets des cartes spécifiques
    static void Atelier(Jeux &j);
    static void Cave(Jeux &j);
    static void Jardins(Player& p);
    static void Bandit(Jeux const&j);
    static void Sorciere(Jeux const&j);
    static void Chapelle(Jeux &j);
    static void Messager(Jeux &j);
    static void Vassal(Jeux &j);
    static void Braconnier(Jeux &j);
    void Salle_du_Conseil(Jeux &j);
    static void Chancelier(Jeux &j);
    static void Festin(Jeux &j);
    static void Preteur(Jeux &j);
    static void Voleur(Jeux &j);

public:
    static std::vector<KingdomCard> DataCards; /**< Liste de toutes les cartes Royaume disponibles. */
    static std::map<std::string, KingdomCard> KingdomCardMap; /**< Map associant les noms de cartes à leurs objets. */

    /**
     * @brief Génère les cartes Royaume à partir d'un fichier.
     * @param nomFichier Chemin du fichier source.
     */
    static void GenerateKingdomFromFile(const std::string& nomFichier);

    /**
     * @brief Renvoie une description du type d'action d'une carte Royaume.
     * @param k Carte Royaume concernée.
     * @return Chaîne décrivant le type d'action.
     */
    static std::string actionType(KingdomCard const&k);

    // Constructeurs et destructeur
    KingdomCard(std::string nom, int cost, bool attack, bool reaction, std::string description, int cards, int actions, int coins, int buys);
    KingdomCard(KingdomCard const& card);
    KingdomCard();
    ~KingdomCard() override = default;

    KingdomCard& operator=(KingdomCard const& other);

    // Méthodes pour l'affichage et l'exécution des actions
    void affichage() const override; /**< Affiche la carte dans le terminal. */
    void action(Jeux &j); /**< Applique l'effet de la carte dans le contexte du jeu. */
    void details() const override; /**< Affiche les détails de la carte. */

    // Accesseurs
    [[nodiscard]] bool isAttack() const; /**< Retourne si la carte est une carte d'attaque. */
    [[nodiscard]] bool isReaction() const; /**< Retourne si la carte est une carte de réaction. */
    [[nodiscard]] int getCards() const; /**< Retourne le nombre de cartes supplémentaires. */
    [[nodiscard]] int getActions() const; /**< Retourne le nombre d'actions supplémentaires. */
    [[nodiscard]] int getCoins() const; /**< Retourne le nombre de pièces supplémentaires. */
    [[nodiscard]] int getBuys() const; /**< Retourne le nombre d'achats supplémentaires. */
    [[nodiscard]] std::string getDescription() const; /**< Retourne la description de la carte. */
};

#endif //KINGDOMCARD_H
