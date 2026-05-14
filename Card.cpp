//
// Created by Asus on 03/11/2024.
//
#include "Card.h"
#include <algorithm>
#include <iostream>
#include <iomanip>
#include "KingdomCard.h"
#include "TreasureCard.h"
#include "VictoryCard.h"



Card::Card(std::string nom,int cost):m_nom(std::move(nom)),m_cost(cost){};
int Card::getCost() const
{
    return m_cost;
}

// Normalisation de la chaine de caractères (majuscule)
std::string normalize(const std::string& s) {
    std::string res = s;
    std::ranges::transform(res.begin(), res.end(), res.begin(), ::toupper);
    return res;
}

std::string Card::getNom() const
{
    return m_nom;
}

void notif(std::string const& message)
{
    std::cout<<"\033[92m"<<message<<"\033[0m"<<std::endl;
}

void alert(std::string const& message)
{
    std::cout<<"\033[31m"<<message<<"\033[0m"<<std::endl;
}
void appuyerPourContinuer() {

    std::cout << "Entrez une touche pour continuer... > " ;
    std::cin.get();  // Attendre que l'utilisateur appuie sur une touche
    std::cin.ignore();  // Ignorer le caractère '\n' restant
}
void Card::afficheCards(const std::vector<Card*>& cards) {
    constexpr int maxCartesParLigne = 5;
    std::vector<std::tuple<std::string, int, std::string, std::string>> cartes;

    for (const auto& card : cards) {
        if (card) { // Vérifiez que la carte n'est pas nulle
            std::string type;
            std::string extraInfo;
            std::string colorCode;

            if (auto* k=dynamic_cast<KingdomCard*>(card)) {
                type = "ROYAUME";
                extraInfo = KingdomCard::actionType(*k);
                colorCode = "\033[34m";  // Bleu pour Royaume
            } else if (auto* treasureCard = dynamic_cast<TreasureCard*>(card)) {
                type = "TRESOR";
                extraInfo = "Piece : " + std::to_string(treasureCard->getTreasure());
                colorCode = "\033[33m";  // Jaune pour Trésor
            } else if (auto* victoryCard = dynamic_cast<VictoryCard*>(card)) {
                type = "VICTOIRE";
                extraInfo = "PV : " + std::to_string(victoryCard->getVictory());
                colorCode = "\033[32m";  // Vert pour Victoire
            } else {
                type = "Inconnu";
                extraInfo = "N/A";
                colorCode = "\033[0m";  // Réinitialiser pour inconnu
            }

            cartes.emplace_back(colorCode + card->getNom() + "\033[0m", card->getCost(), type, extraInfo);
        }
    }

    // Affichage des cartes
    const size_t totalCartes = cartes.size();

    for (size_t i = 0; i < totalCartes; i += maxCartesParLigne) {
        // Bordures supérieures des cartes
        for (size_t j = i; j < i + maxCartesParLigne && j < totalCartes; ++j) {
            std::cout << "\033[31m+----------------+\033[0m  ";
        }
        std::cout << std::endl;

        // Ligne contenant le nom des cartes
        for (size_t j = i; j < i + maxCartesParLigne && j < totalCartes; ++j) {
            std::cout << "\033[31m|\033[0m " << std::setw(24) << std::left
                      << std::get<0>(cartes[j]) << "\033[31m|\033[0m  ";
        }
        std::cout << std::endl;

        // Ligne contenant le type des cartes
        for (size_t j = i; j < i + maxCartesParLigne && j < totalCartes; ++j) {
            std::cout << "\033[31m|\033[0m Type:" << std::setw(10) << std::left
                      << std::get<2>(cartes[j]) << "\033[31m|\033[0m  ";
        }
        std::cout << std::endl;

        // Ligne contenant le coût des cartes
        for (size_t j = i; j < i + maxCartesParLigne && j < totalCartes; ++j) {
            std::cout << "\033[31m|\033[0m Cout: " << std::setw(9) << std::left
                      << std::get<1>(cartes[j]) << "\033[31m|\033[0m  ";
        }
        std::cout << std::endl;

        // Ligne contenant les informations supplémentaires
        for (size_t j = i; j < i + maxCartesParLigne && j < totalCartes; ++j) {
            std::cout << "\033[31m|\033[0m " << std::setw(15) << std::left
                      << std::get<3>(cartes[j]) << "\033[31m|\033[0m  ";
        }
        std::cout << std::endl;

        // Bordures inférieures des cartes
        for (size_t j = i; j < i + maxCartesParLigne && j < totalCartes; ++j) {
            std::cout << "\033[31m+----------------+\033[0m  ";
        }
        std::cout << std::endl << std::endl;  // Espace entre les rangées de cartes
    }
}

