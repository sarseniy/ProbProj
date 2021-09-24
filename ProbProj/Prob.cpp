#include <iostream>
#include <set>
#include <random>
#include "Prob.h"

DiscreteState::DiscreteState(int state) : state(state) { }

bool DiscreteState::contains(int s) const {
    return s == state;
}


SegmentState::SegmentState() : beg(0), end(-1) { }
SegmentState::SegmentState(int beg, int end) : beg(beg), end(end) { }

bool SegmentState::contains(int s) const {
    return s >= beg && s <= end;
}



SetState::SetState() : states() { }
SetState::SetState(std::set<int> const& src) : states(src) { }

bool SetState::contains(int s) const {
    return states.count(s) > 0;
}

UnionState::UnionState(State* x, State* y) : x(x), y(y)
{}
bool UnionState::contains(int s) const {
    return x->contains(s) or y->contains(s);
}

SubstractState::SubstractState(State* x, State* y) : x(x), y(y)
{}
bool SubstractState::contains(int s) const {
    return x->contains(s) and !y->contains(s);
}

IntersectState::IntersectState(State* x, State* y) : x(x), y(y)
{}
bool IntersectState::contains(int s) const {
    return x->contains(s) and y->contains(s);
}

class ProbabilityTest {
private:
    unsigned seed;
    int test_min, test_max;
    unsigned test_count;

public:
    ProbabilityTest(unsigned seed, int test_min, int test_max, unsigned test_count) : seed(seed), test_min(test_min), test_max(test_max), test_count(test_count) { }

    float operator()(State const& s) const {
        std::default_random_engine rng(seed);
        std::uniform_int_distribution<int> dstr(test_min, test_max);
        unsigned good = 0;
        for (unsigned cnt = 0; cnt != test_count; ++cnt)
            if (s.contains(dstr(rng))) ++good;

        return static_cast<float>(good) / static_cast<float>(test_count);
    }

    void convergence_test(State const& s) const {
        std::default_random_engine rng(100);
        std::uniform_int_distribution<int> dstr(test_min, test_max);
        double epsilon = 0.001;
        double old_probability = 1;
        double new_probability = 1;
        int count = 1000;
        int in_a_row = 0;
        while (in_a_row <= 5) {
            unsigned good = 0;
            for (unsigned cnt = 0; cnt != count; ++cnt)
                if (s.contains(dstr(rng))) ++good;
            new_probability = static_cast<double>(good) / static_cast<double>(count);
            if (abs(new_probability - old_probability) < epsilon)
            {
                in_a_row++;
            }
            else
            {
                in_a_row = 0;
            }
            count += 100;
            old_probability = new_probability;
        }
        std::cout << "Probability converges at test_count = " << count << '\n';
    }
};

template<class T>
void measure(size_t n, T t) {
    ProbabilityTest tester(87, 0, 100, n);
    //std::cout << n << ' ' << tester(t) << std::endl;
    std::cout << tester(t) << std::endl;
}

int main(int argc, const char* argv[]) {
    DiscreteState d(1);
    SegmentState s(30, 40);
    SetState ss({ 11, 13, 15, 17, 23, 7, 9});
    ProbabilityTest pt(10, 0, 100, 100000);
    UnionState sd(&s, &d);
    SubstractState s_d(&s, &d);
    IntersectState s_n_d(&s, &d);

    /*for (size_t i = 100; i < 100000; i += 100)
    {
        measure(i, s);
    }*/

    /*for (size_t i = 100; i < 100000; i += 100)
    {
        measure(i, ss);
    }*/

    //measure(1000000, ss);

    pt.convergence_test(s);

    std::cout << pt(d) << std::endl;
    std::cout << pt(s) << std::endl;
    std::cout << pt(sd) << std::endl;
    std::cout << pt(sd) << std::endl;
    std::cout << pt(s_d) << std::endl;
    std::cout << pt(s_n_d) << std::endl;

    return 0;
}
