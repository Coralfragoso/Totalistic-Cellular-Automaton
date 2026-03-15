//Totalistic Cellular Automaton

/*----------------------------------------------------------------------------------------------------------
Program 1: Totalistic Cellular Automation
    Implements the evolution of a one-dimensional cellular automation, with a world of cells 
    inative (whitespace), at-risk (-), or thriving (+). Starting with an initial cell status (1 or 2))
    and user-specified number of generations for evolution. Evolution follows a rule's base-3 representation
    corresponding with local sum of each cell for the next generation of cell statuses.
Course: CS 211, Fall 2025, UIC
Author: Coral Fragoso Herrera
-----------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdbool.h>

const int WORLD_SIZE = 65;

typedef struct cell_struct{
    int localSum; // total sum of local cells, [left] + [me] + [right]: possible values are 0-6
    int status;   // this cell's current status: 0, 1, or 2
    int count;    // running accumulated count of this cell's active status for all generations
} cell;

// This function converts an integer rule (0-2186) to its base-3 representation, 
// stored in reverse order, as an array of 7 status values, i.e. valArray[7] 
//   ex: rule = 777  -> [0121001], since 777  = 1*3^1 + 2*3^2 + 1*3^3 + 1*3^6   
//   ex: rule = 177  -> [0210200], since 177  = 2*3^1 + 1*3^2 + 2*3^4
//   ex: rule = 2040 -> [0210122], since 2040 = 2*3^1 + 1*3^2 + 1*3^4 + 2*3^5 + 2*3^6
//return true if input rule is valid (0-2186)
//return false if input rule is invalid
bool setValArray(int valArray[7], int rule) {

    //TODO: Task 1 - write the setValArray() function

    int currRule = rule; // get current rule

    for (int i = 0; i <= 6; i++) {
        valArray[i] = currRule % 3; // stores the remainder
        currRule = currRule / 3;    // updates the current rule

    }
    // checks for rule validity
    if ((rule <= 2186) && (rule >= 0)) {
        return true;
    }

    return false;
}

// This function displays new cell status using the base-3 representation of the rule as
// a paramter to print the corresponding cell state
void setNewState(int valArray[7]) { 
    for (int index = 6; index >= 0; index--) {
        // checks for corresponding cell status based on the the array
        // position value
        if (valArray[index] == 0) {      // inactive cell status
            printf("| |");
        }
        else if (valArray[index] == 1) { // at-risk cell status
            printf("|-|");
        }
        else {
            printf("|+|");           // thriving cell status
        }
        printf("     ");

        if (index == 0) {
            printf("\n\n");
        }
    }
}

// This function updates the localSum subitem for each cell in the world array based on the
// current statuses for the nearby [left, me, right] cells
// note: world is periodic/cyclic, with front-to-back and back-to-front wrapping 
void setSums(cell world[WORLD_SIZE]) {

    //TODO: Task 4 - write the setSums() function
    for (int i = 0; i < WORLD_SIZE; i++) {
        // checks if a cell is at the beginning or end of the world
        if (i == 0) {       // first cell
            // updates the localSum of the first cell by wrapping world with the last cell 
            world[i].localSum = world[64].status + world[i].status + world[i+1].status;
        }
        else if (i == 64) { // last cell
            // updates the localSum of the last cell by wrapping world with the first cell
            world[i].localSum = world[i-1].status + world[i].status + world[0].status;
        }
        else {
            // updates cell's localSum with sum of the cell's status and its left and right neighbor's status
            world[i].localSum = world[i-1].status + world[i].status + world[i+1].status;
        }
    }

    return;
}

// Evolve the world to the next generation by updating each cell's status value 
// using its localSum subitem (assumed to be updated outside of this function), where
// ruleValArray[7] stores the status values for the 7 possible local sums, in reverse order, 
// e.g. if local sum = 4, the new status value can be found at index 4 of the ruleValArray[].
// This function must also update the count subitems for all cells in world[] 
// with the new generation status values.
// This function returns the total sum of all status values in world[] after the evolution step.
int evolveWorld(cell world[WORLD_SIZE], int ruleValArray[7]) {
    //TODO: Task 6 - write the evolveWorld() function
    int sum = 0; // get the sum of statuses in a generation
    for (int i = 0; i < WORLD_SIZE; i++) {
        world[i].status = ruleValArray[world[i].localSum]; // sets new cell status based on local sum 
        world[i].count += world[i].status;                 // increments count by cell status
        sum += world[i].status;                            // increments sum by each cell status
    }

    return sum; // returns total of all status values in a generation
}

// This function displays the first generation and initializes the world in the world array 
// with the initial parameter as the status of the first cell and updates the count, 
// local sum, and status of all other cells to 0
void initialWorld(cell world[WORLD_SIZE], int initial) {
    for (int i = 0; i < WORLD_SIZE; i++) {
        // checks for middle cell 
        if (i == 32) {
            // initializes middle cell's status and count to initial status
            world[i].status = initial;
            world[i].count = initial;
        }
        else {
            // initializes all other cell's to 0
            world[i].status = 0;
            world[i].count = 0;
        }
    }

    setSums(world); // updates local sums for each cell
    int sum = 0;    // sets total sum of all status values to 0

    for (int i = 0; i < WORLD_SIZE; i++) {
        // checks for cell status to display matching symbol
        if (world[i].status == 1) {
            printf("-"); // at-risk cell
        }
        else if (world[i].status == 2) {
            printf("+"); // thriving cell
        }
        else {
            printf(" "); // inactive cell
        }
        sum += world[i].status; // increments sum by cell status
    }
    printf(" %d ", sum);
    printf("\n");
}

int main() {
    cell world[WORLD_SIZE]; // declares a world array of cells

    printf("Welcome to the Totalistic Cellular Automaton!\n");
    printf("Enter the rule # (0-2186): ");

    //TODO: Task 2 - read in a valid rule#, allowing repeated attempts if necessary,
    //      generate the rule's 7-trit (i.e. 7 base-3 digits) status value array,  
    //      print the status value array in correct ternary (i.e. base-3) number order

    int rule;       // stores user's rule number
    int ternary[7]; // stores base-3 representation of rule

    scanf("%d", &rule);

    // continues prompting for new rule until valid (0-2186)
    while (setValArray(ternary, rule) == false){
        printf("Enter the rule # (0-2186): ");
        scanf("%d", &rule);
    }
    printf("The value array for rule #%d is ", rule);

    // displays base-3 representation of rule
    for (int i = 6; i >= 0; i--) {
        printf("%d", ternary[i]);
    }
    printf("\n");

    // displays all possible states grouped by local sums
    printf("The evolution of all possible states are as follows:\n");
    printf("Local Sum:   6       5       4       3       2       1       0      \n");
    printf("States:    |+++|   |++-|   |++ |   |+- |   |-- |   |-  |   |   |    \n");
    printf("                   |+-+|   |+ +|   |+ -|   |- -|   | - |            \n");
    printf("                   |-++|   | ++|   |-+ |   | --|   |  -|            \n");
    printf("                           |+--|   | +-|   |+  |                    \n");
    printf("                           |-+-|   |- +|   | + |                    \n");
    printf("                           |--+|   | -+|   |  +|                    \n");
    printf("                                   |---|                            \n");
    printf("New Status: ");  

    //TODO: Task 3 - use the rule status value array to report the evolution 
    //      step for all possible cell neighbor states [left, me, right].
    //      Follow the format, including whitespaces, of the sample output EXACTLY.
    
    setNewState(ternary); // displays new status

    printf("Enter the number of generations (1-49): ");     

    //TODO: Task 5a - read in the total number of generation evolution steps
    //      from the user, allowing repeated attempts for invalid values.
    //      Follow the format, including whitespaces, of the sample output EXACTLY.

    int numGen; // stores number of generations
    scanf("%d", &numGen);

    // continues prompting until a valid integer is input (1-49)
    while ((numGen < 1) || (numGen > 49)) {
        printf("Enter the number of generations (1-49): ");
        scanf("%d", &numGen);
    }

    printf("Enter the value (1 or 2) for the initial active cell: ");

    //TODO: Task 5b - read in the initial status value for the middle cell, 
    //      allowing repeated attempts for invalid values. 
    //      Follow the format, including whitespaces, of the sample output EXACTLY.

    int initial; // stores initial status of world of 1 or 2
    scanf("%d", &initial);

    // continues prompting until a valid initial status is input (1 or 2)
    while ((initial < 1) || (initial > 2)) {
        printf("Enter the value (1 or 2) for the initial active cell: ");
        scanf("%d", &initial);
    }

    printf("\nInitializing world & evolving...\n");

    //TODO: Task 5c - initialize the world with the ONLY non-zero cell in the 
    //      exact middle of the world, whose status value is set using the 
    //      scanned-in value from the user above. Make sure to also set the 
    //      localSum subitem for each cell of the initial world.
    //      Follow the format, including whitespaces, of the sample output EXACTLY.

    initialWorld(world, initial); // initializes the world
    
    //TODO: Task 7 - evolve the world the user-specified number of generations,
    //      printing the world after each evolution step, where each cell prints as
    //      '+', '-', or ' ' (whitespace) for status value of 2, 1, or 0, respectively.
    //      After the world display, also print out the total sum of all status values.
    //      Follow the format, including whitespaces, of the sample output EXACTLY.
    //
    //      Ex: world = [00000000000000000020101212111001210011121210102000000000000000000]
    //          display->                  + - -+-+---  -+-  ---+-+- - +                   28 <-display
    //
    //      At the end of ALL evolution steps, print a line under the last generation. 
    //      Ex: world = [02211210000121122111001121121001210012112110011122112100001211220]
    //          display-> ++--+-    -+--++---  --+--+-  -+-  -+--+--  ---++--+-    -+--++  64 <-display
    //          display->_________________________________________________________________<-display

    // evolves world for numGen generations
    for (int gen = 1; gen < numGen; gen++) {
        // current total sum of cell statuses in a generation 
        int sum = evolveWorld(world, ternary); // updates count and status of cells

        // displays the status symbol of each cell in current generation
        for (int j = 0; j < WORLD_SIZE; j++) {
            // checks status value for corresponding symbol
            if (world[j].status == 2) {
                printf("+");
            }
            else if (world[j].status == 1) {
                printf("-");
            }
            else {
                printf(" ");
            }
        }
        printf(" %d \n", sum); // displays sum of cell statuses 
        setSums(world);        // updates local sums of each cell 
    }

    // underlines end of evolution
    for (int i = 0; i < WORLD_SIZE; i++) {
        printf("_");
    }
    printf("\n");
   
    //TODO: Task 8 - after the line under the last generation, 
    //      print the total sum for each cell throughout all evolution steps vertically.
    //      The cell total sums should be printed as two digit numbers across two lines.
    //      Single-digit total sums should be represented as a whitespace on the top line, 
    //      and the single-digit on the lower line. 
    //      For total sums of zero, print both digits as whitespaces.
    //      Follow the format, including whitespaces, of the sample output EXACTLY.
    //
    //      Ex: consider a world after many evolution steps with the following final generation:
    //          display-> ++--+-    -+--++---  --+--+-  -+-  -+--+--  ---++--+-    -+--++  64 <-display
    //          display->_________________________________________________________________<-display   
    //          display->            11111111122121222233233222212122111111111            <-display 
    //          display-> 243666698963456647182091851471191174158190281746654369896666342 <-display 
    //                   ^ ^                             ^
    //      note: the first cell was ALWAYS 0, so its total sum is zero, and prints as two whitespaces
    //            the third cell has a total sum of 4, so it prints as a whitespace above the digit 4
    //            the middle cell has a total sum of 29, so it prints the digit 2 above the digit 9

    // displays count's tens place value for each cell
    for (int i = 0; i < WORLD_SIZE; i++) {
        // checks for digits of 1
        if (world[i].count/10 == 0) {
            // displays whitespace
            printf(" ");
        }
        else {
            // displays tens place
            printf("%d", world[i].count/10);
        }
    }
    printf("\n");

    // displays count's one place value for each cell
    for (int i = 0; i < WORLD_SIZE; i++) {
        // checks for both digits with 0 value
        if ((world[i].count/10 == 0) && (world[i].count % 10 == 0)) {
            // displays whitespace
            printf(" ");
        }
        else {
            // displats ones place
            printf("%d", world[i].count % 10);
        }
    }
    printf("\n"); // make sure to end your program with a newline

    return 0;
}