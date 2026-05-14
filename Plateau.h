//
// Created by Asus on 13/11/2024.
//

#ifndef PLATEAU_H
#define PLATEAU_H
#include <map>
#include <string>
#include <vector>

#include "Reserve.h"
class Jeux;

/**
 * @brief Représente le plateau central du jeu Dominion.
 *
 * Le plateau contient les réserves de cartes (Trésors, Victoires, Royaumes, Malédictions) et gère leur état.
 */
class Plateau {
    std::map<std::string, Reserve> m_reserve; /**< Map associant les noms des cartes à leurs réserves. */
    int m_cuivre; /**< Nombre total de cartes Trésor Cuivre. */
    int m_argent; /**< Nombre total de cartes Trésor Argent. */
    int m_or; /**< Nombre total de cartes Trésor Or. */
    int m_victory; /**< Nombre total de cartes Victoire disponibles. */
    int m_kingdom; /**< Nombre total de cartes Royaume disponibles. */
    int m_curse; /**< Nombre total de cartes Malédiction disponibles. */

public:
    /**
     * @brief Affiche l'état du plateau (réserves de cartes).
     */
    void affichage();

    /**
     * @brief Constructeur initialisant le plateau en fonction du nombre de joueurs.
     * @param nbrJoueur Nombre de joueurs dans la partie.
     */
    explicit Plateau(int nbrJoueur);

    /**
     * @brief Construit le plateau avec les cartes par défaut.
     */
    void built();

    /**
     * @brief Construit le plateau avec des cartes personnalisées.
     * @param choice Liste des cartes choisies pour le plateau.
     */
    void built(std::vector<std::string> choice);

    /**
     * @brief Vérifie si les conditions de fin sont remplies.
     * @return `true` 3 réserves sont vides ou que les provinces sont epuisees, sinon `false`.
     */
    [[nodiscard]] bool isEmpty() const;

    /**
     * @brief Met à jour le nombre de cartes dans une réserve donnée.
     * @param cardName Nom de la carte à modifier.
     * @param nbr Nombre de cartes à ajouter ou retirer.
     */
    void updateReserveByName(const std::string& cardName, int nbr);

    /**
     * @brief Accède à la map des réserves du plateau.
     * @return Référence à la map des réserves.
     */
    std::map<std::string, Reserve>& getReserve();
};

/**
 * @brief Liste par défaut des cartes Royaume de base.
 */
inline std::vector<std::string> BaseBoard = {"atelier", "bucheron", "village", "festin", "laboratoire",
                                             "douves", "jardins", "chapelle", "voleur", "sorciere"};

/**
 * @brief Liste des cartes Royaume bonus.
 */
inline std::vector<std::string> bonus = {"festival", "bandit", "marche", "manufacture", "preteur",
                                         "chancelier", "salle_duconseil", "messager", "vassal", "braconnier"};

#endif //PLATEAU_H
