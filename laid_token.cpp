#include "laid_token.h"
#include "additionalshapedecorator.h"
#include "round_counter.h"
#include <chrono>
#include <cmath>
#include <thread>

laid_Token::laid_Token() {}
void laid_Token::laid (Engine & E)
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        auto t = std::find_if(E.vectok->begin(),E.vectok->end(),[ &E](std::unique_ptr<Token> & t){return t->mouse_on_token(E.window);});
        if(t != E.vectok->end())
        {
            E.controls[E.controls.size()-2] = true;
            while(E.controls[E.controls.size()-2] == true)
            {
                E.gen();
                t->get()->move(E.window);
                E.window.draw(*t->get());
                E.window.display();
                if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
                {
                    t->get()->rotate();
                    std::this_thread::sleep_for(std::chrono::milliseconds(200));
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
                {
                    E.controls[E.controls.size()-2] = false;
                    E.align_tokens();
                }
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    auto it = std::find_if(E.board->vec1.begin(),E.board->vec1.end(),[&E](std::unique_ptr<sextangle> & s){return s->mouse_on(E.window);});
                    if(it != E.board->vec1.end() and it->get()->getFillColor() == sf::Color::White)
                    {
                        auto it1 = std::find_if(E.board->vec1.begin(),E.board->vec1.end(),[ &t](std::unique_ptr<sextangle> & s)
                        {
                            if(s->getFillColor() == sf::Color::White)
                            {
                                return s->vec_on({static_cast<int>(t->get()->token_pair.second->getPosition().x),static_cast<int>(t->get()->token_pair.second->getPosition().y)});
                            }
                            else
                            {
                                return false;
                            }
                        });
                        if(it1 != E.board->vec1.end())
                        {
                            t->get()->align(it->get()->getPosition());
                            it->get()->setOutlineColor(t->get()->get_Color().first);
                            it->get()->setOutlineThickness(5);
                            it1->get()->setOutlineColor(t->get()->get_Color().second);
                            it1->get()->setOutlineThickness(5);
                            std::map <unsigned int, unsigned int> Points_;
                            {

                                //funkcja do obracania wektora
                                auto rotateVector = [](const sf::Vector2f & vec, double angleDegrees) {
                                    double angleRadians = angleDegrees * M_PI / 180.0;
                                    double cosAngle = std::cos(angleRadians);
                                    double sinAngle = std::sin(angleRadians);

                                    sf::Vector2f rotatedVec;
                                    rotatedVec.x = vec.x * cosAngle - vec.y * sinAngle;
                                    rotatedVec.y = vec.x * sinAngle + vec.y * cosAngle;

                                    return rotatedVec;
                                };

                                //wektor ktory bedzie obracany i przedluzany
                                auto z = sf::Vector2f({0,static_cast<float>(t->get()->token_pair.first->h_()*2.05)});

                                // funkcja do szukania szesciokatow dookola danej czesci tokena
                                auto finding_sextangle_that_is_the_same_color_as_this_token = [&rotateVector, &z, &it1, &E, &t, &it, &Points_](std::unique_ptr<sextangle> & tokenpair_one_or_two){

                                //kazda iteracja (i) to kolejna strona szesciokata po ktorej beda szukane szesciokaty w tym samym kolorze
                                for(int i = 0 ; i <= 5 ; i++)
                                {

                                    //y sluzy do wydluzania wektora na ktorym szukamy
                                    int y = 1;
                                    auto vec = rotateVector(z,60*i);

                                    //*iter szesciokat ktory bedziemy sprawdzac
                                    auto iter = std::find_if(E.board->vec1.begin(),E.board->vec1.end(),[&vec, &y, &tokenpair_one_or_two](std::unique_ptr<sextangle> & s){return s->vec_on({static_cast<int>(tokenpair_one_or_two->getPosition().x+y*vec.x),static_cast<int>(tokenpair_one_or_two->getPosition().y+y*vec.y)});}) ;

                                    //w petli sprawdzamy czy na szesciokacie jest polozony jakis token (ma black kolor) lub zostanie na nim polozony ten wlasnie token (iter == it)
                                    while(iter != E.board->vec1.end() and (iter->get()->getFillColor() == sf::Color::Black || (iter == it || iter == it1)))
                                    {
                                        if(iter == it || iter == it1)
                                        {
                                                //jesli szesciakaty zawierajace sie w tokenie nie sa takie same to petla jest przerwana
                                            if(static_cast<AdditionalShapeDecorator*>(t->get()->token_pair.first.get())->get_type_() != static_cast<AdditionalShapeDecorator*>(t->get()->token_pair.second.get())->get_type_())
                                                break;
                                        }
                                        if(iter->get()->getFillColor() == sf::Color::Black)
                                        {
                                            //jesli nie zgadza sie kolor to nie ma sensu dalej przeprowadzac danej petli
                                        if(static_cast<AdditionalShapeDecorator*>(iter->get())->get_type_() != static_cast<AdditionalShapeDecorator*>(tokenpair_one_or_two.get())->get_type_())
                                            break;
                                        iter->get()->setOutlineColor(static_cast<AdditionalShapeDecorator*>(tokenpair_one_or_two.get())->get_color_());
                                        iter->get()->setOutlineThickness(5);
                                        Points_[static_cast<AdditionalShapeDecorator*>(tokenpair_one_or_two.get())->get_type_()]++;
                                        }
                                        else {
                                            break;
                                        }
                                        y++;
                                        iter = std::find_if(E.board->vec1.begin(),E.board->vec1.end(),[&vec, &y, &tokenpair_one_or_two](std::unique_ptr<sextangle> & s){return s->vec_on({static_cast<int>(tokenpair_one_or_two->getPosition().x+y*vec.x),static_cast<int>(tokenpair_one_or_two->getPosition().y+y*vec.y)});}) ;

                                    }

                                }
                                };

                                finding_sextangle_that_is_the_same_color_as_this_token(t->get()->token_pair.first);
                                finding_sextangle_that_is_the_same_color_as_this_token(t->get()->token_pair.second);
                                (*E.score_boards)[E.round_counter->get_round()].ilustrate_possible_points(Points_ , E.players_map->at(E.round_counter->get_round()).Points);
                            }

                            E.controls[E.controls.size()-1] = true;
                            while(E.controls[E.controls.size()-1] == true)
                            {
                                E.gen();
                                for(const auto & x : E.board->vec1)
                                {
                                    if(x->getOutlineThickness() == 5)
                                        E.window.draw(*x);
                                }
                                E.window.draw(*t->get());
                                E.window.display();
                                if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
                                {
                                    E.controls[E.controls.size()-1] = false;
                                    E.board->reset_lines();
                                    (*E.score_boards)[E.round_counter->get_round()].erase_ilustration();

                                }
                                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
                                {
                                    //Dźwięk
                                    E.sound->setBuffer(E.t.boop);

                                    // Odtwórz dźwięk
                                    E.sound->play();

                                    //wymazanie linii ktore pokazywaly ciąg tokenów na planszy
                                    E.board->reset_lines();

                                    //wymazanie ścieżek ktore pokazywaly ciąg tokenów na scorebordzie
                                    (*E.score_boards)[E.round_counter->get_round()].erase_ilustration();

                                    //ozdabianie szesciokatow na planszy, na ktorych polozono token
                                    auto s = std::move(*it);
                                    auto s1 = std::move(*it1);
                                    *it = std::make_unique<AdditionalShapeDecorator>(std::move(s),t->get()->get_types().first);
                                    *it1 = std::make_unique<AdditionalShapeDecorator>(std::move(s1),t->get()->get_types().second);

                                    //wyrównywanie znaczkow z szesciokatami na ktorych sa
                                    static_cast<AdditionalShapeDecorator*>(it->get())->setposition(it->get()->getPosition());
                                    static_cast<AdditionalShapeDecorator*>(it1->get())->setposition(it1->get()->getPosition());

                                    //zakonczenie petli zwiazanych z kladzeniem tokena
                                    E.controls[E.controls.size()-1] = false;
                                    E.controls[E.controls.size()-2] = false;

                                    //losowanie nowych znaczkow na tokenie
                                    t->get()->token_switch( (rand()%6)+1 , (rand()%6)+1 );

                                    //dodawanie punktow graczowi
                                    E.players_map->at(E.round_counter->get_round()).add_point(Points_);

                                    //wyrownanie tokenow
                                    E.align_tokens();

                                    //zegar bedzie potrzebny do animacjii na scoreboardzie
                                    sf::Clock clock;

                                    //bool ktory sprawdza czy ktorys z graczy osiagnal 18 pkt w ktoryms z kolorow
                                    bool InGenious = std::any_of(E.players_map->at(E.round_counter->get_round()).Points.begin() , E.players_map->at(E.round_counter->get_round()).Points.end() , [&E](const std::pair <unsigned int , unsigned int> & p)
                                    {
                                        //bool ktory sprawdza czy gracz juz osiagnal wczesniej geniusza z tego koloru
                                        bool was_Genious = E.players_map->at(E.round_counter->get_round()).Is_Genious[p.first];
                                        if(!was_Genious and p.second == 18)
                                        {
                                            E.players_map->at(E.round_counter->get_round()).Is_Genious[p.first] = true;
                                            return true;
                                        }
                                        else
                                            return false;
                                    });

                                    if(InGenious)
                                    {
                                        E.Ingenious = std::make_unique <sf::Text> ();
                                        E.Ingenious->setFont(E.t.font);
                                        E.Ingenious->setString("InGenious");
                                        E.Ingenious->setCharacterSize(200);
                                        E.Ingenious->setPosition(E.window.getSize().x/2-400,E.window.getSize().y-400);
                                        E.Ingenious->setFillColor(sf::Color::Black);

                                        //Dźwięk
                                        E.sound->setBuffer(E.t.genius);

                                        // Odtwórz dźwięk
                                        E.sound->play();
                                    }
                                    for(unsigned int num = 1 ; num <= 6 ; num++)
                                    {
                                        while(!E.score_boards->at(E.round_counter->get_round()).stop_animation(num , E.players_map->at(E.round_counter->get_round()).Points[num]))
                                        {
                                            auto elapsed = clock.restart();
                                            E.score_boards->at(E.round_counter->get_round()).move_(num,100*elapsed.asSeconds());
                                            E.gen();
                                            if(InGenious)
                                            {
                                                E.window.draw(*E.Ingenious.get());
                                                E.Ingenious->setFillColor(sf::Color(rand()%255,rand()%255,rand()%255));
                                            }
                                            E.window.display();

                                        }
                                    }
                                    if(InGenious)
                                    {
                                        E.gen();
                                        E.window.draw(*E.Ingenious.get());
                                        E.window.display();
                                        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                                        E.Ingenious.reset();
                                    }
                                    else
                                    {
                                        E.gen();
                                        E.window.display();
                                        std::this_thread::sleep_for(std::chrono::milliseconds(500));
                                    }


                                    E.players_map->at(E.round_counter->get_round()).change({E.vectok->at(0).get()->get_types(),E.vectok->at(1).get()->get_types(),E.vectok->at(2).get()->get_types(),E.vectok->at(3).get()->get_types(),E.vectok->at(4).get()->get_types(),E.vectok->at(5).get()->get_types()});
                                    if(!InGenious)
                                        E.next_round();
                                    E.align_tokens();
                                    if(E.board->no_space())
                                    {
                                        E.EndGame();
                                    }
                                        //E.controls[2]=false;

                                }

                            }

                        }

                    }



                }
            }

        }
    }


}



