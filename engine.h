#ifndef ENGINE_H
#define ENGINE_H

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Event.hpp"
#include "button.h"
#include "game_board.h"
#include "menu.h"
#include "player.h"
#include "score_board.h"
#include "setings.h"
#include "token.h"
#include <memory>
#include <round_counter.h>

//Główna klasa która odpowiada za przebieg rozgrywki oraz przechowuje wszystkie obiekty
class Engine : public sf::Drawable
{
public:

    //konstruktor
    Engine(){}

    //pętla główna
    void main_game_loop();

    //klasa odpowiadająca za metodę laid (położenie tokena)
    friend class laid_Token;

    //klasa odpowiadająca za przechowywanie licznika rundy i zmieniania rundy na następną
    friend class Round_Counter;

    //klasa, która jako jedyna ma dostęp do resetowania gry
    friend class setings;

    //metoda z menu która wyświetla menu na oknie należącym do Engine
    friend void Menu::gen_menu(sf::RenderWindow &Window , std::vector<bool> &controls_ , sf::Event & event, Texture_pack &t);

protected:

    //nadpisana metoda draw, rysujaca wszystkie obiekty które wchodzą w skład kompozycjii Engine
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    //metoda która pozycjonuje i ustawia do pionu tokeny
    void align_tokens();

    //metoda wykonywana w każdej pętli, rysuje
    void gen();

    //po wyjściu z menu metoda generuje obiekty rozgrywki i usuwa obiekt menu
    void initiate_game(const std::vector<std::string> &nicks_);

    //po wyjściu z gry do menu, metoda ta usuwa wszystkie obiekty z rozgrywki
    void reset_game();

    //metoda prywatna, do której dostęp ma tylko klasa round counter, która inkrementuje wartość rundy
    void next_round();

    //metoda prywatna wywołana gdy brakuje miejsca na planszy (bool game_board::no_space == true)
    void EndGame();

    //wskaźniki do wszystkich obiektów zawięrających się w Engine
    //wskaźniki, które są czyszczone w momencie wywołania metody reset_game
    std::unique_ptr <game_board> board;

    //wektor Tokenów
    std::unique_ptr <std::vector <std::unique_ptr<Token>>> vectok ;

    //klasa Player i Scoreboard są w obiekcie map, by można było się do nich łatwo odwołać korzystając z numeru rundy, bez konieczności brania pod uwage indeksu 0, jak w przypadku wektora
    std::unique_ptr <std::map <unsigned int, Player>> players_map;
    std::unique_ptr <std::map <unsigned int, Score_board>> score_boards;

    std::unique_ptr <Round_Counter> round_counter;
    std::unique_ptr <sf::RectangleShape> screen;
    std::unique_ptr <setings> seting;

    //wskaźnik do napisu Ingenious, wywoływany w momencie gdy dany gracz osiągnie Ingenious (bedzie miał 18 pkt w jakimś kolorze) i czyszczony w momencie zakończenia tej animacjii
    std::unique_ptr <sf::Text> Ingenious;

    //wzkaźnik do menu, czyszczony w Engine::initiate_game, inicjowany w 1 pętli kontroli
    std::unique_ptr <Menu> menu;

    //obiekt dźwięku wykorzystywany w momencie położenia tokenu i Ingeniousa
    std::unique_ptr <sf::Sound> sound;

    //obiekt dźwięku wykorzystywany w momencie włączenia muzyki
    std::unique_ptr <sf::Sound> game_theme;

    //obiekt event obsługujący zdarzenia (np close window)
    sf::Event event;

    //wczytane tekstury, czcionki i dźwięki
    Texture_pack t;

    //główne okno
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(1920, 1080), "InGenious" , sf::Style::Default);

    //pętla kontroli, wchodząc w kolejne działania kolejne elementy pętli kotrolii zmieniają się na true, pierwsze dwa odpowiadają za menu, kolejny za rozgrywkę a ostatnie dwa za pętle wchodzące w skład laid_token
    std::vector <bool> controls = {false,false,false,false,false};
};

#endif // ENGINE_H
