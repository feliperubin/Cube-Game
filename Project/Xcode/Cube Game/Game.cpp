//
//  Game.cpp
//  GLFWCameraView
//
//  Created by Felipe Rubin on 31/05/18.
//  Copyright © 2018 Felipe Rubin. All rights reserved.
//

#include "Game.h"

Game::Game(void){}
Game::~Game(void){}

/* Begin the Game Create the Scenary */
void Game::init()
{
    loadTexture(&wonTexture,"won.png",GL_TEXTURE_WRAP_S, GL_TEXTURE_WRAP_T, GL_LINEAR,GL_LINEAR);
    loadTexture(&lostTexture,"lost.png",GL_TEXTURE_WRAP_S, GL_TEXTURE_WRAP_T, GL_LINEAR,GL_LINEAR);
    loadTexture(&floorTexture,"grass2.bmp",GL_NEAREST_MIPMAP_LINEAR, GL_NEAREST_MIPMAP_LINEAR, GL_MIRRORED_REPEAT,GL_MIRRORED_REPEAT);
    loadTexture(&skyTexture, "space.bmp",GL_CLAMP_TO_BORDER,GL_CLAMP_TO_BORDER, GL_REPEAT, GL_REPEAT);
    loadTexture(&boxTexture,"box.jpg",GL_CLAMP_TO_BORDER,GL_CLAMP_TO_BORDER, GL_REPEAT, GL_REPEAT);
    loadTexture(&player1texture, "abstract1.bmp",GL_CLAMP_TO_BORDER,GL_CLAMP_TO_BORDER, GL_REPEAT, GL_REPEAT);

    loadTexture(&player2texture, "abstract2.bmp",GL_CLAMP_TO_BORDER,GL_CLAMP_TO_BORDER, GL_REPEAT, GL_REPEAT);
    loadTexture(&bricktexture,"brick1.bmp",GL_NEAREST_MIPMAP_LINEAR, GL_NEAREST_MIPMAP_LINEAR, GL_MIRRORED_REPEAT,GL_MIRRORED_REPEAT);
    
      loadTexture(&bulletTexture, "metal3D.jpg",GL_CLAMP_TO_BORDER,GL_CLAMP_TO_BORDER, GL_REPEAT, GL_REPEAT);
      loadTexture(&marbleTexture, "marble.jpg",GL_CLAMP_TO_BORDER,GL_CLAMP_TO_BORDER, GL_REPEAT, GL_REPEAT);
    
//    
    loadTexture(&gunTexture,"M1911-RIGHT.jpg",GL_NEAREST_MIPMAP_LINEAR, GL_NEAREST_MIPMAP_LINEAR, GL_REPEAT,GL_REPEAT);
    
    loadTexture(&skyBoxTexture, "sky.jpg", GL_NEAREST_MIPMAP_LINEAR, GL_NEAREST_MIPMAP_LINEAR, GL_MIRRORED_REPEAT,GL_MIRRORED_REPEAT);
      loadTexture(&gunBulletTexture, "Black-Ops-Weapons-M1911.jpg",GL_CLAMP_TO_BORDER,GL_CLAMP_TO_BORDER, GL_REPEAT, GL_REPEAT);

    initDataset();
    createObjects();
}
void Game::createObjects(){

    
    int cont = 0;
    for(int i = -3; i < 3; i++){
        for(int j=-3; j < 3; j++) {
            Cube *cb = new Cube();
            cb->setX(i*10.0);
            cb->setSolid(1);
            cb->setZ(j*10.0);
            if(cont == 30){
                cb->setY(5.0f);
            }else if(cont == 28){
                cb->setY(10.0f);
                cb->setX(20);
                cb->setZ(-30);
            }
            else{
                cb->setY(1.1);
            }
            if(cont == 30)
                cb->setTexture(&skyTexture);
            else
                cb->setTexture(&boxTexture);
            objects.push_back(cb);
            cont++;
        }
    }


    
    //Begin Column Test
    Column *col = new Column(); //Obj 37
    col->setX(-90);
    col->setY(0);
    col->setZ(-90);
    col->setTexture(&marbleTexture);
    col->setSolid(1);
    col->setSize(0.9);
    col->setDestructible(0);
    objects.push_back(col);
    
    Column *col2= new Column();
    col2->setX(90);
    col2->setY(0);
    col2->setZ(-90);
    col2->setTexture(&marbleTexture);
    col2->setSolid(1);
    col2->setSize(0.9);
    col2->setDestructible(0);
    objects.push_back(col2);
    
    Column *col3 = new Column();
    col3->setX(90);
    col3->setY(0);
    col3->setZ(90);
    col3->setTexture(&marbleTexture);
    col3->setSolid(1);
    col3->setSize(0.9);
    col3->setDestructible(0);
    objects.push_back(col3);
    

    Column *col4 = new Column();
    col4->setX(-90);
    col4->setY(0);
    col4->setZ(90);
    col4->setTexture(&marbleTexture);
    col4->setSolid(1);
    col4->setSize(0.9);
    col4->setDestructible(0);
    objects.push_back(col4);
    //End Column Test
    
    //Begin Test Inicio Player
    Column *col5 = new Column();
    col5->setX(0);
    col5->setY(0);
    col5->setZ(95);
    col5->setTexture(&marbleTexture);
    col5->setSolid(1);
    col5->setSize(0.01);
    col5->setDestructible(0);
    objects.push_back(col5);
    
    Column *col6 = new Column();
    col6->setX(0);
    col6->setY(0);
    col6->setZ(-95);
    col6->setTexture(&marbleTexture);
    col6->setSolid(1);
    col6->setSize(0.01);
    col6->setDestructible(0);
    objects.push_back(col6);
    //End Test Inicio Player
    
    
    //Begin Bird Test
    Bird *brd = new Bird();
    brd->setX(3);
    brd->setY(2);
    brd->setZ(3);
    brd->setTexture(&marbleTexture);
    brd->setSolid(1); /* Passaro n tem colisao por enquanto */
    brd->setDestructible(1);
    brd->setSize(0.1);
    objects.push_back(brd);
    //End Bird Test
    
//    //Begin Gun
//    Gun *gun = new Gun();
//    gun->setX(5);
//    gun->setY(2);
//    gun->setZ(5);
//    gun->setTexture(&gunTexture);
//    gun->setSolid(0); /* Arma n tem colisao por enquanto */
//    gun->setBulletTexture(&gunBulletTexture);
//    gun->setSize(0.1);
//
//    objects.push_back(gun);
//    //End Gun Test
    
    
    //Begin SkyBox
    Cube *skyBox = new Cube();
    skyBox->setX(0);
    skyBox->setY(0);
    skyBox->setZ(0);
    skyBox->setSize(100.0f);
    skyBox->setSolid(1); /* skyBox n tem colisao por enquanto */
    skyBox->rotateEnabled(0);
    skyBox->setTexture(&skyBoxTexture);
    skyBox->setDestructible(0); //Nao eh destrutivel
    objects.push_back(skyBox);
    //End SkyBox

    //Begin Safezones
    Safezone *safe = new Safezone();
    safe->setX(0);
    safe->setY(0);
    safe->setZ(90);
    safe->setSolid(1);
    safe->setDestructible(0);
    /* Bleu de France */
    safe->setColor(glm::vec4(0.27,0.59,0.96,0.3));
    safe->setTeam(0);
    safe->setMin(glm::vec3(90,0,0));
    safe->setMax(glm::vec3(90,100,10));
    safezones.push_back(safe);
    
    Safezone *safe2 = new Safezone();
    safe2->setX(0);
    safe2->setY(0);
    safe2->setZ(-90);
    safe2->setSolid(1);
    safe2->setDestructible(0);
    safe2->setTeam(0);
    /* Bleu de France */
    safe2->setColor(glm::vec4(0.27,0.59,0.96,0.3));
    safe2->setMin(glm::vec3(90,0,10));
    safe2->setMax(glm::vec3(90,100,0));
    safezones.push_back(safe2);
    //End Safezones
    
    this->respawnTime = 120;

    this->lives = 3;
    this->ended = 0;
    
    
//    Begin Carrega Pessoas do T1
    
    configureDataset();
//    End Carrega Pessoas do T1
    
    Square* ground = new Square();
    ground->setX(100);
    ground->setY(0);
    ground->setZ(100);
    ground->setTexture(&floorTexture);
    ground->setS(-25, -25, 25, 25);
    ground->setT(-25, 25, 25, -25);
    ground->setSolid(1);
    ground->setDestructible(0);
    objects.push_back(ground);

    

    
}
GLuint* Game::getWonTexture(){return &wonTexture;}
GLuint* Game::getLostTexture(){return &lostTexture;}


std::vector<Player*> Game::getPlayers(){return players;}

int Game::hasEnded(){return ended;}
void Game::setLives(int lives){this->lives = lives;}
int Game::getLives(){return this->lives;}

void Game::addPlayer(Player *p)
{
    if(players.size() == 0){
        p->setTexture(&player1texture);
        p->setX(0);
        p->setY(3);
        p->setZ(95);
        p->setTeam(0);
    }else if(players.size() == 1){
        p->setTexture(&player2texture);
        p->setX(0);
        p->setY(3);
        p->setZ(-95);
        //Olha p/ lado contrario
        p->getCamera()->setVz(1.0f);
        p->getCamera()->setWangle(acos(-1)); //PI
        p->setTeam(1);
        /* Mahogany */
        safezones[1]->setColor(glm::vec4(0.76, 0.17, 0.20,0.3));
        safezones[1]->setTeam(1);
    }
    p->setWeaponTextures(&bulletTexture, &gunTexture);
    players.push_back(p);
}

int Game::respawnPlayer(int playerid)
{
    Player *p = players[playerid];
    if(playerid % 2 == 0){
        p->setX(0);
        p->setY(3);
        p->setZ(95);
        p->resetCamera();
    }else{
        p->setX(0);
        p->setY(3);
        p->setZ(-95);
        p->getCamera()->setVz(1.0f);
        p->getCamera()->setWangle(acos(-1));
        p->resetCamera();
        p->getCamera()->setSensibility(0.035);
    }
    return 1;
}

void Game::reset()
{
    //How many players
    int countPlayers = players.size();
    int countLives = lives;
    freeObjects();
    createObjects();
    if(countPlayers >= 1){
        Player *firstplayer = new Player();
        addPlayer(firstplayer);
    }

    if(countPlayers == 2){
        Player *secondplayer = new Player();
        secondplayer->setDevice(1);
        secondplayer->getCamera()->setSensibility(0.1);
        addPlayer(secondplayer); //Padrao eh Teclado+Mouse
    }
    lives = countLives;
}

void Game::playerShoot(Player *p)
{
    Camera *cam = p->getCamera();
    if(p->shootAnimation()){
        Bullet *bullet = new Bullet(cam->getAtX(),cam->getAtY(),cam->getAtZ(),cam->getVx(),cam->getVy(),cam->getVz());
        bullet->setTexture(&bulletTexture);
        bullet->setSize(0.1);
        bullets.push_back(bullet);
    }
}

void Game::playerDied(Player *p)
{
    p->getDeaths()->push_back(global_time);
    if(p->getDeaths()->size() == this->lives) this->ended = 1;
    p->deathAnimation(this->respawnTime,1);
}

std::vector<Bullet*>* Game::getBullets(){return &bullets;}

std::vector<PhysicalObject*>* Game::getObjects(){return &objects;}
std::vector<Safezone*>* Game::getSafezones(){return &safezones;}

int Game::getRespawnTime(){return this->respawnTime;}

void Game::freeObjects()
{
    std::vector<Bullet*>::iterator it  = bullets.begin();
    std::vector<PhysicalObject*>::iterator ito  = objects.begin();
    std::vector<Player*>::iterator itp  = players.begin();
    std::vector<Safezone*>::iterator its  = safezones.begin();
    
    while(it != bullets.end()){
        it = bullets.erase(it);
    }
    while(ito != objects.end()){
        ito = objects.erase(ito);
    }
    
    while(its != safezones.end()){
        its = safezones.erase(its);
    }

//    int playercount = 0;
    while(itp != players.end()){
//        printf("Player %d died %lu times\n",playercount,((Player*)*itp)->getDeaths()->size());
        itp = players.erase(itp);
//        playercount++;
    }
}
void Game::freeDataset()
{
    //Limpa memoria e termina o programa
    if(datasetEnabled)
        for(int i = 0; i < 4; i++){
            printf("Clearing Memory of Video %d\n",i);
            freeVideoInfo(&(vc[i].vi));
            free(vc[i].hascompany);
            freeGList(vc[i].list);
        }

}
void Game::quit()
{
    freeObjects();
    freeDataset();
}

////////////////ABAIXO EH RELACIONADO AO T1
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Game::recognizeGroups(GList *list)
{
    int i,j,k;
    Frame *f;
    int changed = 0;
    int need_merge_group = 0; //1 se tem q unir dois grupos ou mais, 0 se nao precisa
    i = 0;
    f = &viGlobal->frames[i];
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Pessoa Sozinha e outra Pessoa em Grupo
PSPG:
    for(j = 0; j < viGlobal->people; j++){
        if(!hascompany[j]){
            Group *aux = list->head;
            while(aux != NULL){
                for(k = 0; k < viGlobal->people; k++){
                    if(aux->presence[k] > 0){
                        if(ispp(j, k, viGlobal)){
                            addToGroup(aux,j);
                            hascompany[j] = 1;
                            break;
                        }
                    }
                }
                aux = aux->next;
                if(hascompany[j]){
                    break;
                }
            }
        }
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Pessoa Sozinha e outra Pessoa Sozinha
    for(j = 0; j < viGlobal->people; j++){
        if(!hascompany[j]){
            for(k = 0; k < j; k++){
                if(!hascompany[k]){
                    if(ispp(j, k, viGlobal)){
                        int minFrame = viGlobal->personBegin[j];
                        
                        if(minFrame > viGlobal->personBegin[k]) minFrame = viGlobal->personBegin[k];
                        addGroup(list,j,k,viGlobal->people);
                        hascompany[j] = 1;
                        hascompany[k] = 1;
                        changed = 1;
                        break;
                    }
                }
            }
        }
    }
    if(changed == 1){
        changed = 0;
        goto PSPG; //Testa denovo PS + PG = G+
    }
    
    //Prepara p/ fazer merge dos grupos (Verifica Pessoa de um Grupo c/ Pessoa de outro Grupo)
    for(j = 0; j < viGlobal->people; j++){
        if(hascompany[j]){
            Group *aux = list->head;
            while(aux != NULL){
                if(aux->presence[j] == 0){
                    for(k = 0; k < viGlobal->people;k++){
                        if(aux->presence[k] && ispp(j, k, viGlobal)){
                            addToGroup(aux,j);
                            need_merge_group = 1;
                            break;
                            
                        }
                    }
                }
                aux = aux->next;
            }
        }
    }
    
    if(need_merge_group){
        need_merge_group = 0;
        subsetGroups(list);
    }
    //atualiza info dos grupos
    updateGroups(list);
    //ve os grupos e verifica qual  o maior
    Group *aux = list->head;
    while(aux != NULL){
        if(aux->size > *maxGroupSize) *maxGroupSize = aux->size;
        aux = aux->next;
    }
}


/*
 Computa 4 coisas:
 - Quando o grupo eh criado
 - Quando o grupo se desfaz
 - Quando cada integrante entra no grupo
 - Quando cada integrante sai do grupo
 */
void Game::computeinoutgroups()
{
    Group *aux = globalList->head;
    int groupi = 0;
    int i = 0;
    while(aux != NULL){
        printf("---------Group %d------------\n",groupi);
        for(i = 0; i < viGlobal->people; i++){
            if(aux->presence[i] > 0){
                
                inoutGroup(i,aux,viGlobal,&aux->enteredAt[i],&aux->exitedAt[i]);
                if(aux->bornAt == -1) aux->bornAt = aux->enteredAt[i];
                else if(aux->bornAt > aux->enteredAt[i])aux->bornAt = aux->enteredAt[i];
                
                if(aux->deathAt == -1)aux->deathAt = aux->exitedAt[i];
                else if(aux->deathAt < aux->exitedAt[i])aux->deathAt = aux->exitedAt[i];
            }
        }
        printf("Group %d True existance is [%d,%d]\n",groupi,aux->bornAt,aux->deathAt);
        groupi++;
        aux = aux->next;
    }
}

void Game::initDataset()
{
    vc[0].filename = "Austria01.txt";
    vc[1].filename = "France01.txt";
    vc[2].filename = "Germany01.txt";
    vc[3].filename = "Brazil06.txt";
    
    
    //Le os arquivos e depois reconhece os grupos
    //OBS: Soh fiz de tras p/ frente pras referencias globais ja apontarem pro Video 0
    for(int i = 3; i >= 0; i--){
        printf("-------Initializing Video %d-------\n",i);
        VideoInfo *vi = &vc[i].vi;
        //Faz a primeira leitura do arquivo p/ poder dar malloc depois
        readFileInfo(vi, vc[i].filename);
        //Aloca de acordo com os dados que adquiriu na 1a leitura
        allocateVideoInfo(vi);
        //Agora le uma segunda com uma memoria ja alocada
        readFileData(vi,vc[i].filename);
        
        printf("Pixel x Meter: %d\n",vi->pxm);
        printf("Number of People: %d\n",vi->people);
        for(int j = 0; j < vi->people; j++){
            printf("Person %d Timeline [%d,%d]\n",j,vi->personBegin[j],vi->personEnd[j]);
        }
        printf("Begining Frame: %d\n",vi->begin);
        printf("Number of Frames: %d\n",vi->length);
        printf("MinPoint = (%f,%f)\n",vi->minpoint.x,vi->minpoint.y);
        printf("MaxPoint = (%f,%f)\n",vi->maxpoint.x,vi->maxpoint.y);
        vc[i].list = (GList*)malloc(sizeof(GList));
        vc[i].list->size = 0;
        vc[i].list->head = NULL;
        vc[i].list->tail = NULL;
        globalList = vc[i].list;
        viGlobal = &vc[i].vi;
        vc[i].hascompany = (int*)calloc(viGlobal->people,sizeof(int));
        hascompany = vc[i].hascompany;
        vc[i].currFrame = 0;
        vc[i].prevFrame = -1;
        vc[i].frameposGlobal = 0;
        maxGroupSize = &vc[i].maxGroupSize;
        recognizeGroups(vc[i].list);
        printf("------------Processed Data:---------------\n");
        computeinoutgroups();
        printf("Biggest Group Size: %d\n",vc[i].maxGroupSize);
        printGroups(vc[i].list);
        printf("---------------------------------------------\n");
        
    }
    datasetEnabled = 1;

}

void Game::configureDataset()
{
    
    for(int i = 0; i < 4; i++){ //Para cada Video
        VideoInfo *currvideo = &vc[i].vi;
        for(int j = 0; j < currvideo->people; j++){ //Para cada Pessoa de tal Video
            Bird *bird = new Bird();
            bird->setX(0);
            bird->setY(20);
            bird->setZ(0);
            bird->setTexture(&marbleTexture);
            bird->setSolid(1);
            bird->setDestructible(1);
            bird->setSize(0.1);
//            bird->setTimeSeries(currvideo->frames, currvideo->length, j, currvideo->pxm);
            bird->setTimeSeries(currvideo, j);
            objects.push_back(bird);
        }
    }

}














