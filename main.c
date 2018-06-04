#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>

const int WIDTH = 640;
const int HEIGTH = 480;

int main(void){

  ALLEGRO_DISPLAY *janela = NULL;
  ALLEGRO_BITMAP *background = NULL;
  ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;

  // Programacao defensiava xD
  if(!al_init()){
	fprintf(stderr, "Falha ao iniciar o allegro.\n");
	return -1;
  }

  if(!al_init_image_addon()){
	fprintf(stderr, "Falha ao iniciar o add-on de imagem.\n");
	return -1;
  }

  janela = al_create_display(WIDTH, HEIGTH);
  if(!janela){
	fprintf(stderr, "Falha ao criar a janela.\n");
	return -1;
  }

  background = al_load_bitmap("sprites/background.png");
  if(!background){
	fprintf(stderr, "Falha ao criar o background.\n");
	return -1;
  }

  fila_eventos = al_create_event_queue();
  if(!fila_eventos){
	fprintf(stderr, "Falha ao criar fila de eventos.");
	return -1;
  }

  // Iniciando
  al_register_event_source(fila_eventos, al_get_display_event_source(janela));
  al_draw_bitmap(background, 0, 0, 0);
  al_flip_display();

  while(1){
	ALLEGRO_EVENT evento;
	ALLEGRO_TIMEOUT timeout;
	al_init_timeout(&timeout, 0.05);

	int tem_evento = al_wait_for_event_until(fila_eventos, &evento, &timeout);

	if(tem_evento && evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
	  break;
	}

	al_draw_bitmap(background, 0, 0, 0);
	al_flip_display();
  }

  al_destroy_display(janela);
  al_destroy_event_queue(fila_eventos);

  return 0;
}
