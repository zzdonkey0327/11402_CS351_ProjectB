# Intended Use

## Purpose

This project is a lightweight CSV-backed mini database and query engine. It is intended for learning basic database engine concepts by allowing users to load CSV files, store table data in memory, and execute simple SQL-like commands through a command-line interface.[web:60][web:82]

## Intended Users

The intended users are students, instructors, and developers who want to study or demonstrate fundamental database operations without using a full database management system.[web:60][web:79]

## Supported Scope

The first version of the system supports the following commands:

- `LOAD <file.csv>`
- `SELECT * FROM <table>`
- `SELECT <column_list> FROM <table>`
- `INSERT INTO <table> (column1, column2, ...) VALUES (value1, value2, ...)`

The system is designed for local use in a terminal environment and operates on structured CSV files loaded from the local file system.

## Intended Environment

The system is intended to run as a console application on a local machine. The user starts the program in a command-line environment and enters SQL-like commands interactively.

## Assumptions

- Only one CSV table is loaded at a time.
- The CSV file contains a valid header row.
- The first version focuses on `LOAD`, `SELECT`, and `INSERT`.
- The system does not aim to replace a real DBMS such as MySQL or PostgreSQL.

## Limitations

- No support for multi-table joins.
- No advanced SQL clauses such as `GROUP BY`, `HAVING`, or subqueries in version 1.
- Limited input validation compared with production-grade database systems.
- The system is intended for coursework and experimentation rather than production deployment.