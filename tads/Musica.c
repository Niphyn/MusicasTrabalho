#include "Musica.h"

enum
{
	ID,
	NOME_DA_MUSICA,
	POPULARITY,
	DURACAO_MS,
	EXPLICT,
	ARTISTS,
	ID_ARTISTS,
	DATA_LANCAMENTO,
	DANCEABILITY,
	ENERGY,
	KEY,
	LOUNDNESS,
	MODE,
	SPECHINESS,
	ACOUSTINES,
	INSTRUMENTALNES,
	LIVENESS,
	VALENCE,
	TEMPO,
	TIME_ASSIGNATURE
} Musca_atributos;

// informacoes do tipo musica
struct musica
{
	char *id;
	char *nome_da_musica;
	int popularity;
	int duracao_ms;
	int explict;
	int n_artistas;
	char **artists;
	char **id_artists;
	int *idx_artists;
	char *data_lancamento;
	float danceability;
	float energy; //
	int key;
	float loundness;
	int mode;				//
	float speechiness;		//
	float acousticness;		//
	float instrumentalness; //
	float liveness;			//
	float valence;			//
	float tempo;
	int time_assignature;
};

FILE *musica_abre_arquivo(int argc, char **argv)
{
	char dir[100] = "data/tracks_2.csv";
	// verifica se o diretorio foi informado como argumento
	// if (argc > 1)
	// {
	// 	sprintf(dir, "%s", argv[1]);
	// }
	// else
	// {
	// 	printf("Diretorio nao informado!\n");
	// 	exit(EXIT_FAILURE);
	// }
	// verifica se o arquivo aberto eh valido
	FILE *file = fopen(dir, "r");

	if (file == NULL)
	{
		printf("O diretorio de musica'%s' nao existe!\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	return file;
}

Musica musica_create()
{
	return (Musica)calloc(1, sizeof(struct musica));
}

size_t musica_read(FILE *file, Musica musica)
{
	char *linha = NULL;
	size_t len = 0, retorno_get;
	// leitura de uma linha por vez ate o final do arquivo
	retorno_get = getline(&linha, &len, file);
	if (retorno_get == EOF)
	{	
		free(musica);
		free(linha);
		return (retorno_get);
	}
	// printf("linha: %s", linha);
	musica_tok(musica, linha); // quebra a string lida e salva no TAD Musica
	free(linha);
	return retorno_get;
}

// separar as musicas
void musica_tok(Musica musica, char *musica_str)
{
	char *token = NULL;
	for (int seletor = 0; seletor < QTD_ATRIBUTOS_MUSICA; seletor++)
	{
		token = strsep(&musica_str, ";");
		// printf("i: %d token: %s\n",seletor, token);
		switch (seletor)
		{
		case (ID):
			musica->id = musica_salva_string(token);
			break;
		case (NOME_DA_MUSICA):
			musica->nome_da_musica = musica_salva_string(token);
			break;
		case (POPULARITY):
			musica->popularity = musica_salva_inteiro(token);
			break;
		case (DURACAO_MS):
			musica->duracao_ms = musica_salva_inteiro(token);
			break;
		case (EXPLICT):
			musica->explict = musica_salva_inteiro(token);
			break;
		case (ARTISTS):
			musica->artists = musica_salva_artistas(token, &musica->n_artistas);
			break;
		case (ID_ARTISTS):
			musica->id_artists = musica_salva_artistas(token, &musica->n_artistas);
			break;
		case (DATA_LANCAMENTO):
			musica->data_lancamento = musica_salva_string(token);
			break;
		case (DANCEABILITY):
			musica->danceability = musica_salva_float(token);
			break;
		case (ENERGY):
			musica->energy = musica_salva_float(token);
			break;
		case (KEY):
			musica->key = musica_salva_inteiro(token);
			break;
		case (LOUNDNESS):
			musica->loundness = musica_salva_float(token);
			break;
		case (MODE):
			musica->mode = musica_salva_inteiro(token);
			break;
		case (SPECHINESS):
			musica->speechiness = musica_salva_float(token);
			break;
		case (ACOUSTINES):
			musica->acousticness = musica_salva_float(token);
			break;
		case (INSTRUMENTALNES):
			musica->instrumentalness = musica_salva_float(token);
			break;
		case (LIVENESS):
			musica->liveness = musica_salva_float(token);
			break;
		case (VALENCE):
			musica->valence = musica_salva_float(token);
			break;
		case (TEMPO):
			musica->tempo = musica_salva_float(token);
			break;
		case (TIME_ASSIGNATURE):
			musica->time_assignature = musica_salva_inteiro(token);
			break;
		}
	}
}

// imprimir uma musica
void musica_print(Musica musica)
{
	musica_print_nome(musica);
	musica_print_id(musica);
	musica_print_popularidade(musica);
	musica_print_duracao(musica);
	musica_print_explict(musica);
	musica_print_data_lancamento(musica);
	musica_print_danceability(musica);
	musica_print_energy(musica);
	musica_print_key(musica);
	musica_print_loundness(musica);
	musica_print_mode(musica);
	musica_print_spechiness(musica);
	musica_print_instrumentalness(musica);
	musica_print_liveness(musica);
	musica_print_tempo(musica);
	musica_print_time_assignarure(musica);
}

// imprime cada atributo da musica de forma individual
void musica_print_id(Musica musica)
{
	printf("ID: %s\n", musica_get_id(musica));
}
void musica_print_nome(Musica musica)
{
	printf("NOME: %s\n", musica_get_nome(musica));
}
void musica_print_popularidade(Musica musica)
{
	printf("POPULARIDADE: %d\n", musica_get_popularidade(musica));
}
void musica_print_duracao(Musica musica)
{
	printf("DURACAO MS: %d\n", musica_get_duracao(musica));
}
void musica_print_explict(Musica musica)
{
	printf("EXPLICT: %d\n", musica_get_explict(musica));
}
void musica_print_artistas(Musica musica)
{
	int *indice_artistas = musica_get_indices(musica);
	printf("ARTISTAS: ");
	for (int i = 0; i < musica->n_artistas; i++)
	{
		printf("[%d] ", indice_artistas[i]);
	}
	printf("\n");
}
void musica_print_data_lancamento(Musica musica)
{
	printf("DATA DE LANCAMENTO: %s\n", musica_get_data_lancamento(musica));
}
void musica_print_danceability(Musica musica)
{
	printf("DANCEABILITY: %.2f\n", musica_get_danceability(musica));
}
void musica_print_energy(Musica musica)
{
	printf("ENERGY: %.2f\n", musica_get_energy(musica));
}
void musica_print_key(Musica musica)
{
	printf("KEY: %d\n", musica_get_key(musica));
}
void musica_print_loundness(Musica musica)
{
	printf("LOUNDNESS: %.2f\n", musica_get_loundness(musica));
}
void musica_print_mode(Musica musica)
{
	printf("MODE: %d\n", musica_get_mode(musica));
}
void musica_print_spechiness(Musica musica)
{
	printf("SPECHINESS: %.2f\n", musica_get_spechiness(musica));
}
void musica_print_instrumentalness(Musica musica)
{
	printf("INSTRUMENTALNESS: %.2f\n", musica_get_instrumentalness(musica));
}
void musica_print_liveness(Musica musica)
{
	printf("LIVENESS: %.2f\n", musica_get_liveness(musica));
}
void musica_print_tempo(Musica musica)
{
	printf("TEMPO: %.2f\n", musica_get_tempo(musica));
}
void musica_print_time_assignarure(Musica musica)
{
	printf("TIME ASSIGNATURE: %d\n", musica_get_time_assignature(musica));
}

// desaloca uma musica
void musica_destroy(Musica musica)
{
	free(musica->id);
	for (int i = 0; i < musica->n_artistas; i++)
	{
		free(musica->artists[i]);
		free(musica->id_artists[i]);
	}
	free(musica->artists);
	free(musica->id_artists);
	free(musica->idx_artists);
	free(musica->data_lancamento);
	free(musica->nome_da_musica);
	free(musica);
}

/*Insercao de informacoes no struct*/
char *musica_salva_string(char *string_in)
{
	char *string_out = strdup(string_in); // copia as informacoes de uma string para outra
	return string_out;					  // retorna seu ponteiro
}
float musica_salva_float(char *float_str)
{
	return atof(float_str); // converte para float
}
int musica_salva_inteiro(char *inteiro_str)
{
	return atoi(inteiro_str); // converte para inteiro
}
char **musica_salva_artistas(char *artistas_str, int *n_artistas)
{
	int n_alocados = 1, n_add = 0;
	char **artistas_lista = (char **)malloc(n_alocados * sizeof(char *));
	char *token = artistas_str;
	// recebe uma string de artistas e separa a cada pipeline
	while (1)
	{
		// quebra o artista a cada pipeline
		token = strsep(&artistas_str, "|");

		if (token != NULL)
		{ // uma string valida
			n_add++;
			if (n_add == n_alocados)
			{
				n_alocados *= 2;
				artistas_lista = realloc(artistas_lista, sizeof(char *) * n_alocados);
			}
		}
		else
		{
			// se a string acaba, o loop eh encerrado
			break;
		}
		artistas_lista[n_add - 1] = strdup(token); // salva o artista na lista
	}
	*n_artistas = n_add;
	return artistas_lista;
}

// recupera atributos de musica de orma individual
char *musica_get_nome(Musica musica)
{
	return musica->nome_da_musica;
}
int musica_get_popularidade(Musica musica)
{
	return musica->popularity;
}
int musica_get_duracao(Musica musica)
{
	return musica->duracao_ms;
}
int musica_get_explict(Musica musica)
{
	return musica->explict;
}
int *musica_get_indices(Musica musica)
{
	return musica->idx_artists;
}
char *musica_get_data_lancamento(Musica musica)
{
	return musica->data_lancamento;
}
float musica_get_danceability(Musica musica)
{
	return musica->danceability;
}
float musica_get_energy(Musica musica)
{
	return musica->energy;
}
int musica_get_key(Musica musica)
{
	return musica->key;
}
float musica_get_loundness(Musica musica)
{
	return musica->loundness;
}
int musica_get_mode(Musica musica)
{
	return musica->mode;
}
float musica_get_spechiness(Musica musica)
{
	return musica->speechiness;
}
float musica_get_instrumentalness(Musica musica)
{
	return musica->instrumentalness;
}
float musica_get_liveness(Musica musica)
{
	return musica->liveness;
}
float musica_get_tempo(Musica musica)
{
	return musica->tempo;
}
int musica_get_time_assignature(Musica musica)
{
	return musica->time_assignature;
}
char *musica_get_id(Musica musica)
{
	return musica->id;
}
char **musica_get_lista_artistas(Musica musica)
{
	return musica->id_artists;
}
int musica_get_n_artistas(Musica musica)
{
	return musica->n_artistas;
}
Musica musica_add_idx_artistas(Musica musica, int *idx_artistas)
{
	musica->idx_artists = idx_artistas;
	return musica;
}

// compara uma string com o nome de uma musica 
int musica_compara(char *str_musica,Musica musica){
	char *retorno;
		retorno = strstr(musica_get_nome(musica),str_musica);
		if(retorno != NULL){
			return 1;
			//caso igual
		}else{
			return 0;
			//caso não igual
		}
}

void musica_abrir_spotify(Musica musica){
	char escolha;
    printf("Abrir música no spotify ? [s/n] ");
    scanf("%*c%c",&escolha);

    if(escolha == 's'){
		char link[300];
		sprintf(link,"start https://open.spotify.com/track/%s",musica_get_id(musica));
        system(link);
    }
}
