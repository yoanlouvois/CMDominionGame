//
// Created by Asus on 13/11/2024.
//

#include "Plateau.h"
#include "KingdomCard.h"
#include <iostream>
#include "VictoryCard.h"
#include "TreasureCard.h"
#include <iomanip>
#include <algorithm>
#include <set>
#include <vector>
#include <string>

//carte de bases


/**
 * Trie le vecteur de cartes en fonction de son type
 * @param cartes
 */
void triCartes(std::vector<std::tuple<std::string, int, std::string, std::string, int>>& cartes) {
    // Fonction pour attribuer une priorité basée sur le type
    auto getPriority = [](const std::string& type) {
        if (type == "VICTOIRE") return 0;
        if (type == "TRESOR") return 1;
        if (type == "ROYAUME") return 2;
        return 3;  // Type inconnu ou par défaut
    };

    // Trier les cartes en utilisant std::sort
    std::ranges::sort(cartes.begin(), cartes.end(), [&](const auto& a, const auto& b) {
        return getPriority(std::get<2>(a)) < getPriority(std::get<2>(b));
    });
}

/**
 * Affiche le plateau de jeu
 */
void Plateau::affichage() {
    constexpr int maxCartesParLigne = 5;  // Maximum de cartes par ligne
    const auto& reserves = this->getReserve();  // Nombre total de cartes

    std::cout << "______________________________________ PLATEAU ___________________________________________________" << std::endl;
    std::vector<std::tuple<std::string, int, std::string, std::string, int>> cartes;

    for (const auto& [nomCarte, reserve] : reserves) {
        if (reserve.getCard()) {  // Vérifiez que la carte n'est pas nulle
            std::string type;
            std::string extraInfo;
            std::string colorCode;
            int nombre = reserve.getTaille();  // Taille de la réserve
            Card* card = reserve.getCard();

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

            cartes.emplace_back(colorCode + card->getNom() + "\033[0m", card->getCost(), type, extraInfo, nombre);
        }
    }

    // Affichage des cartes
    triCartes(cartes);
    const size_t totalCartes = cartes.size();

    for (size_t i = 0; i < totalCartes; i += maxCartesParLigne) {
        size_t cartesRestantes = std::min(static_cast<size_t>(maxCartesParLigne), totalCartes - i);

        // Bordures supérieures des cartes
        for (size_t j = 0; j < cartesRestantes; ++j) {
            std::cout << "\033[31m+----------------+\033[0m  ";
        }
        std::cout << std::endl;

        // Ligne contenant le nom des cartes
        for (size_t j = 0; j < cartesRestantes; ++j) {
            std::cout << "\033[31m|\033[0m " << std::setw(24) << std::left
                      << std::get<0>(cartes[i + j]) << "\033[31m|\033[0m  ";
        }
        std::cout << std::endl;

        // Ligne contenant le type des cartes
        for (size_t j = 0; j < cartesRestantes; ++j) {
            std::cout << "\033[31m|\033[0m Type:" << std::setw(10) << std::left
                      << std::get<2>(cartes[i + j]) << "\033[31m|\033[0m  ";
        }
        std::cout << std::endl;

        // Ligne contenant le coût des cartes
        for (size_t j = 0; j < cartesRestantes; ++j) {
            std::cout << "\033[31m|\033[0m Cout: " << std::setw(9) << std::left
                      << std::get<1>(cartes[i + j]) << "\033[31m|\033[0m  ";
        }
        std::cout << std::endl;

        // Ligne contenant les informations supplémentaires
        for (size_t j = 0; j < cartesRestantes; ++j) {
            std::cout << "\033[31m|\033[0m " << std::setw(15) << std::left
                      << std::get<3>(cartes[i + j]) << "\033[31m|\033[0m  ";
        }
        std::cout << std::endl;

        // Ligne contenant le nombre de cartes
        for (size_t j = 0; j < cartesRestantes; ++j) {
            std::cout << "\033[31m|\033[0m Nombre: " << std::setw(7) << std::left
                      << std::get<4>(cartes[i + j]) << "\033[31m|\033[0m  ";
        }
        std::cout << std::endl;

        // Bordures inférieures des cartes
        for (size_t j = 0; j < cartesRestantes; ++j) {
            std::cout << "\033[31m+----------------+\033[0m  ";
        }
        std::cout << std::endl << std::endl;  // Espace entre les rangées de cartes
    }
}

/**
 * Constructeur du plateau
 * @param nbrJoueur
 */
Plateau::Plateau( int nbrJoueur):m_cuivre(60),m_argent(40),m_or(30)
{
    if(nbrJoueur==2)
    {
        m_victory=8;//8
        m_kingdom=10;//10
        m_curse=10;
    }
    else if(nbrJoueur==3)
    {
        m_victory=12;
        m_kingdom=12;
        m_curse=20;
    }
    else if(nbrJoueur==4)
    {
        m_victory=12;
        m_kingdom=12;
        m_curse=30;
    }
    else {
        m_victory=0;
        m_kingdom=0;
        m_curse=0;
    }
}

/**
 * Remplit le plateau
 */
void Plateau::built()
{
    m_reserve["CUIVRE"]=Reserve(TreasureCard("CUIVRE"),m_cuivre);
    m_reserve["ARGENT"]=Reserve(TreasureCard("ARGENT"),m_argent);
    m_reserve["OR"]=Reserve(TreasureCard("OR"),m_or);
    m_reserve["DOMAINE"]=Reserve(VictoryCard("DOMAINE"),m_victory);
    m_reserve["DUCHE"]=Reserve(VictoryCard("DUCHE"),m_victory);
    m_reserve["PROVINCE"]=Reserve(VictoryCard("PROVINCE"),m_victory);//m_victory
    m_reserve["MALEDICTION"]=Reserve(VictoryCard("MALEDICTION"),m_curse);
    for(auto &i : BaseBoard)
    {
        auto it = KingdomCard::KingdomCardMap.find(normalize(i));
        if (it != KingdomCard::KingdomCardMap.end())
        {
            m_reserve[normalize(it->second.getNom())]=Reserve(it->second, normalize(i) == "JARDIN" ? m_victory:m_kingdom);
        }
    }



}

void Plateau::built(std::vector<std::string> choice)
{
    m_reserve["CUIVRE"]=Reserve(TreasureCard("CUIVRE"),m_cuivre);
    m_reserve["ARGENT"]=Reserve(TreasureCard("ARGENT"),m_argent);
    m_reserve["OR"]=Reserve(TreasureCard("OR"),m_or);
    m_reserve["DOMAINE"]=Reserve(VictoryCard("DOMAINE"),m_victory);
    m_reserve["DUCHE"]=Reserve(VictoryCard("DUCHE"),m_victory);
    m_reserve["PROVINCE"]=Reserve(VictoryCard("PROVINCE"),m_victory);//m_victory
    m_reserve["MALEDICTION"]=Reserve(VictoryCard("MALEDICTION"),m_curse);
    for(auto &i : choice)
    {
        auto it = KingdomCard::KingdomCardMap.find(normalize(i));
        if (it != KingdomCard::KingdomCardMap.end())
        {
            m_reserve[normalize(it->second.getNom())]=Reserve(it->second, normalize(i) == "JARDIN" ? m_victory:m_kingdom);
        }
        else
            std::cerr<<"la carte "<<i<< " est introuvable, erreur dans le build du plateau"<<std::endl;

    }
    if(m_reserve.size()<17)
    {
        std::cerr<<"plateau incomplet, nombre de cartes insuffisant"<<std::endl;
    }

}

/**
 * Verifie si la condition de fin de jeu est remplie
 * @return
 */
bool Plateau::isEmpty() const
{
    int count(0);
    if(m_reserve.at("PROVINCE").isEmpty())
        return true;
    for(auto &it : m_reserve)
    {

        if(it.first!="PROVINCE" && it.second.isEmpty())
            count++;
        if(count==3)
            return true;
    }
    return false;
}

void Plateau::updateReserveByName(const std::string& cardName,int nbr)
{
    if(m_reserve.find(normalize(cardName))!=m_reserve.end())
        m_reserve.at(cardName).DimTaille(nbr);
    else
        std::cout<<"mise à jour de la réserve impossible"<<std::endl;
}
std::map<std::string,Reserve>& Plateau::getReserve()
{
    return m_reserve;
}



