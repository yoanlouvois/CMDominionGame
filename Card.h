//
// Created by Asus on 03/11/2024.
//

#ifndef CARD_H
#define CARD_H
#include <string>
#include <vector>

class Jeux;

/**
 * @brief Classe représentant une carte générique dans le jeu Dominion.
 *
 * Cette classe constitue la base pour toutes les cartes du jeu, qu'elles soient
 * des cartes Royaume, Trésor ou Victoire. Elle définit les propriétés et
 * comportements communs à toutes les cartes.
 */
class Card {
protected:
    std::string m_nom; ///< Nom de la carte.
    int m_cost = 0;    ///< Coût de la carte en pièces.

public:
    /**
     * @brief Constructeur de la classe `Card`.
     *
     * Initialise une carte avec un nom et un coût.
     *
     * @param nom Nom de la carte.
     * @param cost Coût de la carte.
     */
    Card(std::string nom, int cost);

    /**
     * @brief Affiche un ensemble de cartes dans le terminal.
     *
     * Cette méthode permet d'afficher une liste de cartes avec leurs informations
     * principales, comme leur nom et leur coût.
     *
     * @param cards Un vecteur de pointeurs vers les cartes à afficher.
     */
    static void afficheCards(const std::vector<Card*>& cards);

    /**
     * @brief Destructeur virtuel par défaut.
     *
     * Permet la destruction polymorphique des objets dérivés de `Card`.
     */
    virtual ~Card() = default;

    /**
     * @brief Méthode virtuelle pour afficher une carte.
     *
     * Cette méthode doit être redéfinie dans les classes dérivées pour afficher
     * les informations spécifiques à chaque type de carte.
     */
    virtual void affichage() const = 0;

    /**
     * @brief Méthode virtuelle pour afficher les détails d'une carte.
     *
     * Cette méthode fournit une vue détaillée des propriétés de la carte et
     * doit être implémentée dans les classes dérivées.
     */
    virtual void details() const = 0;

    /**
     * @brief Accesseur pour le coût de la carte.
     *
     * Permet de récupérer le coût d'une carte.
     *
     * @return Le coût de la carte.
     */
    [[nodiscard]] int getCost() const;

    /**
     * @brief Accesseur pour le nom de la carte.
     *
     * Permet de récupérer le nom d'une carte.
     *
     * @return Le nom de la carte.
     */
    [[nodiscard]] std::string getNom() const;
};

/**
 * @brief Normalise une chaîne de caractères.
 *
 * Convertit une chaîne en majuscules et supprime les espaces superflus,
 * ce qui facilite les comparaisons.
 *
 * @param s La chaîne de caractères à normaliser.
 * @return La chaîne normalisée.
 */
std::string normalize(const std::string& s);

/**
 * @brief Affiche un message de notification.
 *
 * Utilisée pour afficher un message d'information au joueur dans le terminal.
 *
 * @param message Le message à afficher.
 */
void notif(const std::string& message);

/**
 * @brief Affiche un message d'alerte.
 *
 * Utilisée pour signaler des erreurs ou des avertissements au joueur.
 *
 * @param message Le message à afficher.
 */
void alert(const std::string& message);

/**
 * @brief Pause l'exécution jusqu'à ce que l'utilisateur appuie sur une touche.
 *
 * Cette fonction est utile pour permettre au joueur de lire un message avant
 * de continuer l'exécution du programme.
 */
void appuyerPourContinuer();

#endif // CARD_H