#include "game.h"

Game::Game(): conn(&player, engine), window(engine), player() {
     timer = new QTimer(this);
     connect(timer, SIGNAL(timeout()), this, SLOT(go()));
     timer->start(FRAMETIME*1000);
	 player.x=5, player.y=5;
	 engine.players.append(player);
	 startTime.start();
}

void Game::start(QString ip, int port) {
    
    //Moottori
    
    
    // Luo verkko
    
    conn.connect(ip,port);

    //Luo ikkuna + piirtopinta
    window.show();

}

/** Weapon load times in ms. */
int loadTimes[] = {0,200};

void Game::go() {
	conn.update();
    engine.go();
    window.updatePlayerMovement(player);
    window.draw(&player); //(player.x,player.y);
	conn.sendStatus();

//	qDebug()<<player.x<<player.y;

	int t = startTime.elapsed();
//	qDebug()<<player.shooting<<startTime.elapsed()<<player.shootTime+loadTimes[player.weapon];
	if (player.shooting && t>player.shootTime+loadTimes[player.weapon]) {
		conn.sendShoot();
		player.shootTime = t;
	}
}
