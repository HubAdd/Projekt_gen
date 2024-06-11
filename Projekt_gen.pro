TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += "C:/SFML-2.5.1/include"

LIBS += -L"C:/SFML-2.5.1/lib"
CONFIG(debug, debug|release){
    LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
} else {
    LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
}

SOURCES += \
        _circle_shape.cpp \
        additionalshapedecorator.cpp \
        button.cpp \
        custom_rectangle.cpp \
        customshape.cpp \
        engine.cpp \
        game_board.cpp \
        hexagon.cpp \
        hollowcircleshape.cpp \
        laid_token.cpp \
        main.cpp \
        menu.cpp \
        player.cpp \
        round_counter.cpp \
        score_board.cpp \
        setings.cpp \
        sextangle.cpp \
        starshape.cpp \
        starshape1.cpp \
        starshape2.cpp \
        texture_pack.cpp \
        token.cpp

HEADERS += \
    _circle_shape.h \
    additionalshapedecorator.h \
    button.h \
    custom_rectangle.h \
    customshape.h \
    engine.h \
    game_board.h \
    hexagon.h \
    hollowcircleshape.h \
    laid_token.h \
    menu.h \
    player.h \
    round_counter.h \
    score_board.h \
    setings.h \
    sextangle.h \
    starshape.h \
    starshape1.h \
    starshape2.h \
    texture_pack.h \
    token.h
