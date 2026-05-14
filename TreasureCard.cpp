//
// Created by Asus on 03/11/2024.
//

#include "TreasureCard.h"

#include <iomanip>
#include <iostream>
#include "Player.h"


TreasureCard::TreasureCard(std::string const&nom) :  Card(normalize(nom),0),m_treasure(0)
{
    if(m_nom=="CUIVRE")
    {
        m_cost = 0;
        m_treasure = 1;
    }
    else if( m_nom == "ARGENT")
    {
        m_cost = 3;
        m_treasure = 2;
    }
    else if(m_nom == "OR")
    {
        m_cost = 6;
        m_treasure = 3;
    }
    else
        std::cerr<<"erreur la carte ne fait pas partie du jeu"<<std::endl;
}

TreasureCard::TreasureCard(TreasureCard const& card):Card(card.m_nom,card.m_cost),m_treasure(card.m_treasure)
{}

int TreasureCard::getTreasure() const
{
    return m_treasure;
}


void TreasureCard::affichage() const
{

    std::cout << "\033[31m+--------------+\033[0m\n";
    std::cout << "\033[31m|\033[0m " << std::setw(13) << std::left << m_nom << "\033[31m|\033[0m\n";
    std::cout << "\033[31m|\033[0m Type: " << std::setw(7) << m_treasure << "\033[31m|\033[0m\n";
    std::cout << "\033[31m|\033[0m Cout: " << std::setw(7) << m_cost << "\033[31m|\033[0m\n";
    std::cout << "\033[31m+--------------+\033[0m\n";
}

void TreasureCard::details()const
{
    std::cout<<"Nom : "<<m_nom<<std::endl;
    std::cout<<"Type : TRESOR "<<std::endl;
    std::cout<<"Cout : "<<m_cost<<std::endl;
    std::cout<<"Description : +"<<m_treasure<<" pieces"<<std::endl;
}

