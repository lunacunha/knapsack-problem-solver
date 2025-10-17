# Knapsack Problem Solver

Course project for Algorithms and Data Structures (L.EIC - FEUP, 2023/2024)

## Problem Description

Given a truck with limited capacity and a set of pallets with specific weights and profits, the goal is to select pallets that maximize total profit without exceeding the truck's weight capacity.

## Algorithms Implemented

### 1. Exhaustive Search (Backtracking)
- **Method**: Branch and bound with pruning
- **Optimality**: Guaranteed optimal solution
- **Complexity**: O(2^n) worst case
- **Best for**: Small datasets (n ≤ 20)

### 2. Dynamic Programming
- **Method**: Bottom-up tabulation approach
- **Optimality**: Guaranteed optimal solution
- **Complexity**: O(n × W) where W is capacity
- **Best for**: Medium datasets with reasonable capacity

### 3. Greedy Approximation
- **Method**: Sort by profit/weight ratio, select greedily
- **Optimality**: Approximate solution (not guaranteed optimal)
- **Complexity**: O(n log n)
- **Best for**: Large datasets requiring fast solutions

### 4. Integer Linear Programming (ILP)
- **Method**: External Python solver using optimization libraries
- **Optimality**: Guaranteed optimal solution
- **Requires**: Python environment with solver library
- **Best for**: Production-grade solutions

## Datasets

The application includes 10 test datasets:
- **Datasets 01-04**: Standard test cases in `datasets/`
- **Datasets 05-10**: Extended test cases in `datasets-extra/`

### Dataset Format

**TruckAndPallets_XX.csv**:
```
Capacity
<truck_capacity>
```

**Pallets_XX.csv**:
```
ID,Weight,Profit
1,<weight>,<profit>
2,<weight>,<profit>
...
```

## Building and Running
```bash
# Compile
g++ -std=c++17 *.cpp -o knapsack_solver

# Run
./knapsack_solver
```

## Usage Flow

1. **Select Dataset**: Choose from datasets 01-10
2. **Select Algorithm**: Choose solving method (1-4)
3. **View Results**: See solution details and execution time

## Output Format
```
=== [Algorithm Name] Result ===
Total profit: <total_profit>
Total weight: <total_weight> / <capacity>
Execution time: <time_ms> ms
Selected pallets: <id1> <id2> ... <idN>
================================
```

## ILP Solver Setup

For the ILP option, ensure Python environment is configured:
```bash
# Create virtual environment
python -m venv .venv

# Activate environment
source .venv/bin/activate  # Linux/Mac
.venv\Scripts\activate     # Windows

# Install required packages
pip install pulp  # or your preferred ILP solver library
```

The ILP solver uses temporary files:
- `input.txt` - Problem specification
- `output.txt` - Solution results

## File Structure
```
├── KnapsackSolver.cpp/h    # Algorithm implementations
├── Parser.cpp/h            # Dataset loading utilities
├── Menu.cpp/h              # User interface
├── main.cpp                # Entry point
├── knapsack_solver.py      # Python ILP solver
├── datasets/               # Standard datasets (01-04)
└── datasets-extra/         # Extended datasets (05-10)
```

## Algorithm Comparison

| Algorithm | Optimality | Speed | Memory | Best Use Case |
|-----------|-----------|-------|--------|---------------|
| Exhaustive | Optimal | Slowest | O(n) | Small n |
| Dynamic | Optimal | Medium | O(n×W) | Medium n, W |
| Greedy | Approximate | Fastest | O(n) | Large n |
| ILP | Optimal | Variable | Variable | Production |

## Optimization Techniques

### Exhaustive Search Pruning
- **Bound pruning**: Skip branches that cannot improve current best
- **Weight pruning**: Skip combinations exceeding capacity

### Dynamic Programming
- **Space optimization**: 1D array instead of 2D table
- **Traceback table**: Reconstruct solution efficiently

## Notes

- All algorithms handle edge cases (empty datasets, zero capacity)
- Execution times are measured in milliseconds
- Selected pallets are displayed by their IDs
- ILP solver requires external Python script to be properly configured
- Dataset selection automatically determines the correct file path
