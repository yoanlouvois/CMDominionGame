//
// Created by Asus on 07/11/2024.
//

#include "GameCommand.h"

#include "KingdomCard.h"
#include "Jeux.h"
#include "Reserve.h"
#include "Player.h"
#include "Plateau.h"
#include <fstream>
#include <iomanip>
#include "TreasureCard.h"
#include "VictoryCard.h"
#include <algorithm>


void GameCommand::getInput(Jeux& j,Phase phase,bool* exitOption,std::string* cardNameOption,std::string* otherInput) {
    while (true) {
        std::cout << "> ";
        std::string commande;
        std::getline(std::cin, commande);

        // Normalisation de la commande
        commande = normalizeCommand(commande);

        // Vérification des commandes communes
        if (commande.find("HELP ") == 0) {
            handleHelp(commande.substr(5), j);
            continue;
        }if (commande.find("SELL ") == 0)
        {
            handleSell(commande.substr(5), j, phase);
            continue;
        }if(commande.find("BUY ") == 0){
            handleBuy(commande.substr(4), j, phase);
            break;
        }
        if(commande.find("PLAY ") == 0){
            handlePlay(commande.substr(5), j, phase);
            break;
        }if(commande.find("PICK ") == 0)
        {
            if(cardNameOption==nullptr)
            {
                alert("Commande indisponible");
                continue;
            }
            *cardNameOption=handlePick(commande.substr(5), j);
            break;
        }
        if (commande == "INFO") {
            handleInfo(j);
            continue;
        }
        if (commande == "END")
        {
            if (exitOption==nullptr) {
                alert("vous ne pouvez pas terminer le tour ou l'action en cours");
                continue;
            }
            *exitOption = true;
            break;
        }
        if(otherInput!=nullptr)
        {
            *otherInput=commande;
            break;
        }
        alert("Commande non reconnue. Essayez 'help [nomCarte]', 'pick [nomCarte]',play [nomCarte],buy[nomCarte] ou 'end'." );
    }
}

void GameCommand::handleHelp(const std::string& nomCarte, const Jeux& j) {
    Plateau& plateau = j.getPlateau();
    auto it = plateau.getReserve().find(normalize(nomCarte));
    if (it != plateau.getReserve().end()) {
        Card* card = it->second.getCard();
        if (auto* treasure = dynamic_cast<TreasureCard*>(card)) {
            treasure->details();
        } else if (auto* kingdom = dynamic_cast<KingdomCard*>(card)) {
            kingdom->details();
        } else if (auto* victory = dynamic_cast<VictoryCard*>(card)) {
            victory->details();
        } else {
            alert("Type de carte inconnu." );
        }
    } else {
        alert("La carte '" + nomCarte + "' n'est pas reconnue." );
    }
}

std::string GameCommand::handlePick(const std::string& nomCarte, const Jeux& j) {
    Plateau& p=j.getPlateau();
    auto it=p.getReserve().find(normalize(nomCarte));
    if(it!=p.getReserve().end())
    {
        return nomCarte;
    }
    alert("carte inexistant");
    return "";
}



void GameCommand::handleBuy(const std::string& nomCarte, Jeux& j, Phase phase) {
    if (phase!=BUY) {
        alert( "Commande indisponible" );
        return;
    }

    Player& player = j.getActifPlayer();
    if(player.buyCard(nomCarte,j)&&player.canBuy())
    {
        j.playerBoard(&player);
        Jeux::phaseMessage(phase);
    }
}


void GameCommand::handlePlay(const std::string& nomCarte, Jeux& j, Phase phase) {
    if (phase!=ACTION) {
        alert( "Commande indisponible " );
        return;
    }

    Player& player = j.getActifPlayer();
    if(player.playAction(nomCarte,j)&&player.canPlayAction())
    {
        j.playerBoard(&player);
        Jeux::phaseMessage(phase);
    }


}

void GameCommand::handleSell(const std::string& nomCarte, const Jeux& j, Phase phase) {
    if (phase!=BUY) {
        alert( "Commande indisponible" );
        return;
    }

    Player& player = j.getActifPlayer();
    if (nomCarte == "ALL") {
        if(player.sellAllTreasure())
        {
            j.playerBoard(&player);
            Jeux::phaseMessage(BUY);
        }
    }else{
        if(player.sellCard(nomCarte))
        {
            j.playerBoard(&player);
            Jeux::phaseMessage(phase);
        }
    }
}

void GameCommand::handleInfo(Jeux const&j)
{
    for(auto it :j.getPlayers())
    {
        if(it!=&j.getActifPlayer())
        {
            std::cout<<it->getName()<<" "<<it->getPoints()<<" PV "<<std::endl;
        }
    }
}
std::string GameCommand::normalizeCommand(const std::string& input) {
    // Étape 1 : Supprimer les espaces en début et en fin
    std::string result = input;
    result.erase(0, result.find_first_not_of(" \t\n\r")); // Trim début
    result.erase(result.find_last_not_of(" \t\n\r") + 1); // Trim fin

    // Étape 2 : Convertir en minuscules
    std::ranges::transform(result.begin(), result.end(), result.begin(), ::toupper);

    // Étape 3 : Réduire les espaces multiples à un seul espace
    std::istringstream iss(result);
    std::ostringstream oss;
    std::string word;
    bool firstWord = true;

    while (iss >> word) {
        if (!firstWord) oss << " ";
        oss << word;
        firstWord = false;
    }

    return oss.str();
}