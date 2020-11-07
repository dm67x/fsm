#pragma once

#include <vector>
#include <map>
#include <utility>
#include <ostream>
#include <algorithm>
#include <type_traits>
#include <exception>

#define state_id(state) ((state & 0xFFFE) >> 1)
#define state_value(state) (state & 0x1)

namespace fsm {
    
// least significant bit for the end value
// most significant bits are for the identifier
using State = unsigned short;
template<typename T>
using Link = std::map<std::pair<State, T>, State>;

template<typename T>
using Alphabet = std::vector<T>;

template<typename T>
void new_alphabet(Alphabet<T>& alphabet, T value) {
    alphabet.push_back(value);
}

template<typename T, typename... Values>
void new_alphabet(Alphabet<T>& alphabet, T value, Values... values) {
    alphabet.push_back(value);
    return new_alphabet(alphabet, values...);
}

template<typename T>
bool exist_in_alphabet(const Alphabet<T>& alphabet, T value) {
    return std::find(alphabet.begin(), alphabet.end(), value) != alphabet.end();
}

class AlphabetException : public std::exception {
    virtual const char* what() const throw() {
        return "Element not found in the alphabet";
    }
};

template<typename T>
struct FSM {
    Alphabet<T>& alphabet;
    Link<T> link;
    unsigned short current_id;

    FSM(Alphabet<T>& alphabet) : alphabet(alphabet), current_id(0) {}

    inline State new_state(bool end = false) {
        return (this->current_id++ << 1) | (end ? 0x1 : 0x0);
    }

    inline FSM* new_link(State from, State to, T by) {
        if (!exist_in_alphabet(alphabet, by)) {
            throw AlphabetException();
        }
        link.insert(std::make_pair(std::make_pair(from, by), to));
        return this;
    }

    bool is_valid() const {
        // all states must have the same number of output
        // outputs = size of the alphabet
        for (State s = 0; s < current_id; s++) {
            size_t counter = 0;
            for (auto it = link.begin(); it != link.end(); it++) {
                if (s == state_id(it->first.first)) {
                    counter++;
                }
            }

            if (counter != alphabet.size()) {
                return false;
            }
        }
        return true;
    }

    bool evaluate(State& current) const {
        return state_value(current) == 0x1;
    }

    template<typename... Args>
    bool evaluate(State& current, T arg, Args... args) const {
        auto it = link.find(std::make_pair(current, arg));
        if (it != link.end()) {
            current = it->second;
        }
        return evaluate(current, args...);
    }

    friend std::ostream& operator<<(std::ostream& out, const FSM& fsm) {
        for (auto it = fsm.link.begin(); it != fsm.link.end(); it++) {
            out << state_id(it->first.first) << " -> " << state_id(it->second)
                << " [" << it->first.second << "]" << std::endl;
        }
        out << "FSM is " << (fsm.is_valid() ? "valid" : "unvalid") << std::endl;
        return out;
    }
};

}