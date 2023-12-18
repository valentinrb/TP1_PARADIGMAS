#include "dijkstra.h"

int at(const std::vector<int>& xs, int i) {
    if (i > 0 && i <= static_cast<int>(xs.size())) {
        return xs[i - 1];
    } else {
        throw std::out_of_range("Index out of range");
    }
}

VC vercono(const VC& verticesprueba, const Vertice& v) {
    VC result;

    std::copy_if(verticesprueba.begin(), verticesprueba.end(), std::back_inserter(result),
                 [v](const Vertice& x) { return x == v; });

    return result;
}

VNC vernocono(const VC& verticesprueba, const Vertice& v) {
    VNC result;

    std::copy_if(verticesprueba.begin(), verticesprueba.end(), std::back_inserter(result),
                 [v](const Vertice& x) { return x != v; });

    return result;
}

int costo(const std::vector<Arista>& as, const Vertice& o, const Vertice& d) {
    auto it = std::find_if(as.begin(), as.end(), [o, d](const Arista& a) {
        return a.orig == o && a.dest == d;
    });

    return (it != as.end()) ? it->peso : oo;
}

Vertice verticenulo() {
    return {0};
}

VC previnicial(const VC& verticesprueba, const Vertice& v) {
    VC resultado;

    std::transform(verticesprueba.begin(), verticesprueba.end(), std::back_inserter(resultado), [v](const Vertice& x) {
                       return (x == v) ? v : verticenulo();
                   });

    return resultado;
}

std::vector<int> acuinicial(const std::vector<Arista>& aristasprueba, const std::vector<Vertice>& verticesprueba, const Vertice& v) {
    std::vector<int> resultado;

    std::transform(verticesprueba.begin(), verticesprueba.end(), std::back_inserter(resultado), [aristasprueba, v](const Vertice& x) {
                       return (x == v) ? 0 : costo(aristasprueba, v, x);
                   });

    return resultado;
}

template<typename T>
std::vector<T> cambiarnth(const T& a, int n, const std::vector<T>& lista) {
    if (n < 0 || n >= lista.size())
        return lista;

    std::vector<T> resultado;
    resultado.reserve(lista.size());

    std::transform(lista.begin(), lista.end(), std::back_inserter(resultado), [a, n, i = 0](const T& elem) mutable {
                       return (i++ == n) ? a : elem;
                   });

    return resultado;
}

Dijkstra generarinicial(const Vertice& v, const std::vector<Arista>& aristasprueba, const std::vector<Vertice>& verticesprueba) {
    return {aristasprueba, vercono(verticesprueba, v), vernocono(verticesprueba, v), acuinicial(aristasprueba, verticesprueba, v), previnicial(verticesprueba, v)};
}

Peso getpeso(const Pacu& p, const Vertice& v) {
    try {
        return at(p, v.nombre);
    } catch (const std::out_of_range& e) {
        std::cout << "Exception: " << e.what() << std::endl;

        return -1;
    }
}

std::pair<Pacu, std::vector<Vertice>> actpeso(const std::pair<Pacu, std::vector<Vertice>>& pares, const std::vector<Arista>& as) {
    if (as.empty()) {
        return pares;
    }

    auto a = as[0];
    auto rest = std::vector<Arista>(as.begin() + 1, as.end());

    Peso costonuevo = a.peso + getpeso(pares.first, a.orig);
    int indiceDest = a.dest.nombre - 1;
    int indiceOrig = a.orig.nombre - 1;

    auto cambiar = cambiarnth(costonuevo, indiceDest, pares.first);
    auto cambiarpre = cambiarnth(a.dest, indiceOrig, pares.second);

    if (costonuevo < getpeso(pares.first, a.dest)) {
        return actpeso(std::make_pair(cambiar, cambiarpre), rest);
    }

    return actpeso(pares, rest);
}

Dijkstra iteracion(const Dijkstra& d) {
    auto next_vertex = *std::min_element(d.vnc.begin(), d.vnc.end(), [&d](const Vertice& x, const Vertice& y) {
        return getpeso(d.pacu, x) < getpeso(d.pacu, y);
    });

    std::vector<Vertice> new_vc = d.vc;
    new_vc.insert(new_vc.begin(), next_vertex);

    std::vector<Vertice> new_vnc;
    std::copy_if(d.vnc.begin(), d.vnc.end(), std::back_inserter(new_vnc),
                 [next_vertex](const Vertice& vertex) { return vertex != next_vertex; });

    std::vector<Arista> acandidata;
    std::copy_if(d.a.begin(), d.a.end(), std::back_inserter(acandidata),
                 [next_vertex](const Arista& a) { return a.orig == next_vertex; });

    std::vector<Arista> avalidas;
    std::copy_if(acandidata.begin(), acandidata.end(), std::back_inserter(avalidas),
                 [&new_vnc](const Arista& a) { return std::find(new_vnc.begin(), new_vnc.end(), a.dest) != new_vnc.end(); });

    auto resul = actpeso(std::make_pair(d.pacu, d.prev), avalidas);

    return {d.a, new_vc, new_vnc, resul.first, resul.second};
}

Dijkstra caminocorto(const Dijkstra& d) {
    if (d.vnc.empty())
        return d;
    else
        return caminocorto(iteracion(d));
}