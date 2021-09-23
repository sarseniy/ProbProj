#pragma once

#include <set>

class State {
public:
    virtual ~State() {}
    virtual bool contains(int s) const = 0;
};

class DiscreteState : public State {
private:
    int const state;

public:
    DiscreteState(int state);

    bool contains(int s) const override;
};

class SegmentState : public State {
private:
    int const beg, end;

public:
    SegmentState();
    SegmentState(int beg, int end);

    bool contains(int s) const override;
};

class SetState : public State {
private:
    std::set<int> const states;

public:
    SetState();
    SetState(std::set<int> const& src);

    bool contains(int s) const override;
};

class UnionState : public State {
private:
    State* const x;
    State* const y;
public:
    UnionState(State* x, State* y);
    bool contains(int s) const override;
};

class SubstractState : public State {
private:
    State* const x;
    State* const y;
public:
    SubstractState(State* x, State* y);
    bool contains(int s) const override;
};

class IntersectState : public State {
private:
    State* const x;
    State* const y;
public:
    IntersectState(State* x, State* y);
    bool contains(int s) const override;
};