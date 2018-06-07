#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>

#include "libs/character/character.h"

const int WIDTH = 640;
const int HEIGTH = 480;
const int FPS = 30;

int init_game(void){
  if(!al_init()){
	fprintf(stderr, "Falha ao iniciar o allegro.\n");
	return 0;
  }

  if(!al_init_image_addon()){
	fprintf(stderr, "Falha ao iniciar o add-on de imagem.\n");
	return 0;
  }

  if(!al_install_keyboard()){
	fprintf(stderr, "Falha ao iniciar o teclado.\n");
	return 0;
  }

  return 1;
}

int main(void){

  ALLEGRO_DISPLAY *janela = NULL;
  ALLEGRO_BITMAP *background = NULL;
  ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
  ALLEGRO_TIMER *timer = NULL;
  bool redraw = true;

  if(!init_game()){
	fprintf(stderr, "Falha ao iniciar o jogo.\n");
	return -1;
  }

  janela = al_create_display(WIDTH, HEIGTH);
  if(!janela){
	fprintf(stderr, "Falha ao criar a janela.\n");
	return -1;
  }
  al_set_window_title(janela, "Game Chat Online");

  timer = al_create_timer(1.0 / FPS);

  struct Character _player1;
  struct Character *player1;

  // Precisa ser adicionado dinamicamente
  _player1 = new_player(1);
  player1 = &_player1;
  player1->sprite = al_load_bitmap("sprites/fenando.png");
  player1->sprite_size = 32;
  player1->sprite_len = 4;

  // Iniciando eventos
  fila_eventos = al_create_event_queue();
  al_register_event_source(fila_eventos, al_get_display_event_source(janela));
  al_register_event_source(fila_eventos, al_get_timer_event_source(timer));
  al_register_event_source(fila_eventos, al_get_keyboard_event_source());

  // TODO - menu
  background = al_load_bitmap("sprites/background.png");

  al_draw_bitmap(background, 0, 0, 0);
  al_draw_bitmap_region(player1->sprite, player1->current_frame, 0,
						player1->sprite_size, player1->sprite_size, 0, 0, 0);
  al_flip_display();

  al_start_timer(timer);
  while(1){
	ALLEGRO_EVENT evento;
	al_wait_for_event(fila_eventos, &evento);

	if(evento.type == ALLEGRO_EVENT_TIMER){
	  redraw = true;
	  idle_player(player1);
	}else if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
	  break;
	else if(evento.type == ALLEGRO_EVENT_KEY_DOWN){
	  switch(evento.keyboard.keycode){
		case ALLEGRO_KEY_UP:
		  move_player(player1, 1, WIDTH, HEIGTH);
		  break;
		case ALLEGRO_KEY_DOWN:
		  move_player(player1, 2, WIDTH, HEIGTH);
		  break;
		case ALLEGRO_KEY_LEFT:
		  move_player(player1, 3, WIDTH, HEIGTH);
		  break;
		case ALLEGRO_KEY_RIGHT:
		  move_player(player1, 4, WIDTH, HEIGTH);
		  break;
	  }
	}

	if(redraw && al_is_event_queue_empty(fila_eventos)){
	  redraw = false;
	  al_draw_bitmap(background, 0, 0, 0);
	  al_draw_bitmap_region(player1->sprite,
							(player1->current_frame * player1->sprite_size), 0,
							player1->sprite_size,
							player1->sprite_size,
							player1->posx,
							player1->posy, 0);
	  al_flip_display();
	}
  }

  al_destroy_display(janela);
  al_destroy_bitmap(background);
  al_destroy_event_queue(fila_eventos);

  return 0;
}
