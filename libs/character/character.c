#include <allegro5/allegro.h>
#include <stdio.h>

struct Character{
  int sprite_len;
  int sprite_size;
  int current_i;
  int current_frame;
  int posx;
  int posy;
  int frame_delay;
  ALLEGRO_BITMAP *sprite;
};

struct Character new_player(int player_preset){
  /* Presets:
	 1 - Dude
	 2 - Fenando
	 TODO - Loading de presets
   */

  struct Character player;
  player.current_frame = 0;
  player.current_i = 0;
  player.posx = 0;
  player.posy = 0;

  return player;
}

void idle_player(struct Character *player){
  int sprite_delay = 8;

  if(player->current_i >= sprite_delay){
	player->current_i = 0;
	player->current_frame ++;
  }

  if(player->current_frame > player->sprite_len - 1)
	player->current_frame = 0;

  player->current_i ++;
}

void move_player(struct Character *player, int movement, int width, int height){
  // TODO - Adicionar movimentos diagonais
  // TODO - Movimentacao com tecla pressionada
  int movement_speed = 12;

  switch(movement){
	case 1:
	  player->posy -= movement_speed;
	  break;
	case 2:
	  // Down
	  player->posy += movement_speed;
	  break;
	case 3:
	  // Left
	  player->posx -= movement_speed;
	  break;
	case 4:
	  // Right
	  player->posx += movement_speed;
	  break;
	default:
	  break;
  }

  if(player->posx < 0)
	player->posx = 0;
  if(player->posx > width)
	player->posx = width;
  if(player->posy < 0)
	player->posy = 0;
  if(player->posy > height)
	player->posy = height;

}
