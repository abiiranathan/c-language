# pdfsearch

## Dependencies

```bash
 sudo apt-get install build-essential cmake pkg-config\
 libpoppler-glib-dev glib2.0 glib2.0-dev libfontconfig1-dev \
 libfreetype6-dev libjpeg-dev libpng-dev libtiff-dev \
 libopenjp2-7-dev libcurl4-gnutls-dev libgtest-dev libboost-dev
```

Compile:

```bash
make
```

Run:

```bash
./pdfsearch "haystack.pdf" "niddle" 25


# binary "path_to_pdf" "search_regex_pattern" context_size(default: 50)
```

Prints the match with context of 100. (ie 50 characters before and after the match).

### Vcode Setup

c_cpp_properties.json

```json
{
  "configurations": [
    {
      "name": "Linux",
      "includePath": [
        "${workspaceFolder}/**",
        "/usr/include/python3.10",
        "/usr/include/glib-2.0", // glib-object.h, glib.h, gobject
        "/usr/lib/x86_64-linux-gnu/glib-2.0/include", // glibconfig.h
        "/usr/include/cairo/" //cairo.h
      ],
      "defines": [],
      "compilerPath": "/usr/bin/clang",
      "cStandard": "c17",
      "intelliSenseMode": "linux-gcc-x64"
    }
  ],
  "version": 4
}
```

### TODO:

- Modularize the application and allow for extensibility
- Pass command-line flags
- Return a data structure of matches from each thread and aggregate into a pdf of results
- Allow user to customize number of threads
