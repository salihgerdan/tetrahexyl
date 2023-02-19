#pragma once
#include <array>
//using std::array;
namespace shapes {
const char Ishape[4][4][4] = {{{'s', 'c', 's', 's'},
                               {'s', 'c', 's', 's'},
                               {'s', 'c', 's', 's'},
                               {'s', 'c', 's', 's'}},
                              {{'s', 's', 's', 's'},
                               {'c', 'c', 'c', 'c'},
                               {'s', 's', 's', 's'},
                               {'s', 's', 's', 's'}},
                              {{'s', 'c', 's', 's'},
                               {'s', 'c', 's', 's'},
                               {'s', 'c', 's', 's'},
                               {'s', 'c', 's', 's'}},
                              {{'s', 's', 's', 's'},
                               {'c', 'c', 'c', 'c'},
                               {'s', 's', 's', 's'},
                               {'s', 's', 's', 's'}}};
const int Ilimit[4][4] = {
    {-1, 8, 20, 3}, {0, 6, 20, 3}, {-1, 8, 20, 3}, {0, 6, 20, 3}};

const char Jshape[4][4][4] = {{{'s', 's', 's', 's'},
                               {'b', 'b', 'b', 's'},
                               {'s', 's', 'b', 's'},
                               {'s', 's', 's', 's'}},
                              {{'s', 'b', 's', 's'},
                               {'s', 'b', 's', 's'},
                               {'b', 'b', 's', 's'},
                               {'s', 's', 's', 's'}},
                              {{'b', 's', 's', 's'},
                               {'b', 'b', 'b', 's'},
                               {'s', 's', 's', 's'},
                               {'s', 's', 's', 's'}},
                              {{'s', 'b', 'b', 's'},
                               {'s', 'b', 's', 's'},
                               {'s', 'b', 's', 's'},
                               {'s', 's', 's', 's'}}};
const int Jlimit[4][4] = {
    {0, 7, 20, 3}, {0, 8, 20, 3}, {0, 7, 20, 3}, {-1, 7, 20, 3}};

const char Lshape[4][4][4] = {{{'s', 's', 's', 's'},
                               {'o', 'o', 'o', 's'},
                               {'o', 's', 's', 's'},
                               {'s', 's', 's', 's'}},
                              {{'o', 'o', 's', 's'},
                               {'s', 'o', 's', 's'},
                               {'s', 'o', 's', 's'},
                               {'s', 's', 's', 's'}},
                              {{'s', 's', 'o', 's'},
                               {'o', 'o', 'o', 's'},
                               {'s', 's', 's', 's'},
                               {'s', 's', 's', 's'}},
                              {{'s', 'o', 's', 's'},
                               {'s', 'o', 's', 's'},
                               {'s', 'o', 'o', 's'},
                               {'s', 's', 's', 's'}}};
const int Llimit[4][4] = {
    {0, 7, 20, 3}, {0, 8, 20, 3}, {0, 7, 20, 3}, {-1, 7, 20, 3}};

const char Oshape[4][4][4] = {{{'y', 'y', 's', 's'},
                               {'y', 'y', 's', 's'},
                               {'s', 's', 's', 's'},
                               {'s', 's', 's', 's'}},
                              {{'y', 'y', 's', 's'},
                               {'y', 'y', 's', 's'},
                               {'s', 's', 's', 's'},
                               {'s', 's', 's', 's'}},
                              {{'y', 'y', 's', 's'},
                               {'y', 'y', 's', 's'},
                               {'s', 's', 's', 's'},
                               {'s', 's', 's', 's'}},
                              {{'y', 'y', 's', 's'},
                               {'y', 'y', 's', 's'},
                               {'s', 's', 's', 's'},
                               {'s', 's', 's', 's'}}};
const int Olimit[4][4] = {
    {0, 8, 20, 3}, {0, 8, 20, 3}, {0, 8, 20, 3}, {0, 8, 20, 3}};

const char Sshape[4][4][4] = {{{'s', 's', 's', 's'},
                               {'s', 'g', 'g', 's'},
                               {'g', 'g', 's', 's'},
                               {'s', 's', 's', 's'}},
                              {{'s', 'g', 's', 's'},
                               {'s', 'g', 'g', 's'},
                               {'s', 's', 'g', 's'},
                               {'s', 's', 's', 's'}},
                              {{'s', 's', 's', 's'},
                               {'s', 'g', 'g', 's'},
                               {'g', 'g', 's', 's'},
                               {'s', 's', 's', 's'}},
                              {{'s', 'g', 's', 's'},
                               {'s', 'g', 'g', 's'},
                               {'s', 's', 'g', 's'},
                               {'s', 's', 's', 's'}}};
const int Slimit[4][4] = {
    {0, 7, 20, 3}, {-1, 7, 20, 3}, {0, 7, 20, 3}, {-1, 7, 20, 3}};

const char Tshape[4][4][4] = {{{'s', 's', 's', 's'},
                               {'p', 'p', 'p', 's'},
                               {'s', 'p', 's', 's'},
                               {'s', 's', 's', 's'}},
                              {{'s', 'p', 's', 's'},
                               {'p', 'p', 's', 's'},
                               {'s', 'p', 's', 's'},
                               {'s', 's', 's', 's'}},
                              {{'s', 'p', 's', 's'},
                               {'p', 'p', 'p', 's'},
                               {'s', 's', 's', 's'},
                               {'s', 's', 's', 's'}},
                              {{'s', 'p', 's', 's'},
                               {'s', 'p', 'p', 's'},
                               {'s', 'p', 's', 's'},
                               {'s', 's', 's', 's'}}};
const int Tlimit[4][4] = {
    {0, 7, 20, 3}, {0, 8, 20, 3}, {0, 7, 20, 3}, {-1, 7, 20, 3}};

const char Zshape[4][4][4] = {{{'s', 's', 's', 's'},
                               {'r', 'r', 's', 's'},
                               {'s', 'r', 'r', 's'},
                               {'s', 's', 's', 's'}},
                              {{'s', 's', 'r', 's'},
                               {'s', 'r', 'r', 's'},
                               {'s', 'r', 's', 's'},
                               {'s', 's', 's', 's'}},
                              {{'s', 's', 's', 's'},
                               {'r', 'r', 's', 's'},
                               {'s', 'r', 'r', 's'},
                               {'s', 's', 's', 's'}},
                              {{'s', 's', 'r', 's'},
                               {'s', 'r', 'r', 's'},
                               {'s', 'r', 's', 's'},
                               {'s', 's', 's', 's'}}};
const int Zlimit[4][4] = {
    {0, 7, 20, 3}, {-1, 7, 20, 3}, {0, 7, 20, 3}, {-1, 7, 20, 3}};

// constexpr char shapes[7][4][4][4] = {Ishape, Jshape, Lshape, Oshape, Sshape,
// Tshape, Zshape};

const char (* get_shape(int index, int rotation_state))[4];
const int * get_limit(int index, int rotation_state);

} // namespace shapes