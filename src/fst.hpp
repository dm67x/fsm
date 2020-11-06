#pragma once

#include <vector>
#include <utility>
#include <ostream>

#define state_id(state) ((state & 0xFFFE) >> 1)
#define state_value(state) (state & 0x1)

// least significant bit for the end value
// most significant bits are for the identifier
using State = unsigned short;
template<typename T>
using Link = std::pair<std::pair<State, State>, T>;

template<typename T>
struct FST {
    std::vector<Link<T>> links;
    unsigned short current_id;

    FST() : current_id(0) {}

    inline State new_state(bool end = false) {
        return (this->current_id++ << 1) | (end ? 0x1 : 0x0);
    }

    inline void new_link(State from, State to, T by) {
        links.push_back(std::make_pair(std::make_pair(from, to), by));
    }

    inline bool is_valid() const {
        return true;
    }

    friend std::ostream& operator<<(std::ostream& out, const FST& fst) {
        for (auto link : fst.links) {
            out << state_id(link.first.first) << " -> " << state_id(link.first.second)
                << " [" << link.second << "]" << std::endl;
        }
        return out;
    }
};