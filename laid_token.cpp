#include "laid_token.h"
#include "additionalshapedecorator.h"
#include "sextangle_with_cords.h"
#include <chrono>
#include <cmath>
#include <iostream>
#include <thread>

laid_Token::laid_Token() {}
void laid_Token::laid (Engine & E, sf::RenderWindow &window)
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        auto t = std::find_if(E.vectok.begin(),E.vectok.end(),[ &window](std::unique_ptr<Token> & t){return t->mouse_on_token(window);});
        if(t != E.vectok.end())
        {
            std::vector <bool> control;
            control.emplace_back(bool(true));
            while(control[0] == true)
            {
                E.gen(control,window);
                t->get()->move(window);
                window.draw(*t->get());
                window.display();
                if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
                {
                    t->get()->rotate();
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
                {
                    control[0]=false;
                    E.align_tokens(window);
                }
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    auto it = std::find_if(E.board.vec1.begin(),E.board.vec1.end(),[ &window](std::unique_ptr<sextangle> & s){return s->mouse_on(window);});
                    if(it != E.board.vec1.end() and it->get()->getFillColor() == sf::Color::White)
                    {
                        auto it1 = std::find_if(E.board.vec1.begin(),E.board.vec1.end(),[ &t](std::unique_ptr<sextangle> & s){
                            if(s->getFillColor() == sf::Color::White)
                            {
                                return s->vec_on({static_cast<int>(t->get()->token_pair.second->getPosition().x),static_cast<int>(t->get()->token_pair.second->getPosition().y)});
                            }
                            else
                            {
                                return false;
                            }
                        });
                        if(it1 != E.board.vec1.end())
                        {
                            t->get()->align(it->get()->getPosition());
                            it->get()->setOutlineColor(t->get()->get_Color().first);
                            it->get()->setOutlineThickness(5);
                            it1->get()->setOutlineColor(t->get()->get_Color().second);
                            it1->get()->setOutlineThickness(5);

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

                                //kazda iteracja i to kolejna strona szesciokata po ktorej beda szukane szesciokaty w tym samym kolorze

                                for(int i = 0 ; i <= 5 ; i++)
                                {
                                    //y sluzy do wydluzania wektora na ktorym szukamy

                                    int y = 1;
                                    auto vec = rotateVector(z,60*i);

                                    //*iter szesciokat ktory bedziemy sprawdzac

                                    auto iter = std::find_if(E.board.vec1.begin(),E.board.vec1.end(),[&vec, &t, &y](std::unique_ptr<sextangle> & s){return s->vec_on({static_cast<int>(t->get()->token_pair.first->getPosition().x+y*vec.x),static_cast<int>(t->get()->token_pair.first->getPosition().y+y*vec.y)});}) ;
                                    //w petli sprawdzamy czy na szesciokacie jest polozony jakis token (ma black kolor) lub zostanie na nim polozony ten wlasnie token (iter == it)
                                        while(iter != E.board.vec1.end() and (iter->get()->getFillColor() == sf::Color::Black || iter == it1))
                                    {
                                        if(iter == it)
                                        {
                                                //jesli szesciakaty zawierajace sie w tokenie nie sa takie same to petla jest przerwana
                                            if(static_cast<AdditionalShapeDecorator*>(t->get()->token_pair.first.get())->get_type_() != static_cast<AdditionalShapeDecorator*>(t->get()->token_pair.second.get())->get_type_())
                                                break;
                                        }
                                        if(iter->get()->getFillColor() == sf::Color::Black)
                                        {
                                            //jesli nie zgadza sie kolor to nie ma sensu dalej przeprowadzac danej petli
                                        if(static_cast<AdditionalShapeDecorator*>(iter->get())->get_type_() != static_cast<AdditionalShapeDecorator*>(t->get()->token_pair.first.get())->get_type_())
                                            break;
                                        iter->get()->setOutlineColor(t->get()->get_Color().first);
                                        iter->get()->setOutlineThickness(5);
                                        }
                                        else {
                                            break;
                                        }
                                        y++;
                                        iter = std::find_if(E.board.vec1.begin(),E.board.vec1.end(),[&vec, &t, &y](std::unique_ptr<sextangle> & s){return s->vec_on({static_cast<int>(t->get()->token_pair.first->getPosition().x+y*vec.x),static_cast<int>(t->get()->token_pair.first->getPosition().y+y*vec.y)});}) ;
                                    }

                                }
                                //ta sama petla, tylko dla drugiej czesci tokena
                                for(int i = 0 ; i <= 5 ; i++)
                                {
                                    int y = 1;
                                    auto vec = rotateVector(z,60*i);
                                    auto iter = std::find_if(E.board.vec1.begin(),E.board.vec1.end(),[&vec, &t, &y](std::unique_ptr<sextangle> & s){return s->vec_on({static_cast<int>(t->get()->token_pair.second->getPosition().x+y*vec.x),static_cast<int>(t->get()->token_pair.second->getPosition().y+y*vec.y)});}) ;

                                    while(iter != E.board.vec1.end() and (iter->get()->getFillColor() == sf::Color::Black || iter == it))
                                    {
                                        if(iter == it)
                                        {
                                            if(static_cast<AdditionalShapeDecorator*>(t->get()->token_pair.first.get())->get_type_() != static_cast<AdditionalShapeDecorator*>(t->get()->token_pair.second.get())->get_type_())
                                                break;
                                        }
                                        if(iter->get()->getFillColor() == sf::Color::Black)
                                        {
                                        if(static_cast<AdditionalShapeDecorator*>(iter->get())->get_type_() != static_cast<AdditionalShapeDecorator*>(t->get()->token_pair.second.get())->get_type_())
                                            break;
                                        iter->get()->setOutlineColor(t->get()->get_Color().second);
                                        iter->get()->setOutlineThickness(5);
                                        }
                                        else
                                            break;
                                        y++;
                                        iter = std::find_if(E.board.vec1.begin(),E.board.vec1.end(),[&vec, &t, &y](std::unique_ptr<sextangle> & s){return s->vec_on({static_cast<int>(t->get()->token_pair.second->getPosition().x+y*vec.x),static_cast<int>(t->get()->token_pair.second->getPosition().y+y*vec.y)});}) ;
                                    }

                                }
                            }

                            control.emplace_back(bool(true));
                            while(control[1] == true)
                            {
                                E.gen(control,window);
                                for(const auto & x : E.board.vec1)
                                {
                                    if(x->getOutlineThickness() == 5)
                                        window.draw(*x);
                                }
                                window.draw(*t->get());
                                window.display();
                                if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
                                {
                                    control[1]=false;
                                    E.board.reset_lines();

                                }
                                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
                                {
                                    E.board.reset_lines();
                                    auto s = std::move(*it);
                                    auto s1 = std::move(*it1);
                                    *it = std::make_unique<AdditionalShapeDecorator>(std::move(s),t->get()->get_types().first);
                                    *it1 = std::make_unique<AdditionalShapeDecorator>(std::move(s1),t->get()->get_types().second);
                                    static_cast<AdditionalShapeDecorator*>(it->get())->setposition(it->get()->getPosition());
                                    static_cast<AdditionalShapeDecorator*>(it1->get())->setposition(it1->get()->getPosition());
                                    control[0]=false;
                                    control[1]=false;
                                    t->get()->token_switch( (rand()%6)+1 , (rand()%6)+1 );
                                    E.align_tokens(window);

                                }

                            }

                        }

                    }



                }
            }

        }
    }


}
