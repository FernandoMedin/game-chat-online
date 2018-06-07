#ifndef CHARACTER_H_
#define CHARACTER_H_

struct Character{
  int sprite_len;
  int sprite_size;
  int current_i;
  int current_frame;
  int posx;
  int posy;
  ALLEGRO_BITMAP *sprite;
};

struct Character new_player(int player_preset);

void idle_player(struct Character *player);

void move_player(struct Character *player, int movement, int width, int height);

#endif // CHARACTER_H_
