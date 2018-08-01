//
//  main.cpp
//  GLFWCameraView
//
//  Created by Felipe Rubin on 19/05/18.
//  Copyright © 2018 Felipe Rubin. All rights reserved.
//

#include "include/globals.h"
#include "Game.h"
#include "include/ps4map.h" //Mapping PS4 Controller
#include "include/camera.h"

double global_time = 0;
/* User Configurations */
int screenWidth, screenHeight;

int joystickPresent = 0;

Game game;
int currentPlayer = 0;

static void joystickCallback(int joy, int event)
{
    if (event == GLFW_CONNECTED){
        printf("Joystick Connected: %s\n",glfwGetGamepadName(GLFW_JOYSTICK_1));
        joystickPresent = 1;
    }else if (event == GLFW_DISCONNECTED){
        printf("Joystick Disconnected\n");
        joystickPresent = 0;
    }
}

void joystickControl(GLFWwindow* window)
{
    
    Player *player = game.getPlayers()[currentPlayer];
    if(!joystickPresent){ /* Usa Setas p/ debug*/
        player->forward(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS);
        player->backwards(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS);
        player->left(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS);
        player->right(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS);
        return;
    }


    int axescount;
    const float *axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axescount);
    
    //Buttons
    int buttoncount;
    const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttoncount);

    player->forward(axes[PS4_ANALOG_LEFT_AXIS_Y] < -PS4_ANALOG_IDLE_THRESHOLD || GLFW_PRESS == buttons[PS4_BUTTON_DPAD_UP]);
    player->backwards(axes[PS4_ANALOG_LEFT_AXIS_Y] > PS4_ANALOG_IDLE_THRESHOLD || GLFW_PRESS == buttons[PS4_BUTTON_DPAD_DOWN]);
    player->right(axes[PS4_ANALOG_LEFT_AXIS_X] > PS4_ANALOG_IDLE_THRESHOLD || GLFW_PRESS == buttons[PS4_BUTTON_DPAD_RIGHT]);
    player->left(axes[PS4_ANALOG_LEFT_AXIS_X] < -PS4_ANALOG_IDLE_THRESHOLD || GLFW_PRESS == buttons[PS4_BUTTON_DPAD_LEFT]);
    player->jump(GLFW_PRESS == buttons[PS4_BUTTON_X]);
    player->setSpeed(GLFW_PRESS == buttons[PS4_BUTTON_L3] ? 0.5f : 0.1f);
    
    if(axes[PS4_ANALOG_RIGHT_TRIGGER] > -1+PS4_ANALOG_IDLE_THRESHOLD)
        game.playerShoot(game.getPlayers()[currentPlayer]);
    
    static float auxy = 0;
    static float auxx = 0;
    int h;
    int w;
    glfwGetWindowSize(window, &w, &h);
    if(axes[PS4_ANALOG_RIGHT_AXIS_Y] > PS4_ANALOG_IDLE_THRESHOLD ||
       axes[PS4_ANALOG_RIGHT_AXIS_Y] < -PS4_ANALOG_IDLE_THRESHOLD){
        auxy+= axes[PS4_ANALOG_RIGHT_AXIS_Y];
        if(auxy > h) auxy = h;
        if(auxy < -h) auxy = -h;
    }
    
    if(axes[PS4_ANALOG_RIGHT_AXIS_X] > PS4_ANALOG_IDLE_THRESHOLD ||
       axes[PS4_ANALOG_RIGHT_AXIS_X] < -PS4_ANALOG_IDLE_THRESHOLD){
        auxx+=axes[PS4_ANALOG_RIGHT_AXIS_X];
    }
    
    player->aim(auxx,auxy);
}
static void mouseCallback(GLFWwindow* window, double x, double y)
{
    Player *player = game.getPlayers()[currentPlayer];
    glfwGetCursorPos(window, &x, &y);
    player->aim(x, y);
}
void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Player* player = game.getPlayers()[currentPlayer];
    if(key == GLFW_KEY_ESCAPE){
        game.quit();
        exit(0);
    }
    player->setSpeed(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ? 0.5f : 0.1f);
    player->forward(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS);
    player->left(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS);
    player->right(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS);
    player->backwards(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS);
    player->jump(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS);
    
    if(glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
        player->setSolid(!player->getSolid());
    
    if(game.hasEnded() && glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        game.reset() ;
        
}
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
        game.playerShoot(game.getPlayers()[currentPlayer]);
    }
}

///////////////////////////////////
double before;
int framecount = 0;

void renderScene3D(GLFWwindow *window)
{
    
    
    /* Referencia p/ Objeto do Player */
    
    Player *player = game.getPlayers()[currentPlayer];
    std::vector<PhysicalObject*>* objects = game.getObjects();
    std::vector<Bullet*>* bullets = game.getBullets();
    std::vector<Safezone*>* safezones = game.getSafezones();

    global_time = glfwGetTime(); //Atualiza o tempo global
    
    //Begin Calculate FPS
    framecount++;
    if(global_time - before >= 1.0){ //Passou 1 seg
//        printf("FPS = %lu\n",framecount/game.getPlayers().size());
        framecount = 0;
        before = global_time;
    }
    //End Calculate FPS
    
    if(!player->isDead())
        player->move();  /* Faz movimento */
    
//    if(game.getPlayers().size() == 1){ //No teams, solo play
//        if(player->getZ() >= 90 || player->getZ() <= -90)
//            player->heal(0.1);
//    }else{
//        if(currentPlayer%2 == 0 && player->getZ() >= 90) //Blue team
//            player->heal(0.1);
//        else if(player->getZ() <= -90) //Red Team
//            player->heal(0.1);
//    }
    
    std::vector<Bullet*>::iterator it  = bullets->begin();
    std::vector<PhysicalObject*>::iterator ito  = objects->begin();
    std::vector<Safezone*>::iterator its  = safezones->begin();
    if(player->getSolid() && !player->isDead()){
        /* Colisao Basica, soh n pode passar, mas n machuca */
        for(int i = 0;  i < objects->size(); i++){
            if(!(*objects)[i]->getSolid()) continue;
            if(player->collision((*objects)[i])){}
        }
//        player->collision((*objects)[0]);
        /* Colisao que causa dano */
        
        if(player->getZ() < 90 || player->getZ() > -90){ //SafeZone player
            while(it != bullets->end()){
                if(player->collision(*it)){
                    //Ele retorna o hp apos causar o dano
                    if(player->damage(25) == 0){
                        game.playerDied(player);
                    }
                    it = bullets->erase(it);
                }else
                    ++it;
            }
        }
        
        /* Colisao com safezone */
        for(int i = 0; i < safezones->size(); i++){
            if(!(*safezones)[i]->getSolid()) continue;
            player->safezonecollision((*safezones)[i]);
        }

    }
    

    
    it = bullets->begin();
    
    int bkflag = 0; //Break flag, deletou a bullet atual, quebra o for
    while (it != bullets->end()) {
        ito = objects->begin();
        its = safezones->begin();
        bkflag = 0;
//        if(((Bullet*)*it)->getZ() <= -90 || ((Bullet*)*it)->getZ() >= 90 ||
//            ((Bullet*)*it)->getX() > 100 ||  ((Bullet*)*it)->getX() < -100 ||
//            ((Bullet*)*it)->getY() > 100 ||  ((Bullet*)*it)->getZ() < -100){
//            it = bullets->erase(it);
//            continue;
//        }
        
        if(((Bullet*)*it)->getX() > 100 ||  ((Bullet*)*it)->getX() < -100 ||
           ((Bullet*)*it)->getY() > 100 ||  ((Bullet*)*it)->getY() < -100||
           ((Bullet*)*it)->getZ() > 100 ||  ((Bullet*)*it)->getZ() < -100){
            it = bullets->erase(it);
            continue;
        }
        
        while(ito != objects->end()){
            int aux = 0;
            if((aux = ((Bullet*)*it)->collision(*ito)) == 1){
                ((PhysicalObject*)*ito)->damage(25);
                it = bullets->erase(it);
                if(((PhysicalObject*)*ito)->getHealth() <= 0){
                    ito = objects->erase(ito);
                }
                bkflag = 1;
                break;
            }
            ++ito;
        }
        
        //!bkflag aqui pois pode ser que o objeto do while
        //anterior termine com todas as balas, ou seja balaAtual = NULL
        while(!bkflag && its != safezones->end()){
            int aux = 0;
            if((aux = ((Bullet*)*it)->collision(*its))){
                it = bullets->erase(it);
                bkflag = 1;
                break;
            }
            ++its;
        }
        
        if(!bkflag)//Se n deu colisao c/ a bullet atual
            ++it;
    }
    
//    Debugging
        printf("P(%f,%f,%f)\n",player->getX(),player->getY(),player->getZ());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(player->getX(), player->getY(), player->getZ(), player->getAtX(), player->getAtY(), player->getAtZ(), player->getUpX(), player->getUpY(), player->getUpZ());
    //Desenha os outros players;
    //O meu player eh invisivel p/ mim
    std::vector<Player*> players = game.getPlayers();
    for(int i = 0; i < players.size(); i++){
        if(i == currentPlayer) continue;
        players[i]->draw();
    }
    

    for(int i = 0; i < objects->size(); i++){
        (*objects)[i]->draw();
        (*objects)[i]->nextStage();
    }
    
    for(int i = 0; i < bullets->size(); i++){
        (*bullets)[i]->draw();
        (*bullets)[i]->nextStage();
    }
    
    //Draw Safezones
    for(int i = 0; i < safezones->size(); i++){
        (*safezones)[i]->draw();
        (*safezones)[i]->nextStage();
    }
}




/* Configuracoes iniciais */
GLFWwindow* initConfig()
{
    glfwInit();
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    int windowWidth = 800;
    int windowHeight = 600;
    //Begin FULLSCREEN
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();

    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
    GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "My Title", monitor, NULL);
    //End FULLSCREEN
//    GLFWwindow *window = glfwCreateWindow(windowWidth, windowHeight, "Game of The Year Remastered", NULL, NULL);
    if(window == NULL){
        printf("Error creating window\n");
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, keyboardCallback);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    
    /*From glfw Docs: This will hide dthe cursor and lock it to the specified Window,
     GLFW will then take care of all the details of cursor re-centering and offset calculation
     and providing the application with a virtual cursor position*/
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("OpenGL version supported %s\n", glGetString(GL_VERSION));
    joystickPresent = glfwJoystickPresent(GLFW_JOYSTICK_1);
    printf("Has Joystick %d\n",joystickPresent);
    printf("Is Gamepad: %d\n",glfwJoystickIsGamepad(GLFW_JOYSTICK_1));
    if(joystickPresent){
        printf("Joystick Connected: %s\n",glfwGetGamepadName(GLFW_JOYSTICK_1));
    }
    glfwSetJoystickCallback(joystickCallback);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDisable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    return window;
}



//TO DO
void drawMenu() //Mexe mouse/joystick ...
{
    
}

void drawGameEnding(float top,float bottom)
{
    Player *player = game.getPlayers()[currentPlayer];
    glPushMatrix();
    glColor3f(1,1,1);
    glEnable(GL_TEXTURE_2D);
    if(player->getDeaths()->size() == game.getLives())
        glBindTexture(GL_TEXTURE_2D,*game.getLostTexture());
    else
        glBindTexture(GL_TEXTURE_2D, *game.getWonTexture());
    glBegin(GL_QUADS);
    glTexCoord2f(0,1);glVertex2f(0,bottom);
    glTexCoord2f(0,0);glVertex2f(0,top);
    glTexCoord2f(1,0);glVertex2f(screenWidth, top);
    glTexCoord2f(1,1);glVertex2f(screenWidth, bottom);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glColor3f(1,1,1);
    glPopMatrix();

}

void drawLives(float top, float bottom)
{
    Player *player = game.getPlayers()[currentPlayer];
    glPushMatrix();
    glColor3f(1,1,1);
    glBegin(GL_QUADS);
    glColor3f(1.0,0.0,0.0);
    int playerLives = game.getLives() - player->getDeaths()->size();
    float prevx = 0;
    for(int i = 0; i < playerLives; i++){
        glVertex2f(i+prevx,top-100);
        glVertex2f(i+prevx, top-50);
        glVertex2f(i+50+prevx, top-50);
        glVertex2f(i+50+prevx, top-100);
        prevx += i+51;
    }
    glEnd();
    glPopMatrix();
}
void drawHPBar(float top, float bottom)
{
    Player *player = game.getPlayers()[currentPlayer];
    //Begin HPBar
    glPushMatrix();
    glColor3f(1,1,1);
    //Comeca a desenha a HUD pro Player
    glBegin(GL_QUADS);
    glColor3f(0.55, 0, 0);
    glVertex2f(0.0f, top);
    glVertex2f(player->getHealth() * screenWidth/300, top);
    glVertex2f(player->getHealth() * screenWidth/300, top-50.0f);
    glVertex2f(0, top-50.0f);
    glEnd();
    glPopMatrix();
    //End HPBar

}

void drawAIM(float top, float bottom)
{
    float midy = bottom+(top - bottom)/2.0f;
    float height = top - bottom;
    //Begin Draw AIM
    glPushMatrix();
    glColor3f(1,1,1);
    glBegin(GL_LINES);
    glColor3f(1,0,0);
    glVertex2f(screenWidth/2.0f, midy-height/5);
    glVertex2f(screenWidth/2.0f, midy+height/5);
    glVertex2f(screenWidth/2.0f+screenWidth/10 ,midy);
    glVertex2f(screenWidth/2.0f-screenWidth/10,midy);
    glEnd();
    glPopMatrix();
    //End Draw AIM

}

void drawDeathFade(float top, float bottom)
{
    Player *player = game.getPlayers()[currentPlayer];
    //Begin Player Death Fade
    
    //60
    //40
    //20
    //0
    if(player->isDead()){
        glPushMatrix();
        glColor3f(1.0f,1.0f,1.0f);
        glEnable(GL_BLEND);
        
        int sinceDeath = player->deathAnimationStep();
        int resptime = game.getRespawnTime();
        if(sinceDeath == 0){
            player->heal(100.0f);
            glColor4f(0.0f,0.0f,0.0f,0.0f);
        }else{
            if(sinceDeath >= 2*resptime/3){//Fade in Escurecendo
                float fade = 2.0f*(((1.0f*resptime)/(1.0f*sinceDeath))-1.0f);
                printf("Fade in = %f\n",fade);
                glColor4f(0.0f,0.0f,0.0f,fade);
            }else if(sinceDeath > resptime/3){ //Preto
                glColor4f(0.0f,0.0f,0.0f,1.0f);
            }else if(sinceDeath == resptime/3){ //Respawn local e reseta camera
                glColor4f(0.0f,0.0f,0.0f,1.0f);
                game.respawnPlayer(currentPlayer);
            }else{ //Fade out Clareando
                float fade = 3.0f*((1.0f*sinceDeath)/(1.0f*resptime));
                printf("Fade out = %f\n",fade);
                glColor4f(0.0f,0.0f,0.0f,fade);
            }
        }
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBegin(GL_QUADS);
        glVertex2f(0,bottom);
        glVertex2f(0,top);
        glVertex2f(screenWidth, top);
        glVertex2f(screenWidth, bottom);
        glEnd();
        //glColor3f(1,1,1);
        glDisable(GL_BLEND);
        glPopMatrix();
        
    }
}

void renderScene2D()
{
    //Dependendo do player, pega qual a parte e alta e baixa da tela q ele usa
    float top = screenHeight;
    float bottom = 0;
    if(game.getPlayers().size() > 1){
        if(currentPlayer == 0)
            top = screenHeight/2.0f;
        else
            bottom = screenHeight/2.0f;
    }
    
    
    //Begin HUD  do player
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0f, screenWidth, bottom, top);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    /*glDisable(GL_CULL_FACE);*/ //Ja esta sempre desabilitado
    glClear(GL_DEPTH_BUFFER_BIT);
    
    if(game.hasEnded()){
        drawGameEnding(top,bottom);
    }else{
        //Begin Desenhos 2D
        drawHPBar(top,bottom);
        drawAIM(top, bottom);
        drawDeathFade(top,bottom);
        drawLives(top,bottom);
        //End Desenhos 2D
    }
    
    //Acaba de desenhar a HUD pro Player
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}
void changeSize(GLFWwindow *window)
{
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    if(screenHeight == 0) screenHeight = 1.0f;
    
    float ratio = screenWidth * 1.0f / screenHeight;
    if(game.getPlayers().size() == 2)
        ratio = screenWidth * 1.0f / (screenHeight/2.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, ratio, 0.1f, 1000.0f);
//    gluPerspective(90.0f, ratio, 0.1f, 1000.0f);
    glViewport(0, 0, screenWidth, screenHeight);
    
}

void playerTurn(GLFWwindow *window)
{
    Player* player = game.getPlayers()[currentPlayer];
    /* Pega as configuracoes de tela p/ esse player TO DO */
    glMatrixMode(GL_MODELVIEW);
    if(game.getPlayers().size() > 1){
        if(currentPlayer == 0){
            glViewport(0.0f, 0.0f, screenWidth, screenHeight/2.0f);
            glScissor(0, 0, screenWidth, screenHeight/2.0f);
        }
        else if(currentPlayer == 1){
            glViewport(0.0f, screenHeight/2.0f, screenWidth, screenHeight/2.0f);
            glScissor(0.0f, screenHeight/2.0f, screenWidth, screenHeight/2.0f);
        }
        glEnable(GL_SCISSOR_TEST);
    }
    
    /* Atualiza a tela do Player */
    if(!game.hasEnded()){
        renderScene3D(window);
    }
    renderScene2D();
    
    /* Nao precisa Habilitar se Tiver so 1 Player */
    if(game.getPlayers().size() > 1) glDisable(GL_SCISSOR_TEST);
    
    /* Le de Joystick/Teclado+Mouse/ o q controlar esse Player  */
    switch(game.getPlayers()[currentPlayer]->getDevice()){
        case 0: glfwPollEvents();break;
        case 1: joystickControl(window);break;
        default: break;
    }
}





int main(int argc, char** argv) {
    
    GLFWwindow *window = initConfig();
    
    //////////////////////////////////////////////
    /* Inicializa Glew p/ usar funcoes da Placa grafica, acho q eh isso ... */
    GLenum err = glewInit();
    std::cout << "GLEW ERROR ? " << err << "\n";
    ////////////////////////////////////////////
    game.init();
    
    Player *firstplayer = new Player();
    game.addPlayer(firstplayer);
    
//     Add 2o Player
    Player *secondplayer = new Player();
    secondplayer->setDevice(1);
    secondplayer->getCamera()->setSensibility(0.035);
    game.addPlayer(secondplayer); //Padrao eh Teclado+Mouse
    
    game.setLives(3);

    while ( !glfwWindowShouldClose( window ) )
    {
        /* Verifica se n alterou o tamanho da Tela */
        changeSize(window);
        /* Cada Player joga seu Turno */
        for(currentPlayer = 0; currentPlayer < game.getPlayers().size(); currentPlayer++){
            playerTurn(window);
        }
        /* Swap Buffers */
        glfwSwapBuffers(window);
    }
    
    game.quit();

    
    return 0;
}
