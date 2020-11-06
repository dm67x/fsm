#pragma once

#include <vector>
#include <utility>
#include <ostream>
#include <algorithm>

#define state_id(state) ((state & 0xFFFE) >> 1)
#define state_value(state) (state & 0x1)

// least significant bit for the end value
// most significant bits are for the identifier
using State = unsigned short;
template<typename T>
using Link = std::pair<std::pair<State, State>, T>;

template<typename T>
struct FSM {
    std::vector<Link<T>> links;
    unsigned short current_id;

    FSM() : current_id(0) {}

    inline State new_state(bool end = false) {
        return (this->current_id++ << 1) | (end ? 0x1 : 0x0);
    }

    inline FSM* new_link(State from, State to, T by) {
        links.push_back(std::make_pair(std::make_pair(from, to), by));
        return this;
    }

    inline bool is_valid() const {
        for (State i = 0; i < current_id; i++) {
            std::vector<T> values;
            for (auto link : links) {
                if (state_id(link.first.first) == i) {
                    auto it = std::find(values.begin(), values.end(), link.second);
                    if (it != values.end()) {
                        return false;
                    }
                    values.push_back(link.second);
                }
            }
        }
        return true;
    }

    friend std::ostream& operator<<(std::ostream& out, const FSM& fsm) {
        for (auto link : fsm.links) {
            out << state_id(link.first.first) << " -> " << state_id(link.first.second)
                << " [" << link.second << "]" << std::endl;
        }
        out << "FSM is " << (fsm.is_valid() ? "valid" : "unvalid") << std::endl;
        return out;
    }
};