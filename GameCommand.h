//
// Created by Asus on 07/11/2024.
//

#ifndef GAMECOMMAND_H
#define GAMECOMMAND_H
#include <string>
#include <iostream>
#include <vector>

#include "Player.h"

class Player;



class Jeux;

/**
 * @brief Enumération représentant les différentes phases du jeu.
 *
 * Ces phases indiquent l'état actuel du jeu :
 * - `ACTION` : Phase où les joueurs jouent des cartes Royaume.
 * - `BUY` : Phase où les joueurs achètent des cartes.
 * - `NONE` : Aucune phase spécifique (état par défaut).
 */
enum Phase { ACTION, BUY, NONE };

/**
 * @brief Classe statique pour gérer les interactions entre les joueurs et le jeu.
 *
 * Cette classe regroupe des méthodes pour traiter les entrées clavier,
 * gérer les commandes des joueurs, et faciliter la communication entre les joueurs
 * et le moteur du jeu. Toutes les méthodes de cette classe sont statiques et ne nécessitent
 * pas d'instanciation de `GameCommand`.
 */
class GameCommand {
    /**
     * @brief Gère la commande "help" pour fournir des informations à un joueur.
     *
     * Cette commande affiche des informations spécifiques à une carte, comme ses effets ou
     * ses coûts, en fonction du jeu en cours.
     *
     * @param nomCarte Nom de la carte pour laquelle une aide est demandée.
     * @param j Référence au jeu en cours.
     */
    static void handleHelp(const std::string& nomCarte, const Jeux& j);

    /**
     * @brief Gère la commande "sell" pour vendre une carte ou des pièces.
     *
     * Cette méthode permet aux joueurs de vendre des cartes ou des pièces pendant une phase
     * spécifique du jeu.
     *
     * @param nomCarte Nom de la carte ou pièce à vendre.
     * @param j Référence au jeu en cours.
     * @param phase Phase actuelle du jeu (`ACTION`, `BUY`, ou autre).
     */
    static void handleSell(const std::string& nomCarte, const Jeux& j, Phase phase);

    /**
     * @brief Gère la commande "play" pour jouer une carte Royaume.
     *
     * Cette commande est utilisée pendant la phase ACTION. Elle permet à un joueur de jouer
     * une carte Royaume pour déclencher son effet.
     *
     * @param nomCarte Nom de la carte à jouer.
     * @param j Référence au jeu en cours.
     * @param phase Phase actuelle du jeu (doit être `ACTION`).
     */
    static void handlePlay(const std::string& nomCarte, Jeux& j, Phase phase);

    /**
     * @brief Gère la commande "buy" pour acheter une carte.
     *
     * Pendant la phase BUY, cette commande permet au joueur d'acheter une carte
     * disponible dans la réserve, si ses ressources le permettent.
     *
     * @param nomCarte Nom de la carte à acheter.
     * @param j Référence au jeu en cours.
     * @param phase Phase actuelle du jeu (doit être `BUY`).
     */
    static void handleBuy(const std::string& nomCarte, Jeux& j, Phase phase);

    /**
     * @brief Affiche les informations générales sur l'état du jeu.
     *
     * Cette commande est utilisée pour afficher des informations générales, comme
     * le plateau, les cartes en jeu, ou les statistiques des joueurs.
     *
     * @param j Référence au jeu en cours.
     */
    static void handleInfo(const Jeux& j);

    /**
     * @brief Gère la commande "pick" pour sélectionner une carte.
     *
     * Cette commande permet à un joueur de sélectionner une carte spécifique parmi
     * celles proposées.
     *
     * @param nomCarte Nom de la carte à sélectionner.
     * @param j Référence au jeu en cours.
     * @return Nom de la carte sélectionnée, après traitement.
     */
    static std::string handlePick(const std::string& nomCarte, const Jeux& j);

    /**
     * @brief Affiche un message générique dans le terminal.
     *
     * Cette méthode est utilisée pour afficher des messages informatifs ou des notifications
     * aux joueurs.
     *
     * @param message Le message à afficher.
     */
    static void displayMessage(const std::string& message);

    /**
     * @brief Normalise une commande saisie par un joueur.
     *
     * Cette méthode transforme la commande saisie pour la rendre insensible à la casse
     * et supprimer les espaces inutiles, afin de faciliter son traitement.
     *
     * @param input La commande brute saisie par le joueur.
     * @return La commande normalisée.
     */
    static std::string normalizeCommand(const std::string& input);

public:
    /**
     * @brief Gère les entrées clavier du joueur.
     *
     * Cette méthode est le point d'entrée principal pour traiter les commandes des joueurs.
     * Elle gère les phases spécifiques du jeu (ACTION, BUY) et permet de capturer
     * les intentions des joueurs.
     *
     * @param j Référence au jeu en cours.
     * @param phase Phase actuelle du jeu (`ACTION`, `BUY`, ou `NONE`).
     * @param exitOption Pointeur optionnel pour indiquer si le joueur souhaite quitter la phase.
     * @param cardNameOption Pointeur optionnel pour récupérer le nom de la carte saisie.
     * @param otherInput Pointeur optionnel pour capturer d'autres entrées utilisateur.
     */
    static void getInput(Jeux& j, Phase phase = NONE, bool* exitOption = nullptr,
                         std::string* cardNameOption = nullptr, std::string* otherInput = nullptr);
};

#endif // GAMECOMMAND_H