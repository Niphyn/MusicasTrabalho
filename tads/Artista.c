#include "Artista.h"

struct artista
{
    char *id;
    float seguidores;
    char **generos;
    int n_generos;
    char *nome_do_artista;
    int popularidade;
};

enum artista_atributos
{
    ID,
    SEGUIDORES,
    GENEROS,
    NOME_DO_ARTISTA,
    POPULARIDADE
};

FILE *artista_abre_arquivo(int argc, char **argv)
{
    char dir[100] = "data/artists_full.csv";
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
        printf("O diretorio de artistas '%s' nao existe!\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    return file;
}
// aloca espaco para uma artista
Artista artista_create()
{
    return (Artista)calloc(1, sizeof(struct artista));
}
// ler arquivo de artista
size_t artista_read(FILE *file, Artista artista)
{
    char *linha = NULL;
    size_t len = 0, retorno_get;
    // leitura de uma linha por vez ate o final do arquivo
    retorno_get = getline(&linha, &len, file);
    if (retorno_get == EOF)
    {
        free(artista);
        free(linha);
        return (retorno_get);
    }
    artista_tok(artista, linha); // quebra a string lida e salva no TAD Musica
    free(linha);
    return retorno_get;
}
// separar as informacoes do artista em tokens e armazena em artista
void artista_tok(Artista artista, char *artista_str)
{
    char *token = NULL;
    int len = 0;
    for (int seletor = 0; seletor < QTD_ATRIBUTOS_ARTISTA; seletor++)
    {
        token = strsep(&artista_str, ";");

        switch (seletor)
        {
        case (ID):
            artista->id = artista_salva_string(token);
            break;
        case (SEGUIDORES):

            artista->seguidores = artista_salva_float(token);
            break;
        case (GENEROS):
            artista->generos = artista_salva_generos(token, &artista->n_generos);
            break;
        case (NOME_DO_ARTISTA):
            artista->nome_do_artista = artista_salva_string(token);
            break;
        case (POPULARIDADE):
            artista->popularidade = artista_salva_inteiro(token);
            break;
        }
    }
}

// imprimir uma artista
void artista_print(Artista artista)
{
    artista_print_nome(artista);
    artista_print_id(artista);
    artista_print_seguidores(artista);
    artista_print_generos(artista);
    artista_print_popularidade(artista);
}
// funcoes auxiliares de impressao individual
void artista_print_id(Artista artista)
{
    printf("ID: %s\n", artista_get_id(artista));
}
void artista_print_seguidores(Artista artista)
{
    printf("SEGUIDORES: %.2f\n", artista_get_seguidores(artista));
}
void artista_print_nome(Artista artista)
{
    printf("NOME_DO_ARTISTA: %s\n", artista_get_nome(artista));
}
void artista_print_popularidade(Artista artista)
{
    printf("POPULARIDADE: %d\n", artista_get_popularidade(artista));
}
void artista_print_generos(Artista artista)
{
    char **generos = artista_get_generos(artista);
    printf("GENEROS: ");
    for (int i = 0; i < artista->n_generos; i++)
    {
        printf("%s  ", generos[i]);
    }
    printf("\n");
}

// salva atributos da artista
char *artista_salva_string(char *string_in)
{
    char *string_out = strdup(string_in); // copia as informacoes de uma string para outra
    return string_out;                    // retorna seu ponteiro
}
float artista_salva_float(char *float_str)
{
    return atof(float_str); // converte para float
}
int artista_salva_inteiro(char *inteiro_str)
{
    return atoi(inteiro_str); // converte para inteiro
}

// os generos sao tratados de forma diferente
// na string sao separados por um pipeline
// entao seu conteudo eh separado e salvo em um char**
char **artista_salva_generos(char *generos_str, int *generos_len)
{

    int n_alocados = 1, n_add = 0;
    char **generos_lista = (char **)malloc(n_alocados * sizeof(char *));
    char *token = generos_str;
    // recebe uma string de generos e separa a cada pipeline
    while (1)
    {
        // quebra o genero a cada pipeline
        token = strsep(&generos_str, "|");

        if (token != NULL)
        { // uma string valida
            n_add++;
            if (n_add == n_alocados)
            {
                n_alocados *= 2;
                generos_lista = realloc(generos_lista, sizeof(char *) * n_alocados);
            }
        }
        else
        {
            // se a string acaba, o loop eh encerrado
            break;
        }
        generos_lista[n_add - 1] = strdup(token); // salva o genero na lista
    }
    *generos_len = n_add;
    return generos_lista;
}
// desaloca artista
void artista_destroy(Artista artista)
{
    free(artista->id);
    for (int i = 0; i < artista->n_generos; i++)
    {
        free(artista->generos[i]);
    }
    free(artista->generos);
    free(artista->nome_do_artista);
    free(artista);
}

char *artista_get_id(Artista artista)
{
    return artista->id; // recupera  o id
}
float artista_get_seguidores(Artista artista)
{
    return artista->seguidores; // recupera seguidor
}
char **artista_get_generos(Artista artista)
{
    return artista->generos; // recupera genero
}
int artista_get_n_generos(Artista artista)
{
    return artista->n_generos; // recupera quantidade de generos
}
char *artista_get_nome(Artista artista)
{
    return artista->nome_do_artista; // recupera o nome do artista
}
int artista_get_popularidade(Artista artista)
{
    return artista->popularidade; // recupera a popularidade
}

int artista_compara(char *str_artista,Artista artista){
    char *retorno;
		retorno = strstr(artista_get_nome(artista),str_artista);
		if(retorno != NULL){
			return 1;
			//caso igual
		}else{
			return 0;
			//caso não igual
		}
}
