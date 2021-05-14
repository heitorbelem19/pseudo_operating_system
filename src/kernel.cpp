#include "kernel.hpp"
#include "escalonador.hpp"
#include "gerenciador_es.hpp"
#include "gerenciador_mem.hpp"

// construtor
kernel::kernel() {
    set_modo_operacao(0);
}
// destrutor
kernel::~kernel() {

}

// metodos GET
escalonador kernel::get_escalonador()
{
    return esc;
}

GerenciadorES kernel::gerenciadorES()
{
    return gerenciadorES_;
}

gerenciador_mem kernel::get_gerenciador_mem()
{
    return g_memoria;
}

int kernel::get_modo_operacao()
{
    return modo_operacao;
}

// metodos SET

void kernel::set_escalonador(escalonador esc_entrada)
{
    esc = esc_entrada;
    return;
}

void kernel::setGerenciadorES(GerenciadorES gerenciadorES_entrada)
{
    gerenciadorES_ = gerenciadorES_entrada;
    return;
}

void kernel::set_modo_operacao(int modo_op)
{
    modo_operacao = modo_op;
}


void kernel::set_gerenciador_mem(gerenciador_mem gerenciador_memoria)
{
    g_memoria = gerenciador_memoria;
    return;
}


// metodos diversos

void kernel::verifica_entrada(int entrada, string arquivo)
{
    GerenciadorES gerenciador_entrada_saida;
    escalonador esc_temp;
    gerenciador_mem gerenciador_memoria;
    switch(entrada) {
        case 1:
        // Gerenciamento de processos
            esc_temp = escalonador();
            esc_temp.le_arquivo_entrada(arquivo);
            set_escalonador(esc_temp);
            set_modo_operacao(1);
            break;
        case 2:
        // gerenciamento de memoria
            gerenciador_memoria = gerenciador_mem();
            gerenciador_memoria.le_arquivo(arquivo);
            set_gerenciador_mem(gerenciador_memoria);
            set_modo_operacao(2);
            break;
        case 3:
        // gerenciamneto de E/S
        // chamar funcao de ler arquivo de processos
            gerenciador_entrada_saida = GerenciadorES();
            setGerenciadorES(gerenciador_entrada_saida);
            gerenciador_entrada_saida.imprimeDistanciaPercorrida(arquivo);
            break;
        default:
            cout << "Tipo de arquivo incorreto!" << endl;
    }

}

void kernel::verifica_modo_op(void)
{
    switch(modo_operacao) {
        case 1:
            gerencia_processos();
            break;
        case 2:
            gerencia_memoria();
            break;
        case 3:
        // gerenciamneto de E/S
            break;
        default:
            cout << "Tipo de arquivo incorreto!" << endl;
    }
}

void kernel::gerencia_processos()
{
    // FIFO
    esc.fifo();
    // SJF
    esc.sjf();
    // Round RObin
    esc.roundrobin(2);
    // PRINTA ESTATISTICAS
    esc.mostra_estatisticas();
    // escreve arquivo de saida
    esc.escreve_historico_processos();

}

void kernel::gerencia_memoria() {
    // chamar os métodos de gerencia de memoria
    g_memoria.fifo();




    estatisticas_paginacao result;
    result = g_memoria.get_estatisticas();
    cout << "FIFO: " << result.fifo_pf << endl;
    
}