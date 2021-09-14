# Mirage-Renderer
A repository to render fractals and encode bitmaps.

## Files
- `bmpEncoder.h` provides functions to initialize and save bitmaps. The cost of function calling might be great in high-performance requirement and it's difficult to write a universal function for every kind of bpps, thus reading and writing operations should be realized by user.
- `bmpLine.h` defines line equations used in fractal rendering. The linear functions is frequently used in fractal rendering in coordination translation. It is the base of almost every fractal lib in this repo. **Might be renamed.**
- `bmpPalette.h` provides some palettes, mainly gradients. The definition of type PALETTE is in `bmpEncoder.h`, and the palettes provided here is the same with that difinition, so it can be used directly to initialize bitmaps.
- `fractalBarnsleyFern.h` renders [Barnsley fern](http://en.wikipedia.org/wiki/Barnsley_fern).
- `fractalFeigenbaumGraph.h` renders [Logistic map](http://en.wikipedia.org/wiki/Logistic_map). **Might be renamed.**
- `fractalIterate.h` renders [Mandelbrot set](http://en.wikipedia.org/wiki/Mandelbrot_set) and [Julia set](http://en.wikipedia.org/wiki/Julia_set). **Might be renamed and/or overwritten.**

## Future work
- Add comments in headers
- Split headers into `.h` and `.c` files
- Rename and/or overwrite the files noted above
- Add more images

## Credits
This lib uses [clibs/mt19937ar](https://github.com/clibs/mt19937ar) under BSD licence to generate random numbers.
