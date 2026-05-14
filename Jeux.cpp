//
// Created by Asus on 08/11/2024.
//
#include<iostream>
#include "Jeux.h"
#include "Player.h"
#include "Plateau.h"
#include "TreasureCard.h"
#include "VictoryCard.h"
#include "KingdomCard.h"
#include <algorithm>
#include <random>
#include <cstdlib> // pour std::system
#include <iomanip>
#include <set>
#include <thread>

#include "GameCommand.h"

#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Rouge */
#define GREEN   "\033[32m"      /* Vert */
#define BLUE    "\033[34m"      /* Bleu */
#define YELLOW  "\033[33m"      /* Jaune */
#define BLINK   "\033[5m"
#define PURPLE      "\033[35m"




/**
 * Constructeur vide
 */
Jeux::Jeux()
    : m_plateau(nullptr),actifIndex(0){}

/**
 * Destructeur vide
 */
Jeux::~Jeux()
{
    delete m_plateau;
    for (auto& player : m_players)
    {
        delete player;
    }
    m_players.clear();
}

/**
 * Reinitialise le terminal
 */
void clearTerminal() {
    std::system("cls");
}

/**
 * Initialise une partie avec les infos
 */


void spaceV(int n)
{
    for(int i=0;i<n;i++)
    {
        std::cout<<std::endl;
    }
}

std::string spaceH(int x)
{
    std::string res;
    for(int i=0;i<x;i++)
    {
        res+=" ";
    }
    return res;
}
void Jeux::initGame() {
    spaceV(2);
    std::cout << BLUE <<spaceH(25)<< "//////////////////////////////////////////////////////////////////////////" << RESET << std::endl;
    std::cout << PURPLE <<spaceH(25)<< "///                              DOMINION                              ///" << RESET << std::endl;
    std::cout << BLUE << spaceH(25)<<"//////////////////////////////////////////////////////////////////////////" << RESET << std::endl;
    std::cout <<spaceH(25)<< "BIENVENUE DANS LE MONDE DU DOMINION !\n";
    std::cout <<spaceH(25)<< "Dans ce jeu, vous construirez votre royaume pour devenir le souverain ultime.\n";
    std::cout <<spaceH(25)<< "Preparez-vous a affronter vos adversaires dans une partie strategique et captivante.\n\n";

    spaceV(2);

    std::cout << "------------------- Configuration des joueurs -----------------------\n";
    int nbJoueurs = 0;
    // Demande le nombre de joueurs
    std::cout<<"Entrez le nombre de joueurs (2-4) > ";
    while (!(std::cin >> nbJoueurs) || nbJoueurs < 2 || nbJoueurs > 4) {
        std::cin.clear(); // Efface les erreurs
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore les entrées incorrectes
        std::cout << "Le nombre de joueurs doit etre entre 2 et 4 ! > ";
    }
    std::string nom;
    // Demande les noms des joueurs
    for (int i = 0; i < nbJoueurs; ++i) {
        std::cout << "Nom du joueur " << i + 1 << " > ";
        std::cin >> nom;
        if(auto it=std::ranges::find_if(m_players,[&nom](const Player* p)
        {
            return p->getName()==nom;
        });it!=m_players.end())
        {
            std::cout<<"Nom deja utilise, veuillez choisir un autre nom"<<std::endl;
            i--;
            continue;
        }
        m_players.push_back(new Player(nom));
    }

    // Mélange aléatoire de l'ordre des joueurs
    std::random_device rd;  // Génère une graine aléatoire
    std::mt19937 g(rd());   // Générateur Mersenne Twister
    std::ranges::shuffle(m_players.begin(),m_players.end(), g);

    spaceV(3);

    std::cout<<"------------------- Configuration du Plateau -----------------------\n";
    std::vector<std::string> royaume;
    royaume.insert(royaume.end(),BaseBoard.begin(),BaseBoard.end());
    royaume.insert(royaume.end(),bonus.begin(),bonus.end());

    int choix;

    std::cout << "\n[1] Choisir les cartes du royaume\n";
    std::cout << "[2] Utiliser un set pas defaut\n";
    std::cout << "Votre choix > ";

    while(true)
    {
        if(!(std::cin>>choix)){
            std::cin.clear(); // Efface les erreurs
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore les entrées incorrectes
            std::cout << "Entree invalide, vous avez le choix en l'option 1 et 2 ! > ";
            continue;
        }
        if(choix==1)
        {
            //creation du plateau de jeu
            m_plateau = new Plateau(nbJoueurs);
            std::vector<std::string> reserve=choisirDixElements(royaume);
            m_plateau->built(reserve);
            break;
        }
        if(choix==2)
        {
            //creation du plateau de jeu
            m_plateau = new Plateau(nbJoueurs);
            m_plateau->built();
            break;
        }
        std::cout << "Entree invalide, vous avez le choix en l'option 1 et 2 ! > ";
    }


    std::cout << "\nPreparation du plateau...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Pause pour simuler le chargement

    std::cout << "\n-- Les cartes du royaume sont pretes !!! --\n";

    spaceV(2);
    std::cout << "\n----------------- Resume de la partie -----------------\n";
    std::cout << "Nombre de joueurs : " << nbJoueurs << std::endl;
    std::cout << "Ordre des joueurs : ";
    for (const auto& joueur : m_players) {
        std::cout << joueur->getName() << " ";
    }
    std::cout << "\nCartes du royaume : ";
    for (const auto& carte : m_plateau->getReserve()) {
        if(auto k=dynamic_cast<KingdomCard*>(carte.second.getCard()))
        {
            std::cout << k->getNom() << " ";
        }
    }
    std::cout << std::endl;

    appuyerPourContinuer();


    std::cin.ignore();
}
//pour les test
void Jeux::initGame(std::string const&nom1, std::string const&nom2)
{
    m_players.push_back(new Player(nom1));
    m_players.push_back(new Player(nom2));
    m_plateau = new Plateau(2);
    m_plateau->built();
}


/**
 * Lance une partie de Dominion
 */
void Jeux::playGame(){
    clearTerminal();
    DistributeCards();
    while(!m_plateau->isEmpty())
    {
        Player* player = m_players.at(actifIndex);
        setPlayer(player);
        actionPhase(player);
        buyPhase(player);
        endTurn(player);
        if(m_plateau->isEmpty()) {
            break;
        }
    }
    endGame();
}

void Jeux::endGame()
{
    //calcul des point bonus pour les cartes JARDINS
    for(auto player:m_players)
    {
        player->defausseAll();
        auto it=std::ranges::find_if(player->getDefausse().begin(),player->getDefausse().end(),[](const Card* c)
        {
            return c->getNom()=="JARDINS";
        });
        if(it!=player->getDefausse().end())
        {
            auto k=dynamic_cast<KingdomCard*>(*it);
            k->action(*this);
        }
    }
    //affichage des scores
    clearTerminal();
    afficheClassement();

}

void Jeux::afficheClassement() const {

    spaceV(2);
    std::vector<Player*> sortedPlayers = m_players; // Copie des joueurs pour ne pas modifier l'ordre original

    // Trie les joueurs par points décroissants
    std::ranges::sort(sortedPlayers.begin(), sortedPlayers.end(), [](const Player* a, const Player* b) {
        return a->getPoints() > b->getPoints(); // Trie par points décroissants
    });

    std::cout <<PURPLE<<spaceH(15)<< "-----------------------CLASSEMENT-----------------------" <<RESET<< std::endl;

    int rank = 1; // Classement initial
    for (auto player : sortedPlayers) {
        std::cout <<spaceH(15) << rank << " - " << player->getName() << " (" << player->getPoints() << " points)" << std::endl;
        ++rank;
    }
}

/**
 * Distribue les cartes de departs aux joueurs
 */
void Jeux::DistributeCards()
{
    std::vector<Card*> deck;
    for(auto i=0;i<10;i++)
    {
        if(i<7)
        {
            deck.push_back(new TreasureCard("CUIVRE"));

        }
        else
        {
            deck.push_back(new VictoryCard("DOMAINE"));
        }
    }
    for (auto* player : m_players)
    {
        //attribution du deck de départ
        player->setDeck(deck);
        //mélange du deck de départ
        player->shuffle();
        //pioche de 5 cartes
        player->pioche(5);

    }
    m_plateau->updateReserveByName("CUIVRE",7*static_cast<int>(m_players.size()));
}
/**
 * Affiche l'ecran de jeu du joueur (plateau,main,infos...)
 * @param player
 */
void Jeux::playerBoard(const Player* player) const {
    clearTerminal();
    m_plateau->affichage();
    player->afficheHand();
    player->info();
}


void Jeux::actionPhase(Player* player)
{

    playerBoard(player);
    phaseMessage(ACTION);
    bool exit(false);
    while(player->canPlayAction()&&!exit)
    {
        GameCommand::getInput(*this,ACTION,&exit);
    }
    std::cout<<"Fin de la phase d'action, passage a la phase d'achat"<<std::endl;
    appuyerPourContinuer();

}

void Jeux::buyPhase(Player* player)
{
    playerBoard(player);
    phaseMessage(BUY);
    bool exit(false);
    while(player->canBuy()&&!exit)
    {
        GameCommand::getInput(*this,BUY,&exit);
    }
    std::cout<<"Fin de la phase d'achat, le prochain joueur est "<<m_players[(actifIndex + 1) % m_players.size()]->getName()<<std::endl;
    appuyerPourContinuer();

}
void Jeux::phaseMessage(Phase phase)
{
    if(phase==ACTION)
    {
        std::cout << BLUE << BLINK
                  << "Jouez des cartes actions (-> play [nomCarte] )"
                  << RESET << std::endl;
    }
    else if(phase==BUY)
    {
        std::cout << BLUE << BLINK
                 << "Achetez des cartes (-> buy [nomCarte] ou sell [nomCarte])"
                 << RESET << std::endl;
    }
    else
        std::cout<<"Phase inconnue"<<std::endl;

    std::cout<<std::endl;
}

/**
 * Gere la fin d'un tour
 * @param player
 */
void Jeux::endTurn(Player* player)
{
    actifIndex = (actifIndex + 1) % m_players.size();
    player->defausseAll();
    player->pioche(5);

}




void Jeux::setPlayer(Player* player)
{
    player->setActions(1);
    player->setBuys(1);
    player->setCoins(0);
}

Plateau& Jeux::getPlateau() const
{
    return *m_plateau;
}


std::vector<Player*>Jeux::getPlayers()const
{
    return m_players;
}

Player& Jeux::getActifPlayer() const
{
    return *m_players.at(actifIndex);
}

size_t Jeux::getActifIndex() const
{
    return actifIndex;
}

std::vector<std::string> choisirDixElements(const std::vector<std::string>& options) {
    if (options.size() < 10) {
        throw std::runtime_error("Le vecteur contient moins de 10 éléments. Impossible de choisir.");
    }

    std::vector<std::string> choix;
    std::set<int> indicesChoisis; // Pour éviter les doublons
    int choixUtilisateur = -1;

    std::cout << "Veuillez choisir 10 elements parmi les cartes suivantes : \n";
    for (size_t i = 0; i < options.size(); ++i) {
        std::cout << "["<<i + 1 << "] " << options[i]<<std::endl ; // Affichage avec index (1-based)
    }

    while (choix.size() < 10) {
        std::cout << "\nChoix " << choix.size() + 1 << " > ";
        std::cin >> choixUtilisateur;
        if (std::cin.fail()) {
            std::cin.clear(); // Réinitialise l'état d'erreur
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore la ligne courante
            std::cout << "Entrée invalide. Veuillez entrer un numéro valide.\n";
            continue;
        }

        // Ajuster l'index de 1-based à 0-based
        choixUtilisateur -= 1;

        if (choixUtilisateur < 0 || choixUtilisateur >= static_cast<int>(options.size())) {
            std::cout << "Numéro invalide. Veuillez choisir un numéro entre 1 et " << options.size() << ".\n";
        } else if (indicesChoisis.find(choixUtilisateur) != indicesChoisis.end()) {
            std::cout << "Vous avez déjà choisi cet élément. Veuillez en choisir un autre.\n";
        } else {
            choix.push_back(options[choixUtilisateur]);
            indicesChoisis.insert(choixUtilisateur);
        }
    }
    return choix;
}
