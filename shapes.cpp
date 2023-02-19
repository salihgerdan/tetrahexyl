#include "shapes.hpp"
namespace shapes {

const char  (* get_shape(int index, int rotation_state))[4] {
    switch (index) {
    case 1:
        return shapes::Ishape[rotation_state];
        break;
    case 2:
        return shapes::Jshape[rotation_state];
        break;
    case 3:
        return shapes::Lshape[rotation_state];
        break;
    case 4:
        return shapes::Oshape[rotation_state];
        break;
    case 5:
        return shapes::Sshape[rotation_state];
        break;
    case 6:
        return shapes::Tshape[rotation_state];
        break;
    case 7:
        return shapes::Zshape[rotation_state];
        break;
    default:
        return shapes::Ishape[rotation_state];
    }
}

const int * get_limit(int index, int rotation_state) {
    switch (index) {
    case 1:
        return shapes::Ilimit[rotation_state];
        break;
    case 2:
        return shapes::Jlimit[rotation_state];
        break;
    case 3:
        return shapes::Llimit[rotation_state];
        break;
    case 4:
        return shapes::Olimit[rotation_state];
        break;
    case 5:
        return shapes::Slimit[rotation_state];
        break;
    case 6:
        return shapes::Tlimit[rotation_state];
        break;
    case 7:
        return shapes::Zlimit[rotation_state];
        break;
    default:
        return shapes::Ilimit[rotation_state];
    }
}

} // namespace shapes