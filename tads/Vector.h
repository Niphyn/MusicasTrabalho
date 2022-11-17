#ifndef _VECTOR_H_
#define _VECTOR_H_
#define STR_IGUAIS 0

typedef enum type
{
    MUSICA,
    ARTISTA,
    PLAYLIST,
    INT,
    FLOAT,
    CHAR
} Type;

typedef void *VectorType;

typedef struct vector *Vector;

// aloca espaco e inicializa um vector para musicas e artistas
Vector vector_create(enum type tipo);

// adiciona um elemento ao final de um vector
void vector_add(Vector v, VectorType elem);

// retorna o elemento da posicao idx do vector
VectorType vector_get(Vector v, int idx);

// recupera  o tamanho do vetor
int vector_size(Vector v);

// encontra a posicao de determinado elemento da lista
int vector_find_id(Vector v, char *id);
// cria uma lista de indices dos artistas de uma musica
int *vector_cria_lista_artistas(VectorType musica, Vector artistas);

// libera toda a memoria alocada em v
void vector_destroy(Vector v);

void vector_print(Vector v);

int vector_busca_musicas(Vector vetor_musica,char *linha,int **lista_musicas);

void vector_print_lista_musicas(int *lista_musicas, int  lista_tamanho, Vector vetor_musica, Vector vetor_artista);

void vector_listar_musica(int idx_m, Vector vetor_musica, Vector vetor_artista);

void vector_gerar_relatorio(Vector vetor_playlist, Vector vetor_artistas);

void vector_ordenar_musicas(Vector vetor_musicas, Vector vetor_qtd);

void vector_ordenar_artistas(Vector vetor_artistas, Vector vetor_qtd);

#endif
