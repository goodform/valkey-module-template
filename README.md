
<h1 align="center">
Valkey Module Example
</h1>

It is mainly used to support the faster development of ValkeyModule, mainly based on [ValkeyTimeSeries](https://github.com/ValkeyTimeSeries).

You can expect from each sample:

- Create a module
- Create a Valkey command
- Write specific test cases

# Usage

- `git clone https://github.com/artikell/ValkeyModuleExample`
- `cd <any-sample-folder>`
- `git submodule update --init --recursive`
- `make & make test`
- Alternatively, running the sample

# Getting Started

Create your own module through unified commands:

```
git clone https://github.com/artikell/ValkeyModuleExample <new-module-name>
cd <new-module-name>
sed -i 's/Valkey_module_example/<new-module-name>/g' src/Makefile
git submodule update --init --recursive
git remote set-url origin <your-repo-path>
```

## Tests

The module includes a basic set of unit tests and integration tests.

**Unit tests**

To run all unit tests, follow these steps:

    $ make unit_tests
