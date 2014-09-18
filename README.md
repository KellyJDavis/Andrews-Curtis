![Cappell-Shaneson Kirby Diagram](https://raw.github.com/KellyJDavis/Andrews-Curtis/master/Cappell-Shaneson_KirbyDiagram.png)

# Andrews-Curtis

*Andrews-Curtis* is an [MPI](http://en.wikipedia.org/wiki/Message_Passing_Interface) based [Andrews-Curtis move](http://www.jstor.org/stable/2033843) enumerator that examines potential counterexamples to the [Andrews-Curtis Conjecture](http://www.jstor.org/stable/2033843).

Specifically, given __P__, a balanced [presentation of a group](http://en.wikipedia.org/wiki/Presentation_of_a_group) that is a *potential* counterexample to the [Andrews-Curtis Conjecture](http://www.jstor.org/stable/2033843), the *Andrews-Curtis* executable attempts to prove the *potential* counterexample __P__ is or is not an *actual* counterexample.

The balanced [presentation](http://en.wikipedia.org/wiki/Presentation_of_a_group) __P__ is fed to the *Andrews-Curtis* executable as a number of [generators](http://en.wikipedia.org/wiki/Generating_set_of_a_group) __a__,__b__... and an equal number of [relators](http://en.wikipedia.org/wiki/Presentation_of_a_group) __r__,__s__... Given these the *Andrews-Curtis* executable, using only [Andrews-Curtis moves](http://www.jstor.org/stable/2033843), then attempts to prove __P__ is [trivial](http://en.wikipedia.org/wiki/Trivial_group).

If it successfully proves __P__ is [trivial](http://en.wikipedia.org/wiki/Trivial_group), it prints out the proof including all [Andrews-Curtis moves](http://www.jstor.org/stable/2033843). If it can not prove __P__ is [trivial](http://en.wikipedia.org/wiki/Trivial_group), it simply prints the original balanced [presentation](http://en.wikipedia.org/wiki/Presentation_of_a_group) indicating it is a counterexample to the [Andrews-Curtis Conjecture](http://www.jstor.org/stable/2033843).

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
