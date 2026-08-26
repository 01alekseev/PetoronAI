# PetoronAI Butler

## Overview

**PetoronAI Butler** is the official public runtime interface for
**PetoronAI**.

Its purpose is to provide a single, stable entry point into the complete
cognitive architecture of PetoronAI. Applications interact only with
Butler rather than directly with internal cognitive subsystems.

------------------------------------------------------------------------

## Purpose

PetoronAI contains many independent cognitive components, including:

-   Goal Resolution
-   Reasoning Engine
-   Executive Layer
-   Agent Cycle
-   Strategy Engine
-   Policy Selection
-   Decision Arena
-   Future Simulation
-   Reflection
-   Learning
-   Memory
-   Knowledge
-   Thought Graph
-   Experience
-   Executive Feedback
-   Goal Policies
-   Context Selection
-   Reinforcement
-   World Model

Butler orchestrates these components into one coherent execution
pipeline.

------------------------------------------------------------------------

## Architecture

```
Application
      │
      ▼
PetoronAI Butler
      │
      ▼
PetoronAI
```

Applications depend only on Butler.

------------------------------------------------------------------------

## Public API

``` cpp
petoron_ai_butler::Request request;

auto result =
    petoron_ai_butler::run(request);
```

------------------------------------------------------------------------

## Execution Pipeline

```
Request
    │
    ▼
Goal Resolution
    │
    ▼
Reasoning
    │
    ▼
Thought Processing
    │
    ▼
Executive Planning
    │
    ▼
Policy Selection
    │
    ▼
Strategy Evaluation
    │
    ▼
Decision Arena
    │
    ▼
Future Simulation
    │
    ▼
Action Selection
    │
    ▼
Reflection
    │
    ▼
Learning
    │
    ▼
Experience Update
    │
    ▼
Result
```

------------------------------------------------------------------------

## Responsibilities

-   Receive requests
-   Coordinate cognitive modules
-   Execute reasoning
-   Execute planning
-   Select strategies and policies
-   Update experience and memory
-   Return a unified execution result

------------------------------------------------------------------------

## What Butler Is Not

Butler is not an LLM, chatbot, compiler, browser, terminal, or
filesystem. It is a cognitive runtime coordinator PetoronAI.

------------------------------------------------------------------------

## Typical Usage

``` cpp
petoron_ai_butler::Request request;

request.goal = "avoid fire";

auto result =
    petoron_ai_butler::run(request);
```

------------------------------------------------------------------------

## Recommended Development Model

``` text
Application
        │
        ▼
PetoronAI Butler
        │
        ▼
PetoronAI
```

Applications should communicate only with Butler.

---

Petoron | Ivan Alekseev
