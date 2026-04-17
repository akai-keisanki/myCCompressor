# ![`myccompressor` logo](img/myccompressor_icon.png) myCCompressor
![created at](https://img.shields.io/github/created-at/akai-keisanki/myCCompressor)
![license](https://img.shields.io/github/license/akai-keisanki/myCCompressor)
![release](https://img.shields.io/github/v/release/akai-keisanki/myCCompressor)
![top language](https://img.shields.io/github/languages/top/akai-keisanki/myCCompressor)
![forks](https://img.shields.io/github/forks/akai-keisanki/myCCompressor)
![stars](https://img.shields.io/github/stars/akai-keisanki/myCCompressor)

Testing file compression in C.

## Features

- Multiple available compressors (WIP);
- Scalable lists of compressors, supporting custom compression and decompression routines;
- Standard I/O for compression and decompression, supporting pipes.

## Usage

### Compiling from source

If you clone this repository, you can compile the program with
```sh
make myccompressor
```

### Command usage

The `myccompressor` binary can be executed in the terminal, taking 2 positional necessary arguments:
```
myccompressor COMPRESSOR OPERATION
```
Where `COMPRESSOR` can be any available compressor (vid. [Available Compressors](#available-compressors) below) and `OPERATION` can be `compress` or `decompress`.

## Available Compressors

- `simple_rle`: simplified Run-Length Encoder
- `rle`: classic Run-Length Encoder
