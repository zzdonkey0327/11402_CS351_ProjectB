# Project B - CSV Mini Database & Query Engine

Project B is a lightweight implementation of a CSV-backed mini database and query engine. It is designed to ingest CSV files, store tabular data efficiently in memory, and support query operations similar to a simple database engine (like MySQL or SQL Server, but backed by CSV files instead).

## Project Description

This project builds a compact database system for structured CSV data. The core idea is to load CSV files into memory and provide database-like operations without relying on external database systems. It focuses on:

- Loading CSV files with the `LOAD` command
- Parsing CSV files and managing rows and columns in memory
- Supporting row insertion with `INSERT INTO ... VALUES ...` syntax
- Supporting `SELECT` queries to retrieve data from loaded CSV tables
- Supporting query operations such as filtering, sorting, and other database-like manipulations
- Providing a simple query interface for extracting and transforming CSV data
- Maintaining a clean, modular implementation suitable for learning database engine fundamentals

## Goals

- Enable users to load CSV tables and execute expressive queries without external databases
- Implement core query engine components (LOAD, INSERT, SELECT) in a self-contained system
- Demonstrate understanding of data parsing, storage, and query execution
- Deliver a practical tool for working with CSV datasets with in-memory database-like operations

## Supported Operations

- **LOAD**: Load CSV files into memory as database tables
- **INSERT INTO ... VALUES ...**: Add new rows to loaded tables
- **SELECT**: Retrieve data from tables with filtering and query capabilities

## Usage

```
LOAD data.csv
INSERT INTO table_name VALUES (col1_value, col2_value, ...)
SELECT * FROM table_name WHERE condition
```
