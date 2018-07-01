/**
 * @file cadastro.cpp
 * @brief Implementação da classe Cadastro e seus métodos.
 * @author Bryan Brito
 * @author Leonardo Matos
 */

#include "gerencia.h"
#include "excecoes.h"

using namespace std;

namespace PetFera{

	/**
	* @brief Construtor padrão da classe Cadastrar
	*/
	Gerencia::Gerencia(){}

	/**
	* @brief Destrutor padrão da classe Cadastrar
	*/
	Gerencia::~Gerencia(){}

	/**
	* @brief 	Método que cadastra funcionário pela sua função
	* @params	String funcao referente a função do funcionário
	*/
	void Gerencia::cadastrar_funcionario(string funcao)
	{
		string aux;
		int id;
		string nome, cpf, tipo_sanguineo, especialidade;
		short idade;
		char fator_rh;

		cout << "Numero de identificação do funcionário (ID): ";
		getline(cin, aux);
		id = stoi(aux);

		cout << "\nNome do funcionário: ";
		getline(cin, nome);

		cout << "\nCPF do funcionário: ";
		getline(cin, cpf);


		cout << "\nIdade do funcionário: ";
		getline(cin, aux);
		idade = stoi(aux);

		cout << "\nTipo sanguíneo do funcionário: ";
		getline(cin, tipo_sanguineo);

		cout << "\nFator RH: ";
		getline(cin, aux);
		fator_rh = aux[0];

		cout << "\nEspecialidade do funcionário: ";
		getline(cin, especialidade);

		shared_ptr<Funcionario> novoFuncionario;

		if(funcao.compare("Tratador") == 0)
		{

			cout << "idade: " << idade << endl;
			cout << "funcao: " << funcao << endl;

			novoFuncionario = make_shared<Tratador>(id, funcao, nome, cpf, idade, tipo_sanguineo,
                    fator_rh, especialidade);
		}
		else if(funcao.compare("Veterinario") == 0)
		{
			novoFuncionario = make_shared<Veterinario>(id, funcao, nome, cpf, idade, tipo_sanguineo, 
                    fator_rh, especialidade);
		}

		m_lista_funcionario.insert(pair<int, shared_ptr<Funcionario>>(id, novoFuncionario));

		cout << endl <<"Cadastro feito com sucesso!" << endl;
	}

	/**
	* @brief	Métodd que busca um funcionário pelo seu ID
	* @params	Int id referente ao id de um funcionário cadastrado 
	*/
	void Gerencia::exibir_funcionario(int id)
	{
		map<int, shared_ptr<Funcionario>>::iterator func = m_lista_funcionario.find(id);
		
		cout << endl << m_lista_funcionario.size() << endl;

		if(func != m_lista_funcionario.end())
		{

			cout << *(func -> second);
		}
		else
		{
			cout << "Funcionário não encontrado" << endl;
		}
	}
	
	/**
	* @brief	Método que remove um funcionário pelo seu ID
	* @params	Int id referente ao id de um funcionário cadastrado 
	*/
	void Gerencia::remover_funcionario(int id)
	{
		map<int, shared_ptr<Funcionario>>::iterator func =  m_lista_funcionario.find(id);

		if(func != m_lista_funcionario.end())
		{
	
			m_lista_funcionario.erase(func);
			cout << "Removido com sucesso!" << endl;
	
		}
		else
		{
			cout << "Funcionário não encontrado" << endl;
		}
	}
	
	/**
	* @brief	Método que le dados de funcionários de um aquivo .csv 
	*/
	void Gerencia::ler_funcionarios()
	{
        ifstream func("data/funcionarios.csv");

        try{
    	    if(!func.is_open()) throw ErroLeitura();

            else{
                string cabecalho, linha;
                getline(func, cabecalho); //Para ler o cabeçalho do arquivo
            
                while(getline(func, linha))
                {
                    stringstream aux(linha);
                    string id, funcao, nome, cpf, idade, tipo_sang, fator_rh, especialidade;
                    
                    getline(aux, id, ';');
                    getline(aux, funcao, ';');
                    getline(aux, nome, ';');
                    getline(aux, cpf, ';');
                    getline(aux, idade,';');
                    getline(aux, tipo_sang, ';');
                    getline(aux, fator_rh, ';');
                    getline(aux, especialidade, ';');
                    
                    if(funcao == "Veterinario")
                    {
                        m_lista_funcionario.insert(pair<int, shared_ptr<Funcionario>>(stoi(id),
                                    make_shared<Veterinario>(stoi(id), funcao, nome, cpf, (short)stoi(idade), 
                                    tipo_sang, fator_rh[0], especialidade)));
                    }
                    else
                    {
                        m_lista_funcionario.insert(pair<int, shared_ptr<Funcionario>>(stoi(id),
                                    make_shared<Tratador>(stoi(id), funcao, nome, cpf, (short)stoi(idade),
                                    tipo_sang, fator_rh[0], especialidade)));
                    }
                }
            }
        }
        catch(ErroLeitura &erro){
            cerr << erro.what() << endl;
            exit(1);
        }
	}


	/**
	* @brief	Método que cadastra um animal pela sua classe
	* @params	String classe referente a classe de um animal
	*/
	void Gerencia::cadastrar_animal(string classe)
	{
		string aux;
		int id, veterinario_resp_id, tratador_resp_id;
		string nome, nome_cientifico, dieta, batismo;
		char sexo;
		double tamanho;

		cout << "Numero de identificação do animal (ID): ";
		getline(cin, aux);
		id = stoi(aux);

		cout << "\nNome do animal: ";
		getline(cin, nome);

		cout << "\nNome científico do animal: ";
		getline(cin, nome_cientifico);

		cout << "\nSexo do animal: ";
		getline(cin, aux);
		sexo = aux[0];

		cout << "\nTamanho em métros do animal: ";
		getline(cin, aux);
		tamanho = stof(aux);

		cout << "\nDieta predominante do animal: ";
		getline(cin, dieta);

		cout << "\nVeterinário associado do animal: ";
		getline(cin, aux);
		veterinario_resp_id = stoi(aux);

		cout << "\nTratador associado do animal: ";
		getline(cin, aux);
		tratador_resp_id = stoi(aux);

		cout << "\nNome de batismo do animal: ";
		getline(cin, batismo);
	
		shared_ptr<Funcionario> veterinario = nullptr;
		shared_ptr<Funcionario> tratador = nullptr;

		if(m_lista_funcionario.find(veterinario_resp_id) != m_lista_funcionario.end())
		{
			veterinario = m_lista_funcionario[veterinario_resp_id];
		}

		if(m_lista_funcionario.find(tratador_resp_id) != m_lista_funcionario.end())
		{
			tratador = m_lista_funcionario[tratador_resp_id];
		}


		if(classe.compare("Anfibio") == 0)
		{
			cadastrar_anfibio(id, nome, nome_cientifico, sexo, tamanho, dieta, veterinario, tratador, batismo);
		}
		else if(classe.compare("Ave") == 0)
		{
			cadastrar_ave(id, nome, nome_cientifico, sexo, tamanho, dieta, veterinario, tratador, batismo);
		}
		else if(classe.compare("Mamifero") == 0)
		{
			cadastrar_mamifero(id, nome, nome_cientifico, sexo, tamanho, dieta, veterinario, tratador, batismo);
		}
		else if(classe.compare("Reptil") == 0)
		{
			cadastrar_reptil(id, nome, nome_cientifico, sexo, tamanho, dieta, veterinario, tratador, batismo);
		}

		cout << "Cdastro realizado com sucesso." << endl;

	}

	void Gerencia::cadastrar_anfibio(int id, string nome, string nome_cientifico, char sexo, float tamanho, string dieta, 
							shared_ptr<Funcionario> veterinario, shared_ptr<Funcionario> tratador, string batismo)
	{
		int total_mudas;
		string aux, ultima_muda;

		cout << "\nTotal de mudas: ";
		getline(cin, aux);
		total_mudas = stoi(aux);

		cout << "\nData da ultima muda (dd/mm/aa): ";
		getline(cin, ultima_muda);

		shared_ptr<Animal> novoAnimal = make_shared<Anfibio>(id, "Anfibio", nome, nome_cientifico, sexo, tamanho, dieta, veterinario, tratador, batismo, total_mudas, ultima_muda);

		m_lista_animal.insert(pair<int, shared_ptr<Animal>>(id, novoAnimal));
	}

	void Gerencia::cadastrar_ave(int id, string nome, string nome_cientifico, char sexo, float tamanho, string dieta, 
							shared_ptr<Funcionario> veterinario, shared_ptr<Funcionario> tratador, string batismo)
	{
		int tamanho_dico, envergadura;
		string aux;

		cout << "\nTamanho do bico: ";
		getline(cin, aux);
		tamanho_dico = stoi(aux);

		cout << "\nEnvergadura: ";
		getline(cin, aux);
		envergadura = stoi(aux);

		shared_ptr<Animal> novoAnimal = make_shared<Ave>(id, "Ave", nome, nome_cientifico, sexo, tamanho, dieta, veterinario, tratador, batismo, tamanho_dico, envergadura);

		m_lista_animal.insert(pair<int, shared_ptr<Animal>>(id, novoAnimal));

	}

	void Gerencia::cadastrar_mamifero(int id, string nome, string nome_cientifico, char sexo, float tamanho, string dieta, 
							shared_ptr<Funcionario> veterinario, shared_ptr<Funcionario> tratador, string batismo)
	{
		string aux, cor;

		cout << "\nCor predominante: ";
		getline(cin, cor);

		shared_ptr<Animal> novoAnimal = make_shared<Mamifero>(id, "Mamifero", nome, nome_cientifico, sexo, tamanho, dieta, veterinario, tratador, batismo, cor);

		m_lista_animal.insert(pair<int, shared_ptr<Animal>>(id, novoAnimal));
	}

	void Gerencia::cadastrar_reptil(int id, string nome, string nome_cientifico, char sexo, float tamanho, string dieta, 
							shared_ptr<Funcionario> veterinario, shared_ptr<Funcionario> tratador, string batismo)
	{
		string aux, venenoso, tipo_veneno;
		bool eh_venenoso = false;

		cout << "\nAnimal venenoso (sim ou não): ";
		getline(cin, venenoso);

		if(venenoso.compare("sim") == 0)
		{
			eh_venenoso = true;
			cout << "\nTipo do veneno: ";
			getline(cin, tipo_veneno);
		}
		else
		{
			tipo_veneno = "Nenhum";
		}


		shared_ptr<Animal> novoAnimal = make_shared<Reptil>(id, "Reptil", nome, nome_cientifico, sexo, tamanho, dieta, veterinario, tratador, batismo, eh_venenoso, tipo_veneno);

		m_lista_animal.insert(pair<int, shared_ptr<Animal>>(id, novoAnimal));
	}


	void Gerencia::exibir_animal(int id)
	{
		map<int, shared_ptr<Animal>>::iterator animal = m_lista_animal.find(id);
		
		cout << endl << m_lista_animal.size() << endl;

		if(animal != m_lista_animal.end())
		{

			cout << *(animal -> second);
		}
		else
		{
			cout << "Animal nao encontrado" << endl;
		}
	}

	void Gerencia::remover_animal(int id)
	{
		map<int, shared_ptr<Animal>>::iterator animal =  m_lista_animal.find(id);

		if(animal != m_lista_animal.end())
		{
	
			m_lista_animal.erase(animal);
			cout << "Removido com sucesso!" << endl;
	
		}
		else
		{
			cout << "Animal não encontrado" << endl;
		}
	}

}
