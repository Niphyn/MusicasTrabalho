#ifndef _PLAYLIST_H_
#define _PLAYLIST_H_

typedef struct playlist *Playlist;

Playlist playlist_create();
char *playlist_nome_create();
void playlist_print(Playlist playlist);
void playlist_add(Playlist playlist, int idx_musica);
void playlist_destroy(Playlist playlist);
char* playlist_get_nome(Playlist playlist);
int playlist_get_n_musicas(Playlist playlist);

int playlist_get_musica(Playlist playlist,int idx);

#endif
