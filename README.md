# Pong

Simple Pong game written in C++ using SFML, Crank and built using Meson. This project is pretty hacky and mostly serves as a project to test the usage of the Crank state framework.

## Content

- [Pong](#pong)
  - [Content](#content)
  - [Building](#building)
    - [Perquisites](#perquisites)
  - [Running](#running)
  - [License, Code of Conduct \& Contributing](#license-code-of-conduct--contributing)

## Building

### Perquisites

- [SFML](https://www.sfml-dev.org/download.php)
- [bpt](bpt.pizza/docs/latest/index.html)

```sh
meson setup targets
meson compile -C targets
```

## Running

```sh
# Launch application
./targets/pong
```

## License, Code of Conduct & Contributing

This project is under the [MIT License](LICENSE). The [code of conduct](CODE_OF_CONDUCT.md) is governed by the contributor covenant (v2.1). Contributing guidelines are outlined in the [here](CONTRIBUTING.md).
