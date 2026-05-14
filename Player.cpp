#include "Player.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <random>
#include "TreasureCard.h"
#include "VictoryCard.h"
#include "KingdomCard.h"
#include "Plateau.h"
#include "Reserve.h"
#include "Jeux.h"

/**
 * Constructeur de Player
 */

int Player::defaultId=1;

Player::Player(std::string const& name) : m_name(normalize(name)), m_actions(0), m_buys(0), m_coins(0), m_points(3)
{}
Player::Player():m_name(normalize("player"+std::to_string(defaultId))),m_actions(0), m_buys(0), m_coins(0), m_points(3){}


Player::~Player() {
    for (auto* card : m_deck) {
        delete card;
    }
    for (auto* card : m_hand) {
        delete card;
    }
    for (auto* card : m_defausse) {
        delete card;
    }
    for (auto* card : m_played) {
        delete card;
    }
    m_deck.clear();
    m_hand.clear();
    m_defausse.clear();
    m_played.clear();
}

void Player::pioche(int x) {
    for (int i = 0; i < x; i++) {
        if (m_deck.empty()) {
            if (m_defausse.empty()) {
                break;
            }
            m_deck = std::move(m_defausse);  // Déplace les cartes de defausse vers deck
            m_defausse.clear();
            shuffle();
        }
        m_hand.push_back(m_deck.back()); // Déplace la carte de deck vers hand
        m_deck.pop_back();
    }
}

void Player::afficheHand() const {
    constexpr int maxCartesParLigne = 5;  // Maximum de cartes par ligne
    const auto& main = m_hand; // Récupérer la main du joueur

    std::cout << "______________________________________ MAIN DE " << m_name<<
        " _____________________________________________" << std::endl;

    // Stockage temporaire des cartes avec leurs informations
    std::vector<std::tuple<std::string, int, std::string, std::string>> cartes;

    for (const auto& card : main) {
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

bool Player::playAction(const std::string& cardName, Jeux& jeux) {
    auto it = std::ranges::find_if(m_hand.begin(), m_hand.end(), [&cardName](const Card* card) {
        return card->getNom() == cardName;
    });
    if (it != m_hand.end()) {
        if(dynamic_cast<KingdomCard*>(*it) &&(*it)->getNom()!= "JARDINS")
        {
            auto *k=dynamic_cast<KingdomCard*>(*it);
            m_played.push_back(*it);
            m_hand.erase(it);
            AddAction(-1);
            k->action(jeux);
            return true;
        }
        if((*it)->getNom()=="JARDINS")
        {
            alert("Vous ne pouvez pas jouer cette carte");
            return false;
        }
    }
    alert("Cette carte n'est pas dans votre main" );
    return false;
}
void Player::defausseCard(std::vector<Card*>& array,int index) {
    if (index >= 0 && index < static_cast<int>(array.size())) {
        m_defausse.push_back(array[index]);
        array.erase(array.begin() + index);
    }
}
void Player::defausseAll() {
    m_defausse.insert(m_defausse.end(), std::make_move_iterator(m_hand.begin()), std::make_move_iterator(m_hand.end()));
    m_hand.clear();
    m_defausse.insert(m_defausse.end(), std::make_move_iterator(m_played.begin()), std::make_move_iterator(m_played.end()));
    m_played.clear();
}

bool Player::defausseFromHand(const std::string& cardName) {
    auto it = std::ranges::find_if(m_hand.begin(), m_hand.end(), [&cardName](const Card* card) {
        return card->getNom() == cardName;
    });
    if (it != m_hand.end()) {
        m_defausse.push_back(*it);
        m_hand.erase(it);
        notif( "La carte "+ (*it)->getNom()+" a ete place dans la defausse" );
        return true;
    }
    alert("cette carte n'est pas dans votre main ");
    return false;
}

void Player::info() const {

    std::cout << m_name << " " << m_points << " PV | "
              << m_actions << " Actions | " << m_buys << " Achats | "
              << m_coins << " Pieces |" << std::endl << std::endl;

}


bool Player::defausseArray(std::vector<Card*>& cards) {
    if (cards.empty()) {
        return false; // Rien à faire
    }
    m_defausse.insert(m_defausse.end(), std::make_move_iterator(cards.begin()), std::make_move_iterator(cards.end()));
    notif("les cartes ont ete place dans la defausse");
    cards.clear();
    return true;
}

bool Player::gainCard(const std::string& cardName, Plateau& p,int minCost,int maxCost) {
    auto& reserve = p.getReserve();
    std::string str = normalize(cardName);
    auto it = reserve.find(str);
    if (it != reserve.end()) {
        auto& res = it->second;
        auto* card = res.getCard();
        if (res.getTaille() > 0 && card->getCost() >= minCost && card->getCost() <= maxCost) {
            if (auto* kingdom = dynamic_cast<KingdomCard*>(card)) {
                m_defausse.push_back(new KingdomCard(*kingdom));
                p.updateReserveByName(str, 1);
                return true;
            }
            if (auto* treasure = dynamic_cast<TreasureCard*>(card)) {
                m_defausse.push_back(new TreasureCard(*treasure));
                p.updateReserveByName(str, 1);
                return true;
            }
            if (auto* victory = dynamic_cast<VictoryCard*>(card)) {
                m_defausse.push_back(new VictoryCard(*victory));
                AddPoint(victory->getVictory());
                p.updateReserveByName(str, 1);
                return true;
            }
        }
        alert("La carte n'est plus disponible ou ne remplie pas les conditions de selection");


    } else {
        alert("cette carte n'est pas presente dans le jeu");
    }
    return false;
}

Card* Player::drawCard() {
    if (m_deck.empty()) {
        if (m_defausse.empty()) {
            return nullptr;
        }
        m_deck = std::move(m_defausse);
        m_defausse.clear();
        shuffle();
    }
    auto* card =m_deck.back();
    m_deck.pop_back();
    return card;
}

void Player::trashCard(const Card* card) {
    delete card;
}

bool Player::buyCard(std::string const& cardName, Jeux const& j)
{

    Plateau &p=j.getPlateau();
    std::map<std::string, Reserve>& reserve = p.getReserve();
    auto it = reserve.find(normalize(cardName));
    if(it!=reserve.end())
    {
        if(it->second.getTaille()>0)
        {

            if(it->second.getCard()->getCost()<=this->getCoins())
            {
                if(auto* k=dynamic_cast<KingdomCard*>(it->second.getCard()))
                {
                    m_defausse.push_back(new KingdomCard(*k));
                    AddBuy(-1);
                    AddCoin(-k->getCost());
                    p.updateReserveByName(k->getNom(),1);
                    notif("Vous avez achete la carte "+k->getNom());
                    return true;

                }
                if(auto* t=dynamic_cast<TreasureCard*>(it->second.getCard()))
                {
                    m_defausse.push_back(new TreasureCard(*t));
                    AddBuy(-1);
                    AddCoin(-t->getCost());
                    p.updateReserveByName(t->getNom(),1);
                    notif("Vous avez achete la carte "+t->getNom());
                    return true;
                }
                if(auto* v=dynamic_cast<VictoryCard*>(it->second.getCard()))
                {
                    m_defausse.push_back(new VictoryCard(*v));
                    AddBuy(-1);
                    AddCoin(-v->getCost());
                    p.updateReserveByName(v->getNom(),1);
                    notif("Vous avez achete la carte "+v->getNom());
                    AddPoint(v->getVictory());
                    return true;
                }

            }
            alert("Vous n'avez pas assez de pieces pour acheter cette carte");
            return false;
        }
        alert("La carte n'est plus disponible");
    }
    alert("La carte n'existe pas");
    return false;
}
bool Player::moveCardFromDefausseToDeck(std::string const&cardName)
{
    auto it=std::ranges::find_if(m_defausse.begin(),m_defausse.end(),[&cardName](const Card* c)
    {
        return c->getNom()==cardName;
    });
    if(it!=m_defausse.end())
    {
        m_deck.push_back(*it);
        m_defausse.erase(it);
        notif("La carte "+cardName+" a ete deplacee de la defausse au deck");
        return true;
    }
    alert("La carte n'est pas dans la defausse");
    return false;
}

bool Player::stealCard(Card* card, std::vector<Card*>& fromCards) {
    auto it = std::ranges::find(fromCards.begin(), fromCards.end(), card);
    if (it != fromCards.end()) {
        fromCards.erase(it); // Supprime la carte des cartes révélées
        m_defausse.push_back(card); // Ajoute à la défausse
        std::cout << "Le joueur " << getName() << " a vole la carte : " << card->getNom() << std::endl;
        return true;
    }
    std::cout << "La carte " << card->getNom() << " n'a pas pu être volee." << std::endl;
    return false;
}

void Player::defausseDeck() {
    m_defausse.insert(m_defausse.end(), std::make_move_iterator(m_deck.begin()), std::make_move_iterator(m_deck.end()));
    m_deck.clear();
}

bool Player::trashCardFromHand(const std::string& cardName) {
    auto it = std::ranges::find_if(m_hand.begin(), m_hand.end(), [&cardName](const Card* card) {
        return card->getNom() == cardName;
    });
    if (it != m_hand.end()) {
        if(auto *v=dynamic_cast<VictoryCard*> (*it))
        {
            AddPoint(-v->getVictory());
        }
        delete *it;
        m_hand.erase(it);
        notif("la carte "+cardName+" a ete trashee");
        return true;
    }
    alert("cette carte n'est pas dans votre main ");
    return false;
}

bool Player::trashCardFromPlayed(std::string const& cardName)
{
    auto it = std::ranges::find_if(m_played.begin(), m_played.end(), [&cardName](const Card* card) {
        return card->getNom() == cardName;
    });
    if (it != m_played.end()) {
        if(auto *v=dynamic_cast<VictoryCard*> (*it))
        {
            AddPoint(-v->getVictory());
        }
        delete *it;
        m_played.erase(it);
        notif("la carte "+cardName+" a ete trashee");
        return true;
    }
    alert("cette carte n'est pas dans votre main ");
    return false;
}


bool Player::canPlayAction() {

    return std::ranges::any_of(m_hand.begin(),m_hand.end(),[this](Card *card)
    {
        return dynamic_cast<KingdomCard*>(card)&&m_actions>0;
    });
}

bool Player::canBuy()const
{
    return m_buys>0;
}

void Player::shuffle() {
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::ranges::shuffle(m_deck.begin(), m_deck.end(), engine);
}

void Player::AddPoint(int points) {
    m_points += points;
}

void Player::AddTreasure(int treasure) {
    m_coins += treasure;
}
void Player::AddAction(int action) {
    m_actions += action;
}
void Player::AddBuy(int buy) {
    m_buys += buy;
}
void Player::AddCoin(int coin) {
    m_coins += coin;
}

bool Player::sellCard(const std::string& cardName) {
    auto it =std::ranges::find_if(m_hand.begin(),m_hand.end(),[&cardName](const Card* c)
    {
        return c->getNom()==cardName;
    });
    if(it!=m_hand.end())
    {
        if(auto* treasure=dynamic_cast<TreasureCard*>(*it))
        {
            m_coins+=treasure->getTreasure();
            m_played.push_back(*it);
            m_hand.erase(it);
            notif("La carte "+treasure->getNom()+" a ete vendue");
            return true;
        }
    }
    alert( "Impossible de vendre cette carte." );
    return false;
}

bool Player::sellAllTreasure()
{
    auto it = m_hand.begin();
    if(it==m_hand.end())
    {
        alert("Vous n'avez pas de carte a vendre");
        return false;
    }
    while (it != m_hand.end()) {
        if (auto* t = dynamic_cast<TreasureCard*>(*it)) {
            m_coins += t->getTreasure();
            m_played.push_back(*it);
            it = m_hand.erase(it); // Utiliser l'itérateur retourné par erase
        } else {
            ++it;
        }
    }
    return true;
}

bool Player::ReactTo(int& index) const{
    for (size_t i = 0; i < m_hand.size(); ++i) {
        if (auto* kingdom = dynamic_cast<KingdomCard*>(m_hand[i])) {
            if (kingdom->isReaction()) {
                index = static_cast<int>(i);
                return true;
            }
        }
    }
    return false;
}

std::vector<Card*>& Player::getDeck() {
    return m_deck;
}

std::vector<Card*>& Player::getHand() {
    return m_hand;
}

std::vector<Card*>& Player::getDefausse() {
    return m_defausse;
}

std::vector<Card*>& Player::getPlayed() {
    return m_played;
}

int Player::getPoints() const {
    return m_points;
}

int Player::getCoins() const {
    return m_coins;
}

int Player::getActions() const {
    return m_actions;
}

std::string Player::getName() const {
    return m_name;
}

int Player::getBuys() const {
    return m_buys;
}

// setters
void Player::setDeck(std::vector<Card*> deck) {
    m_deck = std::move(deck);
}

void Player::setHand(std::vector<Card*> hand) {
    m_hand = std::move(hand);
}

void Player::setDefausse(std::vector<Card*> defausse) {
    m_defausse = std::move(defausse);
}

void Player::setPlayed(std::vector<Card*> played) {
    m_played = std::move(played);
}

void Player::setCoins(int coins) {
    m_coins = coins;
}

void Player::setActions(int actions) {
    m_actions = actions;
}

void Player::setBuys(int buys) {
    m_buys = buys;
}