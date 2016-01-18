@(@pending)[machine learning 机器学习, spark, python]

# Notes of CS100.1x Introduction to Big Data with Apache Spark (2)

## Lecture 5: Semi-Structured Data

### Data

data model: a collection of concepts for describing data.
schema: a description of a particular collection of data using a given data model.

### The structure spectrum

* unstructured, or schema-never data
* semi-structured, or structure-later data
* structured data, and this is schema-first data

### Data frames of pandas and pyspark

* pandas
	a table with named columns.
	
* pyspark
	a DataFrame is a **distributed** collection of data organized into named columns. It is conceptually equivalent to a table in a relational database or a data frame in R/Python, but with richer optimizations under the hood.

The DataFrame of pyspark usually provide **better performance**.

