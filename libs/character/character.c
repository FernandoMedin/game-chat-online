#include <allegro5/allegro.h>
#include <stdio.h>

struct Character{
  int sprite_len;
  int sprite_size;
  int current_i;
  int current_frame;
  int posx;
  int posy;
  ALLEGRO_BITMAP *sprite;
};

struct Character new_player(int player_preset){
  /* Presets:
	 1 - Dude
	 2 - Fenando
   */

  struct Character player;
  player.current_frame = 0;
  player.current_i = 0;
  player.posx = 0;
  player.posy = 0;

  return player;
}

void idle_player(struct Character *player){
  int sprite_delay = 10;

  if(player->current_i >= sprite_delay){
	player->current_i = 0;
	player->current_frame ++;
  }

  if(player->current_frame > player->sprite_len - 1)
	player->current_frame = 0;

  player->current_i ++;
}

void move_player(struct Character *player){
}
