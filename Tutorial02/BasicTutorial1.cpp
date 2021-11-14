// This file is part of the OGRE project.
// It is subject to the license terms in the LICENSE file found in the top-level directory
// of this distribution and at https://www.ogre3d.org/licensing.
// SPDX-License-Identifier: MIT


#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include <iostream>

using namespace Ogre;
using namespace OgreBites;

class BasicTutorial1
        : public ApplicationContext
        , public InputListener
{
public:
    BasicTutorial1();
    virtual ~BasicTutorial1() {}

    void setup();
    bool keyPressed(const KeyboardEvent& evt);
};


BasicTutorial1::BasicTutorial1()
    : ApplicationContext("OgreTutorialApp")
{
}

// Aqui configuramos la escena
void BasicTutorial1::setup()
{
    // do not forget to call the base first
    ApplicationContext::setup();
    addInputListener(this);

    // get a pointer to the already created root
    Root* root = getRoot();
    SceneManager* scnMgr = root->createSceneManager();

    // register our scene with the RTSS
    RTShader::ShaderGenerator* shadergen = RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(scnMgr);

    // -- tutorial section start --
    //! [turnlights]
    scnMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
    //! [turnlights]

    //! Creamos una nueva entidad de tipo Light
    Light* light = scnMgr->createLight("MainLight");

    //! Creamos un nuevo SceneNode para asociarle la Light
    SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();

    //! Asociamos la Light al Scene Node
    lightNode->attachObject(light);

    //! Establecemos su posicion en la escena.
    lightNode->setPosition(20, 80, 50);

    //! Creamos un nuevo SceneNode para asociarle la camara
    SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();

    //! Creamos la camara
    Camera* cam = scnMgr->createCamera("myCam");
    cam->setNearClipDistance(5); // specific to this sample
    cam->setAutoAspectRatio(true);
    camNode->attachObject(cam);         // Asociamos la camara
    camNode->setPosition(0, 0, 140);    // Establecemos su posicion

    //! and tell it to render into the main window
    getRenderWindow()->addViewport(cam);

    // Creamos una entidad (o objeto)
    Entity* ogreEntity = scnMgr->createEntity("ogrehead.mesh");

    // Creamos un SceneNode hijo para asociarle la entidad creada anteriormente
    SceneNode* ogreNode = scnMgr->getRootSceneNode()->createChildSceneNode();

    // En Ogre3D hay que asociar los objetos (o entidades) a SceneNode's
    ogreNode->attachObject(ogreEntity);

    // NOTA: Por defecto los SceneNodes se situan en la posicion 0,0,0 en la escena.

    // Movemos la camara para poder ver todos los objetos
    camNode->setPosition(0, 47, 222);
    
    // Creamos una segunda entidad (o objeto)
    Entity* ogreEntity2 = scnMgr->createEntity("ogrehead.mesh");

    // Creamos un SceneNode hijo para asociarle la entidad creada anteriormente y le pasamos la posicion dentro de la escena
    SceneNode* ogreNode2 = scnMgr->getRootSceneNode()->createChildSceneNode(Vector3(84, 48, 0));

    // En Ogre3D hay que asociar los objetos (o entidades) a SceneNode's
    ogreNode2->attachObject(ogreEntity2);

    // Creamos una tercera entidad (o objeto)
    Entity* ogreEntity3 = scnMgr->createEntity("ogrehead.mesh");

    // Creamos un SceneNode hijo para asociarle la entidad creada anteriormente
    SceneNode* ogreNode3 = scnMgr->getRootSceneNode()->createChildSceneNode();

    // Establecemos la posicion dentro de la escena
    ogreNode3->setPosition(0, 104, 0);

    // Establecemos su escala
    ogreNode3->setScale(2, 1.2, 1);

    // En Ogre3D hay que asociar los objetos (o entidades) a SceneNode's
    ogreNode3->attachObject(ogreEntity3);

    // Creamos una cuarta entidad (o objeto)
    Entity* ogreEntity4 = scnMgr->createEntity("ogrehead.mesh");

    // Creamos un SceneNode hijo para asociarle la entidad creada anteriormente
    SceneNode* ogreNode4 = scnMgr->getRootSceneNode()->createChildSceneNode();

    // Establecemos la posicion dentro de la escena
    ogreNode4->setPosition(-84, 48, 0);

    // Establecemos su rotacion en el eje Z (Roll)
    ogreNode4->roll(Degree(-90));

    // En Ogre3D hay que asociar los objetos (o entidades) a SceneNode's
    ogreNode4->attachObject(ogreEntity4);


}


bool BasicTutorial1::keyPressed(const KeyboardEvent& evt)
{
    if (evt.keysym.sym == SDLK_ESCAPE)
    {
        getRoot()->queueEndRendering();
    }
    return true;
}


int main(int argc, char **argv)
{
    try
    {
    	BasicTutorial1 app;
        app.initApp();
        app.getRoot()->startRendering();
        app.closeApp();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error occurred during execution: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
