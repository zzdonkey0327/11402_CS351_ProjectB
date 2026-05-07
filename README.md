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
