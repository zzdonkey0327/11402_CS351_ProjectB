# Software Design Specification

## 1. Purpose

This document describes the software design of the CSV Mini Database & Query Engine. It explains how the system is organized internally and how each major component contributes to the required features.[web:77][web:86]

## 2. Scope

This design covers the startup interface, command parsing, CSV loading, in-memory table storage, query execution, insertion logic, and error handling for version 1.

## 3. High-Level Architecture

The system follows a modular CLI-based architecture composed of the following parts:

- Command-line interface module
- Command parser module
- CSV loader module
- In-memory table storage module
- Query executor module
- Error handling and output formatter module

## 4. Module Design

### 4.1 CLI Module
Responsibilities:
- Print welcome message
- Display supported commands
- Read user input in a loop
- Forward commands to the parser

### 4.2 Parser Module
Responsibilities:
- Identify command type (`LOAD`, `SELECT`, `INSERT`)
- Extract tokens such as filename, table name, column names, and values
- Validate basic command syntax before execution

### 4.3 CSV Loader Module
Responsibilities:
- Open CSV files
- Read header row
- Parse rows into internal records
- Return a table object to the storage module

### 4.4 In-Memory Storage Module
Responsibilities:
- Store table name
- Store column definitions
- Store rows as structured records
- Provide data access for queries and insertion

Suggested data structure:
- `Table`
  - `name`
  - `columns`
  - `rows`

### 4.5 Query Executor Module
Responsibilities:
- Execute `SELECT *`
- Execute projection queries
- Retrieve requested columns from stored rows
- Format output for display

### 4.6 Insert Executor Module
Responsibilities:
- Validate target table
- Match column names with positions
- Construct a new row
- Append the row to the in-memory table
- Optionally trigger CSV persistence

### 4.7 Error Handling Module
Responsibilities:
- Produce clear user-facing error messages
- Handle invalid syntax, file errors, and schema mismatches
- Prevent abrupt program termination

## 5. Data Design

### 5.1 Table Representation
The table is stored in memory after a successful `LOAD`. The first row of the CSV file becomes the schema, and each subsequent line becomes a row in the table.

### 5.2 Row Representation
A row can be stored as:
- a list of string values aligned by column index, or
- a map from column name to value

For simplicity and speed, version 1 should use a list-based row structure plus a column index map.

## 6. Control Flow

### 6.1 Startup Flow
1. Start program
2. Print help message
3. Enter command loop
4. Wait for user input

### 6.2 LOAD Flow
1. Parse filename
2. Open file
3. Read header
4. Read rows
5. Create table object
6. Store table in memory
7. Print success or error

### 6.3 SELECT Flow
1. Parse query
2. Validate table
3. Validate columns
4. Retrieve matching data
5. Print results

### 6.4 INSERT Flow
1. Parse insert command
2. Validate table
3. Validate columns
4. Validate value count
5. Build new row
6. Append row to memory
7. Print result

## 7. Design Decisions

- The first version supports a single active table to reduce complexity.
- The parser supports only a small SQL-like grammar.
- All loaded data is kept in memory for faster query execution on small datasets.
- Persistence back to CSV is optional in the first implementation.

## 8. Future Extensions

- Add `WHERE`
- Add `DELETE`
- Add `UPDATE`
- Add sorting and aggregation
- Add support for multiple loaded tables