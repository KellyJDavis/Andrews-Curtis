![Cappell-Shaneson Kirby Diagram](https://raw.github.com/KellyJDavis/Andrews-Curtis/master/Cappell-Shaneson_KirbyDiagram.png)

# Andrews-Curtis

*Andrews-Curtis* is an [MPI](http://en.wikipedia.org/wiki/Message_Passing_Interface) based [Andrews-Curtis move](http://www.jstor.org/stable/2033843) enumerator that examines potential counterexamples to the [Andrews-Curtis Conjecture](http://www.jstor.org/stable/2033843).

Specifically, given __P__, a balanced [presentation of a group](http://en.wikipedia.org/wiki/Presentation_of_a_group) that is a *potential* counterexample to the [Andrews-Curtis Conjecture](http://www.jstor.org/stable/2033843), the *Andrews-Curtis* executable attempts to prove the *potential* counterexample __P__ is or is not an *actual* counterexample.

The balanced [presentation](http://en.wikipedia.org/wiki/Presentation_of_a_group) __P__ is fed to the *Andrews-Curtis* executable as a number of [generators](http://en.wikipedia.org/wiki/Generating_set_of_a_group) __a__,__b__... along with an equal number of [relators](http://en.wikipedia.org/wiki/Presentation_of_a_group) __r__,__s__... Given these the *Andrews-Curtis* executable, using only [Andrews-Curtis moves](http://www.jstor.org/stable/2033843), attempts to prove __P__ is [trivial](http://en.wikipedia.org/wiki/Trivial_group).

If it successfully proves __P__ is [trivial](http://en.wikipedia.org/wiki/Trivial_group), it prints out the proof including all [Andrews-Curtis moves](http://www.jstor.org/stable/2033843). If it can not prove __P__ is [trivial](http://en.wikipedia.org/wiki/Trivial_group), it simply prints __P__, the original balanced [presentation](http://en.wikipedia.org/wiki/Presentation_of_a_group), indicating it is a counterexample to the [Andrews-Curtis Conjecture](http://www.jstor.org/stable/2033843).

## Table of Contents

* Quick Start
* Introduction
* Installing
  * Checking Dependencies
  * Building Executable
* Running the Executable
  * Running on a Single Node
  * Running on a Cluster of Nodes
* Where to get help
* Contribution guidelines
* Contributor list
* Credits, Inspiration, and Alternatives

## Quick Start

### Checking Dependencies

*Andrews-Curtis* has the following dependencies:

* An [MPI](http://en.wikipedia.org/wiki/Message_Passing_Interface) implementation (Tested with [Open MPI](http://www.open-mpi.org) version v1.8.1)
* A [Boost](http://www.boost.org) install (Tested with version 1.55.0) with compiled, multi-threaded versions of the following libraries:
  * [boost.mpi](http://www.boost.org/doc/libs/1_55_0/doc/html/mpi.html)
  * [boost.thread](http://www.boost.org/doc/libs/1_55_0/doc/html/thread.html)
  * [boost.system](http://www.boost.org/doc/libs/1_55_0/libs/system/doc/index.html)
  * [boost.date_time](http://www.boost.org/doc/libs/1_55_0/doc/html/date_time.html)
  * [boost.serialization](http://www.boost.org/doc/libs/1_55_0/libs/serialization/doc/index.html)

### Building Executable

Once the dependencies are installed and the environment is set up to allow their access, one can compile *Andrews-Curtis* by opening a terminal and entering the following commands:

```
localhost:~ kdavis$ cd <Andrews-Curtis Root Directory>
localhost:Andrews-Curtis kdavis$ make ac
```

This compiles the *Andrews-Curtis* executable `ac` and places it into the Andrews-Curtis root directory.

### Running the Executable

As the *Andrews-Curtis* executable is [MPI](http://en.wikipedia.org/wiki/Message_Passing_Interface) based, it is started like any other [MPI](http://en.wikipedia.org/wiki/Message_Passing_Interface) executable

```
localhost:Andrews-Curtis kdavis$ mpirun ./ac ab aB b
```

Specifically, the above example is for __P__ a balanced [presentation](http://en.wikipedia.org/wiki/Presentation_of_a_group) with generators __a__ and __b__ and relators __aB__ and __b__. (When using `ac`, the inverse of a relator, __b__ for example, is indicated by using uppercase, in our example __B__.)

Executing the above example on a single node will result in the following proof:

```
localhost:Andrews-Curtis kdavis$ mpirun ./ac ab aB b
Process: 0 Thread pool size: 4
Process: 1 Thread pool size: 4

Completed level: 0
	Uptime: 0ms
	Relators: 2
	Balanced_presentations: 1
	Average Relator Length: 1.5
	Average Balanced presentation Length: 3

Derivation:
(aB, b)
(a, b)
```

As `ac` is [MPI](http://en.wikipedia.org/wiki/Message_Passing_Interface) based, running it on a cluser of nodes is simple. One need only use the standard procedure for your [MPI](http://en.wikipedia.org/wiki/Message_Passing_Interface) implementation.
