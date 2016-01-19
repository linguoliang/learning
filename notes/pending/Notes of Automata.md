[mathematics 数学]

# Notes of Automata

# Deterministic Finite Automata

## Alphabets

An alphabet is any finite set of symbols.

## Strings

A string over an alphabet $\Sigma$ is a list, each element of which is a member of $\Sigma$.

$\Sigma^*$: set of all strings over alphabet $\Sigma$.

The length of a string is its number of positions.

$\epsilon$ stands for the empty string (string of length 0).

## Languages

A language is a subset of $\Sigma^*$ for some alphabet $\Sigma$.

## DFA

A formalism for defining languages, consisting of:

1. A finite set of states ($Q$, typically).
2. An input alphabet ($\Sigma$, typically).
3. A transition function ($\delta$, typically).
4. A start state ($q_0$, $q_0 \in Q$, typically).
5. A set of final states ($F \subseteq Q$, typically).
	* “Final” and “accepting” are synonyms.

dead state: not accepting, has transition to itself on every input symbol.

Convention: Strings and Symbols
* $… w, x, y, z$ are strings.
* $a, b, c, …$ are single input symbols.

## The transition function

$\delta(q,a)=$ the state that DFA can reach to when it is in state q and input a is received.

## Language of a DFA

Automata of all kinds define languages.

If A is an automaton, L(A) is its language.

For a DFA A, L(A) is the set of strings labeling paths from the start state to a final state.

Formally: $L(A) = \{w | \delta(q_0, w) \in F\}$

## Regular Languages

A language L is regular if it is the language accepted by some DFA.
Note: the DFA **must accept only** the strings in L, no others.

# Nondeterministic Finite Automata

## NFA

1. A finite set of states ($Q$, typically).
2. An input alphabet ($\Sigma$, typically).
3. A transition function ($\delta$, typically).
4. A start state ($q_0$, $q_0 \in Q$, typically).
5. A set of final states ($F \subseteq Q$, typically).

## The transition function

$\delta(q,a)=$ a set of states.

## Language of a DFA

The language of the NFA is the set of strings it accepts.

A string w is accepted by an NFA if $\delta_D(\theta,w)$ contains **at least one** final state.

## DFA and NFA

### DFA -> NFA

A DFA can be turned into an NFA that accepts the same language.

$\delta_D(q,a)=p \rightarrow \delta_N(q,a)={p}$

### NFA -> DFA (Subset construction)

Given an NFA with $Q, \Sigma, \delta_N, q_0, F$, equivalent DFA:

* States: $2^Q$ (Set of subsets of Q)
* Inputs: $\Sigma$
* Transition fucntion: $\delta_D({q_1, ..., q_k}, a) = \bigcup_{i \in [1, k]}\delta_N(q_i, a)$
* Start state: ${q_0}$
* Final states: all states contain $F$

Important:

* The sets of NFA states are the DFA states' names. For example, ${p,q}$ in NFA is a single symbol (a state) in DFA.

# $\epsilon \text{-Transition}$

Allow state-to-state transitions on $\epsilon$ input and only regular languages are accepted.

## Closure of States

$closure(q)$ = set of states you can reach from state q following only arcs labeled $\epsilon$.

$closure({q_1, ..., q_k}) = \bigcup_{i \in [1, k]}closure(q_i)$

## Extended $\delta$

$\hat{\delta}(q, w)$ is the set of states you can reach from q following a path labeled w.

* $\hat{\delta}(q, \epsilon) = closure(q)$
* $\hat{\delta}(q, xa) = \bigcup_{p \in \hat{\delta}(q, x)}\hat{\delta}(p, a)$

## Language of $\epsilon \text{-NFA}$

The set of strings w such that $\hat{\delta}(q_0, w)$ contains a final state.

## NFA and $\epsilon \text{-NFA}$

Every NFA is an $\epsilon$-NFA.

### $\epsilon$-NFA -> NFA (Closure construction)

Given an $\epsilon$-NFA with $Q, \Sigma, \delta_E, q_0, F$, equivalent NFA:

* $Q, \Sigma, q_0$
* $\delta_N(q, a) = \bigcup_{p \in closure(q)}{\delta_E}(p, a)$
* $F\prime = \{q | F \in closure(q)\}$

## DFA, NFA, and $\epsilon \text{-NFA}$

* All of them accept regular language.
* The NFA is easier to design. The DFA has exponential states of the NFA's.
* Only DFA can be implemented.

# Regular Expressions

Regular Expressions describe languages by an algebra. They describe exactly the regular languages. If E is a regular expression, then L(E) is the language it defines.

## Operations on Languages

### Union

$L_1 \cup L_2 = \{x, y | x \in L_1, y \in L_2\}$

### Concatenation

$L_1 \circ L_2 = \{xy | x \in L_1, y \in L_2\}$

### Kleene star (Kleene closure)

$$
L^n =
\begin{cases}
\{\epsilon\} & \text{if } n = 0 \\
L^{n-1} \circ L & \text{if } x > 0
\end{cases}
$$

$$
L^* = \bigcup_{i \geq 0}L^i
$$

## RE's Definition

$$
\begin{array}{c|lcr}
& \text{Syntax} & \text{Semantics} \\
\text{Basics } &
\begin{array}{c}
\emptyset \\
\epsilon \\
a
\end{array} &
\begin{array}{c}
L(\emptyset) = \{\} \\
L(\epsilon) = \{\epsilon\} \\
L(a) = \{a\}
\end{array} \\
\text{Induction } &
\begin{array}{c}
E_1 + E_2 \\
E_1 \circ E_2 \\
E_1^*
\end{array} &
\begin{array}{c}
L(E_1 + E_2) = L(E_1) \cup L(E_2) \\
L(E_1 \circ E_2) = L(E_1) \circ L(E_2) \\
L(E_1^*) = {L(E_1)}^*
\end{array} \\
\end{array}
$$

* $\circ$ can be omitted.
* Precedence: $* > \circ > +$

## RE's and Finite Automata

Each of the three types of automata (DFA, NFA, ε-NFA) and regular expressions as well, define exactly the same set of languages: the regular languages.

### RE's -> Finite Automata

Thompson's construction algorithm

### Finite Automata -> RE's

[Transitive closure method](http://cs.stackexchange.com/questions/2016/how-to-convert-finite-automata-to-regular-expressions/2395#2395)

### References

1. [https://courses.engr.illinois.edu/cs373/sp2013/Lectures/lec06.pdf](https://courses.engr.illinois.edu/cs373/sp2013/Lectures/lec06.pdf)
2. [https://people.cs.umass.edu/~immerman/cs250/regExpToNFA.pdf](https://people.cs.umass.edu/~immerman/cs250/regExpToNFA.pdf)
3. [http://cs.stackexchange.com/questions/2016/how-to-convert-finite-automata-to-regular-expressions/2395#2395](http://cs.stackexchange.com/questions/2016/how-to-convert-finite-automata-to-regular-expressions/2395#2395)

## Lexical Analysis

The first thing a compiler does is break a program into tokens (substrings) that together represent a unit.

RE->
$\epsilon \text{-NFA}$ ->
Combine these all (by introducing a new
start state with $\epsilon \text{-transitions }$ to the start states of each $\epsilon \text{-NFA}$) ->
DFA

1. If a DFA state has several final states among its members, give them priority.
2. It must be able to read an input symbol and then, when it accepts, put that symbol back on the input to be read later.

## Decision algorithms