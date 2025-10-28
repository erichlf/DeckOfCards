# Deck of Cards

This is a simple deck of cards implementation in C++. I assumed the deck of cards was
a standard deck of 52 cards with the standard suits and face values.

## Container

For ease of building and testing I have provided a docker container. I even have
provided a devcontainer in case you use VSCode. As a bonus (for nvim users) you
can check out my [devcontainer-cli.nvim](https://github.com/erichlf/devcontainer-nvim/) plugin.

### Building the Container

If you aren't using devcontainers then you can simple issue the following
command to obtain a bash prompt inside the container:

```bash
PUID=$(id -u); PGID=$(id -g); docker compose -f .devcontainer/compose.yml run -v $(pwd):/workspace deck_of_cards bash
```

The `PUID` and `PGID` parameters tells docker compose what your user id and
group id is, so that there are no permission issues. Additionally, this will
create a volume for your current working directory mounted as `/workspace`
inside the container.

## Building Source Code

The code uses CMake and Google Test framework, both of which are provided by the
docker container. As such no additional apps need to be installed. To build the
source code from within the container simply run the following commands:

1. `cmake -S . -B build`
2. `cmake --build build`

## Running Tests

The source code includes tests that rely on Google Test. These tests include
simple checks for dealing cards, but also a more complicated test for checking
the randomness of the shuffle function. The randomness test uses a chi-squared
test to verify that the distribution of cards after a shuffle follows a uniform
distribution.

To run the tests, run the following after [building](#building_source_code):

```bash
ctest --test-dir build
```
