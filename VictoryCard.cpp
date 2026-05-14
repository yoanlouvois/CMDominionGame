//
// Created by Asus on 03/11/2024.
//

#include "VictoryCard.h"

#include <iomanip>
#include <iostream>
#include "Jeux.h"
#include "Player.h"

VictoryCard::VictoryCard(std::string const&nom) : Card(normalize(nom),0), m_victory(0)
{
    if(m_nom=="DOMAINE")
    {
        m_cost=2;
        m_victory=1;
    }
    else if(m_nom=="DUCHE")
    {
        m_cost=5;
        m_victory=3;
    }
    else if(m_nom=="PROVINCE")
    {
        m_cost=8;//8
        m_victory=6;//6
    }
    else if(m_nom=="MALEDICTION")
    {
        m_cost=0;
        m_victory=-1;
    }
    else
        std::cerr<<"erreur la carte ne fait pas partie du jeu"<<std::endl;

}

VictoryCard::VictoryCard(VictoryCard const &card) : Card(card.m_nom,card.m_cost), m_victory(card.m_victory)
{}

void VictoryCard::affichage() const
{
    std::cout << "\033[31m+--------------+\033[0m\n";
    std::cout << "\033[31m|\033[0m " << std::setw(13) << std::left << m_nom << "\033[31m|\033[0m\n";
    std::cout << "\033[31m|\033[0m Type: " << std::setw(7) << m_victory << "\033[31m|\033[0m\n";
    std::cout << "\033[31m|\033[0m Cout: " << std::setw(7) << m_cost << "\033[31m|\033[0m\n";
    std::cout << "\033[31m+--------------+\033[0m\n";
}

void VictoryCard::details()const
{
    std::string type;
    if(m_victory>0)
        type="VICTOIRE";
    else
        type="MALEDICTION";
    std::cout<<"Nom : "<<m_nom<<std::endl;
    std::cout<<"Type : "<<type<<std::endl;
    std::cout<<"Cout : "<<m_cost<<std::endl;
    if(m_victory>0)
        std::cout<<"Description : +"<<m_victory<<" point de victoire"<<std::endl;
    else
        std::cout<<"Description : -"<<m_victory<<" point de victoire"<<std::endl;
}

int VictoryCard::getVictory() const {
    return m_victory;
}

