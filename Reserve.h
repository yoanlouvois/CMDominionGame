//
// Created by Asus on 03/11/2024.
//

#ifndef RESERVE_H
#define RESERVE_H

class Card;
class TreasureCard;
class VictoryCard;
class KingdomCard;


/**
 * @brief Représente une réserve de cartes sur le plateau.
 *
 * Une réserve contient un type spécifique de cartes (Trésor, Victoire ou Royaume) et leur quantité disponible.
 */
class Reserve {
    Card* m_card; /**< Pointeur vers une carte représentant le type de carte de la réserve. */
    int m_taille; /**< Nombre de cartes disponibles dans la réserve. */

public:
    /**
     * @brief Constructeur pour une réserve de cartes Trésor.
     * @param card Carte Trésor associée à la réserve.
     * @param taille Nombre de cartes disponibles dans la réserve.
     */
    Reserve(TreasureCard const& card, int taille);

    /**
     * @brief Constructeur pour une réserve de cartes Victoire.
     * @param card Carte Victoire associée à la réserve.
     * @param taille Nombre de cartes disponibles dans la réserve.
     */
    Reserve(VictoryCard const& card, int taille);

    /**
     * @brief Constructeur pour une réserve de cartes Royaume.
     * @param card Carte Royaume associée à la réserve.
     * @param taille Nombre de cartes disponibles dans la réserve.
     */
    Reserve(KingdomCard const& card, int taille);

    /**
     * @brief Constructeur par déplacement.
     * @param other Réserve à déplacer.
     */
    Reserve(Reserve&& other) noexcept;

    /**
     * @brief Constructeur par copie.
     * @param other Réserve à copier.
     */
    Reserve(const Reserve& other);

    /**
     * @brief Opérateur d'affectation par copie.
     * @param other Réserve à copier.
     * @return Référence à l'objet courant.
     */
    Reserve& operator=(Reserve const& other);

    /**
     * @brief Constructeur par défaut.
     */
    Reserve();

    /**
     * @brief Destructeur.
     */
    ~Reserve();

    /**
     * @brief Vérifie si la réserve est vide.
     * @return `true` si la réserve est vide, sinon `false`.
     */
    [[nodiscard]] bool isEmpty() const;

    /**
     * @brief Obtient la carte de la réserve.
     * @return Pointeur vers la carte associée à la réserve.
     */
    [[nodiscard]] Card* getCard() const;

    /**
     * @brief Obtient la taille actuelle de la réserve.
     * @return Nombre de cartes restantes dans la réserve.
     */
    [[nodiscard]] int getTaille() const;

    /**
     * @brief Diminue la taille de la réserve.
     * @param nbr Nombre de cartes à retirer.
     */
    void DimTaille(int nbr);

    /**
     * @brief Définit une nouvelle taille pour la réserve.
     * @param taille Nouvelle taille de la réserve.
     */
    void setTaille(int taille);

    /**
     * @brief Affiche les informations de la réserve dans le terminal.
     */
    void affichage() const;
};


#endif //RESERVE_H
