#include "Playlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ALOCAR_INICIAL 100

struct playlist
{
    char *nome;   // nome da playlist
    int *musicas; // listas de musicas da playlist
    int n_add;
    int n_alocados;
};

Playlist playlist_create()
{

    Playlist playlist = (Playlist)malloc(sizeof(struct playlist));
    playlist->nome = playlist_nome_create();
    playlist->n_alocados = ALOCAR_INICIAL;
    playlist->musicas = (int *)malloc(playlist->n_alocados * sizeof(int));
    playlist->n_add = 0;
    return playlist;
}

int playlist_get_musica(Playlist playlist,int idx){
    return playlist->musicas[idx];
}

char *playlist_nome_create()
{
    char nome_temp[200];
    printf("Digite o nome da nova playlist: ");
    scanf("%s%*c", nome_temp);
    char *nome = strdup(nome_temp);
    return nome;
}

char* playlist_get_nome(Playlist playlist){
    return playlist->nome;
}
int playlist_get_n_musicas(Playlist playlist){
    return playlist->n_add;
}
void playlist_print(Playlist playlist)
{
    printf("NOME: %s\n", playlist->nome);
    printf("MUSICAS: ");
    for (int i = 0; i < playlist->n_add; i++)
    {
        printf("[%d] ", playlist->musicas[i]);
    }
    printf("\n\n");
}

void playlist_add(Playlist playlist, int idx_musica)
{
    if (playlist->n_alocados == playlist->n_add)
    {
        playlist->n_alocados *= 2;
        playlist->musicas = (int *)realloc(playlist->musicas, playlist->n_alocados * sizeof(int));
    }
    playlist->musicas[playlist->n_add] = idx_musica;
    playlist->n_add++;
}

void playlist_destroy(Playlist playlist)
{
    free(playlist->nome);
    free(playlist->musicas);
    free(playlist);
}
