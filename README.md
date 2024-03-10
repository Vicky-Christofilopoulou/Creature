# Creature
Implementation of a project based on inheritance in C++, as a project in "Object-Oriented Programming" course.


We have a community of creatures: good creatures and bad creatures, each one. Creatures live next to each other, in a specific position. 
The creatures have the following characteristics:
1. Each creature has a name.
2. Each creature has an expected lifespan. Initially, when born, it is L, with L > 0 (L is common for all creatures).
3. When a creature's life is reduced to zero, the creature becomes a zombie. In the zombie state, the following actions have no effect.
4. A creature can be cloned in the position of another creature. In this case, the other creature is destroyed, and a new creature is created as a copy of the first one.
5. Each creature can either be blessed or beaten. In the first case, its lifespan is increased by one unit. In the second case, it is reduced by one unit.

• Good creatures, when blessed and robust enough, clone themselves, occupying the next position in the community (the next position after the last one is the first). They are considered "robust" if their current life is greater than a threshold (good threshold) common to all good creatures.

• Bad creatures, when blessed and robust enough, clone themselves, occupying all their consecutive positions in the community that are already occupied by creatures in the zombie state (unless the bad creature being blessed is at the end). They are considered "robust" if their current life is greater than a threshold (bad threshold) common to all bad creatures.


For the implementation, use the following classes:

# creature: 
This class stores:
1. the name of the creature
2. the expected lifespan of the creature
its behavior is characterized by the fact that
1. initially, its life is equal to L, it is not in zombie state, it belongs to a position in a community, and it takes its name
2. it is checked whether it is a zombie or not by checking if its life is equal to 0 (is a zombie)
3. it is checked whether it is a good creature or not (is a good), deferring the check to the derived classes
4. it is cloned, replacing another creature, destroying it and creating a copy to take its place in the community
5. it is beaten, reducing its life by one unit if it is not in a zombie state
6. it is blessed, increasing its life by one unit if it is not in a zombie state."

# good_bad_creature: 
This class specializes the creature class with the following:
1. When blessed, in addition to the behavior demonstrated as a creature, if it is robust, it clones itself in the next position.
2. The is_a_good check returns true.

# bad_creature: 
This class specializes the creature class with the following:
1. When blessed, in addition to the behavior demonstrated as a creature, if it is robust, it clones itself in all the next positions occupied by creatures in the zombie state and are consecutive to its own (unless it is at the end).
2. The is_a_good check returns false.

# society:
This class stores:
1. the number of creature positions it has
2. an indication of its initial position in the community sequence
Its behavior is as follows:
1. Initially, N creature positions are created, occupied by N creatures that are randomly created as either good or bad creatures.
2. Position i is beaten, beating the creature in that position.
3. Position i is blessed, blessing the creature in that position.
4. Creature in position i is cloned to its next position (clone_next).
5. Creature in position i is cloned to all consecutive positions starting from position i, occupied by creatures in the zombie state — unless i corresponds to the last position — (clone_zombies).
6. The number of good creatures in the community is returned (no_of_good).
7. The number of creatures in the community that are in the zombie state is returned.

