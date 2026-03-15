# Totalistic-Cellular-Automaton
One-dimensional totalistic cellular automaton in C with 65-cell wrapped world. Status values (0=space,1='-',2='+') evolve via local sum (0-6) mapped by user rule (0-2186). Implements ternary conversion, world evolution with running totals, and vertical count display.



Features

  -- Rule-based evolution: 2187 possible rules (0-2186) mapped to 7 ternary digits
  
  -- Local sum calculation: Each cell's next state depends on sum of itself and neighbors (0-6)
  
  -- Wrapped world: First and last cells are neighbors
  
  -- Running totals: Each cell tracks accumulated status values across generations
  
  -- Vertical display: Two-line display shows tens and units digits of totals

  
  

Implementation

  -- Cell structure with localSum, status, and count fields
  
  -- Functions: setValArray() (ternary conversion), setSums() (neighborhood sums), evolveWorld() (generation progression)
  
  -- Input validation for rule numbers (0-2186), generations (1-49), and initial values (1 or 2)

  
  

Sample Rules

  -- Rule 777: Shows growth followed by rapid downturn
  
  -- Rule 993: Exhibits different evolutionary patterns

  

Requirements

  -- World size fixed at 65 cells
  
  -- No additional integer arrays (struct array only)
  
  -- Exact formatting matching sample outputs
