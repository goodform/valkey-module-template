
<h1 align="center">
Valkey Module Template
</h1>

It is mainly used to support the faster development of ValkeyModule.

You can expect from each sample:

- Create a module
- Create a Valkey command
- Write specific test cases

# Usage

- `git clone https://github.com/goodform/valkey-module-template`
- `cd <any-sample-folder>`
- `git submodule update --init --recursive`
- `make & make test`
- Alternatively, running the sample

# Getting Started

Create your own module through unified commands:

```
git clone https://github.com/goodform/valkey-module-template <new-module-name>
cd <new-module-name>
git submodule update --init --recursive
git remote set-url origin <your-repo-path>
python init-project.py <new-module-name>
```

## Tests

The module includes a basic set of unit tests and integration tests.

**Unit tests**

To run all unit tests, follow these steps:

    $ bash runtest.sh