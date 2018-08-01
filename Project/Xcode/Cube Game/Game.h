//
//  Game.hpp
//  GLFWCameraView
//
//  Created by Felipe Rubin on 31/05/18.
//  Copyright © 2018 Felipe Rubin. All rights reserved.
//

#ifndef Game_h
#define Game_h

#include "globals.h"
#include "include/Player.h"
#include "Square.h"
#include "cgutils.h"
#include "Bullet.h"
#include "Column.h"
#include "Bird.h"
#include "Gun.h"
#include "Safezone.h"

//Do T1
#include "T1Files/video.h"
//
typedef struct{
    VideoInfo vi;
    int *hascompany;// hascompany deste video
    int frameposGlobal; //pos do frame atual
    int maxGroupSize; //grupo com maior tamanho
    const char *filename; // Arquivo de dados
    GList *list; //Lista de Grupos
    int currFrame; // currFrame desse Controller
    int prevFrame; //prevFrame desse Controller
}VideoController;

class Game{
public:
    Game(void);
    ~Game(void);
    void init();
    std::vector<Player*> getPlayers();
    void addPlayer(Player *p);
    
    std::vector<PhysicalObject*>* getObjects();
    std::vector<Bullet*>* getBullets();
    std::vector<Safezone*>* getSafezones();
    
    
    void playerShoot(Player *p);
    void playerDied(Player *p);
    
    void quit(void);
    void initDataset(void);
    void configureDataset(void);
    
    
    int respawnPlayer(int playerid);
    int getRespawnTime(void);
    
    GLuint* getWonTexture();
    GLuint* getLostTexture();
    
    
    /**/
    void setLives(int lives);
    int getLives();
    int hasEnded();
    
    void reset();
    
    
    
private:
    void recognizeGroups(GList *list);
    void computeinoutgroups();
    void createObjects();
    void freeObjects();
    void freeDataset();
    
    std::vector<Player*> players;
    std::vector<PhysicalObject*> objects;
    std::vector<Bullet*> bullets;
    std::vector<Safezone*> safezones;
    
    
    //Sempre guarda a quantidade maior de mortes que algum player tem
    int ended;
    int lives;
    
    //Motivo de usar double
    //usando float, 0.1 n funciona, algum erro de arredondamento.
    int respawnTime = 0;
    
    
    /* Textures aqui */
    GLuint floorTexture, skyTexture, boxTexture;
    GLuint player1texture, player2texture, bricktexture;
    GLuint bulletTexture,marbleTexture, gunTexture;
    GLuint skyBoxTexture;
    GLuint gunBulletTexture, terrainTexture;
    GLuint wonTexture, lostTexture;
    
    
    /////////// ABAIXO EH TUDO DO T1
    int datasetEnabled = 0;
    VideoInfo *viGlobal; //Video Atual
    GList *globalList; // Lista de grupos do Video Atual
    int *hascompany; //Se a pessoa ta em grupo = 1 ou nao = 0, do video atual
    int frameposGlobal; // posicao do video atual
    int *maxGroupSize; //tamanho maximo de grupos de cada video
    int pauseVideo = 0; //Pause no video
    int prevFrame = -1; //Frame anterior
    int currFrame = 0; //Frame atual(usado em Desenha(), p/ n alterar o framePosGlobal durante o desenho da tela)
    
    int videoselector = 0; //Seletor de video
    
    //Os videos com suas respectivas informacoes
    VideoController vc[4];
};

#endif /* Game_h */






