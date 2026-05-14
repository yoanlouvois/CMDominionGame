//
// Created by Asus on 03/11/2024.
//

#ifndef VICTORYCARD_H
#define VICTORYCARD_H
#include "Card.h"

/**
 * @brief Représente une carte Victoire dans le jeu Dominion.
 *
 * Les cartes Victoire apportent des points pour déterminer le gagnant à la fin du jeu.
 */
class VictoryCard : public Card {
    int m_victory; /**< Nombre de points de victoire accordés par la carte. */

public:
    /**
     * @brief Constructeur explicit pour une carte Victoire.
     * @param nom Nom de la carte Victoire.
     */
    explicit VictoryCard(std::string const& nom);

    /**
     * @brief Constructeur par copie.
     * @param card Carte Victoire à copier.
     */
    VictoryCard(VictoryCard const& card);

    /**
     * @brief Retourne le nombre de points de victoire accordés par la carte.
     * @return Points de victoire de la carte.
     */
    [[nodiscard]] int getVictory() const;

    /**
     * @brief Affiche les informations principales de la carte.
     */
    void affichage() const override;

    /**
     * @brief Affiche les détails complets de la carte.
     */
    void details() const override;
};


#endif //VICTORYCARD_H
