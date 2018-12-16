# Questions

## What's `stdint.h`?

*stdint.h* - is a header file that declares sets of integer types having specified widths.

It's include:
* int8_t
* int16_t
* int32_t
* uint8_t
* uint16_t
* uint32_t

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

Using integer types with a specified range.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

*BYTE* is a 1-byte (8-bit) unsigned integer.

*DWORD* is a 4-byte (32-bit) unsigned integer.

*LONG* is a 4-byte (32-bit) signed integer.

*WORD* is a 16-bit unsigned integer.

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

These "magic numbers" must be *0x4d42*.

## What's the difference between `bfSize` and `biSize`?

*biSize* is a number of bytes of BITMAPINFOHEADER.

*bfSize* is a size in bytes of bitmap file.

## What does it mean if `biHeight` is negative?

It's the height of the bitmap, in pixels.

This height can be negative or positive.
If *biHeight* is positive - the bitmap is a bottom-up DIB and its origin is the lower-left corner;
if negative - the bitmap is a top-down DIB and its origin is the upper-left corner.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

The BMP's color depth specifies *biClrUsed*.

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

If the file cannot be opened then this function returns NULL.

## Why is the third argument to `fread` always `1` in our code?

Read 1 element that has specified size in bytes.

## What value does line 65 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

It assigns the value 3.

## What does `fseek` do?

This function sets the file position indicator for the stream pointed to by stream.

## What is `SEEK_CUR`?

It's a constant that indicates current position of the file pointer.

## Whodunit?

> It was Professor Plum with the candlestick in the library.