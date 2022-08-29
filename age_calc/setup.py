#!/usr/bin/python3.9

from distutils.core import Extension, setup

module = Extension("fibonacci", sources=["cfib.c"])

setup(
    name="fibonacci",
    version="0.01",
    description="Example module to calculate the nth fibonacci number",
    ext_modules=[module]
)
