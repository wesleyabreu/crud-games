/* 
   Autor: Wesley Abreu
   CRUD de Agenda de Games em C++
*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Declaração do Registro.
struct lista {

	int id;
	int ano;
	string nome, plataforma, descricao;

};

// Subprograma com a Interface do Menu.
void menu() {

    cout << "Escolha uma opcao:" << endl
		 << "[1] - Cadastrar" << endl
		 << "[2] - Listar" << endl
		 << "[3] - Pesquisar" << endl
		 << "[4] - Alterar" << endl
		 << "[5] - Excluir" << endl
		 << "[6] - Gravar" << endl
		 << "[7] - Sair" << endl
		 << endl << "Digite o numero correspondente a opcao desejada: ";

}

/* Subprograma que aloca os dados inseridos nos campos do registro, 
e gera um codigo de Identificador númerico único que começa em 1 para cada item cadastrado.*/
void cadastro(lista vetorGames[], int &memoria) {

	cout << "Nome: ";
	cin.ignore();
	getline(cin, vetorGames[memoria].nome);

	cout << "Ano de lancamento: ";
	cin >> vetorGames[memoria].ano;

	cout << "Plataforma: ";
	cin.ignore();
	getline(cin, vetorGames[memoria].plataforma);

	cout << "Descricao: ";
	getline(cin, vetorGames[memoria].descricao);

	vetorGames[memoria].id = memoria + 1;
	cout << endl << "Cadastro realizado com sucesso! (ID:" << vetorGames[memoria].id << ")" << endl << endl;
	
	memoria++;

}

// Subprograma responsável por imprimir TODOS os campos de TODOS os registros feitos.
void listar(lista vetorGames[], int memoria) {

    for ( int i = 0; i < memoria; i++ ) {
        cout << "Identificador: "
			 << vetorGames[i].id
			 << endl;

		cout << "Nome: "
			 << vetorGames[i].nome
			 << endl;

		cout << "Ano de lancamento: "
			 << vetorGames[i].ano
			 << endl;

		cout << "Plataforma: "
			 << vetorGames[i].plataforma
			 << endl;

		cout << "Descricao: "
			 << vetorGames[i].descricao
			 << endl << endl;
	}

}

// Subprograma auxiliar para imprimir os campos do registro encontrado no item "Pesquisar".
void imprimir(lista vetorGames[], int posicao) {

	cout << endl
		 << "Identificador: "
		 << vetorGames[posicao].id
		 << endl;

	cout << "Nome: "
		 << vetorGames[posicao].nome
		 << endl;

	cout << "Ano de lancamento: "
		 << vetorGames[posicao].ano
		 << endl;

	cout << "Plataforma: "
		 << vetorGames[posicao].plataforma
		 << endl;

	cout << "Descricao: "
		 << vetorGames[posicao].descricao
		 << endl << endl;

}

/* Subprograma que realiza a busca binária, para encontrar o elemento através do Identificador,
ou uma busca sequencial para encotrar o elemento através do Nome.*/
int pesquisa(lista vetorGames[], int memoria, bool retorno) {

	int metodo;
	// Receber qual o campo a ser pesquisado.
	cout << "Escolha uma opcao de busca:" << endl
		 << "[1] - Numero do identificador" << endl
		 << "[2] - Nome do jogo" << endl
		 << endl << "Digite o numero correspondente a opcao desejada: ";
	cin >> metodo;
	// Repetição para receber uma entrada válida.
	while ( ( metodo != 2 ) and ( metodo != 1 ) ) {
		cout << endl << "[!] *ERRO: Opcao invalida (1-2)" << endl
			 << endl << "Escolha uma opcao de busca:" << endl
			 << "[1] - Numero do identificador" << endl
			 << "[2] - Nome do jogo" << endl
			 << endl << "Digite o numero correspondente a opcao desejada: ";
		cin >> metodo;
	}

	int posicao = -1;

	if ( metodo == 1 ) {
		// Busca Binária.
		int buscaID;

		cout << "Digite o numero do identificador: ";
		cin >> buscaID;

		int pos_inicial, pos_final, meio;

		posicao = -1;
		pos_inicial = 0;
		pos_final = memoria - 1;

		while ( pos_inicial <= pos_final ) {
			meio = ( pos_inicial + pos_final ) / 2;
			if ( buscaID == vetorGames[meio].id ){
				posicao = meio;
				pos_inicial = pos_final + 1; // Parar while.
			}
			else {
                if ( buscaID > vetorGames[meio].id ) {
					pos_inicial = meio + 1;
				}
				else {
					pos_final = meio - 1;
				}
			}
		}
	}
	else {
		// Busca Sequencial.
		string buscaStr;

		cout << "Digite o nome do jogo: ";
		cin.ignore();
		getline(cin, buscaStr);

		int i = 0;

		while ( i < memoria ) {
			if ( vetorGames[i].nome == buscaStr ) {
				posicao = i;
				i = memoria; // Parar while.
			}
			i++;
		}

	}
	/* Return referente ao item "alterar" ou "excluir", retornando a posição do item encontrado.
	Este só é ativado quando chamado dentro do outro subprograma "alterar" ou "excluir".
	Onde ele é chamado com o parâmetro retorno com valor true.*/
	if ( retorno ) {
		return posicao;
	}
	// Item não encontrado.
	if ( posicao == -1 ) {
		cout << endl << endl
			 << "[!] *ERRO: Item nao encontrado."
			 << endl << endl;
	}
	// Item encontrado.
	else {
		imprimir(vetorGames, posicao);
	}

	return 0;
}

// Subprograma que verifica a existência de um item nos registros e faz,se possível, sua alteração.
void alterar(lista vetorGames[], int memoria) {

	int opcao;
	// Imprime o painel de opções com os campos a serem alterados.
	cout << "Escolha a opcao que deseja alterar: " << endl
		 << "[1] - Nome" << endl
		 << "[2] - Ano de lancamento" << endl
		 << "[3] - Plataforma" << endl
		 << "[4] - Descricao" << endl
		 << "[5] - Todos" << endl
		 << endl << "Digite o numero correspondente a opcao desejada: ";
	cin >> opcao;
	// Repetição para receber uma entrada válida.
	while ( ( opcao != 1 ) and ( opcao != 2 ) and ( opcao != 3 ) and ( opcao != 4 ) and ( opcao != 5 ) ) {
		cout << endl << "[!] *ERRO: Opcao invalida (1-5)" << endl
			 << "Escolha a opcao que deseja alterar: " << endl
			 << "[1] - Nome" << endl
			 << "[2] - Ano de lancamento" << endl
			 << "[3] - Plataforma" << endl
			 << "[4] - Descricao" << endl
			 << "[5] - Todos" << endl
			 << endl << "Digite o numero correspondente a opcao desejada: ";
		cin >> opcao;
	}

	cout << endl << "Escolha a opcao de busca para o item que deseja alterar:" << endl;
	// Chamada do subprograma "pesquisa", para definir qual o registro alvo da alteração.
	int item = pesquisa(vetorGames, memoria, true);
	// If's para executar cada ação disponível.
	if ( item != -1 ) {
		if ( opcao == 1 ) {
			cout << endl << "Nome antigo: " << vetorGames[item].nome
				 << endl << "Novo nome: ";
			getline(cin, vetorGames[item].nome);
		}
		else if ( opcao == 2 ) {
			cout << endl << "Ano de lancamento antigo: " << vetorGames[item].ano
				 << endl << "Novo ano de lancamento: ";
			cin >> vetorGames[item].ano;
		}
		else if ( opcao == 3 ) {
			cout << endl << "Plataforma antiga: " << vetorGames[item].plataforma
				 << endl << "Nova plataforma: ";
			cin.ignore();
			getline(cin, vetorGames[item].plataforma);
		}
		else if ( opcao == 4 ) {
			cout << endl << "Descricao antiga: " << vetorGames[item].descricao
				 << endl << "Nova descricao: ";
			getline(cin, vetorGames[item].descricao);
		}
		else if ( opcao == 5 ) {
			cout << endl << "Nome antigo: " << vetorGames[item].nome
				 << endl << "Novo nome: ";
			getline(cin, vetorGames[item].nome);

			cout << endl << "Ano de lancamento antigo: " << vetorGames[item].ano
				 << endl << "Novo ano de lancamento: ";
			cin >> vetorGames[item].ano;

			cout << endl << "Plataforma antiga: " << vetorGames[item].plataforma
				 << endl << "Nova plataforma: ";
			cin.ignore();
			getline(cin, vetorGames[item].plataforma);

			cout << endl << "Descricao antiga: " << vetorGames[item].descricao
				 << endl << "Nova descricao: ";
			getline(cin, vetorGames[item].descricao);
		}

		cout << endl << "Alteracao realizada com sucesso!" << endl << endl;

	}
	else {
		cout << endl << "[!] *ERRO: Item nao encontrado." << endl << endl;
	}

}

// Subprograma que verifica a existência de um item nos registros e faz,se possível, sua exclusão.
void excluir(lista vetorGames[], int &memoria) {

	cout << "Escolha a opcao de busca para o item que deseja excluir:" << endl;
	// Chamada do subprograma "pesquisa", para definir qual o registro alvo da exclusão.
	int item = pesquisa(vetorGames, memoria, true);
	
	if ( item != -1 ) {
			
		/* Mover todos os itens para a esquerda do vetor 
		a partir da próxima posição do item a ser excluído */
		for ( int i = item + 1; i < memoria; i++ ) {
			vetorGames[i - 1] = vetorGames[i];
		}
		/* Preencher com vazio a posição do último item cadastrado
		e decrementar a quantidade de itens cadastrados. */
		vetorGames[memoria] = {};
		memoria--;
			
		// Atualizar número de identificador de todos os itens.
		for ( int i = 0; i < memoria; i++ ) {
			vetorGames[i].id = i + 1;
		}
			
		cout << endl << "Exclusao realizada com sucesso! (ID's atualizadas)" << endl << endl;
			
	}
	else {
		cout << endl << "[!] *ERRO: Item nao encontrado." << endl << endl;
	}

}

// Subprograma que grava em um arquivo de texto todos os itens cadastrados.
void gravar(lista vetorGames[], int memoria) {
	
    ofstream arquivo("agenda_games.txt");
    
    for ( int i = 0; i < memoria; i++ ) {
		arquivo << "Identificador: "
				<< vetorGames[i].id
				<< endl;

		arquivo << "Nome: "
				<< vetorGames[i].nome
				<< endl;

		arquivo << "Ano de lancamento: "
				<< vetorGames[i].ano
				<< endl;

		arquivo << "Plataforma: "
				<< vetorGames[i].plataforma
				<< endl;

		arquivo << "Descricao: "
				<< vetorGames[i].descricao
				<< endl << endl;
    }
    
    arquivo.close();
    
    cout << "Todos os cadastros foram salvos com sucesso! (agenda_games.txt)" << endl << endl;
	
}

// Programa principal.
int main() {
	// Título do programa.
	cout << "AGENDA DE GAMES" << endl << endl;
	// Declaração do Vetor de Registros.
	lista vetorGames[100] = {};
	int opcao = 0, memoria = 0;
	// Receber o Número da ação do usuário até que ele deseje fechar o programa, usando o subprograma "menu".
	while ( opcao != 7 ) {
		menu();
		cin >> opcao;
		cout << endl;
		// Acionar o subprograma "cadastro" caso ainda haja espaço para registros.
		if ( opcao == 1 ) {
			if ( memoria < 100 ) {
				cadastro(vetorGames, memoria);
			}
			else {
				cout << "[!] *ERRO: Ja foram cadastrados 100 itens." << endl << endl;
			}
		}
		// Acionar o subprograma "listar" caso algum registro já tenha sido feito.
		else if ( opcao == 2 ) {
			if ( memoria > 0 ) {
				listar(vetorGames, memoria);
			}
			else {
				cout << "[!] *ERRO: Nao existe nenhum item cadastrado." << endl << endl;
			}
		}
		// Acionar o subprograma "pesquisa" caso algum registro já tenha sido feito.
		else if ( opcao == 3 ) {
			if ( memoria > 0 ) {
				pesquisa(vetorGames, memoria, false);
			}
			else {
				cout << "[!] *ERRO: Nao existe nenhum item cadastrado." << endl << endl;
			}
		}
		// Acionar o subprograma "alterar" caso algum registro já tenha sido feito.
		else if ( opcao == 4 ) {
			if ( memoria > 0 ) {
				alterar(vetorGames, memoria);
			}
			else {
				cout << "[!] *ERRO: Nao existe nenhum item cadastrado." << endl << endl;
			}
		}
		// Acionar o subprograma "excluir" caso algum registro já tenha sido feito.
		else if ( opcao == 5 ) {
			if ( memoria > 0 ) {
				excluir(vetorGames, memoria);
			}
			else {
				cout << "[!] *ERRO: Nao existe nenhum item cadastrado." << endl << endl;
			}
		}
		// Acionar o subprograma "gravar" caso algum registro já tenha sido feito.
		else if ( opcao == 6 ) {
			if ( memoria > 0 ) {
				gravar(vetorGames, memoria);
			}
			else {
				cout << "[!] *ERRO: Nao existe nenhum item cadastrado." << endl << endl;
			}
		}
		// Encerrar a execução do programa.
		else if ( opcao == 7 ) {
			int salvar;
			// Perguntar se deseja gravar os dados no disco antes de encerrar o programa.
			cout << "Deseja salvar os dados antes de sair?"
				 << endl << "[1] - Sim"
				 << endl << "[2] - Nao" << endl
				 << endl << "Digite o numero correspondente a opcao desejada: ";
			cin >> salvar;
			// Repetição para receber uma entrada válida.
			while ( ( salvar != 2 ) and ( salvar != 1 )  )  {
				cout << endl << "[!] *ERRO: Opcao invalida (1-2)" << endl
					 << endl << "Deseja salvar os dados antes de sair?"
					 << endl << "[1] - Sim"
					 << endl << "[2] - Nao" << endl
					 << endl << "Digite o numero correspondente a opcao desejada: ";
				cin >> salvar;
			}
			// Gravar os itens em um arquivo de texto caso escolha a opcao 1.
			if ( salvar == 1 ) {
				cout << endl;
				gravar(vetorGames, memoria);
				cout << "Programa finalizado!" << endl;
			}
			else {
				cout << endl << "Programa finalizado!" << endl;
			}
		}
		else {
			cout << "[!] *ERRO: Opcao invalida (1-7)." << endl << endl;
		}
	}

	return 0;
}
