//
// Created by Asus on 03/11/2024.
//

#ifndef TREASURECARD_H
#define TREASURECARD_H
#include "Card.h"



/**
 * @brief Représente une carte Trésor dans le jeu Dominion.
 *
 * Les cartes Trésor sont utilisées pour générer des pièces (monnaie) pendant la phase d'achat.
 */
class TreasureCard : public Card {
    int m_treasure; /**< Nombre de pièces (monnaie) que la carte génère. */

public:
    /**
     * @brief Constructeur explicit pour une carte Trésor.
     * @param nom Nom de la carte Trésor.
     */
    explicit TreasureCard(std::string const& nom);

    /**
     * @brief Constructeur par copie.
     * @param card Carte Trésor à copier.
     */
    TreasureCard(TreasureCard const& card);

    /**
     * @brief Retourne la valeur en pièces de la carte Trésor.
     * @return Nombre de pièces générées par la carte.
     */
    [[nodiscard]] int getTreasure() const;

    /**
     * @brief Affiche les informations principales de la carte.
     */
    void affichage() const override;

    /**
     * @brief Affiche les détails complets de la carte.
     */
    void details() const override;

};


#endif //TREASURECARD_H
