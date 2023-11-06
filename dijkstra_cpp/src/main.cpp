#include "main.h"

int main() {
    Dijkstra dijkstra;
    dijkstra.a = {};
    dijkstra.vc = {};
    dijkstra.vnc = {};
    dijkstra.pacu = {};
    dijkstra.prev = {};

    Vertice v1 = {1};
    Vertice v2 = {2};
    Vertice v3 = {3};
    Vertice v4 = {4};
    Vertice v5 = {5};

    Arista a1 = {v1, v2, 5};
    Arista a2 = {v1, v3, 2};
    Arista a3 = {v1, v4, 3};
    Arista a4 = {v2, v5, 1};
    Arista a5 = {v3, v2, 2};
    Arista a6 = {v4, v2, 1};
    Arista a7 = {v4, v3, 4};
    Arista a8 = {v4, v5, 7};
    
    std::vector<Vertice> verticesprueba = {v1, v2, v3, v4, v5};
    std::vector<Arista> aristasprueba = {a1, a2, a3, a4, a5, a6, a7, a8};

    Grafo grafoPrueba;
    grafoPrueba.vertices = verticesprueba;
    grafoPrueba.aristas = aristasprueba;

    Dijkstra dijkstra_inicial = generarinicial(v1, aristasprueba, verticesprueba);
    
    Dijkstra resultado_iteracion = iteracion(dijkstra_inicial);

    Dijkstra resultado_caminocorto = caminocorto(resultado_iteracion);

    std::cout << "Dijkstra:" << std::endl;

    print_aristas(resultado_caminocorto.a);
    print_vercono(resultado_caminocorto.vc);
    print_vercono(resultado_caminocorto.vnc);
    print_pacu(resultado_caminocorto.pacu);
    print_prev(resultado_caminocorto.prev);

    return 0;
}

void print_aristas(std::vector<Arista> a)
{
    int i = 0;

    std::cout << "A: " << "[";

    for (const auto& arista : a) {
        std::cout << arista;

        if (i < a.size() - 1)
            std::cout << ", ";

        i++;
    }

    std::cout << "]" << std::endl;
}

void print_vercono(VC vc)
{
    int i = 0;

    std::cout << "VC: [";

    for (const auto& vertice : vc) {
        std::cout << vertice.nombre;

        if (i < vc.size() - 1)
            std::cout << ",";

        i++;
    }

    std::cout << "]" << std::endl;
}

void print_vernocono(VNC vnc)
{
    int i = 0;

    std::cout << "VNC: [";

    for (const auto& vertice : vnc) {
        std::cout << vertice.nombre;

        if (i < vnc.size() - 1)
            std::cout << ",";

        i++;
    }

    std::cout << "]" << std::endl;
}

void print_pacu(Pacu pacu)
{
    int i = 0;

    std::cout << "PACU: [";

    for (const auto& peso : pacu) {
        std::cout << peso;

        if (i < pacu.size() - 1)
            std::cout << ",";

        i++;
    }

    std::cout << "]" << std::endl;
}

void print_prev(Prev prev)
{
    int i = 0;

    std::cout << "PREV: [";

    for (const auto& vertice : prev) {
        std::cout << vertice.nombre;

        if (i < prev.size() - 1)
            std::cout << ",";

        i++;
    }

    std::cout << "]" << std::endl;
}
