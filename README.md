### About bioNuSMV
`bioNuSMV` is an extension of [`NuSMV-a`](https://github.com/hklarner/NuSMV-a), which is itself an extension of [`NuSMV 2.6.0`](https://nusmv.fbk.eu).
It adds a handful of features which aim to ease the use of model checking in the analysis of qualitative regulatory networks, through a set of high level temporal operators over CTL.
It was written by André Mendes ([Patriq](https://github.com/Patriq)) as part of a software scolarship under the supervision of Pedro T. Monteiro ([ptgm](https://github.com/ptgm)) at the [Instituto Superior Técnico (Taguspark campus)](https://tecnico.ulisboa.pt).

### Functionalities
This version was a based on a couple a different versions of NuSMV out there, that already had most of the functionalities added here, but were either added to earlier NuSMV versions, or weren't public. The other functionalities were mostly sytax sugar aliases.

Here are the added functionalities:
* ARCTL operators, for (...)
* `-ctlei` command line option, as well as a `SPEC_E` expression, to interpret CTL expressions as there exists an init state (default is for all init state)
* `-a` command line option, for printing and saving the accepting states of queries
* `RS` and `RAS` operators, to check if a given state is or not reachable
* Recursive CTL operators

I will know go, through each one of the functionalities.

#### ARCTL operators
The first version of NuSMV with ARCTL operators was [developed by Simon Busard, Franco Raimondi, José Vander Meulen ](http://lvl.info.ucl.ac.be/Tools/NuSMV-ARCTL-TLACE).
Quoting them:
> ARCTL is an extension of the CTL logic adding action-restricted operators and is interpreted over Mixed Transition Systems.

Here is a list of all ARCTL operators: `EAX`, `EAU`, `AAX`, `AAU`, `EAF`, `AAF` and `AAG`.
The syntax for all these operators is: `OPERATOR(action)(ctl_expression)`.

Check `tests/latch.smv` for an example.

#### `-ctlei` command line option and the `SPEC_E` expression

The command line option `-ctlei` adds support to interpret all CTL expressions as there exists an init state (default is for all init state).
You can use the flag both in interactive and batch mode.

As for the `SPEC_E` expression, it works just like and has the same syntax as `SPEC`, but instead of interpreting the given expression for all init state, it interprets as there exists an init state.

#### `-a` command line option

The command line option `-a` adds support for printing initial states, accepting states and initial and accepting states of a BDD representing a CTL specification to the `nusmv` model checking procedure.
Sets of states are represented as _factored formulas_, that is, as algebraic sums and products of state variables that represent the respective states.
In addition the integer cardinality of each set is given.

The _initial states_ represent the possible starting points of the given CTL property. They are specified by the user. `TRUE` means that the verification of the formula can start at any state of the transition system.

The _accepting states_ are the states in which the CTL specification holds.

The _initial and accepting states_ are the initial states in which the CTL specification holds.


##### Batch mode

- Example file used: `tests/raf_network.smv`
- Command for output on the command line: `nusmv -a print raf_network.smv`
- Generated output:

```
-- specification (EF ((!Erk & !Mek) & Raf) & EF ((Erk & Mek) & Raf))  is false

initial states: TRUE
number of initial states: 8
accepting states: !(Erk & (Mek) | !Erk & ((Raf) | !Mek))
number of accepting states: 3
initial and accepting States: !(Erk & (Mek) | !Erk & ((Raf) | !Mek))
number of initial and accepting states: 3

-- specification (!(EF ((!Erk & !Mek) & Raf)) & EF ((Erk & Mek) & Raf))  is false

initial states: TRUE
number of initial states: 8
accepting states: Erk & (Mek) | !Erk & (Mek & (Raf))
number of accepting states: 3
initial and accepting States: Erk & (Mek) | !Erk & (Mek & (Raf))
number of initial and accepting states: 3

-- specification (EF ((!Erk & !Mek) & Raf) & !(EF ((Erk & Mek) & Raf)))  is false

initial states: TRUE
number of initial states: 8
accepting states: !(Erk | (Mek))
number of accepting states: 2
initial and accepting States: !(Erk | (Mek))
number of initial and accepting states: 2

```

- Command for output into the file `output.txt`: `nusmv -a output.txt raf_network.smv`
- Generated output:

```
CTLSPEC:              (EF ((!Erk & !Mek) & Raf) & EF ((Erk & Mek) & Raf))
INIT:                 TRUE
INIT_SIZE:            8
ACCEPTING:            !(Erk & (Mek) | !Erk & ((Raf) | !Mek))
ACCEPTING_SIZE:       3
INITACCEPTING:        !(Erk & (Mek) | !Erk & ((Raf) | !Mek))
INITACCEPTING_SIZE:   3
ANSWER:               FALSE

CTLSPEC:              (!(EF ((!Erk & !Mek) & Raf)) & EF ((Erk & Mek) & Raf))
INIT:                 TRUE
INIT_SIZE:            8
ACCEPTING:            Erk & (Mek) | !Erk & (Mek & (Raf))
ACCEPTING_SIZE:       3
INITACCEPTING:        Erk & (Mek) | !Erk & (Mek & (Raf))
INITACCEPTING_SIZE:   3
ANSWER:               FALSE

CTLSPEC:              (EF ((!Erk & !Mek) & Raf) & !(EF ((Erk & Mek) & Raf)))
INIT:                 TRUE
INIT_SIZE:            8
ACCEPTING:            !(Erk | (Mek))
ACCEPTING_SIZE:       2
INITACCEPTING:        !(Erk | (Mek))
INITACCEPTING_SIZE:   2
ANSWER:               FALSE

```

##### Interactive shell

- Example file: `raf_network.smv`
- Example ctl_spec: `EF(Mek)`
- Command for output on the shell: `check_ctlspec -p "EF(Mek)" -a`
- Generated output:

```
-- specification EF Mek  is false
-- as demonstrated by the following execution sequence
Trace Description: CTL Counterexample
Trace Type: Counterexample
  -> State: 2.1 <-
    Erk = FALSE
    Mek = FALSE
    Raf = FALSE
    STEADYSTATE = FALSE
    SUCCESSORS = 1
    Raf_STEADY = FALSE
    Mek_STEADY = TRUE
    Erk_STEADY = TRUE
    Raf_IMAGE = TRUE
    Mek_IMAGE = FALSE
    Erk_IMAGE = FALSE

initial states: TRUE
number of initial states: 8
accepting states: Erk | (Mek)
number of accepting states: 6
initial and accepting States: Erk | (Mek)
number of initial and accepting states: 6

```

- Command for output to the file `out.txt`: `check_ctlspec -p "EF(Mek)" -a -o out.txt`
- This command generates the same output as `check_ctlspec -p "EF(Mek)" -a`, but the output is written to the file `out.txt`

#### `RS` and `RAS` operators

Each one of these operators is an alias to an already existing operators:
* `RS(ctl_expression)` is an alias to `EF ( ctl_expression & AG ( ctl_expression ))`
* `RAS(action)(ctl_expression)` is an alias to `EAF (action)( ctl_expression & AAG ( action )( ctl_expression ))`

#### Recursive CTL and ARCTL operators

This syntax only works for all CTL and ARCTL unary operators.

Using CTL it aliases `OPERATOR(ctl_expresion_a, ctl_expresion_b, ..., ctl_expresion_z)` to `OPERATOR(ctl_expresion_a & ( OPERATOR ctl_expresion_b & ... & (OPERATOR ctl_expresion_z)))`
Using ARCTL it aliases `EAX(action_expression)(ctl_expresion_a, ctl_expresion_b, ..., ctl_expresion_z) = EAX(action_expression)(ctl_expresion_a & EAX(action_expression)(ctl_expresion_b & ... &  EAX(action_expression)(ctl_expresion_z)))`
