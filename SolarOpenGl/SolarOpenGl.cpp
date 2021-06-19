#include <iostream>
#include <GL/glew.h>
#include <SFML/Window.hpp>
#include "TextureLoading.h"

int width = 1000;
int height = 900;

using namespace std;
int main() {
    //
    sf::ContextSettings  settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.majorVersion = 4;
    settings.minorVersion = 3;
    settings.antialiasingLevel = 2;

    sf::Window window(sf::VideoMode(width, height, 32), "Solar",
        sf::Style::Titlebar | sf::Style::Close, settings);

    glewExperimental = GL_TRUE;
    glEnable(GL_DEPTH_TEST);

    if (GLEW_OK != glewInit()) {
        cout << "Error:: glew not init =(" << endl;
        return -1;
    }
    //

    //
    TextureLoading earthTex("texture/earth.jpg");
    TextureLoading moonTex("texture/moon.jpg");
    //

    sf::Clock clock;
    bool isGo = true;
    while (isGo) {
        //
        sf::Event windowEvent;
        while (window.pollEvent(windowEvent)) {
            switch (windowEvent.type) {
            case sf::Event::Closed:
                isGo = false;
                break;
            default:
                break;
            }
        }
        //

        //
        glClearColor(0.160f, 0.725f, 0.780f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //

        GLUquadricObj* obj;
        obj = gluNewQuadric();

        auto time = clock.getElapsedTime().asSeconds();

        //солнце
        glPushMatrix();

        //вращение земли вокруг солнца
        glRotatef((time / 5.0f) * 360.0, 0.0, 1.0, 0.0);
        glTranslatef(3.0, 0.0, 0.0);

        //земля и луна
        glPushMatrix();
        
        //земля
        glPushMatrix();

        gluQuadricTexture(obj, GL_TRUE);
        glEnable(GL_TEXTURE_2D);
        earthTex.Binding();

        gluSphere(obj, 1.0, 20, 18);
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();

        //луна
        glPushMatrix();
        glRotatef((time / 5.0f) * 360.0, 0.0, 1.0, 0.0);
        glTranslatef(2.0, 0.0, 0.0);
        glColor4f(0.4, 0.5, 0.6, 1);

        glEnable(GL_TEXTURE_2D);
        moonTex.Binding();
        gluSphere(obj, 0.4, 20, 18);
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();

        glPopMatrix();

        glPopMatrix();

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(70.0, width / height, 1.0, 20.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(0.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

        window.display();
    }
    window.close();
    return 0;
}