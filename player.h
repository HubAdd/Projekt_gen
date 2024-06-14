#ifndef PLAYER_H
#define PLAYER_H

#include <map>
#include <string>
#include <vector>

//klasa przechowująca informacje o graczu

class Player
{
public:
    Player();

    //konstruktor przyjmuje nick oraz unikalny numer gracza
    Player(const std::string & nick_, const unsigned int & num);

    //zwraca typy znaczków na tokenie o podanym indeksie
    std::pair <unsigned int, unsigned int> get_Token_id(const unsigned int & num);

    //zwraca wektor pkt gracza (używany w moencie wywałaniania zwyciężcy)
    std::vector <unsigned int> pkt();

    //zwraca nick gracza
    std::string nick_();

    //dekralacja przyjaźni laid_Token, dzieki temu, tylko ta klasa może użyć metod prywatnych change i add_point
    friend class laid_Token;

private:
    //zmienia tokeny gracza
    void change (const std::vector <std::pair<unsigned int, unsigned int>> & vec);

    //dodaje punkty graczowi
    void add_point (std::map <unsigned int, unsigned int> & Points_);

    //nick gracza
    std::string nick;

    //unikalny numer gracza
    unsigned int Player_number;

    //wektor typów znaczków na tokenach
    std::vector <std::pair<unsigned int, unsigned int>> Tokens_id;

    //pkt gracza
    std::map <unsigned int, unsigned int> Points;

    //mapa, która zwraca czy dla danego typu, gracz zdobył juz 18 pkt (potrzebne jest by unikać wielokrotnego wywoływania funkcji geniusz
    std::map <unsigned int, bool> Is_Genious;
};

#endif // PLAYER_H
