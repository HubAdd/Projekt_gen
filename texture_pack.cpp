#include "texture_pack.h"

Texture_pack::Texture_pack() {}

bool Texture_pack::load_textures()
{
    if(!Two_P.loadFromFile("Two_P.png"))
        return false;
    if(!Three_P.loadFromFile("Three_P.png"))
        return false;
    if(!Four_P.loadFromFile("Four_P.png"))
        return false;
    if(!Player_One.loadFromFile("Player_One.png"))
        return false;
    if(!Player_Two.loadFromFile("Player_Two.png"))
        return false;
    if(!Player_Three.loadFromFile("Player_Three.png"))
        return false;
    if(!Player_Four.loadFromFile("Player_Four.png"))
        return false;
    if(!screen_.loadFromFile("rec_button4.png"))
        return false;
    if(!main_screen.loadFromFile("rec_button3.png"))
        return false;
    if(!font.loadFromFile("Gothic.ttf"))
        return false;
    if(!font1.loadFromFile("Adamina-Regular.ttf"))
        return false;
    if(!metal.loadFromFile("Metalic.png"))
        return false;
    if(!gold.loadFromFile("gold.png"))
        return false;

    if(!icon.loadFromFile("Two_P.png"))
        return false;

    if(!boop.loadFromFile("boop.wav"))
        return false;
    if(!void_.loadFromFile("void.wav"))
        return false;
    if(!genius.loadFromFile("genius.wav"))
        return false;
    if(!party.loadFromFile("party.wav"))
        return false;
    if(!street.loadFromFile("street.wav"))
        return false;
    if(!guitar.loadFromFile("guitar.wav"))
        return false;
    if(!RIO.loadFromFile("RIO-REMIX.wav"))
        return false;

    //=================================================================================================================

    logo_animation = std::vector <sf::Texture>(89);
    if (!logo_animation[0].loadFromFile("Ingenious_logo/logo_projekt_89.png"))
        return false;
    if (!logo_animation[1].loadFromFile("Ingenious_logo/logo_projekt_1.png"))
        return false;
    if (!logo_animation[2].loadFromFile("Ingenious_logo/logo_projekt_2.png"))
        return false;
    if (!logo_animation[3].loadFromFile("Ingenious_logo/logo_projekt_3.png"))
        return false;
    if (!logo_animation[4].loadFromFile("Ingenious_logo/logo_projekt_4.png"))
        return false;
    if (!logo_animation[5].loadFromFile("Ingenious_logo/logo_projekt_5.png"))
        return false;
    if (!logo_animation[6].loadFromFile("Ingenious_logo/logo_projekt_6.png"))
        return false;
    if (!logo_animation[7].loadFromFile("Ingenious_logo/logo_projekt_7.png"))
        return false;
    if (!logo_animation[8].loadFromFile("Ingenious_logo/logo_projekt_8.png"))
        return false;
    if (!logo_animation[9].loadFromFile("Ingenious_logo/logo_projekt_9.png"))
        return false;
    if (!logo_animation[10].loadFromFile("Ingenious_logo/logo_projekt_10.png"))
        return false;
    if (!logo_animation[11].loadFromFile("Ingenious_logo/logo_projekt_11.png"))
        return false;
    if (!logo_animation[12].loadFromFile("Ingenious_logo/logo_projekt_12.png"))
        return false;
    if (!logo_animation[13].loadFromFile("Ingenious_logo/logo_projekt_13.png"))
        return false;
    if (!logo_animation[14].loadFromFile("Ingenious_logo/logo_projekt_14.png"))
        return false;
    if (!logo_animation[15].loadFromFile("Ingenious_logo/logo_projekt_15.png"))
        return false;
    if (!logo_animation[16].loadFromFile("Ingenious_logo/logo_projekt_16.png"))
        return false;
    if (!logo_animation[17].loadFromFile("Ingenious_logo/logo_projekt_17.png"))
        return false;
    if (!logo_animation[18].loadFromFile("Ingenious_logo/logo_projekt_18.png"))
        return false;
    if (!logo_animation[19].loadFromFile("Ingenious_logo/logo_projekt_19.png"))
        return false;
    if (!logo_animation[20].loadFromFile("Ingenious_logo/logo_projekt_20.png"))
        return false;
    if (!logo_animation[21].loadFromFile("Ingenious_logo/logo_projekt_21.png"))
        return false;
    if (!logo_animation[22].loadFromFile("Ingenious_logo/logo_projekt_22.png"))
        return false;
    if (!logo_animation[23].loadFromFile("Ingenious_logo/logo_projekt_23.png"))
        return false;
    if (!logo_animation[24].loadFromFile("Ingenious_logo/logo_projekt_24.png"))
        return false;
    if (!logo_animation[25].loadFromFile("Ingenious_logo/logo_projekt_25.png"))
        return false;
    if (!logo_animation[26].loadFromFile("Ingenious_logo/logo_projekt_26.png"))
        return false;
    if (!logo_animation[27].loadFromFile("Ingenious_logo/logo_projekt_27.png"))
        return false;
    if (!logo_animation[28].loadFromFile("Ingenious_logo/logo_projekt_28.png"))
        return false;
    if (!logo_animation[29].loadFromFile("Ingenious_logo/logo_projekt_29.png"))
        return false;
    if (!logo_animation[30].loadFromFile("Ingenious_logo/logo_projekt_30.png"))
        return false;
    if (!logo_animation[31].loadFromFile("Ingenious_logo/logo_projekt_31.png"))
        return false;
    if (!logo_animation[32].loadFromFile("Ingenious_logo/logo_projekt_32.png"))
        return false;
    if (!logo_animation[33].loadFromFile("Ingenious_logo/logo_projekt_33.png"))
        return false;
    if (!logo_animation[34].loadFromFile("Ingenious_logo/logo_projekt_34.png"))
        return false;
    if (!logo_animation[35].loadFromFile("Ingenious_logo/logo_projekt_35.png"))
        return false;
    if (!logo_animation[36].loadFromFile("Ingenious_logo/logo_projekt_36.png"))
        return false;
    if (!logo_animation[37].loadFromFile("Ingenious_logo/logo_projekt_37.png"))
        return false;
    if (!logo_animation[38].loadFromFile("Ingenious_logo/logo_projekt_38.png"))
        return false;
    if (!logo_animation[39].loadFromFile("Ingenious_logo/logo_projekt_39.png"))
        return false;
    if (!logo_animation[40].loadFromFile("Ingenious_logo/logo_projekt_40.png"))
        return false;
    if (!logo_animation[41].loadFromFile("Ingenious_logo/logo_projekt_41.png"))
        return false;
    if (!logo_animation[42].loadFromFile("Ingenious_logo/logo_projekt_42.png"))
        return false;
    if (!logo_animation[43].loadFromFile("Ingenious_logo/logo_projekt_43.png"))
        return false;
    if (!logo_animation[44].loadFromFile("Ingenious_logo/logo_projekt_44.png"))
        return false;
    if (!logo_animation[45].loadFromFile("Ingenious_logo/logo_projekt_45.png"))
        return false;
    if (!logo_animation[46].loadFromFile("Ingenious_logo/logo_projekt_46.png"))
        return false;
    if (!logo_animation[47].loadFromFile("Ingenious_logo/logo_projekt_47.png"))
        return false;
    if (!logo_animation[48].loadFromFile("Ingenious_logo/logo_projekt_48.png"))
        return false;
    if (!logo_animation[49].loadFromFile("Ingenious_logo/logo_projekt_49.png"))
        return false;
    if (!logo_animation[50].loadFromFile("Ingenious_logo/logo_projekt_50.png"))
        return false;
    if (!logo_animation[51].loadFromFile("Ingenious_logo/logo_projekt_51.png"))
        return false;
    if (!logo_animation[52].loadFromFile("Ingenious_logo/logo_projekt_52.png"))
        return false;
    if (!logo_animation[53].loadFromFile("Ingenious_logo/logo_projekt_53.png"))
        return false;
    if (!logo_animation[54].loadFromFile("Ingenious_logo/logo_projekt_54.png"))
        return false;
    if (!logo_animation[55].loadFromFile("Ingenious_logo/logo_projekt_55.png"))
        return false;
    if (!logo_animation[56].loadFromFile("Ingenious_logo/logo_projekt_56.png"))
        return false;
    if (!logo_animation[57].loadFromFile("Ingenious_logo/logo_projekt_57.png"))
        return false;
    if (!logo_animation[58].loadFromFile("Ingenious_logo/logo_projekt_58.png"))
        return false;
    if (!logo_animation[59].loadFromFile("Ingenious_logo/logo_projekt_59.png"))
        return false;
    if (!logo_animation[60].loadFromFile("Ingenious_logo/logo_projekt_60.png"))
        return false;
    if (!logo_animation[61].loadFromFile("Ingenious_logo/logo_projekt_61.png"))
        return false;
    if (!logo_animation[62].loadFromFile("Ingenious_logo/logo_projekt_62.png"))
        return false;
    if (!logo_animation[63].loadFromFile("Ingenious_logo/logo_projekt_63.png"))
        return false;
    if (!logo_animation[64].loadFromFile("Ingenious_logo/logo_projekt_64.png"))
        return false;
    if (!logo_animation[65].loadFromFile("Ingenious_logo/logo_projekt_65.png"))
        return false;
    if (!logo_animation[66].loadFromFile("Ingenious_logo/logo_projekt_66.png"))
        return false;
    if (!logo_animation[67].loadFromFile("Ingenious_logo/logo_projekt_67.png"))
        return false;
    if (!logo_animation[68].loadFromFile("Ingenious_logo/logo_projekt_68.png"))
        return false;
    if (!logo_animation[69].loadFromFile("Ingenious_logo/logo_projekt_69.png"))
        return false;
    if (!logo_animation[70].loadFromFile("Ingenious_logo/logo_projekt_70.png"))
        return false;
    if (!logo_animation[71].loadFromFile("Ingenious_logo/logo_projekt_71.png"))
        return false;
    if (!logo_animation[72].loadFromFile("Ingenious_logo/logo_projekt_72.png"))
        return false;
    if (!logo_animation[73].loadFromFile("Ingenious_logo/logo_projekt_73.png"))
        return false;
    if (!logo_animation[74].loadFromFile("Ingenious_logo/logo_projekt_74.png"))
        return false;
    if (!logo_animation[75].loadFromFile("Ingenious_logo/logo_projekt_75.png"))
        return false;
    if (!logo_animation[76].loadFromFile("Ingenious_logo/logo_projekt_76.png"))
        return false;
    if (!logo_animation[77].loadFromFile("Ingenious_logo/logo_projekt_77.png"))
        return false;
    if (!logo_animation[78].loadFromFile("Ingenious_logo/logo_projekt_78.png"))
        return false;
    if (!logo_animation[79].loadFromFile("Ingenious_logo/logo_projekt_79.png"))
        return false;
    if (!logo_animation[80].loadFromFile("Ingenious_logo/logo_projekt_80.png"))
        return false;
    if (!logo_animation[81].loadFromFile("Ingenious_logo/logo_projekt_81.png"))
        return false;
    if (!logo_animation[82].loadFromFile("Ingenious_logo/logo_projekt_82.png"))
        return false;
    if (!logo_animation[83].loadFromFile("Ingenious_logo/logo_projekt_83.png"))
        return false;
    if (!logo_animation[84].loadFromFile("Ingenious_logo/logo_projekt_84.png"))
        return false;
    if (!logo_animation[85].loadFromFile("Ingenious_logo/logo_projekt_85.png"))
        return false;
    if (!logo_animation[86].loadFromFile("Ingenious_logo/logo_projekt_86.png"))
        return false;
    if (!logo_animation[87].loadFromFile("Ingenious_logo/logo_projekt_87.png"))
        return false;
    if (!logo_animation[88].loadFromFile("Ingenious_logo/logo_projekt_88.png"))
        return false;

    return true;
}

