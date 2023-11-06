#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <cstdlib>
#include <ctime>

const int oo = 100;

struct Vertice {
    int nombre;

    Vertice(int n) : nombre(n) {}

    bool operator==(const Vertice& other) const {
        return nombre == other.nombre;
    }

    bool operator!=(const Vertice& other) const {
        return !(*this == other);
    }

    friend std::ostream& operator<<(std::ostream& os, const Vertice& v) {
        return os << v.nombre;
    }
};

struct Arista {
    Vertice orig;
    Vertice dest;
    int peso;

    Arista(const Vertice& o, const Vertice& d, int p) : orig(o), dest(d), peso(p) {}

    bool operator==(const Arista& other) const {
        return orig == other.orig && dest == other.dest && peso == other.peso;
    }

    friend std::ostream& operator<<(std::ostream& os, const Arista& a) {
        return os << "(" << a.orig << "->" << a.dest << ", " << a.peso << ")";
    }
};

struct Grafo {
    std::vector<Vertice> vertices;
    std::vector<Arista> aristas;

    friend std::ostream& operator<<(std::ostream& os, const Grafo& g) {
        os << "Vertices: ";
        for (const auto& v : g.vertices) {
            os << v << " ";
        }
        os << "\nAristas: ";
        for (const auto& a : g.aristas) {
            os << a << " ";
        }
        return os;
    }
};

using VC = std::vector<Vertice>;
using VNC = std::vector<Vertice>;
using Peso = int;
using Pacu = std::vector<Peso>;
using Prev = std::vector<Vertice>;
using Aristas = std::vector<Arista>;

struct Dijkstra {
    std::vector<Arista> a;
    VC vc;
    VNC vnc;
    Pacu pacu;
    Prev prev;
};

int at(const std::vector<int>& xs, int i);
VC vercono(const VC& verticesprueba, const Vertice& v);
VNC vernocono(const VC& verticesprueba, const Vertice& v);
int costo(const std::vector<Arista>& as, const Vertice& o, const Vertice& d);
Vertice verticenulo();
std::vector<Vertice> previnicial(const std::vector<Vertice>& verticesprueba, const Vertice& v);
std::vector<int> acuinicial(const std::vector<Arista>& aristasprueba, const std::vector<Vertice>& verticesprueba, const Vertice& v);
template<typename T> std::vector<T> cambiarnth(const T& a, int n, const std::vector<T>& lista);
Dijkstra generarinicial(const Vertice& v, const std::vector<Arista>& aristasprueba, const std::vector<Vertice>& verticesprueba);
Peso getpeso(const Pacu& p, const Vertice& v);
std::pair<Pacu, std::vector<Vertice>> actpeso(const std::pair<Pacu, std::vector<Vertice>>& pares, const std::vector<Arista>& as);
Dijkstra iteracion(const Dijkstra& d);
Dijkstra caminocorto(const Dijkstra& d);