# Project B - CSV Mini Database and Query Engine

Project B is a lightweight CSV-backed mini database and query engine.
It ingests CSV files, keeps tabular data in memory, and supports SQL-like operations without requiring an external database system.

## Overview

This project is designed to demonstrate core database engine concepts using plain CSV files as the data source.

Key focus areas:

- Parse CSV files into in-memory table structures
- Execute table operations through simple query commands
- Provide a modular architecture for learning and extension

## Core Features

- `LOAD`: Load a CSV file into memory as a table
- `INSERT INTO ... VALUES ...`: Insert new rows into a loaded table
- `SELECT`: Query table data (for example, projection and filtering)

## Goals

- Build a self-contained query engine for CSV datasets
- Practice data parsing, storage design, and query execution
- Offer a practical, educational alternative to full DBMS usage for small datasets

## Example Commands

```sql
LOAD data.csv
INSERT INTO table_name VALUES (col1_value, col2_value, ...)
SELECT * FROM table_name WHERE condition
```

## Typical Workflow

1. Load one or more CSV files as tables.
2. Insert or update in-memory records as needed.
3. Run `SELECT` queries to inspect, filter, or transform data.

## Future Extensions

- Additional operators (sorting, grouping, aggregation)
- Better error reporting and query validation
- Support for multiple table joins

## Example Session

A typical interactive session with the mini database might look like this:

1. Load a CSV file as a table:

   ```text
   LOAD students.csv
   -> Loaded table "students" with 100 rows.
   ```

2. Insert a new record:

   ```text
   INSERT INTO students VALUES ("CS351", "Alice", 95)
   -> 1 row inserted into "students".
   ```

3. Query the table:

   ```text
   SELECT * FROM students WHERE score >= 90
   -> Returned all students with scores 90 and above.
   ```

These examples illustrate how the engine reads CSV data into memory and applies simple SQL-like commands to interact with it.

## Technical Highlights

Key technical ideas in this project include:

- Designing an in-memory table structure to represent CSV rows and columns.
- Implementing a minimal command parser to handle `LOAD`, `INSERT`, and `SELECT` operations.
- Organizing the code in a modular way so that future extensions (such as sorting, aggregation, or joins) can be added without rewriting the core.

## Development History

The project evolved step by step:

- Started with basic CSV parsing and in-memory storage of rows.
- Added support for commands to load tables and insert new records.
- Implemented a simple SELECT mechanism for filtering and projection.
- Wrote documentation in the `docs` folder to describe requirements, design decisions, and test plans.
- Used branches and pull requests to integrate changes and keep the main branch stable.

## Testing and Demo Results

The current implementation has been tested with several sample CSV files and interactive command sequences.  
In classroom demos, the engine successfully loads data, executes inserts, and runs SELECT queries without crashing, showing that the core functionality is stable enough for educational use.
