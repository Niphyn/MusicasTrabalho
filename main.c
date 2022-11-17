#include <stdio.h>
#include <stdlib.h>
#include <Musica.h>
#include <Vector.h>
#include <Artista.h>
#include <Menu.h>
#include <Playlist.h>

Vector inicializa_artista(FILE *file_artistas)
{
	Vector vetor_artista = vector_create(ARTISTA);
	size_t retorno = 1;
	// INICIALIZA ARTISTAS
	while (1)
	{
		// cria um artista
		Artista artista = artista_create();

		// le os dados de um artista
		retorno = artista_read(file_artistas, artista);
		if (retorno == EOF) // encerra a funcao ao chegar ao fim do arquivo
		{
			break;
		}
		// adiciona a musica na ultima posicao do vetor
		vector_add(vetor_artista, artista);
	}
	fclose(file_artistas);
	return vetor_artista;
}

Vector inicializa_musica(FILE *file_musicas, Vector vetor_artista)
{
	Vector vetor_musica = vector_create(MUSICA);
	size_t retorno = 1;
	// INICIALIZA MUSICAS
	while (1)
	{
		// cria uma musica
		Musica musica = musica_create();

		// le os dados de uma musica
		retorno = musica_read(file_musicas, musica);
		if (retorno == EOF) // encerra a funcao ao chegar ao fim do arquivo
		{
			break;
		}

		// adiciona o indice dos artistas participantes na composicao da musica
		musica_add_idx_artistas(musica, vector_cria_lista_artistas(musica, vetor_artista));

		// adiciona a musica na ultima posicao do vetor
		vector_add(vetor_musica, musica);
	}
	fclose(file_musicas);
	return vetor_musica;
}

int main(int argc, char **argv)
{
	// Abertura de arquivos
	FILE *file_artistas = artista_abre_arquivo(argc, argv);
	FILE *file_musicas = musica_abre_arquivo(argc, argv);
	// Gravacao dos dados
	Vector vetor_artista = inicializa_artista(file_artistas);
	Vector vetor_musica = inicializa_musica(file_musicas, vetor_artista);
	Vector vetor_playlist = vector_create(PLAYLIST);

	// Inicializacao de variaveis
	Playlist playlist;
	int seletor, idx_p, idx_m, loop = TRUE, lista_tamanho, *lista_musicas = NULL;
	char linha[100];

	// PROGRAMA EM EXECUCAO
	while (loop)
	{
		imprime_menu();
		scanf("%s", linha); // uma forma de evitar que o programa quebre por causa de um erro do usuario
		seletor = atoi(linha);
		
		// Funcionalidades
		switch (seletor) 
		{
		case (INVALIDO):
			printf("Opcao invalida! Por favor digite novamente sua escolha!\n");
			break;
		case (BUSCAR_MUSICA):
			printf("Busque por uma musica :");
			scanf("%s%*c", linha);
			lista_tamanho = vector_busca_musicas(vetor_musica, linha, &lista_musicas); // encontra os indices das musicas 
			vector_print_lista_musicas(lista_musicas, lista_tamanho, vetor_musica, vetor_artista); // imprime a lista de musicas
			break;
		case (LISTAR_MUSICA):
			printf("Digite o índice da música a ser listada: ");
			scanf("%d", &idx_m);
			vector_listar_musica(idx_m, vetor_musica, vetor_artista); // lista todos os atributos da musica e dos artistas que a compoe
			break;
		case (CRIAR_PLAYLIST):
			playlist = playlist_create(); // cria uma playlist
			vector_add(vetor_playlist, playlist); // salva a playlist no vetor de playlists
			printf("\nPlaylist criada com sucesso!\n");
			break;
		case (LISTAR_PLAYLISTS):
			vector_print(vetor_playlist);
			break;
		case (LISTAR_UMA_PLAYLIST):
			// to do: preciso da funcao da gabriela
			printf("Digite o indice da playlist que deseja exibir: ");
			scanf("%d", &idx_p);
			playlist = vector_get(vetor_playlist, idx_p);
			playlist_print(playlist);
			break;
		case (ADICIONAR_MUSICA_PLAYLIST):
			printf("Digite o indice da musica a ser adicionada: ");
			scanf("%d", &idx_m);
			printf("Digite o indice da playlist que deseja adicionar a musica selecionada: ");
			scanf("%d", &idx_p);
			playlist = vector_get(vetor_playlist, idx_p); // recupera a playlist que sera alterada
			playlist_add(playlist, idx_m); // adiciona a musica/altera a playlist
			break;
		case (RECOMENDAR_MUSICA):
			break;
		case (GERAR_RELATORIO):
			vector_gerar_relatorio(vetor_playlist,vetor_artista);
			break;
		case (SAIR):
			printf("SAINDO...\n");
			loop = FALSE; // quebra o loop
			continue;
		default:
			printf("Opcao invalida! Por favor digite novamente sua escolha!\n");
			break;
		}
		tela_espera();
	}
	vector_destroy(vetor_playlist);
	vector_destroy(vetor_artista);
	vector_destroy(vetor_musica);
	return 0;
}
