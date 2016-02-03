# Local Word Count

Count word in a huge record file using single machine.

# Requirement

## Basic

* C/C++
* Using multiple thread to implement the program.

## Function

* Find all word field in the file.
* Tokenizing fields into terms and Calculate the frequency of each term.

## Misc

* The path of dictionary should be configurable.
* Program should be configurable.
    * Passing configuration by parameter.
    * The program, configuration, data and log should be placed in `bin/`, `conf/`, `data/` and `log/` respectively.
* The log are classified as `warning`, `fatal`, `error`, `trace` and `debug`.
    * The `fatal`, `error` should contain function name and the line number.
    * `fprintf` is not allowed.
* Using version control.
* Using google test.

## Output format

* `term, frequency, percentage(frequency/total lines)`
* Fields are separated by `\t`.

# Record File Format

Each line is a record. The line break is `\n`. Fields are separated by `\t`. The 8th and 9th field are wordid and word.

# Progress

## Finished

* Crawler (Python)

## ToDo

* Word Count (C++)

## Project Used

* [nlohmann/json](https://github.com/nlohmann/json)
* [yanyiwu/cppjieba](https://github.com/yanyiwu/cppjieba)
* [gabime/spdlog](https://github.com/gabime/spdlog)