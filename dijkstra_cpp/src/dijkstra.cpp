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
    for (const auto& x : verticesprueba) {
        if (x == v) {
            result.push_back(x);
        }
    }
    return result;
}

VNC vernocono(const VC& verticesprueba, const Vertice& v) {
    VNC result;
    for (const auto& x : verticesprueba) {
        if (x != v) {
            result.push_back(x);
        }
    }
    return result;
}

int costo(const std::vector<Arista>& as, const Vertice& o, const Vertice& d) {
    std::vector<Arista> filtrado;
    for (const auto& a : as) {
        if (a.orig.nombre == o.nombre && a.dest.nombre == d.nombre) {
            filtrado.push_back(a);
        }
    }

    if (filtrado.empty()) {
        return oo;
    } else {
        return filtrado[0].peso;
    }
}

Vertice verticenulo() {
    return {0};
}

std::vector<Vertice> previnicial(const std::vector<Vertice>& verticesprueba, const Vertice& v) {
    std::vector<Vertice> resultado;
    for (const auto& x : verticesprueba) {
        if (x.nombre == v.nombre) {
            resultado.push_back(v);
        } else {
            resultado.push_back(verticenulo());
        }
    }
    return resultado;
}

std::vector<int> acuinicial(const std::vector<Arista>& aristasprueba, const std::vector<Vertice>& verticesprueba, const Vertice& v) {
    std::vector<int> resultado;
    for (const auto& x : verticesprueba) {
        if (x.nombre == v.nombre) {
            resultado.push_back(0);
        } else {
            resultado.push_back(costo(aristasprueba, v, x));
        }
    }
    return resultado;
}

template<typename T>
std::vector<T> cambiarnth(const T& a, int n, const std::vector<T>& lista) {
    if (n < 0 || n >= lista.size()) {
        return lista;
    }

    std::vector<T> resultado;
    for (int i = 0; i < lista.size(); ++i) {
        if (i == n) {
            resultado.push_back(a);
        } else {
            resultado.push_back(lista[i]);
        }
    }
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
    for (const auto& vertex : d.vnc) {
        if (vertex != next_vertex) {
            new_vnc.push_back(vertex);
        }
    }

    std::vector<Arista> acandidata;
    for (const auto& a : d.a) {
        if (a.orig.nombre == next_vertex.nombre) {
            acandidata.push_back(a);
        }
    }

    std::vector<Arista> avalidas;
    for (const auto& a : acandidata) {
        if (std::find(new_vnc.begin(), new_vnc.end(), a.dest) != new_vnc.end()) {
            avalidas.push_back(a);
        }
    }

    std::pair<std::vector<int>, std::vector<Vertice>> resul = actpeso(std::make_pair(d.pacu, d.prev), avalidas);

    std::vector<int> nuevoacu = resul.first;
    std::vector<Vertice> nuevoprev = resul.second;

    return {d.a, new_vc, new_vnc, nuevoacu, nuevoprev};
}

Dijkstra caminocorto(const Dijkstra& d) {
    if (d.vnc.empty())
        return d;
    else
        return caminocorto(iteracion(d));
}