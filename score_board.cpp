#include "score_board.h"
#include "additionalshapedecorator.h"

Score_board::Score_board(){}

Score_board::Score_board(const sf::Vector2f & pos, sf::Font & font, sf::Texture & metal_, const std::string &nick)
{
    unsigned int size = 20;
    auto space_beetwen = size*5/3;
    for(int i = 1 ; i <= 6 ; i++)
    {
        for(int j = 1 ; j < 20 ; j++)
        {

                sextangle s(size);
                s.setPosition(pos.x+space_beetwen*i , pos.y+space_beetwen*j);
                s.setFillColor(sf::Color(230,255,255));
                vec2.emplace_back(std::make_unique <sextangle> (s));

        }
    }
    for(int i = 1 ; i <= 6 ; i++)
    {
        std::unique_ptr <sextangle> s = std::make_unique <sextangle>(size);
        s->setPosition(pos.x+space_beetwen*i , pos.y);
        s->setFillColor(sf::Color::White);
        s->setOutlineColor(sf::Color::Cyan);
        s->setOutlineThickness(1);
        s->rotate(30);
        auto s1 = std::make_unique<AdditionalShapeDecorator>(std::move(s),i);
        static_cast<AdditionalShapeDecorator*>(s1.get())->setposition(s1->getPosition());
        vec2.emplace_back(std::move(s1));
    }
    for(int j = 1 ; j < 20 ; j++)
    {

        sextangle s(size);
        s.setPosition(pos.x , pos.y+space_beetwen*j);
        s.setTexture(&metal_);
        s.setOutlineColor(sf::Color::Cyan);
        s.setOutlineThickness(1);

        sf::Text text_;
        text_.setFont(font);
        text_.setCharacterSize(18);
        text_.setString(std::to_string(j-1));
        if(j-1 < 10)
            text_.setPosition({s.getPosition().x-6 , s.getPosition().y-11});
        else
            text_.setPosition({s.getPosition().x-14 , s.getPosition().y-12});

        text_.setFillColor(sf::Color::Black);

        num_list.emplace_back(text_);
        vec2.emplace_back(std::make_unique <sextangle> (s));

    }
    background = sf::RectangleShape({static_cast<float>(space_beetwen*5),static_cast<float>(space_beetwen*18)});
    background.setPosition(vec2[0]->getPosition());
    background.setFillColor(sf::Color(210,255,255));
    sf::Text text_;
    text_.setFont(font);
    text_.setCharacterSize(size*4/3);
    text_.setString(nick);
    text_.setPosition({pos.x,pos.y-size*3});
    text_.setFillColor(sf::Color::White);
    caption = text_;
    for(unsigned int i = 0 ; i <=5 ; i++)
    {
        sextangle s(size/2);
        s.setPosition(vec2[19*i]->getPosition());
        switch (i) {
        case 0:
            s.setFillColor(sf::Color::Blue);
            break;
        case 1:
            s.setFillColor(sf::Color::Red);
            break;
        case 2:
            s.setFillColor(sf::Color::Yellow);
            break;
        case 3:
            s.setFillColor(sf::Color::Magenta);
            break;
        case 4:
            s.setFillColor(sf::Color(255, 165, 0));
            break;
        case 5:
            s.setFillColor(sf::Color::Green);
            break;
        default:
            break;
        }
        Points_counters.emplace_back(std::make_unique <sextangle> (s));
    }
}

void Score_board::ilustrate_possible_points(std::map < unsigned int , unsigned int > & possible_Points, std::map<unsigned int, unsigned int> Player_Points)
{
    for(unsigned int i = 1 ; i <= 6 ; i++)
    {
        if(possible_Points[i] != 0)
        {
            if(Player_Points[i]+possible_Points[i] < 19)
            {
                for(unsigned int j = (i-1)*19+Player_Points[i] ; j <= (i-1)*19+Player_Points[i]+possible_Points[i] ; j++)
                    vec2[j]->setFillColor(sf::Color(220,220,220));
            }
            else
            {
                for(unsigned int j = (i-1)*19+Player_Points[i] ; j <= (i-1)*19+18 ; j++)
                    vec2[j]->setFillColor(sf::Color(220,220,220));
            }
        }

    }
}

void Score_board::erase_ilustration()
{
    for(unsigned int i = 0 ; i < 114 ; i++)
        vec2[i]->setFillColor(sf::Color(230,255,255));
}

void Score_board::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(background);

    std::for_each(vec2.begin(),vec2.end(),[&states, &target](const std::unique_ptr <sextangle> & s ){target.draw(*s,states);});

    std::for_each(num_list.begin(),num_list.end(),[&states, &target](const sf::Text & s ){target.draw(s,states);});

    target.draw(caption);

    std::for_each(Points_counters.begin(),Points_counters.end(),[&states, &target](const std::unique_ptr <sextangle> & s ){target.draw(*s,states);});
}

void Score_board::move_(const unsigned int & num, const float & down)
{
    Points_counters.at(num-1)->move({0,down});
}
bool Score_board::stop_animation(const unsigned int & num , const unsigned int & destination)
{
    if(vec2[(num-1)*19+destination]->vec_on({static_cast<int>(Points_counters[num-1]->getPosition().x),static_cast<int>(Points_counters[num-1]->getPosition().y)}))
    {
        Points_counters[num-1]->setPosition(vec2[(num-1)*19+destination]->getPosition());
        return true;
    }
    else
        return false;
}
