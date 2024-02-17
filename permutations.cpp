#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <tuple>
#include <climits>
#include <cstdlib>
#include <algorithm>
#include <stdexcept>
#include <random>

auto rng = std::default_random_engine{};


int a_must_be_bigger_or_equal(int a, int b) {
    if (a <b) {
        throw std::invalid_argument("Received total number of states smaller than that of the occupied states.");
    }
}

int main() {
    auto factorial = [](int i) {
        long double count = 1;
        for (int j = i; j > 0; --j) {
            count = j * count;
        }
        return count;
        };
    auto binomial_bracket = [&](int i, int j) {
        long double res;
        res = factorial(i) / (factorial(j) * factorial(i - j));
        return res;
        };
    auto move_vector = [](std::vector <int> perm) {
        //bool not_done = true;
        //for (int j = 0; j < perm.size() - 1; ++j) {
        //    if (perm[j] == 1 && perm[j + 1] == 0 and not_done) {
        //        perm[j] = 0;
        //        perm[j + 1] = 1;
        //        not_done = false;
        //    }
        //}
        std::shuffle(std::begin (perm), std::end (perm), rng);
        return perm;
        };

	int occ, tot;
	std::cout << "Input total number of states." << '\n';
	std::cin >> tot;
	std::cout << "Input maximum number of occupied states." << '\n';
	std::cin >> occ;

    system("cls");
    a_must_be_bigger_or_equal(tot, occ);
    

    while (occ > 0) {
        std::cout << "Occupied states number: " << occ << '\n';
        std::cout << '\n';
        std::vector <std::vector <int>> combs;
        std::vector<int> init(tot, 0);
        for (int i = 0; i < occ; ++i) {
            init[i] = 1;
        }
        combs.push_back(init);
        while (combs.size() != binomial_bracket(tot, occ)) {
            std::vector <int> perm(tot, 0);
            for (int i = 0; i < occ; ++i) {
                perm[i] = 1;
            }
            while (std::find(combs.begin(), combs.end(), perm) != combs.end() && combs.size() < binomial_bracket(tot, occ)) {
                perm = move_vector(perm);
                //std::cout << combs.size()<< " size"<<'\n';
                //std::cout << binomial_bracket(tot, occ) << " target" << '\n';
            }
            combs.push_back(perm);

        }
        for (int i = 0; i < combs.size(); ++i) {
            for (int j = 0; j < tot; ++j) {
                std::cout << combs[i][j] << ", ";
            }
            std::cout << '\n';
        }
        std::cout << '\n';
        std::cout << " Size equal to " << combs.size()  << '\n';
        std::cout << '\n';
        std::cout << '\n';
        occ -= 1;
    }
}