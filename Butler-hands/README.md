# Butler-hands

**Butler-hands is the universal environment and execution interface for PetoronAI-Butler.**

It allows Butler to interact with external systems without adding domain-specific logic to Butler itself.

## What are PetoronAI, Butler, and Butler-hands?

```text
PetoronAI
    =
Cognitive infrastructure:
reasoning, memory, planning, learning,
decision-making, risk assessment and other
cognitive mechanisms.

PetoronAI-Butler
    =
Universal decision-making brain built on PetoronAI.
It receives a goal, evaluates the available information
and actions, and decides what should be done.

Butler-hands
    =
Universal interface between Butler and the external world.
It shows Butler what exists in an environment,
what actions are available, executes the action selected
by Butler, and returns the real result back to Butler.

Your Environment
    =
The concrete world Butler can interact with:
source code, files, scientific data, simulations,
devices, robots, or another external system.
```

In simple terms:

> **PetoronAI provides the cognitive mechanisms. Butler decides. Butler-hands lets Butler act.**

## Who is Butler-hands for?

Butler-hands is intended for developers who want to use PetoronAI-Butler in a real application or domain.

Instead of modifying Butler for every new task, a developer creates an environment that describes:

- what Butler can observe;
- what actions Butler can perform;
- how those actions are executed;
- what happened after execution.

The same Butler can therefore operate in completely different environments.

For example:

```text
Butler + Butler-hands + CoderEnvironment
    → autonomous software engineering

Butler + Butler-hands + LaboratoryEnvironment
    → autonomous scientific research

Butler + Butler-hands + SimulationEnvironment
    → autonomous simulation work

Butler + Butler-hands + RoboticsEnvironment
    → autonomous interaction with a robotic system
```

Butler itself does not need to be rewritten for each domain.

## How It Works

The basic loop is:

```text
External World
      ↓
Environment observes the current state
      ↓
Butler-hands passes it to Butler
      ↓
Butler decides what to do
      ↓
Butler-hands executes the selected capability
      ↓
Environment returns the real result
      ↓
Butler receives feedback and experience
      ↓
Next decision
      ↺
```

The environment provides the world.

Butler provides the decision.

Butler-hands connects them.

## Simple Example

Suppose the goal is:

```text
Fix the C++ project and make all tests pass.
```

A coding environment reports:

```text
Current state:
- build failed
- compiler error exists

Available actions:
- inspect_build_log
- inspect_file
- modify_sandbox
- build_project
- run_tests
```

Butler evaluates the current state and selects:

```text
inspect_build_log
```

Butler-hands executes that action through the coding environment.

The environment returns:

```text
parser.cpp:117: expected ';'
```

That result becomes new information for Butler.

Butler can then select:

```text
inspect_file
```

After inspecting the file, Butler may select:

```text
modify_sandbox
```

Then:

```text
build_project
```

If the build succeeds, Butler can select:

```text
run_tests
```

The important point is that **Butler-hands does not contain the solution**.

The coding environment only exposes the current state and available tools.

Butler decides how to use them.

## How to Use Butler-hands

### 1. Create an Environment

Implement a Butler-hands `Environment` for the system you want Butler to control.

Conceptually, an environment provides two operations:

```cpp
observe()
execute()
```

### 2. Expose the Current World

In `observe()`, provide Butler with the current state of the environment.

This can include:

```text
observations
relations
knowledge
capabilities
constraints
```

For a coding environment, this could be compiler output and available development operations.

For a laboratory environment, it could be datasets, experimental state and available analytical operations.

### 3. Expose Capabilities

Capabilities are actions Butler is allowed to choose.

Examples:

```text
inspect_file
run_build
run_tests
analyze_dataset
run_simulation
measure_state
```

Do not encode the answer into the capabilities.

Expose tools and actions. Let Butler decide how to use them.

### 4. Implement Execution

In `execute()`, connect each capability to the real operation in your environment.

For example:

```text
run_build
    → start the compiler

inspect_file
    → read the requested source information

run_tests
    → execute the test suite

run_simulation
    → execute the simulation
```

### 5. Give Butler a Goal

Start Butler-hands Runtime with the goal you want Butler to pursue.

Butler-hands then manages the interaction loop:

```text
observe
→ decide
→ execute
→ receive result
→ feedback
→ observe again
```

## Core Rule

> **Do not teach Butler how every external system works by modifying Butler. Give Butler an Environment through Butler-hands.**

The architecture remains:

```text
PetoronAI
    ↓
PetoronAI-Butler
    ↓
Butler-hands
    ↓
Your Environment
```

One cognitive architecture, one decision-making layer, one universal execution interface, and any number of external environments.


---

Petoron | Ivan Alekseev