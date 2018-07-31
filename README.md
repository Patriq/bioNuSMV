### About bioNuSMV
`bioNuSMV` is a fork and extension of [`NuSMV-a`](https://github.com/hklarner/NuSMV-a) by Hannes Klarner ([hklarner](https://github.com/hklarner)), which adds a handful of features to ease the use of model checking by biological modelers, in particular, in the context of the verification of qualitative regulatory networks.

It was implemented by André Mendes ([Patriq](https://github.com/Patriq) as part of the FCT funded research project ERGODiC, under the supervision of Pedro T. Monteiro ([ptgm](https://github.com/ptgm)) at [INESC-ID](http://www.inesc-id.pt)/[Instituto Superior Técnico (Taguspark campus)](https://tecnico.ulisboa.pt).

### Features
With respect to the original [`NuSMV 2.6.0`](https://nusmv.fbk.eu), this version adds the following features:
* `-a` command line option, for printing and saving the set of accepting states (see [`NuSMV-a`](https://github.com/hklarner/NuSMV-a))
* ARCTL (Action Restricted CTL) operators, for the verification of Mixed Transition Systems (see [`NuSMV-ARCTL-TLACE`](http://lvl.info.ucl.ac.be/Tools/NuSMV-ARCTL-TLACE))
* `-ctlei` command line option (or equivalently by the `SPEC_E` keyword), where a given CTL expression becomes `TRUE` if it is valid by *at least one* state in the set of the initial states (default is *for all* states in the set of initial states)
* High-level `RS` and `RAS` operators, for the verification of weak and strong reachability, respectively
* Recursive CTL operators

Below we present a small description of each of the functionalities.

#### `-a` command line option

The command line option `-a` adds support for printing initial states, accepting states and initial and accepting states of a BDD representing a CTL specification to the `NuSMV` model checking procedure.
For a complete description of this functionality, please check the original [NuSMV-a](https://github.com/hklarner/NuSMV-a).

#### ARCTL operators
The first version of NuSMV with ARCTL operators was [developed by Simon Busard, Franco Raimondi, José Vander Meulen ](http://lvl.info.ucl.ac.be/Tools/NuSMV-ARCTL-TLACE), with the purpose of extending CTL (Computation Tree Logic) with action-restricted operators, for the verification of Mixed Transition Systems.

Here is a list of all ARCTL operators: `EAX`, `EAU`, `AAX`, `AAU`, `EAF`, `AAF` and `AAG`.
The syntax for all these operators is: `OPERATOR(action_expression)(ctl_expression)`
where `action_expression` is a restriction over transitions labels (i.e., variables under the `VAR` keyword) and `ctl_expression` is a restriction over state labels (i.e., variables under the `VAR` keyword).

Check `tests/latch.smv` for an example.

#### `-ctlei` command line option and the `SPEC_E` expression

For a given specification, the command line option `-ctlei` adds support to interpret each CTL expression, as `TRUE` if it is satisfied by *at least one* state in the set of the initial states (default is *for all* states in the set of initial states)
You can use the flag both in *interactive* and *batch* mode.

Alternatively, one can use the `SPEC_E` keyword, replacing the `SPEC` keyword, in order to interpret each of the subsequent CTL expressions as `TRUE` if and only if it is satisfied by *at least one* state in the set of initial states.


#### `RS` and `RAS` operators

Each one of these operators is an alias to an already existing operators:
* `RS(ctl_expression)` is an alias to `EF ( ctl_expression & AG ( ctl_expression ))`
* `RAS(action)(ctl_expression)` is an alias to `EAF (action)( ctl_expression & AAG ( action )( ctl_expression ))`

#### Recursive CTL and ARCTL operators

We have included the following set of recursive CTL/ARCTL operators, in order to simplify the specification of nested CTL/ARCTL operators:
* bla
* bla

Using CTL:
* it aliases `OPERATOR(ctl_expresion_a, ctl_expresion_b, ..., ctl_expresion_z)` to `OPERATOR(ctl_expresion_a & ( OPERATOR ctl_expresion_b & ... & (OPERATOR ctl_expresion_z)))`

Using ARCTL:
* it aliases `EAX(action_expression)(ctl_expresion_a, ctl_expresion_b, ..., ctl_expresion_z) = EAX(action_expression)(ctl_expresion_a & EAX(action_expression)(ctl_expresion_b & ... &  EAX(action_expression)(ctl_expresion_z)))`

This syntax only works for all CTL and ARCTL *unary* operators.
