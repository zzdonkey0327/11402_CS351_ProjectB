# Software Requirements Specification

## 1. Introduction

### 1.1 Purpose

This document specifies the functional and non-functional requirements for the CSV Mini Database & Query Engine. The system provides a lightweight way to load CSV data and execute basic SQL-like commands in a command-line environment.[web:60][web:75][web:79]

### 1.2 Scope

The system shall load a CSV file into memory as a table and allow users to execute `LOAD`, `SELECT`, and `INSERT` commands. The project is intended for educational use and for demonstrating core database engine concepts.[web:60][web:82]

### 1.3 Definitions

- **CSV**: Comma-Separated Values file format
- **Table**: In-memory representation of CSV data
- **Projection**: Selecting specific columns
- **Row**: One record in a table
- **CLI**: Command-Line Interface

## 2. Overall Description

### 2.1 Product Perspective

The system is a standalone console application. It reads CSV data from local files and processes user commands without relying on an external database server.

### 2.2 User Characteristics

Users are expected to have basic familiarity with command-line interaction and simple SQL-like syntax.

### 2.3 Constraints

- The system operates only on local CSV files.
- Only one table is active at a time in version 1.
- The supported SQL-like commands are limited to `LOAD`, `SELECT`, and `INSERT`.[web:82][web:85]

## 3. Functional Requirements

### FR-01 Startup Help
The system shall print a welcome message when the program starts.  
The system shall display supported commands and example syntax before accepting input.

### FR-02 LOAD Command
The system shall support a `LOAD <file.csv>` command.  
The system shall open the specified CSV file and parse the first row as column names.  
The system shall parse the remaining rows as table data.  
The system shall store the loaded table in memory for later queries.  
The system shall display a success or error message after the `LOAD` operation.

### FR-03 SELECT Command
The system shall support `SELECT * FROM <table>`.  
The system shall support `SELECT <column_list> FROM <table>`.  
The system shall validate that the requested table is currently loaded.  
The system shall validate that all requested columns exist.  
The system shall print the query result in a readable tabular format.

### FR-04 INSERT Command
The system shall support `INSERT INTO <table> (column1, column2, ...) VALUES (value1, value2, ...)`.  
The system shall validate that the specified table is currently loaded.  
The system shall validate that the specified columns exist.  
The system shall validate that the number of values matches the number of specified columns.  
The system shall append the new record to the in-memory table.  
The system shall report insertion success or failure.

### FR-05 Error Handling
The system shall display an error message when the command syntax is invalid.  
The system shall display an error message when a file cannot be opened.  
The system shall display an error message when a column or table does not exist.

## 4. Non-Functional Requirements

### NFR-01 Usability
The system shall provide clear command syntax instructions at startup.

### NFR-02 Maintainability
The source code shall be organized into modular components so that parsing, storage, and command execution can be maintained independently.[web:62][web:77]

### NFR-03 Reliability
The system shall reject malformed commands without terminating unexpectedly.

### NFR-04 Performance
The system should handle small-to-medium CSV files efficiently in memory for coursework-scale datasets.

## 5. External Interface Requirements

### 5.1 User Interface
The interface shall be a text-based terminal interface.

### 5.2 File Interface
The system shall read CSV files from the local file system and may optionally write updated data back to CSV.

## 6. Acceptance Criteria

- The user can load a valid CSV file.
- The user can run `SELECT *` on a loaded table.
- The user can run `SELECT` with specific columns.
- The user can insert a valid new row.
- The system reports meaningful errors for invalid input.